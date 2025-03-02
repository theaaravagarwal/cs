#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int s, n; cin>>s>>n;
    vector<pair<int,int>> d;
    for(int i=0; i<n; i++) {
        int x, y; cin>>x>>y;
        d.emplace_back(x, y);
    }
    sort(d.begin(), d.end());
    for(const auto& [x, y]:d) {
        if(s<=x) cout<<"NO", exit(0);
        s+=y;
    }
    cout<<"YES";
    return 0;
}