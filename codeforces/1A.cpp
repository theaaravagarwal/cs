#include <iostream>
typedef long long ll;
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, m, a;
    cin>>n>>m>>a;
    ll res = ((n+a-1)/a)*((m+a-1)/a);
    cout << res << "\n";
    return 0;
}
