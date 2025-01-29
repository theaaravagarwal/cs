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
    int k, l, m, n, d; cin>>k>>l>>m>>n>>d;
    int c = 0;
    for(int i=1; i<=d; i++) if(i%k==0||i%l==0||i%m==0||i%n==0) c++;
    cout<<c;
    return 0;
}