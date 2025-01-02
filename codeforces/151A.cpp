#include <iostream>
#include <algorithm>
using namespace std;
void solve() {
    short n, k, l, c, d, p, nl, np;
    cin >> n >> k >> l >> c >> d >> p >> nl >> np;
    int x = (k*l)/nl;
    int y = c*d;
    int z = p/np;
    short t = min(min(x, y), z);
    cout << t/n << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}