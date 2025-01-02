#include <iostream>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    bool x;
    cin >> n;
    while (n--) {
        cin >> x;
        if (x==1) {
            cout << "HARD\n";
            return 0;
        }
    }
    cout << "EASY\n";
    return 0;
}