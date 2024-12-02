#include<bits/stdc++.h>
using namespace std;

#define _for(i,a,b) for(int i=(a);i<(int)(b);++i)
#define _rep(i,a,b) for(int i=(a);i<=(int)(b);++i)

typedef long long LL;
template<int SZ>
struct BIT{
  LL C[SZ];
  int N;
  void init(int _n){N=_n;}
  inline int lowbit(int x){return x&-x;}
  inline void add(int x,int d){ while(x<=N) C[x]+=d,x+=lowbit(x);}
  inline LL sum(int x){
	LL ret=0;
	while(x) ret+=C[x],x-=lowbit(x);
	return ret;
  }
};
struct Rain{int l,r,a;};
const int NN=3e5+8;
Rain Rs[NN];
vector<int > St[NN];
int N,M,Ans[NN],P[NN];
BIT<NN> S;
inline void apply(const Rain& q,bool revert=false){
  int x=q.a,l=q.l,r=q.r;
  if(revert) x=-x;
	if(l<=r) S.add(l,x),S.add(r+1,-x);
	else S.add(l,x),S.add(M+1,-x),S.add(l,x),S.add(r+1,-x);
}
void solve(const vector<int>& C,int l,int r){
  if(C.empty()) return;
  if(l==r){
	for(int c:C) Ans[c]=l;
	return;
  }
  int m=(l+r)/2;
  _rep(ai,l,m) apply(Rs[ai]);
  vector<int> LC,RC;
  for(int c:C){
	int &p=P[c];
	LL x=0;
	for(int s:St[c]) if((x+=S.sum(s))>=p) break;
	if(p<=x) LC.push_back(c);
	else p-=x,RC.push_back(c);
  }
  _rep(ai,l,m) apply(Rs[ai],true);
  solve(LC,l,m), solve(RC,m+1,r);
}
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  cin>>N>>M,S.init(M+2);
  int qc,x;
  vector<int >C;
  _rep(i,1,M) cin>>x,St[x].push_back(i);
  _rep(i,1,M) cin>>P[i],C.push_back(i);
  cin>>qc;
  _rep(i,1,qc) cin>>Rs[i].l>>Rs[i].r>>Rs[i].a;
  solve(C,1,qc+1);
  _rep(i,1,N){
	if(Ans[i]<=qc) cout<<Ans[i]<<endl;
	else cout<<"NIE"<<endl;
  }
  return 0;
}
