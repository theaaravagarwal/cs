#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 23;
ll s[N], len[N], t[N], oid[N];
ll f[1<<N], fr[1<<N], idx[1<<N], tim[1<<N], timk[1<<N];
ll tl[N], tr[N];
int ps[N], dt[N];
signed main() {
    int n, p;
    cin >> n >> p;
    vector<tuple<ll, ll, ll, ll>> v(n);
    for (int i=0; i<n; i++) {
        ll s, len, t;
        cin >> s >> len >> t;
        v[i] = {s, len, t, i};
    }
    sort(v.begin(), v.end());
    for (int i=0; i<n; i++) tie(s[i], len[i], t[i], oid[i]) = v[i];
    memset(f, 0x3f, sizeof(f));
    for (int i=0; i<n; i++) {
        tl[i] = s[i];
        tr[i] = s[i] + len[i] - 1;
    }
    tl[n] = tr[n] = 3e9;
    f[0] = 1;
    if (tl[0] == 1) {
        cout << "NO\n";
        return 0;
    }
    for (int i=0; i<(1<<n); i++) {
        if (f[i] > 3e9) continue;
        for (int j=0; j<n; j++) {
            if ((i >> j) & 1) continue;
            int i_ = i | (1 << j);
            ll tim_ = i ? tim[i] + t[idx[i]] : 1;
            ll l = tim_, r = tim_ + t[j];
            int lk = 0, rk = 0;
            while (l <= tr[n-1]) {
                while (l > tr[lk]) lk++;
                while (r > tr[rk]) rk++;
                if (l >= tl[lk]) {
                    l = tr[lk] + 1;
                    r = l + t[j];
                    continue;
                }
                int rk_ = rk - (r < tl[rk]);
                ll mask = (1 << (rk_ + 1)) - (1 << lk);
                if (i_ & mask) {
                    l = tr[lk] + 1;
                    r = l + t[j];
                    continue;
                }
                break;
            }
            tim_ = l;
            if (l > tr[n-1]) continue;
            if (rk - 1 >= j) continue;
            if (f[i_] > tim_ + t[j]) {
                f[i_] = tim_ + t[j];
                fr[i_] = i;
                idx[i_] = j;
                tim[i_] = tim_;
                timk[i_] = rk;
            }
        }
    }
    if (p == 1) {
        if (f[(1 << n) - 1] > 3e9) {
            cout << "NO\n";
            return 0;
        }
        cout << "YES\n";
        for (int i = (1 << n) - 1; i; i = fr[i]) {
            ps[oid[idx[i]]] = 1;
            dt[oid[idx[i]]] = tim[i];
        }
        for (int i = 0; i < n; i++) cout << ps[i] << " " << dt[i] << '\n';
        return 0;
    } else {
        for (int p = 0; p < (1 << n); p++) {
            int q = (1 << n) - 1 - p;
            if (f[p] > 3e9 || f[q] > 3e9) continue;
            cout << "YES\n";
            for (int i = p; i; i = fr[i]) {
                ps[oid[idx[i]]] = 1;
                dt[oid[idx[i]]] = tim[i];
            }
            for (int i = q; i; i = fr[i]) {
                ps[oid[idx[i]]] = 2;
                dt[oid[idx[i]]] = tim[i];
            }
            for (int i = 0; i < n; i++) cout << ps[i] << " " << dt[i] << '\n';
            return 0;
        }
        cout << "NO\n";
        return 0;
    }
    return 0;
}