#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
signed main() {
    string t, s;
    cin>>t>>s;
    reverse(s.begin(), s.end());
    if (t==s) cout<<"YES";
    else cout<<"NO";
    return 0;
}