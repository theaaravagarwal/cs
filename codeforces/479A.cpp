#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    short a, b, c; cin>>a>>b>>c;
    cout<<max(a+b+c, max(a*b*c, max(a*(b+c), (a+b)*c)));
    return 0;
}