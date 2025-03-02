#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    string s; cin>>s;
    string res;
    bool space = false;
    for(int i=0; i<s.length(); i++) {
        if(i+2<s.length()&&s[i]=='W'&&s[i+1]=='U'&&s[i+2]=='B') {
            i+=2;
            if(!res.empty() && !space) {
                res+=' ';
                space = true;
            }
        } else {
            res+=s[i];
            space = false;
        }
    }
    if(!res.empty()&&res.back()==' ') res.pop_back();
    cout<<res;
    return 0;
}