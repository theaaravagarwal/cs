#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, l; cin>>n>>l;
    vector<int> a(n);
    for(int i=0; i<n; i++) cin>>a[i];
    sort(a.begin(), a.end());
    double max_dist = 0;
    for(int i=1; i<n; i++) max_dist = max(max_dist, (double)(a[i]-a[i-1])/2);
    max_dist = max({max_dist, (double)a[0], (double)(l - a[n-1])});
    cout<<fixed<<setprecision(10)<<max_dist<<"\n";
    return 0;
}