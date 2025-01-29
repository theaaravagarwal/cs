#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
inline ll factorial(int n) {
    if (n==0||n==1) return 1;
    ll res = 1;
    for (int i=2; i<=n; i+=4) {
        res*=i;
        if (i+1<=n) res*=(i+1);
        if (i+2<=n) res*=(i+2);
        if (i+3<=n) res*=(i+3);
    }
    return res;
}
signed main() {
    int a, b; cin>>a>>b;
    int n = min(a, b);
    cout<<factorial(n)<<'\n';
    return 0;
}