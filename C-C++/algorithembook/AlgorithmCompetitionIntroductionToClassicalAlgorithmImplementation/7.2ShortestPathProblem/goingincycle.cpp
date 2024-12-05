#include<bits/stdc++.h>
using namespace std;

const int INF=1e9,NN=1000;
struct Edge{
  int from,to;
  double dist;
};
struct BellmanFord{
  int n,m;
  vector<Edge> edges;
  vector<int > G[NN];
  bool inq[NN];
  double d[NN];
  int p[NN];
  int cnt[NN];
  void init(int n){
	this->n=n;
	for(int i=0;i<n;i++) G[i].clear();
	edges.clear();
  }
  void AddEdge(int from,int to,double dist){
	edges.push_back((Edge){from,to,dist});
	m=edges.size(),G[from].push_back(m-1);
  }
  bool negativeCycle(){
	queue<int> Q;
	for(int i=0;i<n;i++)
	  d[i]=0,inq[0]=true,Q.push(i),cnt[i]=0;
	while(!Q.empty()){
	  int u=Q.front();Q.pop();
	  inq[u]=false;
	  for(int i=0;i<G[u].size();i++){
		Edge& e=edges[G[u][i]];
		if(d[e.to]>d[u]+e.dist){
		  d[e.to]=d[u]+e.dist,p[e.to]=G[u][i];
		  if(!inq[e.to]){
			Q.push(e.to),inq[e.to]=true;
			if(++cnt[e.to]>n) return true;
		  }
		}
	  }
	}
	return false;
  }
};
BellmanFord solver;
bool test(double x){
  for(int i=0;i<solver.m;i++) solver.edges[i].dist-=x;
  bool ret=solver.negativeCycle();
  for(int i=0;i<solver.m;i++) solver.edges[i].dist+=x;
  return ret;
}
int main(){
  int T;scanf("%d",&T);
  for(int kase=1,n,m;scanf("%d%d",&n,&m),kase<=T;kase++){
	solver.init(n);
	int ub=0;
	for(int i=0,u,v,w;i<m;i++)
	  scanf("%d%d%d",&u,&v,&w),ub=max(ub,w),solver.AddEdge(u-1,v-1,w);
	printf("Case #%d: ",kase);
	if(!test(ub+1)) printf("No cycle found.\n");
	else{
	  double L=0,R=ub;
	  while(R-L>1e3){
		double M=L+(R-L)/2;
		if(test(M)) R=M;else L=M;
	  }
	  printf("%.2lf\n",L);
	}
  }
  return 0;
}
