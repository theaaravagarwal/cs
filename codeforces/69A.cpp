#include <bits/stdc++.h>
using namespace std;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n;
    cin>>n;
    int sumX = 0, sumY = 0, sumZ = 0;
    for(int i=0; i<n; i++) {
        int x, y, z;
        cin>>x>>y>>z;
        sumX+=x;
        sumY+=y;
        sumZ+=z;
    }
    if (sumX==0&&sumY==0&&sumZ==0) cout<<"YES";
    else cout<<"NO";
    return 0;
}