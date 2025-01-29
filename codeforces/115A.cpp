#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
const int MAXN = 2010;
vector<int> graph[MAXN];
vector<bool> visited;
int depth[MAXN];
void bfs(queue<int>& q) {
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for (int n:graph[curr]) {
            if (!visited[n]) {
                visited[n] = true;
                depth[n] = depth[curr]+1;
                q.push(n);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin>>n;
    visited.assign(n, false);
    queue<int> q;
    for (int i=0; i<n; ++i) {
        int parent;
        cin>>parent;
        if (parent!=-1) graph[parent-1].push_back(i);
        else {
            q.push(i);
            visited[i] = true;
            depth[i] = 0;
        }
    }
    bfs(q);
    int res = 0;
    for (int i=0; i<n; ++i) res = max(res, depth[i]);
    cout<<res+1<<'\n';
    return 0;
}