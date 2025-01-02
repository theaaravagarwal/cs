#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#define ll long long
using namespace std;
void solve() {
    ll n, k;
    cin >> n >> k;
    map<ll, ll> m;
    for (ll p = 0; p < k; p++) {
        ll b, c;
        cin >> b >> c;
        m[b] += c;
    }
    vector<ll> v;
    for (auto it = m.begin(); it != m.end(); it++) v.push_back(it->second);
    sort(v.rbegin(), v.rend());
    ll total = 0;
    for (ll p = 0; p < v.size() && p < n; p++) total += v[p];
    cout << total << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll T;
    cin >> T;
    while (T--) solve();
    return 0;
}