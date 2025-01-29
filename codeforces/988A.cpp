#include <bits/stdc++.h>
using namespace std;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    short n, k;
    scanf("%hd %hd", &n, &k);
    vector<short> idx;
    idx.reserve(k);
    bool seen[101] = {false};
    for (short i = 0; i < n; i++) {
        short temp;
        scanf("%hd", &temp);
        if (!seen[temp]) {
            seen[temp] = true;
            idx.emplace_back(i+1);
            if (idx.size()==k) break;
        }
    }
    if (idx.size()<k) {
        printf("NO\n");
        return 0;
    }
    printf("YES\n");
    for (short i=0; i<k; i++) printf("%hd ", idx[i]);
    return 0;
}