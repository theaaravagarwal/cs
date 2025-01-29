#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;
inline bool solve(const string &s) {  
    string t = "hello";
    short j = 0;
    for (char c:s) {
        if (c==t[j]) j++;
        if (j==t.length()) return true;
    }
    return false;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    string s; cin>>s;
    cout<<(solve(s)?"YES":"NO");
    return 0;
}