#include<bits/stdc++.h>
using namespace std;

#define _for(i,a,b) for(int i=(a);i<(b);++i)
#define _rep(i,a,b) for(int i=(a);i<=(b);++i)

typedef long long LL;

template<typename T,size_t SZ>
struct BIT{
  T C[SZ];
  size_t N;
  inline void init(size_t sz){
	N=sz;
	assert(N+1<SZ);
	fill_n(C,N+1,0);
  }
  inline int lowbit(int x){ return x& -x;}
  inline T sum(size_t i){
	T ans=0;
	while(i>0) ans+=C[i],i-=lowbit(i);
	return ans;
  }
  inline void add(size_t i,const T& v){
	while(i<=N) C[i] +=v,i+=lowbit(i);
  }
};
const int MAXN =20000+4,MAXA=1e5;
int A[MAXN],C[MAXN],D[MAXN];
int main(){
  int T,N;
  ios::sync_with_stdio(false),cin.tie(0);
  cin>>T;
  BIT<int ,MAXA+4> X;
  while(T--){
	cin>>N,fill_n(C,N+1,0);
	X.init(MAXA);
	_rep(i,1,N) cin>>A[i],C[i]=X.sum(A[i]-1),X.add(A[i],1);
	X.init(MAXA);
	LL ans=0;
	for(int i=N;i>=1;i--){
	  int d=X.sum(A[i]-1);
	  X.add(A[i],1);
	  if(i<N&& i>1) ans+=C[i]*(N-i-d)+(i-1-C[i])*d;
	}
	cout<<ans<<endl;
  }
  return 0;
}
