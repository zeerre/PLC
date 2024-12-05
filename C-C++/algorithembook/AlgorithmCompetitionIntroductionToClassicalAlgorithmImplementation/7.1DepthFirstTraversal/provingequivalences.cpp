#include<bits/stdc++.h>
using namespace std;

const int NN=20000+10;
vector<int> G[NN];
int pre[NN],lowlink[NN],sccno[NN],dfs_clock,scc_cnt;
stack<int> S;
void dfs(int u){
  int &lu=lowlink[u];
  pre[u]=lu=++dfs_clock,S.push(u);
  for(size_t i=0;i<G[u].size();i++){
	int v=G[u][i];
	if(!pre[v]) dfs(v),lu=min(lu,lowlink[v]);
	else if(!sccno[v]) lu=min(lu,pre[v]);
  }
  if(lu==pre[u]){
	scc_cnt++;
	for(int x=-1;x!=u;S.pop()) x=S.top(),sccno[x]=scc_cnt;
  }
}
void find_scc(int n){
  dfs_clock=scc_cnt=0;
  fill_n(sccno,n,0),fill_n(pre,n,0);
  for(int i=0;i<n;i++) if(!pre[i]) dfs(i);
}
bool in0[NN],out0[NN];
int solve(int n){
  if(scc_cnt==1)return 0;
  fill_n(in0+1,scc_cnt,true),fill_n(out0+1,scc_cnt,true);
  for(int u=0;u<n;u++)
	for(size_t i=0;i<G[u].size();i++){
	  int v=G[u][i];
	  if(sccno[u] !=sccno[v]) in0[sccno[v]]=out0[sccno[u]]=false;
	}
  return max(count(in0+1,in0+scc_cnt+1,true),
			 count(out0+1,out0+scc_cnt+1,true));
}
int main(){
  int T,n,m;
  scanf("%d",&T);
  while(T--){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++) G[i].clear();
	for(int i=0,u,v;i<m;i++)
	  scanf("%d%d",&u,&v),G[u-1].push_back(v-1);
	find_scc(n);
	printf("%d\n",solve(n));
  }
  return 0;
}
