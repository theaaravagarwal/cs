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
    set<short> levels;
    short p; cin>>p;
    for(short i=0; i<p; i++) {
        short level; cin>>level;
        levels.insert(level);
    }
    short q; cin>>q;
    for(short i=0; i<q; i++) {
        short level; cin>>level;
        levels.insert(level);
    }
    cout<<(levels.size()==n?"I become the guy.":"Oh, my keyboard!");
    return 0;
}