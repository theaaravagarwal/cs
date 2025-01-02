#include <iostream>
using namespace std;
void solve() {
    short k;
    cin>>k;
    short l=1, r=1666;
    while (l<r) {
        int m=l+(r-l)/2;
        short c=m-(m/3)-(m/10)+(m/30);
        if (c>=k) r=m;
        else l=m+1;
    }
    cout<<l<<"\n";
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    short t;
    cin>>t;
    while (t--) solve();
    return 0;
}