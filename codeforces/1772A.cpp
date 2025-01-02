#include <iostream>
using namespace std;
void solve() {
    char a, none, b;
    cin >> a >> none >> b;
    cout << (a-'0') + (b-'0') << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}