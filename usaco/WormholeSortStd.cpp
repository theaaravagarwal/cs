#include <bits/stdc++.h>
using namespace std;
class DSU {
public:
    vector<int> parent, rank;
    DSU(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);
        if (root_x != root_y) {
            if (rank[root_x] > rank[root_y]) parent[root_y] = root_x;
            else if (rank[root_x] < rank[root_y]) parent[root_x] = root_y;
            else {
                parent[root_y] = root_x;
                rank[root_x]++;
            }
        }
    }
};
bool canSort(const vector<tuple<int, int, int>>& wormholes, const vector<int>& p, int n, int min_width) {
    DSU dsu(n);
    for (const auto& [a, b, w] : wormholes) if (w >= min_width) dsu.unite(a, b);
    for (int i = 1; i <= n; i++) if (dsu.find(i) != dsu.find(p[i - 1])) return false;
    return true;
}
void solve() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M;
    cin >> N >> M;
    vector<int> p(N);
    for (int i = 0; i < N; i++) cin >> p[i];
    vector<tuple<int, int, int>> wormholes(M);
    for (int i = 0; i < M; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        wormholes[i] = {a, b, w};
    }
    bool sorted = true;
    for (int i = 0; i < N; i++) {
        if (p[i] != i + 1) {
            sorted = false;
            break;
        }
    }
    if (sorted) {
        cout << -1 << '\n';
        return;
    }
    int low = 1, high = 1e9, best = -1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (canSort(wormholes, p, N, mid)) {
            best = mid;
            low = mid + 1;
        } else high = mid - 1;
    }
    cout << best << '\n';
}
int main() {
    solve();
    return 0;
}