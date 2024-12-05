#include<bits/stdc++.h>
using namespace std;

const int maxn=100+10,INF=1e9;
int N,pa[maxn];
int find_pa(int x){return pa[x]!=x ? pa[x]=find_pa(pa[x]) : x;}
struct Edge{
  int u,v,d;
  Edge(int u,int v,int d):u(u),v(v),d(d){}
  bool operator<(const Edge& rhs) const {return d<rhs.d;}
};
vector<Edge> E;
int solve(){
  int m=E.size(),ans=INF;
  sort(E.begin(),E.end());
  for(int L=0;L<m;L++){
	for(int i=1;i<=N;i++) pa[i]=i;
	for(int R=L,cnt=N;R<m;R++){
	  int u=find_pa(E[R].u),v=find_pa(E[R].v);
	  if(u==v) continue;
	  pa[u]=v;
	  if(--cnt==1){
		ans=min(ans,E[R].d-E[L].d);
		break;
	  }
	}
  }
  if(ans==INF) ans=-1;
  return ans;
}
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  for(int m;cin>>N>>m && N;E.clear()){
	for(int i=0,u,v,d;i<m;i++)
	  cin>>u>>v>>d,E.push_back(Edge(u,v,d));
	printf("%d\n",solve());
  }
  return 0;
}
