#include<bits/stdc++.h>
using namespace std;

const int NN=10000+8;
struct Edge{
  int v,w;
};
vector<Edge> G[NN];
int N,F[NN],SF[NN],FV[NN],H[NN];
int dfsF(int u){
  int &f=F[u],&sf=SF[u];
  f=0,sf=0;
  for(size_t ei=0;ei<G[u].size();ei++){
	const Edge e=G[u][ei];
	int nf=dfsF(e.v)+e.w;
	if(nf>=f){
	  sf=f;
	  f=nf,FV[u]=e.v;
	}else if(nf>sf)
	  sf=nf;
  }
  return f;
}
void dfsH(int u){
  for(size_t ei=0;ei<G[u].size();ei++){
	const Edge& e=G[u][ei];
	H[e.v]=max(H[u],FV[u]==e.v?SF[u]:F[u])+e.w;
	dfsH(e.v);
  }
}
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  while(cin>>N&&N){
	for(int i=1;i<=N;++i) G[i].clear();
	for(int u=2,v,w;u<=N;++u)
	  cin>>v>>w,G[v].push_back((Edge){u,w});
	dfsF(1);
	H[1]=0;
	dfsF(1);
	for(int i=1;i<=N;++i) cout<<max(F[i],H[i])<<endl;
  }
  return 0;
}
