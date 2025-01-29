#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
int main() {
    ll s1, s2, s3, s4; cin>>s1>>s2>>s3>>s4;
    set<ll> colors;
    colors.insert(s1);
    colors.insert(s2);
    colors.insert(s3);
    colors.insert(s4);
    cout<<4-colors.size();
    return 0;
}