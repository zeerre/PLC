#include<bits/stdc++.h>

using namespace std;
const int MAXN=40000+4;
int N,L,Tin[MAXN],Tout[MAXN],UP[MAXN][18],timer;
struct Edge{
  int v,k;
  Edge(int _v,int _k):v(_v),k(_k){}
};
vector<Edge> G[MAXN];
int Dist[MAXN],D[MAXN];
void dfs(int u,int fa){
  Tin[u]= ++timer,UP[u][0]=fa;
  if(u) D[u]=D[fa]+1;
  for(int i=1;i<L;i++) UP[u][i]=UP[UP[u][i-1]][i-1];
  for(size_t i=0;i<G[u].size();i++){
	const Edge& e=G[u][i];
	if(e.v!=fa) Dist[e.v]=Dist[u]+e.k,dfs(e.v,u);
  }
  Tout[u]= ++timer;
}
bool isAncestor(int u,int v){return Tin[u]<=Tin[v] && Tout[u]>=Tout[v];}
int LCA(int u,int v){
  if(D[u]>D[v]) return LCA(v,u);
  if(isAncestor(u,v)) return u;
  for(int i=L;i>=0;--i)
	if(!isAncestor(UP[u][i],v)) u=UP[u][i];
  return UP[u][0];
}
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  int T,M,u,v,k;
  L=ceil(log2(N));
  cin>>T;
  while(T--){
	cin>>N>>M;
	for(int i=0;i<N;i++) G[i].clear();
	for(int i=0;i<N-1;i++) {
	  cin>>u>>v>>k,u--,v--;
	  G[u].push_back(Edge(v,k)),G[v].push_back(Edge(u,k));
	}
	memset(UP,0,sizeof(UP));
	Dist[0]=0,D[0]=0;
	dfs(0,0);
	for(int i=0;i<M;i++){
	  cin>>u>>v,u--,v--;
	  cout<<Dist[u]+Dist[v]-2*Dist[LCA(u,v)]<<endl;
	}
  }
  return 0;
}
