#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin>>n;
    int p[n];
    for(int i=0; i<n; i++) cin>>p[i];
    sort(p, p+n);
    int q; cin>>q;
    while(q--) {
        int m; cin>>m;
        cout<<upper_bound(p, p+n, m)-p<<'\n';
    }
    return 0;
}