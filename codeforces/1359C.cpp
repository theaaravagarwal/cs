#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
typedef long double ld;
using namespace std;
inline void solve() {
    ll h, c, t; cin>>h>>c>>t;
    if (h+c>=(t*2)) {cout<<"2\n"; return;}
    ll l = 0, r = 1e9;
    while(r-l>1) {
        ll m = (l+r)/2;
        ld hot = h*1.0;
        ld cold = c*1.0;
        ld target = t*1.0;
        ld x = (hot+hot*m+cold*m)/(m*2+1);
        if (x>target) l = m;
        else r = m;
    }
    pair<ll, ll> one = make_pair(abs(t*(l*2+1)-(h+h*l+c*l)), l*2+1);
    pair<ll, ll> two = make_pair(abs(t*(r*2+1)-(h+h*r+c*r)), r*2+1);
    ll y = one.first*two.second-one.second*two.first;
    cout<<(y>0?r*2+1:l*2+1)<<'\n';
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t; cin>>t;
    while (t--) solve();
    return 0;
}