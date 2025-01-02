#include <iostream>
#include <string>
using namespace std;
#define str string
int main(){
    int n;
    cin>>n;
    str s1,s2;
    cin>>s1>>s2;
    int ans=0;
    for(int i=0;i<n;i++)if(s1[i]!=s2[i] && s1[i+1]==s2[i+1]) ans++;
    cout<<ans<<"\n";
    return 0;
}