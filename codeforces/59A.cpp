#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s; cin>>s;
    int x = 0;
    for (char c:s) x+=isupper(c)?1:-1;
    if (x>0) for (char &c:s) c = toupper(c);
    else for (char &c:s) c = tolower(c);
    cout<<s<<'\n';
    return 0;
}