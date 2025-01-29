#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        int mx(0), c(0);
        for(int p=1; p<=n; p++){
            int x; cin>>x;
            mx = max(mx, x);
            c+=(mx==p);
        }
        cout<<c<<'\n';
    }
    return 0;
}