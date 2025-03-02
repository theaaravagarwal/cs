#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")
#pragma GCC optimize("unroll-loops")
typedef long long ll;
using namespace std;
inline void solve() {
    int n; cin>>n;
    vector<int> a(n);
    for (int i=0; i<n; i++) cin>>a[i];
    vector<ll> pref(n+1, 0);
    for(int i=0; i<n; i++) pref[i+1] = pref[i]+a[i];
    vector<bool> uni(n+1, false);
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            ll sum = pref[j+1]-pref[i];
            if(sum>n) break;
            uni[sum] = true;
        }
    }
    int c = 0;
    for(int i=0; i<n; i++) if(a[i]<=n&&uni[a[i]]) c++;
    cout<<c<<'\n';
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    short t; cin>>t;
    while (t--) solve();
    return 0;
}