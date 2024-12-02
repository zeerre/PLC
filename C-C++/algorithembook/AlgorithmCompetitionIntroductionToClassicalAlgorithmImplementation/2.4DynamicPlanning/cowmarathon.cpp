#include<bits/stdc++.h>

using namespace std;
const int MAXN=1e6+4;
struct Edge{
  Edge(int _v,int _w):v(_v),w(_w){}
  int v,w;
};
int N,M,ans;
vector<Edge> G[MAXN];
int D[MAXN];
void dfs(int u,int fa){
  int &d=D[u],dl=0;
  d=0;
  for(size_t i=0;i<G[u].size();i++){
	const Edge& e=G[u][i];
	if(e.v==fa) continue;
	dfs(e.v,u);
	int nd=e.w+D[e.v];
	if(nd>=d)
	  dl=d,d=nd;
	else if(nd>dl)
	  dl=nd;
  }
  ans=max(ans,d+dl);
}
int main(){
  scanf("%d %d",&N,&M);
  char S[8];
  for(int i=1,u,v,w;i<=M;i++){
	G[u].push_back(Edge(v,w)),G[v].push_back(Edge(u,w));
  }
  ans=-1;
  dfs(1,-1);
  printf("%d\n",ans);
  return 0;
}
