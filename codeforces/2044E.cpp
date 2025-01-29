#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
inline void solve() {
    ll k, l1, r1, l2, r2;
    cin>>k>>l1>>r1>>l2>>r2;
    ll kn = 1, c = 0;
    for (int n=0; r2/kn>=l1; n++) {
        c+=max(0ll, min(r2/kn, r1)-max((l2-1)/kn+1, l1)+1ll);
        kn*=k;
    }
    cout<<c<<'\n';
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    short t; cin>>t;
    while (t--) solve();
    return 0;
}