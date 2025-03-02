#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
inline int solve(string s, string t) {
    int n = s.length();
    vector<pair<int,int>> blocks;
    for(int i = 0; i < n; ) {
        int j = i;
        while(j < n && s[j] == s[i]) j++;
        blocks.push_back({i, j-1});
        i = j;
    }
    int ops = 0;
    string current = s;
    for(int i = 0; i < blocks.size(); i++) {
        int start = blocks[i].first;
        int end = blocks[i].second;
        char blockChar = s[start];
        bool valid = true;
        for(int j = start; j <= end; j++) {
            if(t[j] != blockChar) {
                valid = false;
                break;
            }
        }
        if(!valid) {
            if(i == blocks.size() - 1) return -1;
            ops += (blocks[i+1].second - blocks[i].first + 1) / 2;
            blocks[i+1].first = blocks[i].first;
        }
    }
    string result = s;
    for(int i = 0; i < n; i++) {
        if(t[i] != '?' && result[i] != t[i]) {
            return -1;
        }
    }
    return ops;
}
signed main() {
    int tc; cin>>tc;
    while (tc--) {
        string s, t; cin>>s>>t;
        cout<<solve(s, t)<<'\n';
    }
}