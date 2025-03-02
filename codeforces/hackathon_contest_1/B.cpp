#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")
#pragma GCC optimize("unroll-loops")
typedef long long ll;
using namespace std;
inline void solve() {
    int n, k; cin>>n>>k;
    if (n<k) {
        cout<<"NO\n";
        return;
    }
    if (n>=k&&n%2==k%2) {
        cout<<"YES\n";
        for(int i=0; i<k-1; i++) cout<<"1 ";
        cout<<n-(k-1)<<"\n";
        return;
    }
    if (n>=2*k&&n%2==0) {
        cout<<"YES\n";
        for(int i=0; i<k-1; i++) cout<<"2 ";
        cout<<n-2*(k-1)<<"\n";
        return;
    }
    cout<<"NO\n";
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    short t; cin>>t;
    while (t--) solve();
    return 0;
}