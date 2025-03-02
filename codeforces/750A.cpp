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
    int n, k; cin>>n>>k;
    int time = 240-k;
    int c = 0;
    for(int i=1; i<=n; i++) {
        if(time-5*i>=0) time-=5*i, c++;
        else break;
    }
    cout<<c<<"\n";
}