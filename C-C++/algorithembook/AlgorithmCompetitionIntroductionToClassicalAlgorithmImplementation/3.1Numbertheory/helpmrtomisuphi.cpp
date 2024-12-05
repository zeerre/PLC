#include<bits/stdc++.h>
using namespace std;

#define _for(i,a,b) for(int i=(a);i<(b);++i)
#define _rep(i,a,b) for(int i=(a);i<=(b);++i)

typedef long long LL;
const LL MOD=1e8+7;
const int MAXM=1e7+4,MAXP=MAXM+4;
LL PF[MAXM+4];
bool isPrime[MAXP];
vector<int >primes;
void sieve(){
  fill_n(isPrime,MAXP,true);
  _for(i,2,MAXP) if(isPrime[i]){
	LL j=i;
	for(j*=i;j<MAXP;j+=i) isPrime[j]=false;
	primes.push_back(i);
  }
}
void init(){
  sieve();
  PF[1]=1,PF[2]=1;
  _rep(n,3,MAXM){
	if(isPrime[n])
	  PF[n]=(n-1)*PF[n-1];
	else
	  PF[n]=n*PF[n-1];
	PF[n]%=MOD;
  }
}
int main(){
  init();
  for(LL N,M;scanf("%lld%lld",&N,&M)==2 && N && M;){
	LL ans=1;
	_rep(i,M+1,N) ans=(ans*i)%MOD;
	ans=(ans*PF[M]-1)%MOD;
	printf("%lld\n",ans);
  }
  return 0;
}
