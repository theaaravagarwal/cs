#include <bits/stdc++.h>
using namespace std;
class DSU {
public:
    vector<int> parent, rank;
    DSU(int n) {
        parent.resize(n+1);
        rank.resize(n+1, 0);
        for (int i=1; i<=n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x]!=x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);
        if (root_x!=root_y) {
            if (rank[root_x]>rank[root_y]) parent[root_y] = root_x;
            else if (rank[root_x]<rank[root_y]) parent[root_x] = root_y;
            else {
                parent[root_y] = root_x;
                rank[root_x]++;
            }
        }
    }
};
bool check(const vector<tuple<int, int, int>>& wormholes, const vector<int>& p, int n, int min_width) {
    DSU dsu(n);
    for (const auto& [a, b, w]:wormholes) if (w>=min_width) dsu.unite(a, b);
    for (int i=1; i<=n; i++) if (dsu.find(i)!=dsu.find(p[i-1])) return false;
    return true;
}
void solve() {
    ifstream fin("wormsort.in");
    ofstream fout("wormsort.out");
    int n, m;
    fin>>n>>m;
    vector<int> p(n);
    for (int i=0; i<n; i++) fin>>p[i];
    vector<tuple<int, int, int>> wormholes(m);
    for (int i=0; i<m; i++) {
        int a, b, w;
        fin>>a>>b>>w;
        wormholes[i] = {a, b, w};
    }
    bool sorted = true;
    for (int i=0; i<n; i++) {
        if (p[i]!=i+1) {
            sorted = false;
            break;
        }
    }
    if (sorted) {
        fout<<-1<<'\n';
        return;
    }
    int l = 1, h = 1e9, b = -1;
    while (l<=h) {
        int mid = (l+h)/2;
        if (check(wormholes, p, n, mid)) {
            b = mid;
            l = mid+1;
        } else h = mid-1;
    }
    fout<<b<<'\n';
}
int main() {
    solve();
    return 0;
}
