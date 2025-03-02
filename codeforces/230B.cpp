#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
const int MAXN = 1e6+1;
vector<bool> isp(MAXN, true);
vector<int> p;
inline void sieve() {
    isp[0] = isp[1] = false;
    for(int i=2; i*i<MAXN; i++) if(isp[i]) for(int j=i*i; j<MAXN; j+=i) isp[j] = false;
    for(int i=2; i<MAXN; i++) if(isp[i]) p.push_back(i);
}
inline bool check(ll x) {
    if(x==1) return false;
    ll sq = sqrt(x);
    return sq*sq==x&&binary_search(p.begin(), p.end(), sq);
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    sieve();
    int n; cin>>n;
    while(n--) {
        ll x; cin>>x;
        cout<<(check(x)?"YES":"NO")<<'\n';
    }
    return 0;
}