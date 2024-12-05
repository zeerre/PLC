#include<bits/stdc++.h>
using namespace std;

const int MAXN=20000+4;
int N,MaxS,Centroid;
vector<int>E[MAXN];
int dfs(int u,int fa){
  int s=1,max_s=-1;
  for(size_t i=0;i<E[u].size();i++){
	int v=E[u][i];
	if(v==fa) continue;
	int sv=dfs(v,u);
	s+=sv,max_s=max(max_s,sv);
  }
  max_s=max(max_s,N-s);
  if(max_s<MaxS || (max_s==MaxS && Centroid>u))
	MaxS=max_s,Centroid=u;
  return s;
}
int main(){
  int T;
  scanf("%d",&T);
  while(T--){
	scanf("%d",&N);
	for(int i=1;i<=N;i++) E[i].clear();
	for(int i=1,u,v;i<N;i++){
	  scanf("%d %d",&u,&v);
	  E[u].push_back(v),E[v].push_back(u);
	}
	MaxS=MAXN,Centroid=0;
	dfs(1,-1);
	printf("%d %d\n",Centroid,MaxS);
  }
  return 0;
}
