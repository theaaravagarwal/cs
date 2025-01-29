#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
inline void solve() {
    short c = 0;
    string s;
    cin>>s;
    for (int i=0; i<s.length(); i++) {
        if (i==0||s[i]==s[i-1]) c++;
        else c = 1;
        if (c>=7) {
            cout<<"YES";
            return;
        }
    }
    cout<<"NO";
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    solve();
    return 0;
}