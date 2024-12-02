#include<bits/stdc++.h>
using namespace std;

const int NN=10004;
int D[NN],A[NN];
int main(){
  for(int n;scanf("%d",&n)==1&&n;){
	D[0]=0;
	for(int i=1;i<=n;i++){
	  int &a=A[i];
	  scanf("%d",&a);
	  D[i]=max(D[i-1]+a,a);
	}
	int ed_v=A[1],maxd=D[1],ed=1;
	for(int i=1;i<=n;i++)
	  if(D[i]>maxd) maxd=D[i],ed_v=A[i],ed=i;
	int st_v=A[ed];
	for(int i=ed,s=0;i>0&& s<maxd;i--) s+=A[i],st_v=A[i];
	if(maxd>=0) printf("%d %d %d\n",maxd,st_v,ed_v);
	else printf("%d %d %d\n",0,A[1],A[n]);
  }
  return 0;
}
