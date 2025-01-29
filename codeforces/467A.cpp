#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n; cin>>n;
    int c = 0;
    for (int i=0; i<n; i++) {
        int p, q; cin>>p>>q;q
        if (q-p>=2) c++;
    }
    cout<<c;  
    return 0;
}