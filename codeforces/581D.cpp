#include<bits/stdc++.h>
using namespace std;
struct node{
    int x,y,id;
    bool operator<(const node &p)const{
        return y>p.y;
    }
}a[4];
int main()
{
    int i,j,k;
    int x[4],y[4];
    for(i=1;i<=3;i++){
        cin>>a[i].x>>a[i].y;
        a[i].id=i;
        if(a[i].x>a[i].y) swap(a[i].x,a[i].y);
    }
    int sum=0;
    for(i=1;i<=3;i++) sum+=a[i].x*a[i].y;
    int len=sqrt(sum);
    if(len*len!=sum) return puts("-1");
    if(len==a[1].y&&len==a[2].y&&len==a[3].y){
        cout<<len<<'\n';
        for(i=1;i<=3;i++) for(j=1;j<=a[i].x;j++){
                for(k=1;k<=len;k++) cout<<char('A'+i-1);
                cout<<'\n';
            }
        return 0;
    }
    sort(a+1,a+4);
    if(len!=a[1].y) return puts("-1");
    if(a[2].y==a[3].y&&a[2].x+a[3].x==len){
        cout<<len<<'\n';
        for(j=1;j<=a[1].x;j++){
            for(k=1;k<=len;k++) cout<<char('A'+a[1].id-1);
            cout<<'\n';
        }
        for(j=1;j<=len-a[1].x;j++){
            for(k=1;k<=a[2].x;k++) cout<<char('A'+a[2].id-1);
            for(k=1;k<=a[3].x;k++) cout<<char('A'+a[3].id-1);
            cout<<'\n';
        }
        return 0;
    }
    if(a[2].x==a[3].x&&a[2].y+a[3].y==len){
        cout<<len<<endl;
        for(j=1;j<=a[1].x;j++){
            for(k=1;k<=len;k++){
                cout<<char('A'+a[1].id-1);
            }
            cout<<endl;
        }
        for(j=1;j<=len-a[1].x;j++){
            for(k=1;k<=a[2].y;k++) cout<<char('A'+a[2].id-1);
            for(k=1;k<=a[3].y;k++) cout<<char('A'+a[3].id-1);
            cout<<'\n';
        }
        return 0;
    }
    if(a[2].y==a[3].x&&a[2].x+a[3].y==len){
        cout<<len<<'\n';
        for(j=1;j<=a[1].x;j++){
            for(k=1;k<=len;k++) cout<<char('A'+a[1].id-1);
            cout<<'\n';
        }
        for(j=1;j<=len-a[1].x;j++){
            for(k=1;k<=a[2].x;k++) cout<<char('A'+a[2].id-1);
            for(k=1;k<=a[3].y;k++) cout<<char('A'+a[3].id-1);
            cout<<'\n';
        }
        return 0;
    }
    if(a[2].x==a[3].y&a[2].y+a[3].x==len){
        cout<<len<<endl;
        for(j=1;j<=a[1].x;j++){
            for(k=1;k<=len;k++) cout<<char('A'+a[1].id-1);
            cout<<'\n';
        }
        for(j=1;j<=len-a[1].x;j++){
            for(k=1;k<=a[2].y;k++) cout<<char('A'+a[2].id-1);
            for(k=1;k<=a[3].x;k++) cout<<char('A'+a[3].id-1);
            cout<<'\n';
        }
        return 0;
    }
    puts("-1");
}