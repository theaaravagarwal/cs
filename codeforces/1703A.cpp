#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
inline void solve() {
    string s; cin>>s;
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    cout<<(s=="YES")?"YES\n":"NO\n";
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    short t; cin>>t;
    while(t--) solve();
    return 0;
}