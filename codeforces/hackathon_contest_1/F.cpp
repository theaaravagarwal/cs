#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")
#pragma GCC optimize("unroll-loops")
typedef long long ll;
using namespace std;
inline void solve() {
    int n0, n1, n2; cin>>n0>>n1>>n2;
    if (n1==0) {
        string s = "";
        if (n0) s = string(n0+1, '0');
        if (n2) s+=string(n2+1, '1');
        cout<<s<<'\n';
        return;
    }
    string s = "";
    for (int i=0; i<=n1; i++) s+=(i&1)?'0':'1';
    if (n0) {
        int first_zero_idx = s.find("0");
        s.insert(first_zero_idx, n0, '0');
    }
    if (n2) {
        int first_one_idx = s.find("1");
        s.insert(first_one_idx, n2, '1');
    }
    cout<<s<<'\n';
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    short t; cin>>t;
    while (t--) solve();
    return 0;
}