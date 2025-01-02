#include <iostream>
#include <string>
#define ll long long
using namespace std;
void solve() {
    string str;
    cin >> str;
    if (str.length()>10) cout << str[0] << str.length()-2 << str[str.length()-1] << "\n";
    else cout << str << "\n";
}
int main() {
    short T;
    cin >> T;
    while (T--) solve();
    return 0;
}