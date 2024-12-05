#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define _for(i,a,b) for(int i=(a);i<(int)(b);++i)

template<int SZ>
struct BIT{
  int C[SZ],N;
  inline int lowbit(int x){return x& -x;}
  void add(int x, int v){
	while(x<=N) C[x]+=v,x+=lowbit(x);
  }
  int sum(int x){
	int r=0;
	while(x) r+=C[x],x-=lowbit(x);
	return r;
  }
};
const int NN=1e5+8;
BIT<NN> S;
struct OP{
  int id,p,v;
  bool operator<(const OP &b){return p>b.p;}
}O[NN],T[NN];
int N,M,A[NN],Pos[NN],Vis[NN];
LL Ans[NN];
void sovle(int l,int r){
  if(l==r) return;
  int m=(l+r)/2,l1=1,l2=m+1;
  for(int i=1;i<=r;i++){
	const OP &o=O[i];
	if(o.id<=m) S.add(o.v,l);
	else Ans[o.id]+=S.sum(o.v);
  }
  for(int i=1;i<=r;i++) if(O[i].id<=m) S.add(O[i].v,-1);
  for(int i=r;i>=l;--i){
	const OP &o=O[i];
	if(o.id<=m) S.add(N-o.v+1,1);
	else Ans[o.id]+= S.sum(N-o.v+1);
  }
  for(int i=1;i<=r;i++){
	const OP &o=O[i];
	if(o.id<=m) T[l1++]=o,S.add(N-o.v+1,-1);
	else T[l2++]=o;
  }
  copy(T+1,T+r+1,O+1);
  sovle(l,m),sovle(m+1,r);
}
int main(){
  cin>>N>>M;
  int id=N,qc=M;
  S.N=N;
  for(int i=1;i<=N;++i) cin>>A[i],Pos[A[i]]=i;
  for(int i=1;i<=M;++i){
	OP &q=O[i];
	cin>>q.v,Vis[q.p=Pos[q.v]] =true,q.id=id--;
  }
  for(int i=1;i<=N;++i){
	if(Vis[i]) continue;
	O[++qc]={id--,i,A[i]};
  }
  sort(O+1,O+1+N);
  sovle(1,N);
  for(int i=1;i<=N;++i) Ans[i]+=Ans[i-1];
  _for(i,0,M) cout<<Ans[N-i]<<endl;
  return 0;
}
