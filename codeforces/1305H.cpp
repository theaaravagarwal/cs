#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define fbo find_by_order
#define ook order_of_key
typedef long long ll;
typedef pair<int,int> ii;
typedef vector<ll> vi;
typedef long double ld;
typedef tree<ll,null_type,less<ll>,rb_tree_tag,tree_order_statistics_node_update> pbds;
const int N=150000,M=150000;
int L[N+10],R[N+10],a[N+10],n,m;
ll T;
void read(){cin>>n>>m;for(int i=0;i<n;i++)cin>>L[i]>>R[i];fill(a,a+m,-1);int q;cin>>q;while(q--){int rk,sc;cin>>rk>>sc;a[m-rk]=sc;}cin>>T;}
vector<ll> sortedL,sortedR;
struct ConvexHull{
    struct Line{ll m,c;Line(ll _m,ll _c):m(_m),c(_c){}inline ll pass(ll x)const{return m*x+c;}};
    deque<Line> d;
    inline bool irrelevant(const Line& Z)const{if(d.size()<2)return 0;const Line &X=d[d.size()-2],&Y=d.back();return(X.c-Z.c)*(Y.m-X.m)<=(X.c-Y.c)*(Z.m-X.m);}
    inline void push_line(ll m,ll c){Line l(m,c);while(irrelevant(l))d.pop_back();d.pb(l);}
    inline ll query(ll x){while(d.size()>1&&(d[0].c-d[1].c<=x*(d[1].m-d[0].m)))d.pop_front();return d[0].pass(x);}
};
bool check(vector<int> b){
    ll sumB=0,sumL=0;sort(b.begin(),b.end());
    for(int i=0;i<b.size();i++){sumB+=b[i];if(a[i]!=-1)assert(a[i]==b[i]);if(i>0)assert(b[i]>=b[i-1]);}
    for(int i=0;i<n;i++)sumL+=L[i];
    assert(int(b.size())==m&&sumB==T);
    ll cursum=0;ConvexHull ch1,ch2;
    for(int j=n;j>=0;j--){ch1.push_line(n-j,-sortedR[j]+j*1LL*m);ch2.push_line(n-j,-sortedL[j]+j*1LL*m);}
    for(int i=0;i<=m;i++){
        if(-ch1.query(i)<sumB-(cursum+n*1LL*m)||-ch2.query(i)<sumL-(cursum+n*1LL*m))return 0;
        if(i<m)cursum+=b[i];
    }
    return 1;
}
void greedyrange(vector<int>&v,int l,int r,int ub,ll&S){
    if(S<=0)return;
    ll ext=0;
    for(int i=l;i<=r;i++)ext+=ub-v[i];
    if(ext<=S){S-=ext;fill(v.begin()+l,v.begin()+r+1,ub);return;}
    deque<ii>dq;dq.emplace_back(v[l],1);
    for(int i=l+1;i<=r;i++) {
        if(dq.back().fi==v[i]) {
            dq.back().se++;
        } else {
            dq.emplace_back(v[i],1);
        }
    }
    while(S>0&&dq.size()>1){
        int L=dq[0].fi,cnt=dq[0].se,R=dq[1].fi;
        if((R-L)*1LL*cnt<=S){S-=(R-L)*1LL*cnt;dq[1].se+=cnt;dq.pop_front();}
        else{ll q=S/cnt,rem=S%cnt;dq[0].fi+=q;
            if(rem>0){ii tmp=dq.front();dq.pop_front();dq.push_front({rem,tmp.fi+1});dq.push_front({cnt-rem,tmp.fi});}
            S=0;break;
        }
    }
    if(S>0){
        assert(dq.size()==1);ll q=S/(r-l+1),rem=S%(r-l+1);
        fill(v.begin()+l,v.begin()+r+1,dq[0].fi+q);
        for(int i=0,ptr=r;i<rem;i++)v[ptr--]++;S=0;
    }else{
        int ptr=l;for(auto x:dq)for(int j=0;j<x.se;j++)v[ptr++]=x.fi;
    }
}
void greedy(vector<int>&v,ll&S){
    if(S<=0)return;
    vector<ii>ranges;int l=0;
    for(int i=0;i<m;i++){
        if(a[i]==-1)continue;
        if(l<=i-1)ranges.pb({l,i-1});
        l=i+1;
    }
    if(l<m)ranges.pb({l,m-1});
    for(auto x:ranges)greedyrange(v,x.fi,x.se,x.se+1<m&&a[x.se+1]!=-1?a[x.se+1]:n,S);
}
ii solve_full(){
    sortedL.clear();sortedR.clear();sortedL.reserve(n+1);sortedR.reserve(n+1);
    sortedL.pb(0);sortedR.pb(0);
    for(int i=0;i<n;i++){sortedL.pb(L[i]);sortedR.pb(R[i]);}
    sort(sortedL.begin(),sortedL.end());sort(sortedR.begin(),sortedR.end());
    for(int i=1;i<=n;i++){sortedL[i]+=sortedL[i-1];sortedR[i]+=sortedR[i-1];}
    int lo=1,hi=m,anstie=-1,ansm=0;vector<int>testb;vi ori(m,-1);
    while(lo<=hi){
        int mid=(lo+hi)>>1;vector<int>b;int curmin=0;ll cursum=0;
        for(int i=0;i<m;i++){if(a[i]!=-1)curmin=a[i];b.pb(curmin);cursum+=b[i];}
        bool pos=0;int forcedM=-1;
        for(int j=m-mid;j<m;j++)if(a[j]>=0)forcedM=forcedM>=0&&forcedM!=a[j]?-2:a[j];
        if(forcedM>=-1){
            int L2=curmin,R2=n;
            if(forcedM>=0)L2=R2=forcedM;
            if(forcedM<0){
                int lo2=curmin,hi2=static_cast<int>(max(0LL,min(ll(n),(T-cursum)/mid+curmin)));L2=1e9;
                while(lo2<=hi2){
                    int mid2=(lo2+hi2)>>1;vector<int>nwb=b;ll rem=T-cursum;
                    for(int j=m-mid;j<m;j++){
                        rem+=b[j]-mid2;nwb[j]=mid2;
                        if(a[j]>=0&&nwb[j]!=a[j])rem=-1e18;
                        ori[j]=a[j];a[j]=mid2;
                    }
                    greedy(nwb,rem);
                    for(int j=m-mid;j<m;j++)a[j]=static_cast<int>(ori[j]);
                    rem==0?hi2=mid2-1,L2=mid2:lo2=mid2+1;
                }
            }
            while(L2<=R2){
                int M=(L2+R2)>>1;vector<int>nwb=b;ll rem=T-cursum;
                for(int j=m-mid;j<m;j++){
                    rem+=b[j]-M;nwb[j]=M;
                    if(a[j]>=0&&nwb[j]!=a[j])rem=-1e18;
                    ori[j]=a[j];a[j]=M;
                }
                greedy(nwb,rem);
                if(rem==0&&check(nwb)){testb=nwb;ansm=M;pos=1;L2=M+1;}
                else R2=M-1;
                for(int j=m-mid;j<m;j++)a[j]=static_cast<int>(ori[j]);
            }
        }
        pos?anstie=mid,lo=mid+1:hi=mid-1;
    }
    return anstie==-1?ii(-1,-1):ii(anstie,ansm);
}
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    read();
    const ii sol2=solve_full();
    cout<<sol2.fi<<' '<<sol2.se<<'\n';
    return 0;
}