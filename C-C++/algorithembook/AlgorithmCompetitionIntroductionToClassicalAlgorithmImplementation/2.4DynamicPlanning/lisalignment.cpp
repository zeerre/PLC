#include<bits/stdc++.h>
using namespace std;
const int NN =1000+4;
int F[NN],G[NN];
float A[NN];
int main(){
  for(int n,ans=0;scanf("%d",&n)==1;){
	fill_n(F,n,0),fill_n(G,n,0);
	for(int i=1;i<=n;i++) scanf("%f",&A[i]);
	for(int i=1;i<=n;i++){
	  F[i]=1;
	  for(int j=i-1;j>=1;j--)
		if(A[i]>A[j]&&F[i]<F[j]+1) F[i]=F[j]+1;
	}
	for(int i=n;i>=1;i--){
	  G[i]=1;
	  for(int j=i+1;j<=n;j++)
		if(A[i]>A[j]&& G[i]<G[j]+1) G[i]=G[j]+1;
	}
	for(int i=1;i<=n;i++)
	  for(int j=i+1;j<=n;j++) ans=max(ans,F[i]+G[j]);
	printf("result:%d\n",n-ans);
  }
  return 0;
}
