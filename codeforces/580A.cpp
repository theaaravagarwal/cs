#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("avx,avx2,fma")
using namespace std;
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n; cin>>n;
    int a[n];
    for (int i=0; i<n; i++) cin>>a[i];
    int curr = 1;
    int ans = 1;
    for (int i=1; i<n; i++) {
        if (a[i]>=a[i-1]) {
            curr++;
            ans = max(ans, curr);
        } else curr = 1;
    }
    cout<<ans;
}