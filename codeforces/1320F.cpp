#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
constexpr int N = 233333, dx[] = {1, -1, 0, 0, 0, 0}, dy[] = {0, 0, 1, -1, 0, 0}, dz[] = {0, 0, 0, 0, 1, -1};
int n, m, k, a[N], top[N], s[N][6];
inline void dfs(int p, int c, int op) {
    int &current_a = a[p];
    if (current_a == -1 || current_a == c) {
        current_a = c;
        s[p][top[p]++] = op;
        if (!c) {
            int tx = (p / (m * k) + dx[op]);
            int ty = (p % (m * k) / k + dy[op]);
            int tz = (p % (m * k) % k + dz[op]);
            dfs((tx - 1) * m * k + (ty - 1) * k + tz, c, op);
        }
        return;
    }
    if (current_a > 0) {
        while (top[p] > 0) {
            int t = s[p][--top[p]];
            int tx = (p / (m * k) + dx[t]);
            int ty = (p % (m * k) / k + dy[t]);
            int tz = (p % (m * k) % k + dz[t]);
            dfs((tx - 1) * m * k + (ty - 1) * k + tz, current_a, t);
        }
    }
    current_a = 0;
    int tx = (p / (m * k) + dx[op]);
    int ty = (p % (m * k) / k + dy[op]);
    int tz = (p % (m * k) % k + dz[op]);
    dfs((tx - 1) * m * k + (ty - 1) * k + tz, c, op);
}
inline void solve(int a, int b, int op) {
    #pragma omp parallel for collapse(2) schedule(dynamic)
    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= b; j++) {
            int x;
            #pragma omp critical
            scanf("%d", &x);
            int startX = (!op ? 1 : (op > 1 ? i : n));
            int startY = (op < 2 ? i : (op > 3 ? j : (op < 3 ? 1 : m)));
            int startZ = (op < 4 ? j : (op < 5 ? 1 : k));
            dfs((startX - 1) * m * k + (startY - 1) * k + startZ, x, op);
        }
    }
}
signed main() {
    memset(a, -1, sizeof(a)), memset(top, 0, sizeof(top));
    scanf("%d %d %d", &n, &m, &k);
    solve(m, k, 0), solve(m, k, 1), solve(n, k, 2), solve(n, k, 3), solve(n, m, 4), solve(n, m, 5);
    for (int i = 1; i <= n * m * k; i++) printf("%d ", max(a[i], 0));
    return 0;
}