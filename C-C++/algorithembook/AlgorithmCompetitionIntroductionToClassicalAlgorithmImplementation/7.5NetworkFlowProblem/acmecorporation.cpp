#include<bits/stdc++.h>
using namespace std;
const int maxn=202+10,INF=1e9;
typedef long long LL;
struct Edge{
  int from,to,cap,flow,cost;
};
struct MCMF{
  int n,m,s,t;
  vector<Edge> edges;
  vector<int> G[maxn];
  int inq[maxn];
  int d[maxn];
  int p[maxn];
  int a[maxn];
  void init(int n){
	this->n=n;
	for(int i=0;i<n;i++) G[i].clear();
	edges.clear();
  }
  void AddEdge(int from,int to,int cap,int cost){
	edges.push_back((Edge){from,to,cap,0,cost});
	edges.push_back((Edge){to,from,0,0,-cost});
	m=edges.size();
	G[from].push_back(m-2);
	G[to].push_back(m-1);
  }
  bool BellmanFord(int a,int t,LL& ans){
	fill_n(inq,n+1,false),fill_n(d,n+1,INF);
	queue<int> Q;
	d[s]=0,inq[s]=1,p[s]=0,a[s]=INF,Q.push(s);
	while(!Q.empty()){
	  int u=Q.front();
	  Q.pop();
	  inq[u]=0;
	  for(size_t i=0;i<G[u].size();i++){
		Edge& e=edges[G[u][i]];
		if(e.cap>e.flow && d[e.to]>d[u]+e.cost){
		  d[e.to]=d[u]+e.cost,p[e.to]=G[u][i];
		  a[e.to]=min(a[u],e.cap-e.flow);
		  if(!inq[e.to]) Q.push(e.to),inq[e.to]=1;
		}
	  }
	}
	if(d[t]>0) return false;
	ans+=(LL)d[t]*(LL)a[t];
	int u=t;
	while(u!=s){
	  edges[p[u]].flow+=a[t],edges[p[u]^1].flow-=a[t];
	  u=edges[p[u]].from;
	}
	return true;
  }
  LL Mincost(int s,int t){
	LL cost=0;
	while(BellmanFord(s,t,cost))
	  ;
	return cost;
  }
};
MCMF g;
int main(){
  int T;
  scanf("%d",&T);
  for(int kase=1,M,store_cost;kase<=T;kase++){
	scanf("%d%d",&M,&store_cost);
	g.init(2*M+2);
	int source=0,sink=2*M+1;
	for(int i=1,make_cost,make_limit,price,sell_limit,max_store;i<=M;i++){
	  scanf("%d%d%d%d%d",&make_cost,&make_limit,&price,&sell_limit,&max_store);
	  g.AddEdge(source,i,make_limit,make_cost);
	  g.AddEdge(M+i,sink,sell_limit,-price);
	  for(int j=0;j<=max_store;j++)
		if(i+j<=M)
		  g.AddEdge(i,M+i+j,INF,store_cost*j);
	}
	printf("Case %d: %lld\n",kase,-g.Mincost(source,sink));
  }
  return 0;
}
