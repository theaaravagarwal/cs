#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
inline bool check(int n) {
    while (n>0) {
        int d = n%10;
        if (d!=4&&d!= 7) return false;
        n/=10;
    }
    return true;
}
signed main() {
    int n; cin>>n;
    bool l = false;
    for (int i=1; i<=n; i++) {
        if (check(i)&&n%i==0) {
            l = true;
            break;
        }
    }
    cout<<(l?"YES":"NO");
    return 0;
}
