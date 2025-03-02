#include <bits/stdc++.h>
using namespace std;
const int MAXN = 4e5 + 5;
const long long INF = 1e18;
struct SegTree {
    vector<long long> tree;
    int n;
    SegTree(int size) {
        n = size;
        tree.resize(4 * n, INF);
    }
    void update(int pos, long long val) { update(1, 0, n-1, pos, val); }
    void update(int node, int l, int r, int pos, long long val) {
        if (l == r) {
            tree[node] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid) update(2*node, l, mid, pos, val);
        else update(2*node+1, mid+1, r, pos, val);
        tree[node] = min(tree[2*node], tree[2*node+1]);
    }
    long long query(int ql, int qr) { return query(1, 0, n-1, ql, qr); }
    
    long long query(int node, int l, int r, int ql, int qr) {
        if (ql > qr) return INF;
        if (l == ql && r == qr) return tree[node];
        int mid = (l + r) / 2;
        return min(
            query(2*node, l, mid, ql, min(qr, mid)),
            query(2*node+1, mid+1, r, max(ql, mid+1), qr)
        );
    }
};
void solve() {
    string s, t;
    cin >> s >> t;
    int n = s.length();
    vector<pair<int, int>> blocks;
    for (int i = 0; i < n; i++) {
        int j = i;
        while (j < n && s[j] == s[i]) j++;
        blocks.push_back({i, j-1});
        i = j-1;
    }
    for (int i = 0; i < blocks.size(); i++) {
        for (int j = blocks[i].first; j <= blocks[i].second; j++) {
            if (t[j] != '?' && t[j] != s[j]) {
                bool can_match = false;
                for (int k = i + 1; k < blocks.size(); k++) {
                    if (s[blocks[k].first] == t[j]) {
                        can_match = true;
                        break;
                    }
                }
                if (!can_match) {
                    cout << -1 << '\n';
                    return;
                }
            }
        }
    }
    vector<long long> dp(blocks.size(), INF);
    dp[0] = 0;
    
    SegTree st(n);
    st.update(0, 2*dp[0] - 0);
    for (int i = 1; i < blocks.size(); i++) {
        int left = 0;
        for (int j = 0; j < i; j++) {
            if (s[blocks[j].first] == s[blocks[i].first]) {
                left = max(left, j + 1);
            }
        }
        if (left <= i-1) {
            long long min_val = st.query(left, i-1);
            if (min_val != INF) {
                dp[i] = (min_val + i) / 2;
            }
        }
        if (dp[i] == INF) {
            cout << -1 << '\n';
            return;
        }   
        st.update(i, 2*dp[i] - i);
    }
    cout << dp[blocks.size()-1] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}