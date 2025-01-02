#include <iostream>
#include <algorithm>
#include <string>
typedef long long ll;
using namespace std;
void solve() {
    string s;
    cin >> s;
    if (s.substr(0,s.length()/2)==s.substr(s.length()/2,s.length())) cout << "YES\n";
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