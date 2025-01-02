#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N, Q;
    cin>>N>>Q;
    vector<long long> prefixSum(N+1);
    prefixSum[0] = 0;
    for (int i=1; i<=N; i++) {
        int x;
        cin>>x;
        prefixSum[i] = prefixSum[i-1]+x;
    }
    for (int i=0; i<Q; i++) {
        int l, r;
        cin>>l>>r
        cout<<(prefixSum[r]-prefixSum[l])<<'\n';
    }
    return 0;
}