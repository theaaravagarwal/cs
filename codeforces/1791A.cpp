#include <iostream>
#include <algorithm>
#include <string>
#define ll long long
using namespace std;
void solve() {
    char a;
    string str = "codeforces";
    cin >> a;
    if (str.find(a)!=string::npos) cout << "YES\n";
    else cout << "NO\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}