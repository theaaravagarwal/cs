#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
inline void solve() {
    int n, k;
    cin>>n>>k;
    vector<int> a(n), b(n);
    for (int i=0; i<n; i++) cin>>a[i];
    for (int i=0; i<n; i++) cin>>b[i];
    sort(a.begin(), a.end());
    sort(b.rbegin(), b.rend());
    for (int i=0; i<k; i++) {
        if (a[i]<b[i]) swap(a[i], b[i]);
        else break;
    }
    cout<<accumulate(a.begin(), a.end(), 0)<<'\n';
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    short t; cin>>t;
    while(t--) solve();
    return 0;
}