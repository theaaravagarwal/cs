#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
inline int calc(vector<int>& arr) {
    if (arr.empty()) return 0;
    vector<int> temp = arr;
    int ops = 0;
    while (!temp.empty()) {
        int mv = *min_element(temp.begin(), temp.end());
        vector<int> a;
        for (int x:temp) if (x!=mv) a.push_back(x);
        temp = a;
        ops++;
    }
    return ops;
}
inline void solve() {
    int n, k; cin>>n>>k;
    map<int, int> freq;
    set<int> unique;
    for (int i=0; i<n; i++) {
        int x; cin>>x;
        freq[x]++;
        unique.insert(x);
    }
    vector<pair<int, int>> freqp;
    for (auto [num, c]:freq) freqp.push_back({c, num});
    sort(freqp.begin(), freqp.end());
    int d = unique.size();
    int usedK = 0;
    for (auto [c, num]:freqp) {
        if (usedK+c<=k) {
            d--;
            usedK+=c;
        }
    }
    cout<<max(1, d)<<'\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int t; cin>>t;
    while (t--) solve();
    return 0;
}