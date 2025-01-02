#include <iostream>
#include <string>
using namespace std;
void solve() {
    string s;
    cin >> s;
    char a = s[0];
    char op = s[1];
    char b = s[2];
    int num1 = a - '0';
    int num2 = b - '0';
    if ((op == '<' && num1 < num2) || (op == '=' && num1 == num2) || (op == '>' && num1 > num2)) {
        cout << s << '\n';
        return;
    }
    if (num1 < num2) cout << a << "<" << b << '\n';
    else if (num1 == num2) cout << a << "=" << b << '\n';
    else cout << a << ">" << b << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}