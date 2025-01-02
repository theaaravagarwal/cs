#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int optCows(double a, double l) {
    int c = max(1, (int)sqrt(a / l));
    if ((a / (c + 1) + l * (c + 1)) < (a / c + l * c)) ++c;
    return c;
}
pair<double, int> calc(const vector<double>& a, double l) {
    double t = 0.0;
    int cows = 0;
    for (double ai:a) {
        int c = optCows(ai, l);
        t+=ai/c;
        cows+=c;
    }
    return {t, cows};
}
int solve(int n, int k, const vector<double>& a) {
    double lo = 0.0, hi = *max_element(a.begin(), a.end()), eps = 1e-7;
    while (hi-lo>eps) {
        double mid = (lo+hi)/2;
        auto [t, c] = calc(a, mid);
        if (c<=k) hi = mid;
        else lo = mid;
    }
    return (int)round(calc(a, hi).first);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("tallbarn.in");
    ofstream fout("tallbarn.out");
    int n, k;
    fin>>n>>k;
    vector<double> a(n);
    for (double& ai:a) fin>>ai;
    fout<<solve(n, k, a)<<'\n';
    return 0;
}