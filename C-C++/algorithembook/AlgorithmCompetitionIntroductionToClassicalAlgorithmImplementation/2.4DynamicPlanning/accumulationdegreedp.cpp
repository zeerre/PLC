#include<bits/stdc++.h>
using namespace std;

const int MAXN=2e5+4;
int N,F[MAXN],D[MAXN];
struct Edge{
  int v,w;
  Edge(int to=0,int _w=0):v(to),w(_w){}
};
vector<Edge>G[MAXN];
int dfs1(int u,int fa){
  int& d=D[u];
  d=0;
  for(size_t i=0;i<G[u].size();i++){
	const Edge& e=G[u][i];
	if(e.v==fa) continue;
	int c=e.w;
	if(G[e.v].size()>1) c=min(c,dfs1(e.v,u));
	d+=c;
  }
  return d;
}
void dfs2(int u,int fa){
  for(size_t i=0;i<G[u].size();i++){
	const Edge& e=G[u][i];
	if(e.v==fa) continue;
	if(G[u].size()==1)
	  F[e.v]=D[e.v]+e.w;
	else
	  F[e.v]=D[e.v]+min(e.w,F[u]-min(D[e.v],e.w));
	dfs2(e.v,u);
  }
}
int main(){
  int T;
  scanf("%d",&T);
  while(T--){
	scanf("%d",&N);
	fill_n(D,N+1,0);
	for(int i=0;i<=N;i++) G[i].clear();
	for(int i=1,x,y,z;i<N;i++){
	  scanf("%d%d%d",&x,&y,&z);
	  G[x].push_back(Edge(y,z)),G[y].push_back(Edge(x,z));
	}
	dfs1(1,-1);
	F[1]=D[1];
	dfs2(1,-1);
	int ans=*max_element(F+1,F+N+1);
	printf("%d\n",ans);
  }
  return 0;
}
