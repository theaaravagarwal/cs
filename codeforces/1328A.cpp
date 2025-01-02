#include <iostream>
#define ll long long
using namespace std;
void solve() {
    ll a, b;
    cin >> a >> b;
    ll res = (b-a)%(b);
    if (res<0) res+=b;
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