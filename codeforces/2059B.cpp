//WA
#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
inline void solve() {
    int n, k; cin>>n>>k;
    vector<int> a(n);
    for (int i=0; i<n; i++) cin>>a[i];
    int res = n+1;
    for (int fl=1; fl<=n-(k-1); fl++) {
        int pos = fl;
        vector<int> b;
        bool poss = true;
        int remk = k-1;
        while (remk>0&&pos<n&&poss) {
            if (remk%2==0) {
                int val = 1;
                int start = pos;
                while (pos<n&&val<=b.size()+1) {
                    if (a[pos]==val) val++;
                    pos++;
                }
                if (start==pos) poss = false;
                if (poss) b.push_back(val-1);
            } else pos++;
            remk--;
        }
        if (poss&&pos==n&&remk==0) {
            b.push_back(0);
            for (int i=0; i<b.size(); i++) {
                if (b[i]!=i+1) {
                    res = min(res, i+1);
                    break;
                }
            }
        }
    }
    cout<<res<<'\n';
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    short t; cin>>t;
    while (t--) solve();
    return 0;
}