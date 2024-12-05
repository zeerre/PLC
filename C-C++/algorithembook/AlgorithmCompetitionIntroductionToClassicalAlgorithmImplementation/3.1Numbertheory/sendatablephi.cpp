#include<bits/stdc++.h>
const int NN=50000;
int Phi[NN+1],PhiS[NN+1];
void phi_table(int n){
  Phi[1]=0;
  for(int i=2;i<=n;i++){
	if(Phi[i]) continue;
	for(int j=i;j<=n;j+=i){
	  int &pj=Phi[j];
	  if(pj==0) pj=j;
	  pj=pj/i*(i-1);
	}
  }
}
int main(){
  phi_table(NN);
  PhiS[0]=0;
  for(int i=1;i<=NN;i++) PhiS[i]=PhiS[i-1]+Phi[i];
  for(int n;scanf("%d",&n)==1 && n;) printf("%d\n",2*PhiS[n]+1);
  return 0;
}
