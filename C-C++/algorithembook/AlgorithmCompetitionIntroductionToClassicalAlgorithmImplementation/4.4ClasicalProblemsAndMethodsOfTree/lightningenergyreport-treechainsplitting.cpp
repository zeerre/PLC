#include<bits/stdc++.h>
using namespace std;
#define _for(i,a,b) for(int i=(a);i<(b);i++)
#define _rep(i,a,b) for(int i=(a);i<=(b);i++)
typedef long long LL;

const int MAXN=65536;
struct SegTree{
  int addv[MAXN*4],N;
  void update(int o,int L,int R,int qL,int qR,int val){
	if(qL<=L && R<=qR){
	  addv[o]+=val;
	  return;
	}
	int M=(L+M)/2;
	if(qL<=M) update(o<<1,L,M,qL,qR,val);
	if(M<qR) update(o<<1|1,M+1,R,qL,qR,val);
  }
  void add(int qL,int qR,int val){update(1,1,N,qL,qR,val);}
  void init(int o,int L,int R){
	addv[o]=0;
	if(L==R) return;
	int M=(L+R)/2;
	init(o<<1,L,M),init(o<<1|1,M+1,R);
  }
  int query(int o,int L,int R,int qv,int val){
	if(L==R) return val+addv[o];
	int M=(L+R)>>1;
	if(qv<=M) return query(o<<1,L,M,qv,val+addv[o]);
	return query(o<<1|1,M+1,R,qv,val+addv[o]);
  }
};
int Fa[MAXN],HcHead[MAXN],Depth[MAXN],HSon[MAXN],SZ[MAXN],ID[MAXN],intSz;
SegTree ST;
vector<int> G[MAXN];
int dfs(int u,int fa){
  SZ[u]=1,Fa[u]=fa,HSon[u]=0,Depth[u]=Depth[fa]+1;
  for(auto v:G[u]){
	if(v==fa) continue;
	SZ[u]+=dfs(v,u);
	if(SZ[v]>SZ[HSon[u]]) HSon[u]=v;
  }
  return SZ[u];
}
void hld(int u,int fa,int x){
  ID[u]= ++intSz,HcHead[u]=x;
  if(HSon[u])
	hld(HSon[u],u,x);
  for(auto v: G[u])
	if(v!=fa && v!=HSon[u]) hld(v,u,v);
}
void addPath(int u,int v,int w){
  while(true){
	int hu=HcHead[u],hv=HcHead[v];
	if(hu==hv) break;
	if(Depth[hu]<Depth[hv]) swap(u,v),swap(hu,hv);
	ST.add(ID[hu],ID[u],w),u=Fa[hu];
  }
  if(Depth[u]<Depth[v]) swap(u,v);
  ST.add(ID[v],ID[u],w);
}
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  int T;
  cin>>T;
  for(int kase=1,Q,N;kase<=T;kase++){
	cin>>N;
	assert(N<MAXN);
	ST.N=N,ST.init(1,1,N);
	for(int i=1;i<=N;i++) G[i].clear();
	SZ[0]=0,Depth[1]=0;
	for(int i=1,u,v;i<N;i++)
	  cin>>u>>v,G[u+1].push_back(v+1),G[v+1].push_back(u+1);
	dfs(1,1);
	intSz=0;
	hld(1,1,1);
	cin>>Q;
	for(int i=0,u,v,w;i<Q;i++)
	  cin>>u>>v>>w,addPath(u+1,v+1,w);
	printf("Case #%d:\n",kase);
	for(int i=1;i<=N;i++) printf("%d\n",ST.query(1,1,N,ID[i],0));
  }
  return 0;
}
