#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
void solve() {
    string a, b;
    cin>>a>>b;
    char temp = b[0];
    b[0] = a[0];
    a[0] = temp;
    cout<<a<<' '<<b<<'\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int t;
    cin>>t;
    while (t--) solve();
    return 0;
}