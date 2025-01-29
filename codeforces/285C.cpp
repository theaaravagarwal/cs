#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n; cin>>n;
    vector<int> a(n);
    for (int i=0; i<n; i++) cin>>a[i];
    sort(a.begin(), a.end());
    ll c = 0;
    for (int i=0; i<n; i++) c+=abs(a[i]-(i+1));
    cout<<c;
    return 0;
}