#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n, a, t = 0, c1 = 0;
    cin>>n;
    while (n--) {
        cin>>a;
        t+=a;
        if (a==1) c1++;
    }
    cout<<((t%2==0&&c1>=t/2-(t/2%2))?"YES\n":"NO\n");
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin>>t;
    while (t--) solve();
    return 0;
}s