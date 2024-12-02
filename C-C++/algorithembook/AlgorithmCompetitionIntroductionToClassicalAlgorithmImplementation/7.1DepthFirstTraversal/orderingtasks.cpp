#include<bits/stdc++.h>

using namespace std;

#define _for(i,a,b) for(int i=(a);i<(b);++i)
typedef long long LL;
const int NN=1024;
vector<int > G[NN];
int VIS[NN];

void dfs(int u,deque<int>& order){
  VIS[u]=-1;
  for(auto v:G[u]){
	assert(VIS[v] != -1);
	if(!VIS[v]) dfs(v,order);
  }
  VIS[u]=1;
  order.push_front(u);
}
int main(){
  for(int n,m,u,v;scanf("%d%d",&n,&m)==2 && n;){
	_for(i,0,n) G[i].clear();
	_for(i,0,m) {
	  scanf("%d%d",&u,&v);
	  G[u-1].push_back(v-1);
	}
	fill_n(VIS,NN,0);
	deque<int> O;
	_for(u,0,n) if(VIS[u] !=1) dfs(u,O);
	for(size_t i=0;i<O.size();i++)
	  printf("%d%s",O[i]+1,i==O.size()-1 ? "\n":" ");
  }
  return 0;
}
