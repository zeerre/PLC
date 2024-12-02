#include<bits/stdc++.h>
using namespace std;
const int maxn=1000+5;
struct BPM{
  int n,m;
  vector<int> G[maxn];
  int left[maxn];
  bool T[maxn];
  int right[maxn];
  bool S[maxn];

  void init(int n,int m){
	this->n=n,this->m=m;
	for(int i=0;i<n;i++) G[i].clear();
  }
  void AddEdge(int u,int v){ G[u].push_back(v);}
  bool match(int u){
	S[u]=true;
	for(size_t i=0;i<G[u].size();i++){
	  int v=G[u][i];
	  if(!T[v]){
		T[v]=true;
		if(left[v]==-1 || match(left[v])){
		  left[v]=u,right[u]=v;
		  return true;
		}
	  }
	}
	return false;
  }
  int solve(){
	fill_n(left,m+1,-1),fill_n(right,n+1,-1);
	int ans=0;
	for(int u=0;u<n;u++){
	  fill_n(S,n+1,false),fill_n(T,m+1,false);
	  if(match(u)) ans++;
	}
	return ans;
  }
  int mincover(vector<int>& X,vector<int>& Y){
	int ans=solve();
	fill_n(S,n+1,false),fill_n(T,m+1,false);
	for(int u=0;u<n;u++) if(right[u]==-1) match(u);
	for(int u=0;u<n;u++) if(!S[u]) X.push_back(u);
	for(int v=0;v<m;v++) if(T[v]) Y.push_back(v);
	return ans;
  }
};
BPM solver;
int main(){
  for(int R,C,N;scanf("%d%d%d",&R,&C,&N)==3 && R&& C&& N;){
	solver.init(R,C);
	for(int i=0,r,c;i<N;i++)
	  scanf("%d%d",&r,&c),solver.AddEdge(r-1,c-1);
	vector<int> X,Y;
	int ans=solver.mincover(X,Y);
	printf("%d",ans);
	for(size_t i=0;i<X.size();i++) printf(" r%d",X[i]+1);
	for(size_t i=0;i<Y.size();i++) printf(" c%d",Y[i]+1);
	printf("\n");
  }
  return 0;
}
