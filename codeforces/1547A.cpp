#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
inline void solve() {
    int xA, yA, xB, yB, xF, yF;
    cin>>xA>>yA>>xB>>yB>>xF>>yF;
    int d = abs(xA-xB)+abs(yA-yB);
    if ((xA==xB&&xA==xF&&((yF>min(yA, yB))&&(yF<max(yA, yB))))||(yA==yB&&yA==yF&&((xF>min(xA, xB))&&(xF<max(xA, xB))))) d+=2;
    cout<<d<<'\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    short t; cin>>t;
    while (t--) solve();
    return 0;
}