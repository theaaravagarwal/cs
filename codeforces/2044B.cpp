#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
inline void solve() {
    string s;
    cin>>s;
    reverse(s.begin(), s.end());
    for (int i=0; i<s.length(); i++) {
        if (s[i]=='p') s[i]='q';
        else if (s[i]=='q') s[i]='p';
    }
    cout<<s<<'\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    short t; cin>>t;
    while(t--) solve();
    return 0;
}