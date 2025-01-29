#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;
signed main() {
    int n, a;
    cin>>n>>a;
    int mina(a), maxa(a), mini(0), maxi(0);
    for (int i=1; i<n; ++i) {
        cin>>a;
        if (a>maxa) {
            maxa = a;
            maxi = i;
        }
        if (a<=mina) {
            mina = a;
            mini = i;
        }
    }
    cout<<maxi+(n-1-mini)-(mini<maxi?1:0);
    return 0;
}