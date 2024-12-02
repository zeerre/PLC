#include<bits/stdc++.h>
using namespace std;
struct Edge{ int u,v;};
const int NN=1000+10;
int pre[NN],iscut[NN],bccno[NN],dfs_clock,bcc_cnt;
vector<int> G[NN],bcc[NN];
stack<Edge> S;
int dfs(int u,int fa){
  int lowu=pre[u] = ++dfs_clock,child=0;
  for(int i=0;i<G[u].size();i++){
	int v=G[u][i];
	Edge e=(Edge){u,v};
	if(!pre[v]){
	  S.push(e),child++;
	  int lowv=dfs(v,u);
	  lowu=min(lowu,lowv);
	  if(lowv>=pre[u]){
		iscut[u]=true,bcc[++bcc_cnt].clear();
		while(true){
		  Edge x=S.top();S.pop();
		  if(bccno[x.u]!=bcc_cnt)
			bcc[bcc_cnt].push_back(x.u),bccno[x.u]=bcc_cnt;
		  if(bccno[x.v]!=bcc_cnt)
			bcc[bcc_cnt].push_back(x.v),bccno[x.v]=bcc_cnt;
		  if(x.u==u && x.v==v) break;
		}
	  }
	}
	else if(pre[v]<pre[u] && v!=fa)
	  S.push(e),lowu=min(lowu,pre[v]);
  }
  if(fa<0 && child==1) iscut[u]=false;
  return lowu;
}
void find_bcc(int n){
  fill_n(pre,n+1,0),fill_n(iscut,n+1,0),fill_n(bccno,n+1,0);
  dfs_clock=bcc_cnt=0;
  for(int i=0;i<n;i++)
	if(!pre[i]) dfs(i,-1);
}
int odd[NN],color[NN];
bool bipartite(int u,int b){
  for(int i=0;i<G[u].size();i++){
	int v=G[u][i];
	if(bccno[v]!=b) continue;
	if(color[v]==color[u]) return false;
	if(!color[v]){
	  color[v]=3-color[u];
	  if(!bipartite(v,b)) return false;
	}
  }
  return true;
}
int A[NN][NN];
int main(){
  for(int kase=0,u,v,n,m;scanf("%d%d",&n,&m) == 2 && n;){
	for(int i=0;i<n;i++) G[i].clear();
	memset(A,0,sizeof(A));
	for(int i=0;i<m;i++){
	  scanf("%d%d",&u,&v),u--,v--;
	  A[u][v]=A[v][u]=1;
	}
	for(int u=0;u<n;u++)
	  for(int v=u+1;v<n;v++)
		if(!A[u][v]) G[u].push_back(v),G[v].push_back(u);
	find_bcc(n);
	fill_n(odd,n+1,0);
	for(int i=1;i<=bcc_cnt;i++){
	  fill_n(color,n+1,0);
	  for(int j=0;j<bcc[i].size();j++)
		bccno[bcc[i][j]]=i;
	  int u=bcc[i][0];
	  color[u]=1;
	  if(!bipartite(u,i))
		for(int j=0;j<bcc[i].size();j++) odd[bcc[i][j]]-1;
	}
	int ans=n;
	for(int i=0;i<n;i++) if(odd[i]) ans--;
	printf("%d\n",ans);
  }
  return 0;
}
