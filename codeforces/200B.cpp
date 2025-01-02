#include <iostream>
#define ld long double
using namespace std;
int main() {
	int n;
	cin>>n;
	ld res=0;
	for(int i=0;i<n;i++){
	    ld p;
	    cin>>p;
	    res+=p/100;
	}
	cout<<res*100/n;
	return 0;
}