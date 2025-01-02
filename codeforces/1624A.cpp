#include <iostream>
#include <limits>
using namespace std;
void solve() {
    int n;
    cin >> n;
    int min_val = numeric_limits<int>::max(), max_val = numeric_limits<int>::min();
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x<min_val) min_val = x;
        if (x>max_val) max_val = x;
    }
    cout << max_val-min_val << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}