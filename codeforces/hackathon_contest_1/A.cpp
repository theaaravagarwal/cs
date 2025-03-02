#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")
#pragma GCC optimize("unroll-loops")
typedef long long ll;
using namespace std;
inline void solve() {
    int n; cin>>n;
    vector<int> result;
    string s = to_string(n);
    int len = s.length();
    for (int i=0; i<len; i++) if(s[i]!='0') result.push_back((s[i]-'0')*pow(10, len-i-1));
    cout<<result.size()<<'\n';
    for(int x:result) cout<<x<<' ';
    cout<<'\n';
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    short t; cin>>t;
    while (t--) solve();
    return 0;
}