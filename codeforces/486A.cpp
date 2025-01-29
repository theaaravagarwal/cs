#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
signed main() {
    ll n; cin>>n;
    if (n%2==0) cout<<n/2;
    else cout<<-(n+1)/2;
    return 0;
}