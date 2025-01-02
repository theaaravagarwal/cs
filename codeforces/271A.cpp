#include <iostream>
using namespace std;
void solve() {
    int n;
    cin >> n;
    int yr = n + 1;
    while (true) {
        int a = yr/1000;
        int b = (yr/100)%10;
        int c = (yr/10)%10;
        int d = yr%10;
        if (a!=b&&a!=c&&a!=d&&b!=c&&b!=d&&c!=d) {
            cout << yr << "\n";
            return;
        }
        yr++;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}