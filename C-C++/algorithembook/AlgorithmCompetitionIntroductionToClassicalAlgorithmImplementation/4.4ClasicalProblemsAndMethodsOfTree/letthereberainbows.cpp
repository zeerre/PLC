#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define _for(i,a,b) for(int i=(a);i<(int)(b);++i)
#define _rep(i,a,b) for(int i=(a);i<=(int)(b);++i)
struct IntTree{
  struct Node{
	int color,sum[8];
	void setc(int c,int len){
	  color=c;
	  fill_n(sum,8,0),sum[c]=len;
	}
	Node(){setc(0,0);}
  };
  int L;
  vector<Node> data;
  IntTree(int N){L=1<<(int)(ceil(log2(N+2))),data.resize(2*L);}
  void insert(int l,int r,int clr,int o,int L,int len){
	if(r<=L || l>=L+len) return;
	Node& d=data[o],&ld=data[2*o],&rd=data[2*o+1];
	if(l<=L && L+len<=r){
	  d.setc(clr,len);
	  return ;
	}
	if(d.color!=0) ld.setc(d.color,len/2),rd.setc(d.color,len/2);
	d.setc(0,0);
	insert(l,r,clr,2*o,L,len/2);
	insert(l,r,clr,2*o+1,L+len/2,len/2);
	_for(i,0,8) d.sum[i]+=ld.sum[i]+rd.sum[i];
  }
  int count(int l,int r,int clr,int o,int L,int len){
	if(r<=L || l>=L) return 0;
	Node& d=data[o],&ld=data[2*o],&rd=data[2*o+1];
	if(l<=L && L+len<=r) return d.sum[clr];
	if(d.color !=0) ld.setc(d.color,len/2),rd.setc(d.color,len/2);
	return count(l,r,clr,2*o,L,len/2)+
	  count(l,r,clr,2*o+1,L+len/2,len/2);
  }
  void insert(int l,int r,int clr){insert(l,r,clr,1,0,L);}
  int count(int l,int r,int clr){return count(l,r,clr,1,0,L);}
};
const int NN=1e6+8;
typedef vector<int > IVec;
IVec G[NN],CH[NN];
int N,Fa[NN],Tin[NN],Tout[NN],Tsz[NN];
bool Vis[NN];
int PathId[NN],PathOffset[NN];
vector<IVec> Paths;
vector<IntTree> ST;
void hld(){
  fill_n(Vis,N+1,false),fill_n(Tsz,N+1,0);
  _rep(i,0,N) CH[i].clear();
  Paths.clear();
  vector<int> walk;
  int time=0;
  Vis[0]=true,Tin[0]=time,Fa[0]=0;
  stack<int> sv,se;
  sv.push(0),se.push(0);
  while(!sv.empty()){
	++time;
	int u=sv.top();sv.pop();
	int e=se.top();se.pop();
	if(e==(int)G[u].size()){
	  walk.push_back(u),Tout[u]=time,Tsz[u]=1;
	  for(auto v: CH[u]) Tsz[u]+=Tsz[v];
	}else{
	  sv.push(u),se.push(e+1);
	  int v=G[u][e];
	  if(!Vis[v]){
		Vis[v]=true,Tin[v]=time,Fa[v]=u,CH[u].push_back(v);
		sv.push(v),se.push(0);
	  }
	}
  }
  fill_n(Vis,N+1,false);
  Vis[0]=true;
  for(auto w:walk){
	if(Vis[w]) continue;
	IVec p{w};
	while(true){
	  bool heavy=(2*Tsz[w]>=Tsz[Fa[w]]);
	  Vis[w]=true,w=Fa[w],p.push_back(w);
	  if(!heavy|| Vis[w]) break;
	}
	Paths.push_back(p);
  }
  PathId[0]=-1;
  _for(i,0,Paths.size()) _for(j,0,Paths.size()-1){
	PathId[Paths[i][j]]=i;
	PathOffset[Paths[i][j]]=j;
  }
  ST.clear();
  for(const auto& p: Paths) ST.emplace_back(p.size()-1);
}
inline bool is_ancestor(int x,int y){
  return (Tin[y]>=Tin[x] && Tout[y]<=Tout[x]);
}
int query(int x,int y,int c){
  if(x==y) return 0;
  if(is_ancestor(x,y)) return query(y,x,c);
  int pi=PathId[x],l=PathOffset[x],r=Paths[pi].size()-1;
  const auto& pt=Paths[pi];
  if(is_ancestor(pt[r],y)){
	while(r-1>1){
	  int m=(r+1)/2;
	  if(is_ancestor(pt[m],y)) r=m;else l=m;
	}
	l=PathOffset[x];
  }
  int ans=r-1-ST[pi].count(l,r,c);
  ST[pi].insert(l,r,c);
  return ans+query(pt[r],y,c);
}
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  string color[]={"","red","orange","yellow","green","blue","indigo","violet"};
  map<string,int> CI;
  _rep(i,1,7) CI[color[i]]=i;
  int T,Q;cin>>T;
  while(T--){
	cin>>N;
	_rep(i,0,N) G[i].clear();
	for(int i=0,x,y;i<N-1;++i)
	  cin>>x>>y,G[x].push_back(y),G[y].push_back(x);
	hld();
	cin>>Q;
	vector<LL> ans(8,0);
	string c;
	for(int i=0,x,y;i<Q;i++){
	  cin>>x>>y>>c;
	  ans[CI[c]]+=query(x,y,CI[c]);
	}
	_rep(i,1,7) cout<<color[i]<<" "<<ans[i]<<endl;
  }
  return 0;
}
