#include<bits/stdc++.h>

using namespace std;
const int MOD=1e8+1;
int B[13],St[377],F[13][377];
int main(){
  int S=1<<12,k=0;
  for(int i=0;i<(1<<12);i++)
	if(!(i&(i<<1))) St[k++]=i;
  St[k]=S;
  int M,N,t;
  scanf("%d%d",&M,&N);
  for(int i=0;i<M;i++)
	for(int j=0;j<N;j++)
	  scanf("%d",&t),B[i]=(B[i]<<1)|!t;
  S=1<<N;
  for(int i=0;St[i]<S;i++)
	if(!(B[0]&St[i])) F[0][i]=1;
  for(int r=1;r<M;r++){
	for(int i=0;St[i]<S;i++){
	  if(B[r-1]&St[i]) continue;
	  for(int ri=0;St[ri]<S;ri++)
		if(!(B[r]&St[ri]) && !(St[i]&St[ri]))
		  (F[r][ri]+=F[r-1][i])%=MOD;
	}
  }
  int r=M-1,ans=F[r][0];
  for(int i=1;St[i]<S;i++)
	ans=(ans+F[r][i]) %MOD;
  printf("%d\n",ans);
  return 0;
}
