#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;
int main() {  
    int n, t; cin>>n>>t;  
    string s; cin>>s;
    for (int time=0; time<t; time++) {  
        for (int i=0; i<n-1; i++) {
            if (s[i]=='B'&&s[i+1]=='G') {
                swap(s[i], s[i+1]);
                i++;
            }
        }
    }
    cout<<s;
    return 0;
}