#include<bits/stdc++.h>
using namespace std;
#define _for(i,a,b) for(int i=(a);i<(b);++i)
#define _rep(i,a,b) for(int i=(a);i<=(int)(b);++i)
typedef long long LL;
const int MAXC=100+4,INF=1e9;
int G[MAXC][MAXC];

int main(){
  for(int kase=1,C,S,Q,c1,c2,d;
	  scanf("%d%d%d",&C,&S,&Q)==3 && C;kase++){
	if(kase>1) puts("");
	printf("Case #%d\n",kase);
	_for(i,0,C) _for(j,0,C) G[i][j]=i==j?0:INF;
	_for(i,0,S){
	  scanf("%d%d%d",&c1,&c2,&d),--c1,--c2;
	  G[c1][c2]=min(G[c1][c2],d),G[c2][c1]=G[c1][c2];
	}
	_for(k,0,C) _for(i,0,C) _for(j,0,C){
	  if(G[i][k]!=INF && G[k][j]!=INF)
		G[i][j]=min(G[i][j],max(G[i][k],G[k][j]));
	}
	_for(i,0,Q){
	  scanf("%d%d",&c1,&c2),--c1,--c2;
	  int ans=G[c1][c2];
	  if(ans==INF) puts("no path");
	  else printf("%d\n",ans);
	}
  }
  return 0;
}
