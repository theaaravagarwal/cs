#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, s, c[5]= {0};
    cin>>n;
    while (n--) cin>>s, c[s]++;
    int t = c[4]+c[3]+c[2]/2;
    c[1]-=c[3];
    if (c[2]%2==1) c[1]-=2, t++;
    if (c[1]>0) t+=(c[1]+3)/4;
    cout<<t;
    return 0;
}