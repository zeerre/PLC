#include<bits/stdc++.h>
using namespace std;

template<int SZ>
struct LCT{
  int ch[SZ][2],fa[SZ],minw[SZ];
  bool rev[SZ];
  inline int& ls(int x){return ch[x][0];}
  inline int& rs(int x){return ch[x][1];}
  inline void reverse(int x){ rev[x]^=1,swap(ls(x),rs(x));}
  inline void maintain(int x){
	minw[x]=min(x,min(minw[ls(x)],minw[rs(x)]));
  }
  inline void pushdown(int x){
	if(rev[x]) reverse(ls(x)),reverse(rs(x)),rev[x]=false;
  }
  inline bool isroot(int x){return ls(fa[x])!=x && rs(fa[x]) !=x;}
  inline int isright(int x){ return rs(fa[x])==x;}
  void rotate(int x){
	int y=fa[x],z=fa[y],k=isright(x),&t=ch[x][k^1];
	if(!isroot(y)) ch[z][isright(y)]=x;
	ch[y][k]=t,fa[t]=y;
	t=y,fa[y]=x,fa[x]=z;
	maintain(y),maintain(x);
  }
  void pushup(int x){
	if(!isroot(x)) pushup(fa[x]);
	pushdown(x);
  }
  void splay(int x){
	pushup(x);
	while(!isroot(x)){
	  int y=fa[x];
	  if(!isroot(y)) rotate(isright(y)==isright(x)?x:y);
	  rotate(x);
	}
  }
  void access(int x){
	for(int t=0;x;t=x,x=fa[x]) splay(x),rs(x)=t,maintain(x);
  }
  void makeroot(int x){access(x),splay(x),reverse(x);}
  void link(int x,int y){makeroot(x),fa[x]=y;}
  void cut(int x,int y){
	makeroot(x),access(y),splay(y);
	ls(y)=fa[x]=0;
	maintain(y);
  }
  void split(int x,int y){makeroot(x),access(y),splay(y);}
  int findroot(int x){
	access(x),splay(x);
	while(ls(x)) pushdown(x),x=ls(x);
	splay(x);
	return x;
  }
  void init(int sz){
	minw[0]=1e9;
	assert(sz<SZ);
	for(int i=1;i<=sz;i++)
	  minw[i]=i,ch[i][0]=ch[i][1]=fa[i]=0,rev[i]=0;
  }
};
template<int SZ>
struct BIT{
  int C[SZ],n;
  void init(int sz){assert(sz+1<SZ);fill_n(C,sz+1,0),this->n=sz;}
  inline int lowbit(int x){return x& -x;}
  void add(int x,int v){
	while(x<=n) C[x]+=v,x+=lowbit(x);
  }
  int sum(int x){
	int ret=0;
	while(x) ret+=C[x],x-=lowbit(x);
	return ret;
  }
};
const int NN=2e5+4;
BIT<NN> S;
LCT<NN*2> lct;
int QL[NN],Ans[NN],EU[NN],EV[NN];
vector<int > EQ[NN];
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  int T;
  cin>>T;
  for(int t=0,n,m,q;t<T;t++){
	cin>>n>>m>>q;
	for(int i=1;i<=m;i++){
	  int &u=EU[i],&v=EV[i];
	  cin>>u>>v,u+=m,v+=m,EQ[i].clear();
	}
	S.init(m),lct.init(m+n);
	for(int i=1,qr;i<=q;i++) cin>>QL[i]>>qr,EQ[qr].push_back(i);
	for(int i=1;i<=m;i++){
	  int u=EU[i],v=EV[i];
	  if(lct.findroot(u)==lct.findroot(v)){
		lct.split(u,v);
		int e=lct.minw[v];
		if(e<i){
		  lct.cut(e,EU[e]),lct.cut(e,EV[e]),S.add(e,-1);
		  lct.link(i,u),lct.link(i,v),S.add(i,1);
		}
	  }else
		lct.link(u,i),lct.link(v,i),S.add(i,1);
	  for(size_t xi=0;xi<EQ[i].size();xi++)
		Ans[EQ[i][xi]]=n-(S.sum(i)-S.sum(QL[EQ[i][xi]]-1));
	}
	for(int i=1;i<=q;i++) cout<<Ans[i]<<endl;
  }
  return 0;
}
