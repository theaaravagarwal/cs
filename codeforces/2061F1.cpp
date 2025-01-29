#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
inline int solve(string s, string t) {
    int n = s.length();
    if (s==t) return 0;
    int ones_s = 0, ones_t = 0;
    for (int i=0; i<n; i++) {
        ones_s+=(s[i] == '1');
        ones_t+=(t[i] == '1');
    }
    if (ones_s!=ones_t) return -1;
    string sorted_t = t;
    for (int i=0; i<n-1; i++) for (int j=0; j<n-1-i; j++) if (sorted_t[j]>sorted_t[j+1]) swap(sorted_t[j], sorted_t[j+1]);
    string sorted_s = s;
    for (int i=0; i<n-1; i++) for (int j=0; j<n-1-i; j++) if (sorted_s[j]>sorted_s[j+1]) swap(sorted_s[j], sorted_s[j+1]);
    if (sorted_s!=sorted_t) return -1;
    int diff = 0;
    for (int i=0; i<n; i++) if (s[i]!=t[i]) diff++;
    return (diff + 1) / 2;
}
signed main() {
    int tc; cin>>tc;
    while (tc--) {
        string s, t; cin>>s>>t;
        cout<<solve(s, t)<<'\n';
    }
}