#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
signed main() {
    int n; cin>>n;
    int coins[n];
    for (int i=0; i<n; i++) cin>>coins[i];
    sort(coins, coins+n);
    int sum = 0, c = 0;
    for (int i=0; i<n; i++) sum+=coins[i];
    int ms = 0;
    for (int i=n-1; i>=0; i--) {
        ms+=coins[i];
        c++;
        if (ms>sum-ms) break;
    }
    cout<<c<<'\n';
    return 0;
}