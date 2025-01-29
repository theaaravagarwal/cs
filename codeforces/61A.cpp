#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;
signed main() {
    string a, b, res; cin>>a>>b;
    for (size_t i=0; i<a.size(); i++) res+=(a[i]!=b[i])?'1':'0';
    cout<<res;
    return 0;
}