#include<bits/stdc++.h>
using namespace std;
const int maxn=50*50+10,INF=1e9;
struct Edge{
  int from,to,cap,flow;
};
bool operator<(const Edge& a,const Edge& b){
  return a.from<b.from || (a.from==b.from && a.to<b.to);
}
struct Dinic{
  int n,m,s,t;
  vector<Edge> edges;
  vector<int> G[maxn];
  bool vis[maxn];
  int d[maxn];
  int cur[maxn];
  void init(int n){
	for(int i=0;i<n;i++) G[i].clear();
	edges.clear();
  }
  void AddEdge(int from,int to,int cap){
	edges.push_back((Edge){from,to,cap,0});
	edges.push_back((Edge){to,from,0,0});
	m=edges.size(),G[from].push_back(m-2),G[to].push_back(m-1);
  }
  bool BFS(){
	memset(vis,0,sizeof(vis));
	queue<int> Q;
	Q.push(s),vis[s]=1,d[s]=0;
	while(!Q.empty()){
	  int x=Q.front();
	  Q.pop();
	  for(size_t i=0;i<G[x].size();i++){
		Edge& e=edges[G[x][i]];
		if(!vis[e.to] && e.cap>e.flow)
		  vis[e.to]=1,d[e.to]=d[x]+1,Q.push(e.to);
	  }
	}
	return vis[t];
  }
  int DFS(int x,int a){
	if(x==t || a==0) return a;
	int flow=0,f;
	for(int& i=cur[x];(size_t)i<G[x].size();i++){
	  Edge& e=edges[G[x][i]];
	  if(d[x]+1==d[e.to] && (f=DFS(e.to,min(a,e.cap-e.flow)))>0){
		e.flow+=f,edges[G[x][i]^1].flow-=f;
		flow+=f,a-=f;
		if(a==0) break;
	  }
	}
	return flow;
  }
  int Maxflow(int s,int t){
	this->s=s,this->t=t;
	int flow=0;
	while(BFS()) memset(cur,0,sizeof(cur)),flow+=DFS(s,INF);
	return flow;
  }
};
Dinic g;
int w,h;
char pool[99][99];
inline int ID(int i,int j){return i*w+j;}
int main(){
  int T,d,f,b;
  scanf("%d",&T);
  while(T--){
	scanf("%d%d%d%d%d",&w,&h,&d,&f,&b);
	for(int i=0;i<h;i++) scanf("%s",pool[i]);
	int cost=0;
	for(int i=0;i<h;i++){
	  if(pool[i][0]=='.') pool[i][0]='#',cost+=f;
	  if(pool[i][w-1]=='.') pool[i][w-1]='#',cost+=f;
	}
	for(int i=0;i<w;i++){
	  if(pool[0][i]=='.') pool[0][i]='#',cost+=f;
	  if(pool[h-1][i]=='.') pool[h-1][i]='#',cost+=f;
	}
	g.init(h*w+2);
	for(int i=0;i<h;i++)
	  for(int j=0;j<w;j++){
		if(pool[i][j]=='#'){
		  int cap=INF;
		  if(i!=0 && i!=h-1 && j!=0 && j!=w-1) cap=d;
		  g.AddEdge(h*w,ID(i,j),cap);
		}else{
		  g.AddEdge(ID(i,j),h*w+1,f);
		}
		if(i>0) g.AddEdge(ID(i,j),ID(i-1,j),b);
		if(i<h-1) g.AddEdge(ID(i,j),ID(i+1,j),b);
		if(j>0) g.AddEdge(ID(i,j),ID(i,j-1),b);
		if(j<w-1) g.AddEdge(ID(i,j),ID(i,j+1),b);
	  }
	printf("%d\n",cost+g.Maxflow(h*w,h*w+1));
  }
  return 0;
}
