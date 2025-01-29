#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;
inline bool tricheck(int a, int b, int c) {return (a+b>c)&&(b+c>a)&&(a+c>b);}
inline bool segcheck(int a, int b, int c) {return (a+b==c)||(b+c==a)||(a+c==b);}
inline string solve() {
    vector<int> s(4);
    for (int &stick:s) cin>>stick;
    sort(s.begin(), s.end());
    bool has_segment = false;
    for (int i=0; i<4; ++i) {
        vector<int> ts(s.begin(), s.begin()+i);
        ts.insert(ts.end(), s.begin()+i+1, s.end());
        if (tricheck(ts[0], ts[1], ts[2])) return "TRIANGLE";
        if (segcheck(ts[0], ts[1], ts[2])) has_segment = true;
    }
    return has_segment?"SEGMENT":"IMPOSSIBLE";
}
signed main() {
    cout<<solve();
    return 0;
}