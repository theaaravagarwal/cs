#include <iostream>
#include <string>
using namespace std;
void solve() {
    short n;
    string s;
    cin >> n >> s;
    int c = 0;
    for (int i=1; i<n; ++i) if (s[i]==s[i-1]) ++c;
    cout << c << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}