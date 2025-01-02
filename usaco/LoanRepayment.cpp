#include <iostream>
#include <algorithm>
#include <climits>
#define ll long long
using namespace std;
bool canRepay(ll N, ll K, ll M, ll X) {
    ll totalGiven = 0;
    while (K > 0 && totalGiven < N) {
        ll Y = (N - totalGiven) / X;
        if (Y < M) {
            ll remainingDays = (N - totalGiven + M - 1) / M;
            return remainingDays <= K;
        }
        ll days = min((N - totalGiven - X * Y) / Y + 1, K);
        totalGiven += Y * days;
        K -= days;
    }
    return totalGiven >= N;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll N, K, M;
    cin >> N >> K >> M;
    ll low = 1, high = N / M;
    while (low < high) {
        ll mid = (low + high + 1) / 2;
        if (canRepay(N, K, M, mid)) low = mid;
        else high = mid - 1;
    }
    cout << low << endl;
    return 0;
}