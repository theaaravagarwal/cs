#include <cstdio>
using namespace std;
inline short in() {
    short x = 0, c = getchar();
    while (c<'0'||c>'9') c = getchar();
    while (c>='0'&&c<='9') {
        x = x*10+(c-'0');
        c = getchar();
    }
    return x;
}
inline void out(unsigned char x) {
    if (x==0) {
        putchar('0');
        putchar('\n');
        return;
    }
    char buf[4];
    unsigned char len = 0;
    while (x>0) {
        buf[len++] = (x%10)+'0';
        x/=10;
    }
    while (len--) putchar(buf[len]);
    putchar('\n');
}
void solve() {
    unsigned char n = in();
    unsigned char freq[21] = {0};
    while (n--) ++freq[in()];
    unsigned char res = 0;
    for (unsigned char i=1; i<=20; ++i) {
        res+=(freq[i]>>1);
    }
    out(res);
}
int main() {
    short T = in();
    while (T--) solve();
    return 0;
}