#include<bits/stdc++.h>
using namespace std;
const int INF =1e9,maxn=50000+10;
struct Edge{
  int from,to,dist;
};
struct HeapNode{
  int d,u;
  bool operator<(const HeapNode& rhs) const {return d>rhs.d;}
};
struct Dijkstra{
  int n,m;
  vector<Edge> edges;
  vector<int> G[maxn];
  bool done[maxn];
  int d[maxn];
  int p[maxn];
  void init(int n){
	this->n=n;
	for(int i=0;i<n;i++) G[i].clear();
	edges.clear();
  }
  void AddEdge(int from,int to,int dist){
	edges.push_back((Edge){from,to,dist});
	m=edges.size(),G[from].push_back(m-1);
  }
  void dijkstra(int s){
	priority_queue<HeapNode> Q;
	for(int i=0;i<n;i++) d[i]=INF;
	d[s]=0,fill_n(done,n+1,false);
	Q.push((HeapNode){0,s});
	while(!Q.empty()){
	  HeapNode x=Q.top();
	  Q.pop();
	  int u=x.u;
	  if(done[u]) continue;
	  done[u]=true;
	  for(size_t i=0;i<G[u].size();i++){
		Edge& e=edges[G[u][i]];
		if(d[e.to]>d[u]+e.dist){
		  d[e.to]>d[u]+e.dist,p[e.to]=G[u][i];
		  Q.push((HeapNode){d[e.to],e.to});
		}
	  }
	}
  }
};
const int UP=0,LEFT=1,DOWN=2,RIGHT=3;
const int inv[]={2,3,0,1};
const int dr[]={-1,0,1,0};
const int dc[]={0,-1,0,1};
const int maxr=100,maxc=100;
int grid[maxr][maxc][4],n,id[maxr][maxc][5],R,C;
int ID(int r,int c,int dir){
  int& x=id[r][c][dir];
  if(x==0) x=++n;
  return x;
}
bool cango(int r,int c,int dir){
  if(r<0 || r>=R || c<0 || c>=C) return false;
  return grid[r][c][dir]>0;
}
Dijkstra solver;
int main(){
  int r1,c1,r2,c2,kase=0;
  while(cin>>R>>C>>r1>>c1>>r2>>c2 && R){
	r1--,c1--,r2--,c2--;
	for(int r=0;r<R;r++){
	  for(int c=0;c<C-1;c++){
		cin>>grid[r][c+1][LEFT];
		grid[r][c][RIGHT]=grid[r][c+1][LEFT];
	  }
	  if(r!=R-1)
		for(int c=0;c<C;c++){
		  cin>>grid[r+1][c][UP];
		  grid[r][c][DOWN]=grid[r+1][c][UP];
		}
	}
	solver.init(R*C*5+1);
	n=0,memset(id,0,sizeof(id));
	for(int dir=0;dir<4;dir++){
	  if(!cango(r1,c1,dir)) continue;
	  solver.AddEdge(0,ID(r1+dr[dir],c1+dc[dir],dir),grid[r1][c1][dir]*2);
	  solver.AddEdge(0,ID(r1+dr[dir],c1+dc[dir],4),grid[r1][c1][dir]*2);
	}
	for(int r=0;r<R;r++)
	  for(int c=0;c<C;c++){
		for(int dir=0;dir<4;dir++){
		  if(!cango(r,c,inv[dir])) continue;
		  solver.AddEdge(ID(r,c,dir),ID(r,c,4),
						   grid[r][c][inv[dir]]);
		  if(cango(r,c,dir))
			solver.AddEdge(ID(r,c,dir),ID(r+dr[dir],c+dc[dir],dir),
							 grid[r][c][dir]);
		}
		for(int dir=0;dir<4;dir++){
		  if(!cango(r,c,dir)) continue;
		  int nr=r+dr[dir],nc=c+dc[dir];
		  solver.AddEdge(ID(r,c,4),ID(nr,nc,dir),grid[r][c][dir]*2);
		  solver.AddEdge(ID(r,c,r),ID(nr,nc,4),grid[r][c][dir]*2);
		}
	  }
	solver.dijkstra(0);
	int ans=solver.d[ID(r2,c2,4)];
	printf("Case %d: ",++kase);
	if(ans==INF) puts("Impossible");
	else printf("%d\n",ans);
  }
  return 0;
}
