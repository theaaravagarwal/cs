#include <iostream>
#include <algorithm>
#include <cmath>
#define ll long long
using namespace std;
void solve() {
    int a, b;
    cin >> a >> b;
    int c = abs(b-a);
    int d = (c+9)/10;
    cout << d << endl;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}