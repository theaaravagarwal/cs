#include <bits/stdc++.h>
using namespace std;
inline void solve() {
    short n;
    cin>>n;
    cout<<(n<=1399?"Division 4":n<=1599?"Division 3":n<=1899?"Division 2":"Division 1")<<'\n';
}
signed main() {
    short t;
    cin>>t;
    while (t--) solve();
    return 0;
}