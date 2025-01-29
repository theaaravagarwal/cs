#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;
signed main() {
    int n, h; cin>>n>>h;
    vector<int> heights(n);  
    for(int i=0; i<n; ++i) cin>>heights[i];
    int total = 0;
    for(int i=0; i<n; ++i) {
        if(heights[i]>h) total+=2;
        else total++;
    }
    cout<<total;
    return 0;
}