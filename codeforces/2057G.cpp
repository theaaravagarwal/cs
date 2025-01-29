#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
inline void solve() {
    int n, m; cin>>n>>m;
    vector<string> v(n);
    for (auto& w:v) cin>>w;
    auto col = [](int x, int y) {
        int c = (x+2*y)%5;
        if (c<0) c+=5;
        return c;
    };
    auto cell = [&](int x, int y) {
        if (x<0||y<0||x>=n||y>=m) return false;
        return v[x][y]=='#';
    };
    array<vector<pair<int, int>>, 5> colorings;
    for (int i=0; i<n; ++i)
    for (int j=0; j<m; ++j) {
        if (!cell(i, j)) continue;
        colorings[col(i, j)].emplace_back(i, j);
        for (int di=-1; di<=1; ++di)
        for (int dj=-1; dj<=1; ++dj) {
            if (abs(di)+abs(dj)!=1) continue;
            if (!cell(i+di, j+dj)) colorings[col(i+di, j+dj)].emplace_back(i, j);
        }
    }
    auto coloring = colorings[0];
    for (const auto& w:colorings) if (w.size()<coloring.size()) coloring = w;
    for (auto [x, y]:coloring) v[x][y] = 'S';
    for (auto ln:v) cout<<ln<<'\n';
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t; cin>>t;
    while (t--) solve();
    return 0;
}