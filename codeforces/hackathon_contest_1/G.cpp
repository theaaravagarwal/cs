#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")
#pragma GCC optimize("unroll-loops")
typedef long long ll;
using namespace std;
inline void solve() {
    int n; cin>>n;
    if (n<=3) {
        cout<<"-1\n";
        return;
    }
    vector<int> ans;
    for (int i=1; i<=(n+1)/2; i++) ans.push_back(i*2-1);
    reverse(ans.begin(), ans.end());
    for (int i=1; i<=n/2; i++) ans.push_back(i*2);
    for (int i=0; i<ans.size()-1; i++) if (ans[i]==2&&ans[i+1]==4) swap(ans[i], ans[i+1]);
    for (int i=0; i<n; i++) cout<<ans[i]<<(i==n-1?'\n':' ');
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    short t; cin>>t;
    while (t--) solve();
    return 0;
}