#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;
void solve() {
    string s;
    cin>>s;
    int n = s.length();
    int sum = 0;
    for (int i=0; i<n; i++) {
        if (s[i]=='1') {
            sum++;
        }
    }
    cout<<sum<<'\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin>>t;
    while (t--) solve();
    return 0;
}