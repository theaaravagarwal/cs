#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    string s; cin>>s;
    for (char c:s) {
        if (c=='H'||c=='Q'||c=='9') {
            cout<<"YES";
            return 0;
        }
    }
    cout<<"NO";
    return 0;
}