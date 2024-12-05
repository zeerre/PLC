#include<bits/stdc++.h>
using namespace std;
#define _for(i,a,b) for(int i=(a);i<(b);++i)
typedef long long LL;
int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
const int MAXA=2000+4;
LL Phi[MAXA];
void init(){
  fill_n(Phi,MAXA,0);
  Phi[1]=1;
  _for(i,2,MAXA) if(Phi[i]==0){
	for(LL j=i;j<MAXA;j+=i){
	  LL& pj=Phi[j];
	  if(pj==0) pj=j;
	  pj=pj/i*(i-1);
	}
  }
}
int main(){
  init();
  for(int A,B;scanf("%d%d",&A,&B)==2 && A && B;){
	LL P=0;
	for(int x=1;x<=A;x++){
	  int k=B/x;
	  P+=k*Phi[x];
	  for(int y=k*x+1;y<=B;y++) if(gcd(x,y)==1) P++;
	}
	double ans=4*(P+1);
	LL N = 4LL * A *B+2LL*A+2LL*B;
	printf("%.7f\n",ans/N);
  }
  return 0;
}
