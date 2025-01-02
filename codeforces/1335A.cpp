#include <iostream>
#include <algorithm>
#include <string>
typedef long long ll;
using namespace std;
void solve() {
    int n;
    cin >> n;
    int res = (n-1)>>1;
    cout << res << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}