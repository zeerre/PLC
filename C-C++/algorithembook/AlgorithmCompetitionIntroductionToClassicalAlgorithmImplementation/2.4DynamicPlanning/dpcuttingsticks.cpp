#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN=50+2,INF=0x7f7f7f7f;
int L,N,C[MAXN],D[MAXN][MAXN];
int dp(int l,int r){
  assert(l<r);
  int &d=D[l][r];
  if(d!=-1) return d;
  if(l+1==r) return d=0;
  d=INF;
  for(int i=l+1;i<r;i++)
	d=min(C[r]-C[l]+dp(l,i)+dp(i,r),d);
  return d;
}
int main(){
  while(scanf("%d",&L)==1&&L){
	scanf("%d",&N);
	C[0]=0,C[N+1]=L;
	for(int i=1;i<=N;i++) scanf("%d",&(C[i]));
	memset(D,-1,sizeof(D));
	int ans=dp(0,N+1);
	printf("The min cutting is :%d.\n",ans);
  }
  return 0;
}
