#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
inline int lcm(int a, int b) {
    return (a*b)/gcd(a, b);
}
inline void solve() {
    string a, b, ra, rb;
    cin>>a>>b;
    if (a.back()!=b.back()) {
        cout<<"-1\n";
        return;
    }
    int al = a.length(), bl = b.length();
    int len = lcm(al, bl);
    if (len%al!=0||len%bl!= 0) {
        cout<<"-1\n";
        return;
    }
    while ((int)ra.size()<len)ra+=a;
    while ((int)rb.size()<len)rb+=b;
    if (ra==rb) cout<<ra<<'\n';
    else cout<<"-1\n";
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    short t; cin >> t;
    while (t--) solve();
    return 0;
}