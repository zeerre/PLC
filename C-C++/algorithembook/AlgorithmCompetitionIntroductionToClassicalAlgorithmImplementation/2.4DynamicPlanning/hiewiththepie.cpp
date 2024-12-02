#include<bits/stdc++.h>
using namespace std;

const int NN=10+1,INF=0x3f3f3f3f;
int N,D[NN][NN],F[NN][1<<12];
inline void floyd(){
  for(int k=0;k<=N;k++)
	for(int i=0;i<=N;i++)
	  for(int j=0;j<=N;j++)
		D[i][j]=min(D[i][k]+D[k][j],D[i][j]);
}
int dp(int i,int s){
  int &f=F[i][s];
  if(s==0) return f=D[i][0];
  if(f!=-1) return f;
  f=INF;
  for(int j=0;j<=N;j++){
	if(s&(1<<j))
	  f=min(f,D[i][j]+dp(j,s^(1<<j)));
  }
  return f;
}
int main(){
  while(scanf("%d",&N)==1&&N){
	memset(F,-1,sizeof(F)),memset(D,0x3f,sizeof(D));
	for(int i=0;i<=N;i++)
	  for(int j=0;j<=N;j++) scanf("%d",&D[i][j]);
	floyd();
	printf("%d\n",dp(0,(1<<(N+1))-1));
  }
  return 0;
}
