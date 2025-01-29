#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    const int tr = 3, tc = 3;
    int matrix[5][5];
    int cr = -1, cc = -1;
    for (int i=0; i<5; ++i) {
        for (int j=0; j<5; ++j) {
            cin>>matrix[i][j];
            if (matrix[i][j]==1) {
                cr = i+1;
                cc = j+1;
            }
        }
    }
    int res = abs(tr-cr)+abs(tc-cc);
    cout<<res<<'\n';
    return 0;
}