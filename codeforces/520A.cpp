#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    short n; cin>>n;
    string s; cin>>s;
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    set<char> chars(s.begin(), s.end());
    cout<<(chars.size()==26?"YES":"NO");
    return 0;
}