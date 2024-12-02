#include<bits/stdc++.h>
using namespace std;

const int NN=1000+10;
vector<int> G[NN];
int pre[NN],lowlink[NN],sccno[NN],dfs_clock,scc_cnt;
stack<int > S;
void dfs(int u){
  int& lu=lowlink[u];
  pre[u]=lu=++dfs_clock,S.push(u);
  for(size_t i=0;i<G[u].size();i++){
	int v=G[u][i];
	if(!pre[v])
	  dfs(v),lu=min(lu,lowlink[v]);
	else if(!sccno[v])
	  lu=min(lu,pre[v]);
  }
  if(lu==pre[u]){
	scc_cnt++;
	for(int x=-1;x!=u;S.pop()) sccno[x=S.top()]=scc_cnt;
  }
}
void find_scc(int n){
  dfs_clock=scc_cnt=0;
  fill_n(sccno,n,0),fill_n(pre,n,0);
  for(int i=0;i<n;i++) if(!pre[i]) dfs(i);
}
int SccSz[NN],TG[NN][NN],D[NN];
int dp(int u){
  int& d=D[u];
  if(d>=0) return d;
  d=SccSz[u];
  for(int v=1;v<=scc_cnt;v++)
	if(u!=v && TG[u][v]) d=max(d,dp(v)+SccSz[u]);
  return d;
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
	memset(TG,0,sizeof(TG)),fill_n(SccSz,n+1,0);
	for(int i=0;i<n;i++){
	  SccSz[sccno[i]]++;
	  for(size_t j=0;j<G[i].size();j++)
		TG[sccno[i]][sccno[G[i][j]]]=1;
	}
	int ans=0;
	fill_n(D,n+1,-1);
	for(int i=1;i<=scc_cnt;i++)
	  ans=max(ans,dp(i));
	printf("%d\n",ans);
  }
  return 0;
}
