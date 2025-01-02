#include <iostream>
#include <string>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    int count[4] = {0};
    for (char c : s) if (c != '+') count[c - '0']++;
    string res;
    for (int i = 1; i <= 3; ++i) {
        for (int j = 0; j < count[i]; ++j) {
            if (!res.empty()) res += "+";
            res += to_string(i);
        }
    }
    cout << res << "\n";
    return 0;
}