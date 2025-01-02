#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>

using namespace std;

using Pair = pair<char, string>;

bool solve(int n) {
    string numStr = to_string(n);
    unordered_map<char, string> keys;
    keys.insert(Pair('1', "1234567890"));
    keys.insert(Pair('2', "2356890"));
    keys.insert(Pair('3', "369"));
    keys.insert(Pair('4', "4567890"));
    keys.insert(Pair('5', "56890"));
    keys.insert(Pair('6', "69"));
    keys.insert(Pair('7', "7890"));
    keys.insert(Pair('8', "890"));
    keys.insert(Pair('9', "9"));
    keys.insert(Pair('0', "0"));
    for (size_t i = 0; i < numStr.length() - 1; i++) {
        char current = numStr[i];
        char next = numStr[i + 1];
        if (keys[current].find(next) == string::npos) return false;
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    string res;

    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        int offset = 0;

        auto start = chrono::high_resolution_clock::now();

        while (!solve(m + offset) && !solve(m - offset)) offset++;
        int answer = (solve(m + offset)) ? (m + offset) : (m - offset);
        res += to_string(answer) + "\n";

        auto end = chrono::high_resolution_clock::now();
        auto duration_ns = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        double duration_ms = duration_ns / 1e6;

        cout << answer << " (" << duration_ms << " ms)" << endl;
    }

    return 0;
}