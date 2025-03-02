#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
typedef long long ll;
using namespace std;
signed main() {
    string s1, s2, s3; cin>>s1>>s2>>s3;
    vector<int> freq1(26, 0);
    vector<int> freq2(26, 0);
    vector<int> freq3(26, 0);
    for(char c:s1) freq1[c-'A']++;
    for(char c:s2) freq2[c-'A']++;
    for(char c:s3) freq3[c-'A']++;
    for(int i=0; i<26; i++) if(freq1[i]+freq2[i]!=freq3[i]) cout<<"NO", exit(0);
    cout<<"YES";
    return 0;
}