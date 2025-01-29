#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
void solve() {
    int T;
    cin >> T;
    while (T--) {
        string s;
        cin>>s;
        string n = "abc";
        int c = 0;
        for (int i=0; i<3; ++i) if (s[i]!=n[i]) c++;
        if (c==0||c==2) cout << "YES\n";
        else cout << "NO\n";
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve();
    return 0;
}