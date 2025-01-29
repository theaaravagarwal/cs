#include<bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    string s; getline(cin, s);
    set<char> a;
    for(char c:s) if(islower(c)) a.insert(c);
    cout<<a.size();
    return 0;
}