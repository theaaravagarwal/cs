#include <iostream>
#include <string>
#include <unordered_set>
#include <sstream>
using namespace std;
int main() {
    string s;
    cin >> s;
    for (char &c : s) c = tolower(c);
    ostringstream res;
    unordered_set<char> vowels = {'a', 'o', 'y', 'e', 'u', 'i'};
    res.reserve(s.size()*2);
    for (char c:s) {
        if (vowels.find(c) == vowels.end()) res<<'.'<<c;
    }
    cout<<res.str()<<"\n";
    return 0;
}