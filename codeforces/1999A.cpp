#include <iostream>
#include <algorithm>
#include <cmath>
#define ll long long
using namespace std;
void solve() {
    short n;
    cin >> n;
    short res = (n%10)+(n/10);
    cout << res << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}