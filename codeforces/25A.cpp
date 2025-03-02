#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;
const int MAX_N = 100;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n; cin>>n;
    int numbers[MAX_N], evens = 0, evenidx= 0, oddidx = 0;
    for (int i=0; i<n; i++) {
        cin >> numbers[i];
        if (numbers[i]%2==0) {
            evens++;
            evenidx = i+1;
        } else oddidx = i+1;
    }
    if (evens==1) cout<<evenidx;
    else cout<<oddidx;
    return 0;
}