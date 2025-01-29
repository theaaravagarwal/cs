#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin>>n;
    int b = 0;
    b+=n/100; n%=100;
    b+=n/20; n%=20;
    b+=n/10; n%=10;
    b+=n/5; n%=5;
    b+=n;
    cout<<b;
    return 0;
}