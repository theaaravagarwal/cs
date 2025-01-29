#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
inline void solve() {
    ll n, a, b, c;
    cin>>n>>a>>b>>c;
    ll dist = a+b+c;
    ll cy = n/dist;
    ll d = cy*3;
    ll rem = n%dist;
    if (rem>0) {
        if (rem<=a) d++;
        else if (rem<=a+b) d+=2;
        else d+=3;
    }
    cout<<d<<'\n';
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    short t; cin>>t;
    while (t--) solve();
    return 0;
}