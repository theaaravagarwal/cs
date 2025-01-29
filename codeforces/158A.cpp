#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    short n, k; cin>>n>>k;
    short a[n];
    for (short i=0; i<n; i++) cin>>a[i];
    short c=0;
    for (short i=0; i<n; i++) if (a[i]>=a[k-1]&&a[i]>0) c++;
    cout<<c<<'\n';
    return 0;
}