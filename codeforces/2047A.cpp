#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("fast-math")
typedef long long ll;
using namespace std;
inline void solve() {
    int n; cin>>n;
    vector<int> p(n);
    for (int i=0; i<n; ++i) cin>>p[i];
    int days = 0, total = 0, curr = 1, req = 1;
    for (int i=0; i<n; ++i) {
        total+=p[i];
        bool happy = false;
        while (total>=req) {
            total-=req; curr++; req = 8*(curr-1); happy = true;
            if (total>0&&total<req) happy = false;
        }
        if (happy) days++;
    }
    cout<<days<<'\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int t; cin>>t;
    while (t--) solve();
    return 0;
}