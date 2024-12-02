#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int MOD;
LL _addM(LL a,LL b){return (a+b)%MOD;}
LL _mulM(LL a,LL b){return (a*b)%MOD;}
void addM(LL &a,LL b){a=_addM(a,b);}
void mulM(LL &a,LL b){a=_mulM(a,b);}

template <typename T,int SZ=1000000>
struct IntervalTree{
  T addv[SZ],mulv[SZ],sum[SZ];
  int qL,qR;
  T build(int o,int l,int r,T *A){
	mulv[o]=1,addv[o]=0;
	if(l==r) return sum[o]=A[l];
	int m=l+(r-l)/2;
	return sum[o]=_addM(build(2*o,l,m,A),build(2*o+1,m+1,r,A));
  }
  T query(int o,int L,int R){
	if(qL<=L&& R<=qR) return sum[o];
	int m=L+(R-L)/2;
	T ans=0;
	pushdown(o,L,R);
	if(qL<=m) addM(ans,query(2*o,L,m));
	if(qR>m) addM(ans,query(2*o+1,m+1,R));
	return ans;
  }
  void pushdown(int o,int L,int R){
	int lc=2*o,rc=lc+1,M=L+(R-L)/2;
	LL &mo=mulv[o],&ao=addv[o];
	assert(L<R);
	if(mo!=1){
	  mulM(addv[lc],mo),mulM(addv[rc],mo);
	  mulM(sum[lc],mo),mulM(addv[rc],mo);
	  mo=1;
	}
	if(ao!=o){
	  addM(addv[lc],ao),addM(addv[rc],ao);
	  addM(sum[lc],_mulM(M-L+1,ao));addM(sum[rc],_mulM(R-M,ao));
	  ao=0;
	}
  }
  void update(int o,int L,int R,int op,T v){
	if(qL<=L&&R<=qR){
	  if(op==2)
		addM(addv[o],v),addM(sum[o],_mulM(R-L+1,v));
	  else
		mulM(addv[o],v),mulM(sum[o],v),mulM(mulv[o],v);
	  return;
	}
	int m=L+(R-L)/2,lc=2*o,rc=lc+1;
	pushdown(o,L,R);
	if(qL<=m) update(2*o,L,m,op,v);
	if(qR>m) update(2*o+1,m+1,R,op,v);
	sum[o]= _addM(sum[lc],sum[rc]);
  }
};
const int NN=1e5+8;
IntervalTree<LL,NN*3> tree;
LL A[NN];
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  int N,M;
  cin>>N>>MOD;
  for(int i=1;i<=N;i++) cin>>A[i],A[i]%=MOD;
  tree.build(1,1,N,A);
  cin>>M;
  for(int i=0,o,v;i<M;i++){
	cin>>o>>tree.qL>>tree.qR;
	if(o!=3)
	  cin>>v,tree.update(1,1,N,o,v);
	else
	  cout<<tree.query(1,1,N)<<endl;
  }
  return 0;
}
