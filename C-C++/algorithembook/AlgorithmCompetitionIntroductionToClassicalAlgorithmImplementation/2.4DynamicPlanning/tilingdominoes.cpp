#include<bits/stdc++.h>
using namespace std;

int n,m,cur;
const int maxn=15;
typedef long long LL;
LL d[2][1<<maxn],memo[maxn*maxn][maxn*maxn];
void up(int a,int b){
  if(b&(1<<m)) d[cur][b^(1<<m)]+=d[1-cur][a];
}
LL solve(int n,int m){
  memset(d,0,sizeof(d));
  cur=0;
  d[0][(1<<m)-1]=1;
  for(int i=0;i<n;i++)
	for(int j=0;j<m;j++){
	  cur^=1;
	  memset(d[cur],0,sizeof(d[cur]));
	  for(int k=0;k<(1<<m);k++){
		up(k,k<<1);
		if(i&&!(k&(1<<m-1))) up(k,(k<<1)^(1<<m)^1);
		if(j&&!(k&1)) up(k,(k<<1)^3);
	  }
	}
  return d[cur][(1<<m)-1];
}
int main(){
  memset(memo,-1,sizeof(memo));
  while(scanf("%d%d",&n,&m)==2){
	if(n<m) swap(n,m);
	if(memo[n][m]<0) memo[n][m]=solve(n,m);
	printf("%lld\n",memo[n][m]);
  }
  return 0;
}
