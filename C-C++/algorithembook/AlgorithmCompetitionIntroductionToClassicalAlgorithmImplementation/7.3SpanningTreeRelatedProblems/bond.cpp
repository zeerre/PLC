#include<bits/stdc++.h>
using namespace std;

#define _for(i,a,b) for(int i=(a);i<(int)(b);++i)
const int MAXN=50000+4;
struct Edge{
  int u,v,w;
  Edge(int _u=0,int _v=0,int _w=0):u(_u),v(_v),w(_w){}
  bool operator<(const Edge& e) const {
	return w<e.w;
  }
};
int N,M;
vector<Edge> G[MAXN];
int L,Tin[MAXN],Tout[MAXN],UP[MAXN][20],MaxW[MAXN][20],timer;
bool isAncestor(int u,int v){return Tin[u]<=Tin[v] && Tout[u]>=Tout[v];}
void dfs(int u,int fa,int w){
  Tin[u]= ++ timer,UP[u][0]=fa,MaxW[u][0]=w;
  for(int i=1;i<=L;i++){
	int ui=UP[u][i-1];
	UP[u][i]=UP[ui][i-1];
	MaxW[u][i]=max(MaxW[u][i-1],MaxW[ui][i-1]);
  }
  _for(i,0,G[u].size()){
	const Edge& e=G[u][i];
	if(e.v!=fa) dfs(e.v,u,e.w);
  }
  Tout[u]= ++timer;
}
int LCA(int u,int v){
  if(isAncestor(u,v)) return u;
  if(isAncestor(v,u)) return v;
  for(int i=L;i>=0;--i) if(!isAncestor(UP[u][i],v)) u=UP[u][i];
  return UP[u][0];
}
int find_maxw(int u,int v){
  if(u==v) return 0;
  assert(isAncestor(u,v));
  int w=0;
  for(int i=L;i>=0;--i)
	if(!isAncestor(UP[v][i],u) && UP[v][i]!=u)
	  w=max(w,MaxW[v][i]),v=UP[v][i];
  assert(UP[v][0]==u);
  return max(w,MaxW[v][0]);
}
int PA[MAXN];
int find_pa(int i){
  return PA[i]==i ? i:(PA[i]=find_pa(PA[i]));
}
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  vector<Edge> es;
  for(int kase=0,Q;cin>>N>>M;kase++){
	L=ceil(log2(N));
	if(kase) puts("");
	es.clear();
	Edge e;
	_for(i,0,M) cin>>e.u>>e.v>>e.w,es.push_back(e);
	sort(es.begin(),es.end());
	for(int i=0;i<=N;i++) PA[i]=i,G[i].clear();
	_for(i,0,es.size()){
	  const Edge& e=es[i];
	  int u=e.u,v=e.v,pu=find_pa(u),pv=find_pa(v);
	  if(pu!=pv){
		PA[pv]=pu;
		G[u].push_back(Edge(u,v,e.w)),G[v].push_back(Edge(v,u,e.w));
	  }
	}
	timer=0,dfs(1,1,0);
	cin>>Q;
	for(int i=0,s,t;i<Q;i++){
	  cin>>s>>t;
	  int l=LCA(s,t);
	  assert(s!=t);
	  printf("%d\n",max(find_maxw(l,s),find_maxw(1,t)));
	}
  }
  return 0;
}
