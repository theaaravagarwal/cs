#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
void solve() {
    int x;
    cin>>x;
    int best_y = 1;
    int max_value = 0; 
    for (int y=1; y<x; ++y) {
        int curr_gcd = gcd(x, y);
        int val = curr_gcd+y;
        if (val>max_value) {
            max_value = val;
            best_y = y;
        }
    }
    cout<<best_y<<'\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int t;
    cin>>t;
    while (t--) solve();
    return 0;
}