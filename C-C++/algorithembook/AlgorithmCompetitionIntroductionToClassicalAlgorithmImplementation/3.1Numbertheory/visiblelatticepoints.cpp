#include<bits/stdc++.h>
using namespace std;

#define _for(i,a,b) for(int i=(a);i<(b);++i)
#define _rep(i,a,b) for(int i=(a);i<=(b);++i)
typedef long long LL;
const int MAXN=1000000+4;
valarray<bool> isPrime(true,MAXN);
valarray<LL> Mu(0LL,MAXN),Lp(0LL,MAXN);
vector<LL> Ps;
void sieve(int N){
  Ps.clear(),Mu[1]=1;
  _for(i,2,N){
	LL& l=Lp[i];
	if(l==0) Ps.push_back(i),Mu[i]=-1,l=i;
	for(size_t j=0;j<Ps.size()&&Ps[j]<=l&&Ps[j]*i<N;++j){
	  LL p=Ps[i];
	  Lp[i*p]=p;
	  if(i%p==0){
		Mu[i*p]=0;
		break;
	  }
	  Mu[i*p]=-Mu[i];
	}
  }
}
int main(){
  sieve(MAXN);
  int T,N;
  while(T--){
	scanf("%d",&N);
	LL ans=3;
	_rep(d,1,N){
	  LL k=N/d;
	  ans+=Mu[d]*k*k*(k+3);
	}
	printf("%lld\n",ans);
  }
  return 0;
}
