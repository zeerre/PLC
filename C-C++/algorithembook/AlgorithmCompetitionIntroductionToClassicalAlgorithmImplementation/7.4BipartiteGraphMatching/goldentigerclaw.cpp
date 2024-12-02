#include<bits/stdc++.h>
using namespace std;
const int INF=1e9;
template<size_t SZ>
struct KM{
  int n;
  vector<int>G[SZ];
  int W[SZ][SZ];
  int Lx[SZ],Ly[SZ];
  int left[SZ];
  bool S[SZ],T[SZ];
  void init(int n){
	this->n=n;
	for(int i=0;i<n;i++) G[i].clear();
	memset(W,0,sizeof(W));
  }
  void AddEdge(int u,int v,int w){
	G[u].push_back(v),W[u][v]=w;
  }
  bool match(int u){
	S[u]=true;
	for(size_t i=0;i<G[u].size();i++){
	  int v=G[u][i];
	  if(Lx[u]+Ly[v]==W[u][v] && !T[v]){
		T[v]=true;
		if(left[v]==-1 || match(left[v])){
		  left[v]=u;
		  return true;
		}
	  }
	}
	return false;
  }
  void update(){
	int a=INF;
	for(int u=0;u<n;u++)
	  if(S[u])
		for(size_t i=0;i<G[u].size();i++){
		  int v=G[u][i];
		  if(!T[v]) a=min(a,Lx[u]+Ly[v]-W[u][v]);
		}
	for(int i=0;i<n;i++){
	  if(S[i]) Lx[i]-=a;
	  if(T[i]) Ly[i]+=a;
	}
  }
  void solve(){
	for(int i=0;i<n;i++)
	  Lx[i]= *max_element(W[i],W[i]+n),left[i]=-1,Ly[i]=0;
	for(int u=0;u<n;u++){
	  while(true){
		for(int i=0;i<n;i++) S[i]=T[i]=false;
		if(match(u)) break;else update();
	  }
	}
  }
};
const int maxn=500+5;
KM<maxn> km;
int main(){
  for(int n,w;scanf("%d",&n) ==1;){
	km.init(n);
	for(int i=0;i<n;i++)
	  for(int j=0;j<n;j++)
		scanf("%d",&w),km.AddEdge(i,j,w);
	km.solve();
	int sum=0;
	for(int i=0;i<n-1;i++) printf("%d ",km.Lx[i]),sum+=km.Lx[i];
	printf("%d\n",km.Lx[n-1]);
	for(int i=0;i<n-1;i++) printf("%d ",km.Ly[i]),sum+=km.Ly[i];
	printf("%d\n",km.Ly[n-1]);
	printf("%d\n",sum+km.Lx[n-1]+km.Ly[n-1]);
  }
  return 0;
}
