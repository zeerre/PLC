#include<bits/stdc++.h>
using namespace std;
const int INF=1e9,maxn=100+10;
struct MDST{
  int n;                   //边权
  int w[maxn][maxn];       //访问标记，仅用来判断无解
  int vis[maxn];           //计算答案
  int ans;                 //每个点是否被删除
  int removed[maxn];       //所在圈编号
  int cid[maxn];           //最小入边的起点
  int pre[maxn];           //最小入边的权值
  int iw[maxn];            //最大圈编号
  int max_cid;

  void init(int n){
	this->n=n;
	for(int i=0;i<n;i++)
	  for(int j=0;j<n;j++) w[i][j]=INF;
  }
  void AddEdge(int u,int v,int cost){
	w[u][v]=min(w[u][v],cost);
  }
  int dfs(int s){
	vis[s]=1;
	int ans=1;
	for(int i=0;i<n;i++)
	  if(!vis[i] && w[s][i]<INF) ans+=dfs(i);
	return ans;
  }
  bool cycle(int u){
	max_cid++;
	int v=u;
	while(cid[v]!=max_cid){cid[v]=max_cid;v=pre[v];}
	return v==u;
  }
  void update(int u){
	iw[u]=INF;
	for(int i=0;i<n;i++)
	  if(!removed[i] && w[i][u]<iw[u]){
		iw[u]=w[i][u];
		pre[u]=i;
	  }
  }
  bool solve(int s){
	memset(vis,0,sizeof(vis));
	if(dfs(s)!=n) return false;
	memset(removed,0,sizeof(removed));
	memset(cid,0,sizeof(cid));
	for(int u=0;u<n;u++) update(u);
	pre[s]=s;iw[s]=0;
	ans=max_cid=0;
	for(;;){
	  bool have_cycle=false;
	  for(int u=0;u<n;u++) if(u!=s && !removed[u] && cycle(u)){
		  have_cycle=true;
		  int v=u;
		  do{
			if(v!=u) removed[v]=1;
			ans+=iw[v];
			for(int i=0;i<n;i++) if(cid[i]!=cid[u] && !removed[i]){
				if(w[i][v]<INF) w[i][u]=min(w[i][u],w[i][v]-iw[v]);
				w[u][i]=min(w[u][i],w[v][i]);
				if(pre[i]==v) pre[i]=u;
			  }
			v=pre[v];
		  }while(v!=u);
		  update(u);
		  break;
		}
	  if(!have_cycle) break;
	}
	for(int i=0;i<n;i++)
	  if(!removed[i]) ans+=iw[i];
	return true;
  }
};
MDST solver;
struct Edge{
  int u,v,b,c;
  bool operator<(const Edge& rhs) const{
	return b>rhs.b;
  }
};
const int maxm=10000+10;
int N,M,C;
Edge edges[maxm];
bool check(int cnt){
  solver.init(N);
  for(int i=0;i<cnt;i++)
	solver.AddEdge(edges[i].u,edges[i].v,edges[i].c);
  if(!solver.solve(0)) return false;
  return solver.ans<=C;
}
int main(){
  int T;
  scanf("%d",&T);
  while(T--){
	scanf("%d%d%d",&N,&M,&C);
	for(int i=0;i<M;i++){
	  scanf("%d%d%d%d",&edges[i].u,&edges[i].v,&edges[i].b,&edges[i].c);
	}
	sort(edges,edges+M);
	int l=1,r=M,ans=-1;
	while(l<=r){
	  int m=l+(r-1)/2;
	  if(check(m)) ans=edges[m-1].b,r=m-1;
	  else l=m+1;
	}
	if(ans<0) printf("streaming not possible.\n");
	else printf("%d kbps\n",ans);
  }
  return 0;
}
