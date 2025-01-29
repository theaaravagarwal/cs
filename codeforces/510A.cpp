#include <bits/stdc++.h>
using namespace std;
signed main() {
    int n, m; cin>>n>>m;
    vector<string> res(n, string(m, '.'));
    for (int i=0; i<n; i++) {
        if (i%2==0) {
            res[i] = string(m, '#');  
        } else {
            if ((i/2)%2==0) res[i][m-1] = '#';
            else res[i][0] = '#';
        }
    }
    for (const auto& r:res) cout<<r<<'\n';
    return 0;
}