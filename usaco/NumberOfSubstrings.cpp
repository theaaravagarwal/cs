#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define ll long long
#define str string
using namespace std;
vector<int> buildSuffix(const str& s) {
    int n = s.size();
    vector<int> suffixArray(n), rank(n), temp(n), count(max(256, n), 0);
    for (int i = 0; i < n; ++i) {
        suffixArray[i] = i;
        rank[i] = s[i];
    }
    for (int step = 1; step < n; step *= 2) {
        auto cmp = [&](int a, int b) {
            if (rank[a] != rank[b]) return rank[a] < rank[b];
            int ra = (a + step < n) ? rank[a + step] : -1;
            int rb = (b + step < n) ? rank[b + step] : -1;
            return ra < rb;
        };
        sort(suffixArray.begin(), suffixArray.end(), cmp);
        temp[suffixArray[0]] = 0;
        for (int i = 1; i < n; ++i)
            temp[suffixArray[i]] = temp[suffixArray[i - 1]] + cmp(suffixArray[i - 1], suffixArray[i]);
        rank = temp;
    }
    return suffixArray;
}
vector<int> buildLCP(const str& s, const vector<int>& suffixArray) {
    int n = s.size();
    vector<int> lcp(n), rank(n);
    for (int i = 0; i < n; ++i) rank[suffixArray[i]] = i;
    int h = 0;
    for (int i = 0; i < n; ++i) {
        if (rank[i] > 0) {
            int j = suffixArray[rank[i] - 1];
            while (i + h < n && j + h < n && s[i + h] == s[j + h]) ++h;
            lcp[rank[i]] = h;
            if (h > 0) --h;
        }
    }
    return lcp;
}
ll solve(const str& s) {
    int n = s.size();
    vector<int> suffixArray = buildSuffix(s);
    vector<int> lcp = buildLCP(s, suffixArray);
    ll total = 0;
    for (int i = 0; i < n; ++i)
        total += n - suffixArray[i] - lcp[i];
    return total;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    str s;
    cin >> s;
    cout << solve(s) << endl;
    return 0;
}