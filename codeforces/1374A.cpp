#include <iostream>
#include <algorithm>
#include <cmath>
#define ll long long
using namespace std;
void solve() {
    int x, y, n;
    cin >> x >> y >> n;
    cout << (((n-y)/x)*x+y) << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}