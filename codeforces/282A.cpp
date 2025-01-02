#include <iostream>
#include <string>
using namespace std;
int main() {
    short n;
    cin>>n;
    int x=0;
    for (short i=0; i<n; ++i) {
        string s;
        cin>>s;
        if (s=="++X"||s=="X++")x++;
        else if (s=="--X"||s=="X--")x--;
    }
    cout<<x<<"\n";
    return 0;
}