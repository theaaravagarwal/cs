#include <iostream>
#define ull unsigned long long
#define ui unsigned int
using namespace std;
void solve(ui n, ui m) {
    if (n <= 0) return;
    ull prev2 = 0;
    ull prev1 = 1;
    cout << prev2;
    if (n > 1) cout << " " << prev1;
    for (int i = 2; i < n; i++) {
        ull current = (i * ((prev1 + prev2) % m)) % m;
        cout << " " << current;
        prev2 = prev1;
        prev1 = current;
    }
    cout << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ui n, m;
    cin >> n >> m;
    solve(n, m);
    return 0;
}