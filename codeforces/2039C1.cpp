#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
void solve() {
    int x; ll m; cin>>x>>m;
    int c = 0;
    for (int y=1; y<=min(2LL*x, m); y++) if (x!=y&&((x%(x^y))==0||(y%(x^y)==0))) c++;
    cout<<c<<'\n';
}
int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t; cin>>t;
    while (t--) solve();
    return 0;
}