#include <bits/stdc++.h>
using namespace std;
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define int long long
inline void solve() {
    int n,s=0;
    cin>>n;
    for(;n;n>>=1)s+=n;
    cout<<s<<'\n';
}
signed main(){
    fast;
    int t;cin>>t;
    for(;t--;)solve();
    return 0;
}