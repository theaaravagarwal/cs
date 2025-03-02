#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")
#pragma GCC optimize("unroll-loops")
typedef long long ll;
using namespace std;
inline void solve() {
    short n; cin>>n;
    vector<short> a(n);
    for (int i=0; i<n; i++) cin>>a[i];
    int c = 0, l = 0, r = n-1;
    ll al = 0, b = 0, prev = 0;
    al+=a[l++];
    prev = a[0];
    c++;
    while (l<=r) {
        c++;
        ll curr = 0;
        while (r>=l&&curr<=prev) {
            curr+=a[r];
            b+=a[r];
            r--;
        }
        if (l>r) break;
        prev = curr;
        c++;
        curr = 0;
        while (l <= r && curr<=prev) {
            curr+=a[l];
            al+=a[l];
            l++;
        }
        prev = curr;
    }
    cout<<c<<" "<<al<<" "<<b<<'\n';
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    short t; cin>>t;
    while (t--) solve();
    return 0;
}