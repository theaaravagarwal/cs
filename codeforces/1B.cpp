#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    string ch;
    cin>>n;
    while (n--) {
        cin>>ch;
        const size_t m = ch.length();
        size_t C = 1;
        while (C<m&&isdigit(ch[C])) C++;
        if (C>1&&C<m) {
            int col = 0;
            for (size_t i=C+1; i<m; ++i) col = col*10+(ch[i]-'0');
            int pow = 26;
            while (col>pow) {
                col-=pow;
                pow*=26;
            }
            col--;
            string result;
            while (pow!=1) {
                pow/=26;
                result+=(col/pow+'A');
                col%=pow;
            }
            ch[C] = 0;
            cout<<result<<ch.substr(1)<<'\n';
        } else {
            int col = 0, val = 0;
            int pow = 1;
            size_t i = 0;
            while (i<ch.length()&&isalpha(ch[i])) {
                col+=pow;
                pow*=26;
                val = val*26+(ch[i]-'A');
                i++;
            }
            col += val;
            cout<<"R"<<ch.substr(i)<<"C"<<col<<'\n';
        }
    }
    return 0;
}