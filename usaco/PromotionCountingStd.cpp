#include <iostream>
using namespace std;
int main() {
    int bb, ab, bs, as, bg, ag, bp, ap, bts, stg, gtp;
    cin >> bb >> ab;
    cin >> bs >> as;
    cin >> bg >> ag;
    cin >> bp >> ap;
    gtp = ap-bp;
    stg = ag-bg+gtp;
    bts = as-bs+stg;
    cout << bts << "\n" << stg << "\n" << gtp << "\n";
}