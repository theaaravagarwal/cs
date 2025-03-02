#include<bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;
int a[3];
signed main() {
    cin>>a[0]>>a[1]>>a[2];
    sort(a, a+3);
    cout<<a[2]-a[0];
}