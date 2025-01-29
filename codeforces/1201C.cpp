#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
inline void solve() {
    int n, k;
    cin>>n>>k;
    vector<int> a(n);
    for (int i=0; i<n; i++) cin>>a[i];
    sort(a.begin(), a.end());
    int idx = n/2;
    ll low = a[idx], high = a[idx]+k+1;
    while (low<high) {
        ll mid = low+(high-low)/2;
        ll o = 0;
        for (int i = idx; i<n; i++) if (a[i]<mid) o+=mid-a[i];
        if (o<=k) low = mid+1;
        else high = mid;
    }
    cout<<low-1<<'\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve();
    return 0;
}