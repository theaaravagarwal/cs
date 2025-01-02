#include <bits/stdc++.h>

void generateRandomNumbers() {
    random_device rd; // Obtain a random number from hardware
    mt19937 eng(rd()); // Seed the generator
    uniform_int_distribution<> distr(1, 100); // Define the range
    for (int i = 0; i < 10; ++i) {
        int random_number = distr(eng); // Generate random number
        cout << random_number << " "; // Output the random number
    }
}

int main() {
    generateRandomNumbers();
    return 0;
}
