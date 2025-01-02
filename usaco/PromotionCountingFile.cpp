#include <fstream>
using namespace std;
int main() {
    int bb, ab, bs, as, bg, ag, bp, ap, bts, stg, gtp;
    ifstream in("promote.in");
    ofstream out("promote.out");
    in >> bb >> ab;
    in >> bs >> as;
    in >> bg >> ag;
    in >> bp >> ap;
    gtp = ap-bp;
    stg = ag-bg+gtp;
    bts = as-bs+stg;
    out << bts << "\n" << stg << "\n" << gtp << "\n";
}