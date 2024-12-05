#include<bits/stdc++.h>
using namespace std;

#define _for(i,a,b) for(int i=(a);i<(b);++i)
typedef long long LL;
struct Edge{
  int from,to,cap,flow,cost;
  Edge(int u,int v,int c,int f,int co):
	from(u),to(v),cap(c),flow(f),cost(co){}
};
template <int maxn,int INF>
struct MCMF{
  int n,m;
  vector<Edge> edges;
  vector<int> G[maxn];
  bool inq[maxn];
  int d[maxn];
  int p[maxn];
  int a[maxn];
  void init(int n){
	this->n=n;
	for(int i=0;i<n;i++) G[i].clear();
	edges.clear();
  }
  void AddEdge(int from,int to,int cap,int cost){
	edges.push_back(Edge(from,to,cap,0,cost));
	edges.push_back(Edge(to,from,0,0,-cost));
	m=edges.size();
	G[from].push_back(m-2),G[to].push_back(m-1);
  }
  bool BellmanFord(int s,int t,int& flow,LL& ans){
	fill_n(d,n,INF),fill_n(inq,n,false);
	d[s]=0,inq[s]=true,p[s]=0,a[s]=INF;
	queue<int> Q;
	Q.push(s);
	while(!Q.empty()){
	  int u=Q.front();
	  Q.pop();
	  inq[u]=false;
	  for(size_t i=0;i<G[u].size();i++){
		Edge& e=edges[G[u][i]];
		if(e.cap>e.flow && d[e.to]>d[u]+e.cost){
		  d[e.to]=d[u]+e.cost,p[e.to]=G[u][i];
		  a[e.to]=min(a[u],e.cap-e.flow);
		  if(!inq[e.to]) Q.push(e.to),inq[e.to]=true;
		}
	  }
	}
	if(d[t]==INF) return false;
	flow+=a[t];
	ans+=(LL)d[t]*(LL)a[t];
	int u=t;
	while(u!=s){
	  edges[p[u]].flow+=a[t],edges[p[u]^1].flow-=a[t];
	  u=edges[p[u]].from;
	}
	return true;
  }
  LL Mincost(int s,int t,int& flow){
	LL ans=0;
	flow=0;
	while(BellmanFord(s,t,flow,ans))
	  ;
	return ans;
  }
};
const int MAXV=1000+4,INF=0x7f7f7f7f;
MCMF<2*MAXV+2,INF> solver;
int main(){
  for(int a,b,c,V,E,flow;cin>>V>>E;){
	solver.init(2*V+2);
	int S=1,T=V+V;
	solver.AddEdge(1,1+V,2,0);
	_for(v,2,V) solver.AddEdge(v,v+V,1,0);
	solver.AddEdge(V,V+V,2,0);
	_for(i,0,E) cin>>a>>b>>c,solver.AddEdge(a+V,b,1,c);
	LL ans=solver.Mincost(S,T,flow);
	assert(flow==2);
	cout<<ans<<endl;
  }
  return 0;
}
