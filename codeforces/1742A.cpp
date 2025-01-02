#include <iostream>
using namespace std;
void solve() {
    short a, b, c;
    cin >> a >> b >> c;
    short larg = max(max(a, b), c);
    short sum = (a+b+c)-larg;
    if (sum==larg) cout << "YES\n";
    else cout << "NO\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    short T;
    cin >> T;
    while (T--) solve();
    return 0;
}