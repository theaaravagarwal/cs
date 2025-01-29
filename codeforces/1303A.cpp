#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
inline void solve() {
    string s; cin>>s;
    int l = s.find('1'), r = s.rfind('1');
    if (l==string::npos) {
        cout<<0<<'\n';
        return;
    }
    int c = 0;
    for (int i=l; i<=r; ++i) if (s[i]=='0') c++;
    cout<<c<<'\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    short t;
    cin>>t;
    while(t--) solve();
    return 0;
}