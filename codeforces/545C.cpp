#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin>>n;
    vector<pair<int, int>> a(n+1);
    for (int i=0; i<n; i++) cin>>a[i].first>>a[i].second;
    a[n] = {-1, 0};
    int ans = 1;
    ll last = a[0].first;
    for (int i=1; i<n; i++) {
        ll x = a[i].first, h = a[i].second;
        if (x-h>last) last = x, ans++;
        else if (x+h<a[i+1].first||a[i+1].first==-1) last = x+h, ans++;
        else last = x;
    }
    cout<<ans;
    return 0;
}