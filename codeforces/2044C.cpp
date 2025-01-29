#include <bits/stdc++.h>
using namespace std;
inline void solve() {
    int m, a, b, c;
    cin>>m>>a>>b>>c;
    cout<<min(m, a+c)+min(m, b+c-max(0, min(m, a+c)-a))<<'\n';
}
signed main() {
    cin.tie(0)->sync_with_stdio(0);
    short t; cin>>t;
    while(t--) solve();
    return 0;
}