#include <bits/stdc++.h>
using namespace std;
signed main() {
    int n; cin>>n;
    int o = 0, u = 0;
    for (int i=0; i<n; i++) {
        int x; cin>>x;
        if (x==-1) {
            if (o>0) o--;
            else u++;
        } else o+=x;
    }
    cout<<u;
    return 0;
}