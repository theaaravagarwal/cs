#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, c0, c1, h;
        cin >> n >> c0 >> c1 >> h;
        string s;
        cin >> s;
        int cost_0 = min(c0, c1 + h);
        int cost_1 = min(c1, c0 + h);
        int count_0 = count(s.begin(), s.end(), '0');
        int count_1 = n - count_0;
        int total_cost = count_0 * cost_0 + count_1 * cost_1;
        cout << total_cost << endl;
    }
    return 0;
}