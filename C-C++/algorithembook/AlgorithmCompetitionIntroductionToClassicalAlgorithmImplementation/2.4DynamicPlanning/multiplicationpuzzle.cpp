#include<bits/stdc++.h>
using namespace std;

const int NN=100+10;
int N,A[NN],F[NN][NN];
int main(){
  scanf("%d",&N);
  memset(F,0x3f,sizeof F);
  for(int i=1;i<=N;i++) scanf("%d",A+1);
  for(int len=2;len<=N;len++)
	for(int i=1;i+len-1<=N;i++){
	  F[i][i]=F[i][i+1]=0;
	  for(int j=i+len-1,k=i;k<j;k++)
		F[i][j]=min(F[i][k]+F[k][j]+A[i]*A[k]*A[j],F[i][j]);
	}
  printf("%d",F[1][N]);
  return 0;
}
