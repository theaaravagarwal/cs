#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> computeZ(const string &S) {
    int n = S.size();
    vector<int> Z(n, 0);
    Z[0] = n; // The full string matches itself
    
    int l = 0, r = 0; // Window of the current Z-box
    for (int i = 1; i < n; ++i) {
        if (i <= r) {
            Z[i] = min(r - i + 1, Z[i - l]); // Use previously computed Z-values
        }
        while (i + Z[i] < n && S[Z[i]] == S[i + Z[i]]) {
            ++Z[i]; // Extend the match
        }
        if (i + Z[i] - 1 > r) {
            l = i;
            r = i + Z[i] - 1; // Update Z-box
        }
    }
    return Z;
}

int main() {
    string S;
    cin >> S;
    vector<int> Z = computeZ(S);

    for (int val : Z) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}