#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int v[N], tot = 1;
vector<int> to[N];
bool vis[N], vvis[N];
vector<int> cy[N];
int cnt = 0;
int q[N], f[N], g[N];
#pragma GCC optimize("Ofast,inline-functions,no-stack-protector,fast-math")
#pragma GCC target("avx,avx2,fma,sse3,sse4.2,sse4.1,tune=native")
inline pair<int, int> ss(int x, int fa) {
    vis[x] = 1;
    pair<int, int> ret = {0, 0};
    for (int i : to[x]) {
        int v = ::v[i];
        if (v == fa) continue;
        if (vvis[i] || vvis[i ^ 1]) continue;
        vvis[i] = 1;
        if (vis[v]) {
            ++cnt;
            cy[cnt].push_back(i);
            ret = {v, cnt};
            continue;
        }
        auto t = ss(v, x);
        if (t.second) {
            cy[t.second].push_back(i);
            if (x != t.first) ret = t;
        }
    }
    return ret;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        ++tot;
        v[tot] = y;
        to[x].push_back(tot);
        ++tot;
        v[tot] = x;
        to[y].push_back(tot);
    }
    ss(1, 0);
    if (cnt != m - n + 1) {
        cout << cnt - (m - n + 1);
        return 0;
    }
    for (int i = 1; i <= cnt; i++) {
        for (size_t j = 0; j < cy[i].size(); j++) {
            if (v[cy[i][j] ^ 1] != v[cy[i][(j + 1) % cy[i].size()]]) {
                cout << i * 100;
                return 0;
            }
        }
    }
    for (int i = 1; i <= cnt; i++) {
        int mx = max_element(cy[i].begin(), cy[i].end()) - cy[i].begin();
        rotate(cy[i].begin(), cy[i].begin() + mx, cy[i].end());
        int mn = min_element(cy[i].begin(), cy[i].end()) - cy[i].begin();
        if (is_sorted(cy[i].begin(), cy[i].begin() + mn, greater<int>()) && is_sorted(cy[i].begin() + mn, cy[i].end())) q[cy[i][mn]] = cy[i][0];
    }
    for (int i = 1; i <= n; i++) f[i] = 1;
    for (int i = tot; i >= 2; i -= 2) {
        int u = v[i], v = ::v[i ^ 1];
        int x = f[u] + f[v];
        f[u] = f[v] = (q[i] + q[i ^ 1] ? x - g[q[i] + q[i ^ 1]] : x);
        g[i ^ 1] = g[i] = f[u];
    }
    for (int i = 1; i <= n; i++) cout << f[i] - 1 << " ";
    return 0;
}