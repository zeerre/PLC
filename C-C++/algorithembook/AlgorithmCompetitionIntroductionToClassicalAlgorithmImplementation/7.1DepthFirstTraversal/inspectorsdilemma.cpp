#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXV=1000+4;
vector<int > G[MAXV];
int V,E,T,VIS[MAXV];

void dfs(int u,int& cnt){
  VIS[u]=1,cnt+=G[u].size()%2;
  for(size_t vi=0;vi<G[u].size();++vi){
	int v=G[u][vi];
	if(!VIS[v]) dfs(v,cnt);
  }
}
int main(){
  for(int k=1;scanf("%d%d%d",&V,&E,&T)==3 && (V ||E ||T);k++){
	for(int i=0;i<V;++i) G[i].clear();
	fill_n(VIS,MAXV,0);
	for(int i=0,a,b;i<E;++i){
	  scanf("%d%d",&a,&b),--a,--b;
	  G[a].push_back(b),G[b].push_back(a);
	}
	int nc=0,ans=0;
	for(int u=0;u<V;++u)
	  if(!G[u].empty() && !VIS[u]){
		int p=0;
		dfs(u,p);
		if(p>2) ans+=(p-2)/2;
		nc++;
	  }
	printf("Case %d: %d\n",k,T*(E+ans+max(0,nc-1)));
  }
  return 0;
}
