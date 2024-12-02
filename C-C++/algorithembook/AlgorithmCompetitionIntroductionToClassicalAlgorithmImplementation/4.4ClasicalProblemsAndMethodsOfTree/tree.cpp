#include<bits/stdc++.h>

using namespace std;
const int INF=2147483647,MAXN=10000+4;
struct Edge{
  int v,w;
  Edge(int _v,int _w):v(_v),w(_w){}
};
int N,K;
vector<Edge> G[MAXN];
bool VIS[MAXN];
int get_size(int u,int fa){
  assert(!VIS[u]);
  int ans=1;
  for(size_t i=0;i<G[u].size();i++){
	int v=G[u][i].v;
	if(v==fa||VIS[v]) continue;
	ans+=get_size(v,u);
  }
  return ans;
}
int find_centroid(int u,int fa,int usz,int &ch_sz,int &ct){
  assert(!VIS[u]);
  int sz=1,max_ch=INF;
  for(size_t i=0;i<G[u].size();i++){
	int v=G[u][i].v;
	if(v==fa || VIS[v]) continue;
	int chsz=find_centroid(v,u,usz,ch_sz,ct);
	sz+=chsz,max_ch=max(max_ch,chsz);
  }
  max_ch=max(max_ch,usz=sz);
  if(max_ch<ch_sz) ch_sz=max_ch,ct=u;
  return sz;
}
int find_centroid(int u){
  int ch_sz=INF,ct=-1,sz=get_size(u,-1);
  find_centroid(u,-1,sz,ch_sz,ct);
  assert(ct!=-1 && ch_sz<=sz/2);
  return ct;
}
void get_paths(int u,int fa,int plen,vector<int>& paths){
  if(plen>K) return;
  paths.push_back(plen);
  for(size_t i=0;i<G[u].size();i++){
	const Edge &e=G[u][i];
	if(e.v!=fa && !VIS[e.v])
	  get_paths(e.v,u,plen+e.w,paths);
  }
}
inline int count_pairs(vector<int>& P){
  sort(P.begin(),P.end());
  int ans=0;
  for(int l=0,r=P.size()-1;;l++){
	while(r>l && P[r]+P[l]>K) r--;
	if(r<=l) break;
	ans+=r-1;
  }
  return ans;
}
int solve(int u){
  int ans=0;
  vector<int > lens;
  for(size_t i=0;i<G[u].size();i++){
	const Edge &e=G[u][i];
	if(VIS[e.v]) continue;
	vector<int> ps;
	get_paths(e.v,u,e.w,ps),ans-=count_pairs(ps);
	copy(ps.begin(),ps.end(),back_inserter(lens));
  }
  ans+=count_pairs(lens)+lens.size();
  VIS[u]=true;
  for(size_t i=0;i<G[u].size();i++){
	const Edge &e=G[u][i];
	if(!VIS[e.v]) ans+=solve(find_centroid(e.v));
  }
  return ans;
}
int main(){
  while(scanf("%d%d",&N,&K) ==2&&(N||K)){
	for(int i=0;i<=N;i++) G[i].clear(),VIS[i]=false;
	for(int i=0,u,v,w;i<N-1;i++){
	  scanf("%d%d%d",&u,&v,&w),u--,v--;
	  G[u].push_back(Edge(v,w)),G[v].push_back(Edge(u,w));
	}
	printf("%d\n",solve(find_centroid(0)));
  }
  return 0;
}
