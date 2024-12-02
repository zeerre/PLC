#include<bits/stdc++.h>
using namespace std;

const int INF=1e9,NN=500+10,MM=2700+10;
struct Edge{
  int to,dist;
};
struct BellmanFord{
  int n,m,head[NN],next[MM];
  Edge edges[MM];
  bool inq[NN];
  int d[NN];
  int cnt[NN];
  void init(int n){this->n=n,m=0,fill_n(head,n+1,-1);}
  void AddEdge(int from,int to,int dist){
	next[m]=head[from],head[from]=m,edges[m++]=(Edge){to,dist};
  }
  bool negativeCycle(){
	queue<int> Q;
	fill_n(inq,n+1,false),fill_n(cnt,n+1,0);
	for(int i=0;i<n;i++) d[i]=0,Q.push(i);
	while(!Q.empty()){
	  int u=Q.front();
	  Q.pop(),inq[u]=false;
	  for(int i=head[u];i!=-1;i=next[i]){
		Edge& e=edges[i];
		if(d[e.to]>d[u]+e.dist){
		  d[e.to]=d[u]+e.dist;
		  if(inq[e.to]) continue;
		  Q.push(e.to),inq[e.to]=true;
		  if(++cnt[e.to]>n) return true;
		}
	  }
	}
	return false;
  }
};
BellmanFord solver;
bool test(int x){
  for(int i=0;i<solver.m;i++) solver.edges[i].dist-=x;
  bool ret=solver.negativeCycle();
  for(int i=0;i<solver.m;i++) solver.edges[i].dist+=x;
  return !ret;
}
int main(){
  for(int n,m;scanf("%d%d",&n,&m)==2;){
	solver.init(n);
	int ub=0;
	for(int i=0,u,v,d;i<m;i++){
	  scanf("%d%d%d",&u,&v,&d);
	  ub=max(ub,d);
	  solver.AddEdge(u-1,v-1,d);
	}
	if(test(ub+1)) puts("Infinite");
	else if(!test(1)) puts("No Solution");
	else{
	  int L=2,R=ub,ans=1;
	  while(L<=R){
		int M=L+(R-L)/2;
		if(test(M)) ans=M,L=M+1;
		else R=M-1;
	  }
	  printf("%d\n",ans);
	}
  }
  return 0;
}
