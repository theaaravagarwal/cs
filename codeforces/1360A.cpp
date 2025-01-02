#include <iostream>
#include <algorithm>
using namespace std;
void solve() {
    int a, b;
    cin>>a>>b;
    int s = min(max(a+b, max(a, b)), max(2*min(a, b), max(a, b)));
    cout<<s*s<<'\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}