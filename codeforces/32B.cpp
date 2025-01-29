#include <bits/stdc++.h>
using namespace std;
signed main() {
    string s;
    string res = "";
    cin>>s;
    for (int i=0; i<s.length(); i++) {
        if (s[i]=='-') {
            if (s[i+1]=='.') {
                res+='1';
                i++;
            } else if (s[i+1]=='-') {
                res+='2';
                i++;
            }
        } else if (s[i]=='.') res+='0';
    }
    cout<<res;
    return 0;
}