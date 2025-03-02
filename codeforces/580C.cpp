#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("avx,avx2,fma")
typedef long long ll;
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m; cin>>n>>m;
    vector<int> a(n);
    for (int i=0; i<n; i++) cin>>a[i];
    vector<vector<int>> adj(n);
    for (int i=0; i<n-1; i++) {
        int x, y; cin>>x>>y;
        x--; y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    int res = 0;
    vector<bool> visited(n, false);
    function<void(int, int, int)> dfs = [&](int v, int ccars, int parent) {
        visited[v] = true;
        if (a[v]==1) ccars++;
        else ccars = 0;
        if (ccars>m) return;
        bool is_leaf = true;
        for (int u:adj[v]) {
            if (u!=parent) {
                is_leaf = false;
                if (!visited[u]) dfs(u, ccars, v);
            }
        }
        if (is_leaf && ccars <= m) res++;
    };
    dfs(0, 0, -1);
    cout<<res;
    return 0;
}