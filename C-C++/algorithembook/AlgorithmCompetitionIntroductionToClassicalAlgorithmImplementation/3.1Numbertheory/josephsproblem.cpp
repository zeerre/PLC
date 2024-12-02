#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
int main(){
  for(int N,K;scanf("%d%d",&N,&K)==2;){
	LL ans=0;
	if(N>K) ans=(LL)(N-K)*K,N=K-1;
	for(int i=1,j;i<=N;i=j+1){
	  j=min(K/(K/i),N);
	  ans+=(LL)(K%i+K%j)*(LL)(j-i+1)/2;
	}
	printf("%lld\n",ans);
  }
  return 0;
}
