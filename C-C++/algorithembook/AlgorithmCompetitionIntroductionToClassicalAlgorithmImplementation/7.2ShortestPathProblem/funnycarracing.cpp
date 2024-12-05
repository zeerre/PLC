#include<bits/stdc++.h>
using namespace std;

const int MAXV=305;
typedef pair<int ,int> IPair;
struct Edge{
  int from,to,open,close,w;
  Edge(int f,int t,int a,int b,int c):
	from(f),to(t),open(a),close(b),w(c){}
};
vector<Edge> G[MAXV];
int N,M,S,T,D[MAXV];
int arrive(int t,const Edge& e){
  int k=t % (e.open+e.close);
  if(k+e.w<=e.open) return t+e.w;
  return t+e.open+e.close-k+e.w;
}
void Dijkstra(){
  priority_queue<IPair,vector<IPair>,greater<IPair>> Q;
  fill(D,D+MAXV,INT_MAX),D[S]=0,Q.push(make_pair(0,S));
  while(!Q.empty()){
	IPair p=Q.top();
	Q.pop();
	int u=p.second,d=p.first;
	if(D[u]!=d) continue;
	for(size_t i=0;i<G[u].size();i++){
	  const Edge& e=G[u][i];
	  int v=e.to,&dv=D[e.to],nd=arrive(D[u],e);
	  if(dv>nd) dv=nd,Q.push({dv,v});
	}
  }
}
int main(){
  for(int kase =1;scanf("%d%d%d%d",&N,&M,&S,&T)==4;++kase){
	for(int i=0;i<=N;i++) G[i].clear();
	for(int i=0,u,v,a,b,t;i<M;i++){
	  scanf("%d%d%d%d%d",&u,&v,&a,&b,&t);
	  if(t>a) continue;
	  G[u].push_back(Edge(u,v,a,b,t));
	}
	Dijkstra();
	printf("Case %d: %d\n",kase,D[T]);
  }
  return 0;
}
