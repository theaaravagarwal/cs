#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;
int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin>>n;
    unordered_map<string, int> m;
    m.reserve(n);
    string s;
    s.reserve(32);
    while (n--) {
        cin>>s;
        auto it = m.find(s);
        if (it!=m.end()) {
            cout<<s<<it->second<<'\n';
            it->second++;
        } else {
            cout<<"OK\n";
            m[s] = 1;
        }
    }
    return 0;
}