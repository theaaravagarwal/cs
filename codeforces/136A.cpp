#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
signed main() {
    short n; cin>>n;
    vector<short> a(n);
    for (short i=0;i<n;i++) cin>>a[i];
    vector<short> result(n);
    for (short i=0; i<n; i++) {
        for (short j=0; j<n; j++) {
            if (a[j]==i+1) {
                result[i] = j+1;
                break;
            }
        }
    }
    for (short i=0;i<n;i++) cout<<result[i]<<" ";
}