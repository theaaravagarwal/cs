#include <iostream>
using namespace std;
void solve() {
    int n;
    cin>>n;
    int guestCount[101] = {0};
    int homeUniforms[30];
    for (int i=0; i<n; ++i) {
        int home, guest;
        cin >>home>>guest;
        homeUniforms[i] = home;
        guestCount[guest]++;
    }
    int c=0;
    for (int i=0; i<n; ++i) c+=guestCount[homeUniforms[i]];
    cout<<c<<'\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}