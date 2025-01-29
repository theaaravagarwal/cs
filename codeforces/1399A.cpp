#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
inline void solve() {
    short n; cin>>n;
    vector<short> a(n);
    for (short i=0; i<n; i++) cin>>a[i];
    sort(a.begin(), a.end());
    for (short i=1; i<n; i++) {
        if (a[i]-a[i-1]>1) {
            cout<<"NO\n";
            return;
        }
    }
    cout<<"YES\n";
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    short t; cin>>t;
    while(t--) solve();
    return 0;
}