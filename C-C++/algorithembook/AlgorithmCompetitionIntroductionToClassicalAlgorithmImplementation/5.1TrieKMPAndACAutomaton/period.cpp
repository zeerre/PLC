#include<bits/stdc++.h>

using namespace std;
const int NN=1e6+4;
char P[NN];
int F[NN];
int main(){
  for(int n,kase=1;scanf("%d",&n)==1 && n;kase++){
	scanf("%s",P);
	F[0]=0,F[1]=0;
	for(int i=1;i<n;i++){
	  int j=F[i];
	  while(j && P[i]!=P[j]) j=F[j];
	  F[i+1]=(P[i]==P[j]?j+1:0);
	}
	printf("Test case #%d\n",kase);
	for(int i=2;i<=n;i++)
	  if(F[i]>0 && i%(i-F[i])==0) printf("%d %d\n",i,i/(i-F[i]));
	printf("\n");
  }
  return 0;
}
