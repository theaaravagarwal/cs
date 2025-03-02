#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
inline void solve() {
    int n, m; cin>>n>>m;
    vector<int> a(n);
    for (int i=0; i<n; i++) cin>>a[i];
    int b; cin>>b;
    vector<vector<bool>> dp(n, vector<bool>(2, false));
    vector<vector<ll>> prev(n, vector<ll>(2, -1));
    dp[0][0] = true;
    dp[0][1] = true;
    for(int i=1; i<n; i++) {
        ll orig = a[i];
        ll oper = b-a[i];
        if(orig>=a[i-1]&&dp[i-1][0]) dp[i][0] = true;
        if(orig>=(b-a[i-1])&&dp[i-1][1]) dp[i][0] = true;
        if(oper>=a[i-1]&&dp[i-1][0]) dp[i][1] = true;
        if(oper>=(b-a[i-1])&&dp[i-1][1]) dp[i][1] = true;
    }
    if (dp[n-1][0]||dp[n-1][1]) cout<<"YES\n";
    else cout<<"NO\n";
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin>>t;
    while (t--) solve();
    return 0;
}