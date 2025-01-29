#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    short t; cin>>t;
    while(t--) {
        int n; cin>>n;
        vector<ll> a(n);
        for(int i=0; i<n; i++) cin>>a[i];
        vector<pair<int, ll>> nums;
        for(ll x:a) {
            int c = 0;
            while(x%2==0) {
                c++;
                x/=2;
            }
            nums.push_back({c, x});
        }
        sort(nums.rbegin(), nums.rend());
        ll sum = 0;
        int p = 0;
        for(auto [zeros, odd]:nums) {
            sum+=odd*(1LL<<zeros);
            if(sum%2==0) {
                p++;
                while(sum%2==0) sum/=2;
            }
        }
        cout<<p<<'\n';
    }
    return 0;
}