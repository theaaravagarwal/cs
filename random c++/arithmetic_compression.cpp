#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <cstdint>
#include <cmath>
#include <iterator>
#include <stdexcept>

struct Range {
    double low;
    double high;
};

class ArithmeticCoder {
private:
    std::map<uint8_t, double> frequencies;
    std::map<uint8_t, Range> ranges;
    double totalFrequency;

    void calculateRanges() {
        double cumulative = 0.0;
        for (const auto& [byte, freq] : frequencies) {
            ranges[byte] = {cumulative, cumulative + freq / totalFrequency};
            cumulative += freq / totalFrequency;
        }
    }

public:
    ArithmeticCoder(const std::vector<uint8_t>& input) : totalFrequency(0.0) {
        // Calculate byte frequencies
        for (uint8_t byte : input) {
            frequencies[byte]++;
            totalFrequency++;
        }
        calculateRanges();
    }

    std::vector<bool> compress(const std::vector<uint8_t>& input) {
        double low = 0.0, high = 1.0;

        for (uint8_t byte : input) {
            const Range& range = ranges[byte];
            double rangeWidth = high - low;
            high = low + rangeWidth * range.high;
            low = low + rangeWidth * range.low;
        }

        // Convert final range to binary
        double value = (low + high) / 2.0;
        std::vector<bool> bitstream;

        // Generate the bitstream
        for (int i = 0; i < 64; ++i) { // Limit to 64 bits
            value *= 2;
            if (value >= 1) {
                bitstream.push_back(1);
                value -= 1;
            } else {
                bitstream.push_back(0);
            }
        }

        return bitstream;
    }

    void writeBitstreamToFile(const std::string& outputFilePath, const std::vector<bool>& bitstream, size_t originalSize) {
        std::ofstream outputFile(outputFilePath, std::ios::binary);
        if (!outputFile) {
            throw std::runtime_error("Error opening output file for writing.");
        }

        // Write the original size as a fixed-size binary value
        outputFile.write(reinterpret_cast<const char*>(&originalSize), sizeof(originalSize));

        // Write the bitstream to the file
        uint8_t byte = 0;
        int bitCount = 0;

        for (bool bit : bitstream) {
            byte = (byte << 1) | bit; // Add bit to byte
            bitCount++;
            if (bitCount == 8) { // Write byte when it's full
                outputFile.put(byte);
                byte = 0;
                bitCount = 0;
            }
        }

        // Write any remaining bits
        if (bitCount > 0) {
            byte <<= (8 - bitCount); // Pad remaining bits
            outputFile.put(byte);
        }

        outputFile.close();
    }

    std::vector<bool> readBitstreamFromFile(const std::string& inputFilePath) {
        std::ifstream inputFile(inputFilePath, std::ios::binary);
        if (!inputFile) {
            throw std::runtime_error("Error opening input file for reading.");
        }

        size_t originalSize; // Variable to hold original size
        inputFile.read(reinterpret_cast<char*>(&originalSize), sizeof(originalSize)); // Read original size

        std::vector<bool> bitstream;
        char byte;
        while (inputFile.get(byte)) {
            for (int i = 7; i >= 0; --i) {
                bitstream.push_back((byte >> i) & 1);
            }
        }
        inputFile.close();

        // Debugging output
        std::cout << "Original size read: " << originalSize << std::endl;
        std::cout << "Bitstream size: " << bitstream.size() << std::endl;

        return bitstream;
    }

    std::vector<uint8_t> decompress(const std::vector<bool>& bitstream, size_t outputLength) {
        double value = 0.0;

        // Convert bitstream to floating-point range
        for (size_t i = 0; i < bitstream.size(); ++i) {
            value += bitstream[i] * std::pow(2, -(i + 1));
        }

        std::vector<uint8_t> output;

        for (size_t i = 0; i < outputLength; ++i) {
            for (const auto& [byte, range] : ranges) {
                if (value >= range.low && value < range.high) {
                    output.push_back(byte);
                    double rangeWidth = range.high - range.low;
                    value = (value - range.low) / rangeWidth;
                    break;
                }
            }
        }

        return output;
    }

    void compressFile(const std::string& inputFilePath, const std::string& outputFilePath) {
        std::ifstream inputFile(inputFilePath, std::ios::binary);
        if (!inputFile) {
            throw std::runtime_error("Error opening input file for reading.");
        }

        // Read the entire file into a vector
        std::vector<uint8_t> inputData((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
        inputFile.close();

        // Compress the input data
        std::vector<bool> bitstream = compress(inputData);
        size_t originalSize = inputData.size(); // Store original input size

        // Write the compressed data to the output file
        writeBitstreamToFile(outputFilePath, bitstream, originalSize);
    }

    std::vector<uint8_t> decompressFile(const std::string& inputFilePath) {
        // Read the bitstream from the file
        std::vector<bool> bitstream = readBitstreamFromFile(inputFilePath);
        
        // Ensure the bitstream is large enough to read the original size
        if (bitstream.size() < sizeof(size_t) * 8) {
            throw std::runtime_error("Bitstream does not contain enough data to read the original size.");
        }

        // Get the original size from the first bits of the bitstream
        size_t originalSize = 0;
        for (size_t i = 0; i < sizeof(originalSize) * 8; ++i) {
            originalSize = (originalSize << 1) | bitstream[i]; // Construct the size from the first bits
        }

        // Ensure we have enough bits to decompress
        if (originalSize > (bitstream.size() - sizeof(size_t) * 8) / 8) {
            throw std::runtime_error("Bitstream does not contain enough data for the specified original size.");
        }

        return decompress(bitstream, originalSize); // Use original size for decompression
    }
};

int main(int argc, char* argv[]) {
    if (argc != 3) { // Expecting 2 arguments: input file and output file
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file.acomp>" << std::endl;
        return 1; // Exit with error code
    }

    std::string inputFilePath = argv[1]; // First argument is the input file path
    std::string outputFilePath = argv[2]; // Second argument is the output file path

    try {
        // Example usage for compressing a file
        ArithmeticCoder coder({}); // Initialize with an empty vector
        coder.compressFile(inputFilePath, outputFilePath); // Compress specified input file

        // Example usage for decompressing a file
        std::vector<uint8_t> decompressedData = coder.decompressFile(outputFilePath);
        std::ofstream outputFile("decompressed_output.bin", std::ios::binary);
        outputFile.write(reinterpret_cast<const char*>(decompressedData.data()), decompressedData.size());
        outputFile.close();

        // Check if decompressed data matches original input
        std::ifstream inputFile(inputFilePath, std::ios::binary);
        std::vector<uint8_t> originalData((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
        inputFile.close();

        if (decompressedData.size() == originalData.size() && std::equal(decompressedData.begin(), decompressedData.end(), originalData.begin())) {
            std::cout << "Decompression successful! Output matches the original input." << std::endl;
        } else {
            std::cout << "Decompression failed! Output does not match the original input." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1; // Exit with error code
    }

    return 0;
}
