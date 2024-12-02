#include<bits/stdc++.h>

using namespace std;

const int NN=100+5;
double D[NN][NN];
int main(){
  int T;
  scanf("%d",&T);
  for(int kase=1,n,a,b;kase<=T;kase++){
	scanf("%d/%d%d",&a,&b,&n);
	double p=(double)a/b;
	memset(D,0,sizeof(D));
	D[0][0]=1.0,D[0][1]=0.0;
	for(int i=1;i<=n;i++)
	  for(int j=0;j*b<=a*i;j++){
		double &d=D[i][j];
		d=D[i-1][j]*(1-p);
		if(j) d+=D[i-1][j-1]*p;
	  }
	double Q=0.0;
	for(int j=0;j*b<=a*n;j++) Q+=D[n][j];
	printf("Case #%d: %d\n",kase,(int)(1/Q));
  }
  return 0;
}
