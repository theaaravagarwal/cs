#include<bits/stdc++.h>
using namespace std;
signed main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin>>n;
        vector<int> a(n);
        for (int &i:a) cin>>i;
        unordered_set<int> x;
        for (int i=1; i<=n; ++i) x.insert(i);
        for (int i=0; i<n; ++i) x.erase(a[i]);
        unordered_map<int, bool> m;
        for (int i=0; i < n; ++i) {
            if (!m[a[i]]&&x.count(a[i])==0) {
                cout<<a[i]<<' ';
                m[a[i]] = true;
            }
        }
        for (auto i:x) cout<<i<<' ';
        cout<<'\n';
    }
    return 0;
}