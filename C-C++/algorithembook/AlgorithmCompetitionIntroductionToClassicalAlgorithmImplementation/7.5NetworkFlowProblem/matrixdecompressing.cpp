#include<bits/stdc++.h>
using namespace std;
const int NN =50+5,INF=1e9;
struct Edge{
  int from,to,cap,flow;
  Edge(int u,int v,int c,int f):from(u),to(v),cap(c),flow(f){}
};
struct EdmondsKarp{
  int n,m;
  vector<Edge> edges;
  vector<int > G[NN];
  int a[NN];
  int p[NN];
  void init(int n){
	for(int i=0;i<n;i++) G[i].clear();
	edges.clear();
  }
  void AddEdge(int from,int to,int cap){
	edges.push_back(Edge(from,to,cap,0));
	edges.push_back(Edge(to,from,0,0));
	m=edges.size();
	G[from].push_back(m-2),G[to].push_back(m-1);
  }
  int Maxflow(int s,int t){
	int flow=0;
	for(;;){
	  memset(a,0,sizeof(a));
	  queue<int> Q;
	  Q.push(s);
	  a[s]=INF;
	  while(!Q.empty()){
		int x=Q.front();Q.pop();
		for(size_t i=0;i<G[x].size();i++){
		  Edge& e=edges[G[x][i]];
		  if(!a[e.to] && e.cap>e.flow){
			p[e.to]=G[x][i];
			a[e.to]=min(a[x],e.cap-e.flow);
			Q.push(e.to);
		  }
		}
		if(a[t]) break;
	  }
	  if(!a[t]) break;
	  for(int u=t;u!=s;u=edges[p[u]].from){
		edges[p[u]].flow+=a[t];
		edges[p[u]^1].flow-=a[t];
	  }
	  flow+=a[t];
	}
	return flow;
  }
};
EdmondsKarp g;
int no[NN][NN];
int main(){
  int T;scanf("%d",&T);
  for(int kase=1,R,C,v;kase<=T;kase++){
	scanf("%d%d",&R,&C);
	g.init(R+C+2);
	for(int i=1,last=0;i<=R;i++){
	  scanf("%d",&v);
	  g.AddEdge(0,i,v-last-C);
	  last=v;
	}
	for(int i=1,last=0;i<=C;i++){
	  scanf("%d",&v);
	  g.AddEdge(R+i,R+C+1,v-last-R);
	  last=v;
	}
	for(int i=1;i<=R;i++)
	  for(int j=1;j<=C;j++)
		g.AddEdge(i,R+j,19),no[i][j]=g.edges.size()-2;
	g.Maxflow(0,R+C+1);
	printf("Matrix %d\n",kase);
	for(int i=1;i<=R;i++){
	  for(int j=1;j<=C;j++)
		printf("%d ",g.edges[no[i][j]].flow+1);
	  puts("");
	}
	puts("");
  }
  return 0;
}
