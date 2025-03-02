#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin>>n;
    vector<int> a(n);
    for (int i=0; i<n; i++) cin>>a[i];
    vector<ll> c(100001, 0);
    for(int x:a) c[x]++;
    vector<ll> dp(100001, 0);
    dp[1] = c[1];
    for(int i=2; i<=100000; i++) dp[i] = max(dp[i-1], dp[i-2]+i*c[i]);
    cout<<dp[100000];
}