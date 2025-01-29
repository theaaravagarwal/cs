#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n; cin>>n;
    string s; cin>>s;
    int a = 0;
    for (char c:s) if (c=='A') a++;
    int d = n-a;
    cout<<(a>d?"Anton":(d>a?"Danik":"Friendship"));
    return 0;
}