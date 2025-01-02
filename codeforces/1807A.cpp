#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
void solve() {
    short a, b, c;
    cin >> a >> b >> c;
    if ((a+b)==c) cout << "+\n";
    else cout << "-\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    short T;
    cin >> T;
    while (T--) solve();
    return 0;
}