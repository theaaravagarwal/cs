#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
int32_t main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s; cin>>s;
    bool all = true;
    for(int i=1; i<s.length(); i++) {
        if(!isupper(s[i])) {
            all = false;
            break;
        }
    }
    if(all) {
        s[0] = isupper(s[0])?tolower(s[0]):toupper(s[0]);
        for(int i=1; i<s.length(); i++) s[i] = tolower(s[i]);
    }
    cout<<s;
    return 0;
}