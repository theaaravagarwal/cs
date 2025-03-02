#include <bits/stdc++.h>
using namespace std;
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    string s; cin>>s;
    s = "00"+s;
    int n = s.length();
    for (int i=0; i<n-2; i++) {
        int num = 100*(s[i]-'0');
        for (int j=i+1; j<n-1; j++) {
            num+=10*(s[j]-'0');
            for (int k=j+1; k<n; k++) {
                num+=(s[k]-'0');
                if (num%8==0) {
                    cout<<"YES\n"<<num;
                    return 0;
                }
                num-=(s[k]-'0');
            }
            num-=10*(s[j]-'0');
        }
        num-=100*(s[i]-'0');
    }
    cout<<"NO";
    return 0;
}