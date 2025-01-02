import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

public class StringStats {
    // Function to compute the mean string based on ASCII values of characters
    public static String findMeanString(String[] array) {
        if (array.length == 0) return "";

        int maxLength = Arrays.stream(array).mapToInt(String::length).max().orElse(0);
        int[] asciiSum = new int[maxLength];
        int[] count = new int[maxLength];

        // Sum ASCII values for each position in the strings
        for (String str : array) {
            for (int i = 0; i < str.length(); i++) {
                asciiSum[i] += (int) str.charAt(i);
                count[i]++;
            }
        }

        // Compute the mean ASCII values and construct the result string
        StringBuilder meanString = new StringBuilder();
        for (int i = 0; i < maxLength; i++) {
            if (count[i] > 0) {
                char averageChar = (char) (asciiSum[i] / count[i]);
                meanString.append(averageChar);
            }
        }

        return meanString.toString();
    }

    // Function to find the median of an array of strings
    public static String findMedian(String[] array) {
        Arrays.sort(array);
        int n = array.length;
        if (n % 2 != 0) {
            return array[n / 2];
        } else {
            return array[(n / 2) - 1] + " and " + array[n / 2];
        }
    }

    // Function to find the mode of an array of strings
    public static String findMode(String[] array) {
        HashMap<String, Integer> frequencyMap = new HashMap<>();

        // Count frequencies of each string
        for (String str : array) {
            frequencyMap.put(str, frequencyMap.getOrDefault(str, 0) + 1);
        }

        int maxCount = 0;
        String mode = null;
        boolean multipleModes = false;

        // Find the string with the highest frequency
        for (Map.Entry<String, Integer> entry : frequencyMap.entrySet()) {
            if (entry.getValue() > maxCount) {
                maxCount = entry.getValue();
                mode = entry.getKey();
                multipleModes = false;
            } else if (entry.getValue() == maxCount) {
                multipleModes = true;
            }
        }

        // Handle the case of multiple modes
        if (multipleModes) {
            return "No unique mode";
        } else {
            return mode;
        }
    }

    public static void main(String[] args) {
        String[] array = {"apple", "banana", "apple", "orange", "banana", "apple", "monkey", "potato", "ameer", "kanishk", "banana", "balls", "apple"};

        // Calculate and print the mean string
        String meanString = findMeanString(array);
        System.out.println("Mean String: " + meanString);

        // Find and print the median
        String median = findMedian(array);
        System.out.println("Median: " + median);

        // Find and print the mode
        String mode = findMode(array);
        System.out.println("Mode: " + mode);
    }
}