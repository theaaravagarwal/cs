#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, m; cin>>n>>m;
    vector<int> puzzles(m);
    for (int i=0; i<m; ++i) cin>>puzzles[i];
    sort(puzzles.begin(), puzzles.end());
    int diff = std::numeric_limits<int>::max();
    for (int i=0; i<=m-n; ++i) {
        int a = puzzles[i+n-1];
        int b = puzzles[i];
        diff = min(diff, a-b);
    }
    cout<<diff;
    return 0;
}