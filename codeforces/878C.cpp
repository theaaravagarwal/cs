#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
const int inf = 1<<30;
struct Node {
    int mx[20], mn[20], sz;
    inline void init(int val, int size, int k) {
        for (int i=1; i<=k; i++) mx[i] = mn[i] = val;
        sz = size;
    }
    inline bool operator<(const Node &other) const {
        extern int k;
        for (int i=1; i<=k; i++) if (mx[i]>other.mn[i]) return false;
        return true;
    }
    inline void unit(const Node &other) {
        extern int k;
        sz += other.sz;
        for (int i=1; i<=k; i++) {
            mx[i] = max(mx[i], other.mx[i]);
            mn[i] = min(mn[i], other.mn[i]);
        }
    }
};
int n, k;
set<Node> S;
vector<set<Node>::iterator> del;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin>>n>>k;
    Node tmp;
    tmp.init(0, 0, k);
    S.insert(tmp);
    tmp.init(inf, 0, k);
    S.insert(tmp);
    for (int i=1; i<=n; i++) {
        tmp.sz = 1;
        for (int j=1; j<=k; j++) {
            cin>>tmp.mx[j];
            tmp.mn[j] = tmp.mx[j];
        }
        auto l = S.lower_bound(tmp);
        auto r = S.upper_bound(tmp);
        del.reserve(distance(l, r));
        for (auto it=l; it!=r; ++it) {
            del.push_back(it);
            tmp.unit(*it);
        }
        for (auto &it:del) S.erase(it);
        del.clear();
        S.insert(tmp);
        auto it = S.end();
        --it;
        --it;
        cout<<it->sz<<'\n';
    }
    return 0;
}