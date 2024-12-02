#include<bits/stdc++.h>
using namespace std;

#define _for(i,a,b) for(int i=(a);i<(b);++i)
typedef long long LL;
const int MAXN=20+4;
int N,R;
double P[MAXN],P1[MAXN],B;
int main(){
  for(int  t=1;scanf("%d%d",&N,&R)==2 && N;t++){
	printf("Case %d: \n",t);
	B=0;
	_for(i,0,N) P1[i]=0,scanf("%lf",&(P[i]));
	_for(s,0,(1<<N)){
	  int r=0,sc=s;
	  while(sc) r++,sc=sc&(sc-1);
	  if(R!=r) continue;
	  double p=1;
	  _for(i,0,N) p*=(s&(1<<i))?P[i]:1-P[i];
	  B+=p;
	  _for(i,0,N) if(s&(1<<i)) P1[i]+=p;
	}
	_for(i,0,N) printf("%.6lf\n",P1[i]/B);
  }
  return 0;
}
