#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
const int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
inline ll ff(short i, short j, short n, short m, short a[][1000], vector<vector<bool>> &visited) {
    stack<pair<short, short>> s;
    s.push({i, j});
    visited[i][j] = true;
    ll volume = 0;
    while (!s.empty()) {
        auto [x, y] = s.top(); s.pop();
        volume+=a[x][y];
        for (int d=0; d<4; d++) {
            short nx = x+dx[d];
            short ny = y+dy[d];
            if (nx>=0&&nx<n&&ny>=0&&ny<m&&!visited[nx][ny]&&a[nx][ny]>0) {
                visited[nx][ny] = true;
                s.push({nx, ny});
            }
        }
    }
    return volume;
}
inline void solve() {
    short n, m;
    cin>>n>>m;
    short a[n][1000];
    for (int i=0; i<n; i++) for (int j=0; j < m; j++) cin>>a[i][j];
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    ll volume = 0;
    for (int i=0; i<n; i++) for (int j=0; j<m; j++) if (a[i][j]>0&&!visited[i][j]) volume = max(volume, ff(i, j, n, m, a, visited));
    cout<<volume<<'\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    short t; cin>>t;
    while (t--) solve();
    return 0;
}