#include<bits/stdc++.h>
using namespace std;
#define _for(i,a,b) for(int i=(a);i<(b);++i)
#define _rep(i,a,b) for(int i=(a);i<=(b);++i)
typedef long long LL;
const int MOD=1000007,MAXC=400+4;
int M,N,K;
LL C[MAXC][MAXC];
void init(){
  C[1][0]=C[1][1]=1;
  for(int n=2;n<MAXC;n++){
	C[n][0]=1;
	for(int k=1;k<=n;k++)
	  C[n][k]=(C[n-1][k-1]+C[n-1][k])%MOD;
  }
}
inline LL CK(int m,int n){return C[m*n][K];}
LL solve(){
  if(K<2|| K>M*N) return 0;
  LL S=C[M*N][K];
  S+=(4*CK(M-1,N-1)+CK(M-2,N)+CK(M,N-2))%MOD;
  S-=(2*CK(M-2,N-1)+2*CK(M-1,N-2))%MOD;
  S+=CK(M-2,N-2);
  for(int b=1;b<16;b++){
	int cnt=0,m=M,n=N;
	if(b&8) --m,++cnt;
	if(b&4) --m,++cnt;
	if(b&2) --n,++cnt;
	if(b&1) --n,++cnt;
	LL x=C[m*n][K];
	if(cnt%2) x=-x;
	S=(S+MOD+x) % MOD;
  }
  return S;
}
int main(){
  int T;
  init();
  ios::sync_with_stdio(false),cin.tie(0);
  cin>>T;
  for(int t=1;t<=T;t++){
	cin>>M>>N>>K;
	printf("Case %d: %lld\n",t,solve());
  }
  return 0;
}
