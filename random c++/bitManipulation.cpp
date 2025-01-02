#include <bits/stdc++.h>

int main() {
    int a = 5;  // Binary: 0101
    int b = 3;  // Binary: 0011

    // Bitwise AND
    int andResult = a & b; // 0101 & 0011 = 0001 (1 in decimal)
    cout << "Bitwise AND (5 & 3): " << andResult << endl;

    // Bitwise OR
    int orResult = a | b; // 0101 | 0011 = 0111 (7 in decimal)
    cout << "Bitwise OR (5 | 3): " << orResult << endl;

    // Bitwise XOR
    int xorResult = a ^ b; // 0101 ^ 0011 = 0110 (6 in decimal)
    cout << "Bitwise XOR (5 ^ 3): " << xorResult << endl;

    // Bitwise NOT
    int notResult = ~a; // ~0101 = 1010 (in 32-bit signed, this is -6)
    cout << "Bitwise NOT (~5): " << notResult << endl;

    // Left Shift
    int leftShiftResult = a << 1; // 0101 << 1 = 1010 (10 in decimal)
    cout << "Left Shift (5 << 1): " << leftShiftResult << endl;

    // Right Shift
    int rightShiftResult = a >> 1; // 0101 >> 1 = 0010 (2 in decimal)
    cout << "Right Shift (5 >> 1): " << rightShiftResult << endl;

    return 0;
}