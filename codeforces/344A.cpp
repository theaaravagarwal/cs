#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;
signed main() {
    int n; cin>>n;
    string prev, curr; cin>>prev;
    int g = 1;
    for (int i=1; i<n; i++) {
        cin>>curr;
        if (curr!=prev) g++;
        prev = curr;
    }
    cout<<g;
    return 0;
}