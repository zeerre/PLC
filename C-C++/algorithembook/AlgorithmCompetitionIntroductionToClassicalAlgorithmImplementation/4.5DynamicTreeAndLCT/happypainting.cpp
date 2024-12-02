#include<bits/stdc++.h>
using namespace std;
const int NN=1000005;

template<int SZ>
struct LCT{
  int ch[SZ][2],fa[SZ],rev[SZ],size[SZ],clr[SZ],set[SZ],mark[SZ];
  void init(int x){
	ch[x][0]=ch[x][1]=fa[x]=0;
	rev[x]=size[x]=clr[x]=set[x]=mark[x]=0;
  }
  int is_right_ch(int x){return ch[fa[x]][1]==x;}
  bool is_root(int x){return ch[fa[x]][0] != x && ch[fa[x]][1]!=x;}
  void maintain(int x){
	int &sx=set[x],&sz=size[x],ls=ch[x][0],rs=ch[x][1];
	sx=0,sz=1;
	if(ls) sx|=set[ls] | (1<<clr[ls]),sz+=size[ls];
	if(rs) sx|=set[rs] | (1<<clr[rs]),sz+=size[rs];
  }
  void rotate_up(int x){
	int y=fa[x],d=is_right_ch(x),&t=ch[y][d],z=fa[y],
	  cy_bak=clr[y],&cx=clr[x],&cy=clr[y];
	fa[x]=z;
	if(!is_root(y)) ch[z][is_right_ch(y)]=x;
	t=ch[x][d^1];
	if(t)
	  fa[t]=y,cy=clr[t],clr[t]=cx,cx=cy_bak;
	else
	  swap(cx,clr[y]);
	ch[x][d^1]=y,fa[y]=x;
	maintain(y),maintain(x);
  }
  void pushup(int x){
	if(!is_root(x)) pushup(fa[x]);
	pushdown(x);
  }
  void pushdown(int x){
	int ls=ch[x][0],rs=ch[x][1],&mk=mark[x];
	if(mk){
	  if(ls) clr[ls]=mark[ls]=mk,set[ls]=set[x];
	  if(rs) clr[rs]=mark[rs]=mk,set[rs]=set[x];
	  mk=0;
	}
	if(rev[x]){
	  swap(ch[x][0],ch[x][1]);
	  if(ls) rev[ls]^=1;
	  if(rs) rev[rs]^=1;
	  rev[x]=0;
	}
  }
  void splay(int x){
	pushup(x);
	for(int f=fa[x];f=fa[x],!is_root(x);rotate_up(x))
	  if(!is_root(f)) rotate_up(is_right_ch(x)==is_right_ch(f)?f:x);
	maintain(x);
  }
  void access(int x){
	for(int last=0;x;x=fa[x])
	  splay(x),ch[x][1]=last,last=x,maintain(last);
  }
  int find_root(int x){
	access(x),splay(x);
	while(ch[x][0]) x=ch[x][0];
	splay(x);
	return x;
  }
  void make_root(int x){access(x),splay(x),rev[x]^=1;}
  void split(int x,int y){make_root(x),access(y),splay(y);}
  void cut(int x){
	access(x),splay(x);
	int& ls=ch[x][0];
	if(ls) fa[ls]=0,clr[ls]=0,ls=0;
  }
  void link(int x,int y,int color){
	access(y),splay(x);
	cut(x),fa[x]=y,clr[x]=color;
  }
  void paint(int x,int y,int c){
	int rx=find_root(x);
	if(rx!=find_root(y)) return;
	split(x,y),set[y]=1<<c,mark[y]=c;
	make_root(rx);
  }
  void query(int x,int y,int& sz,int& cc){
	int rx=find_root(x);
	sz=0,cc=0;
	if(rx!=find_root(y)) return;
	split(x,y);
	for(int k=set[y];k;k>>1) cc+=k&1;
	sz=size[y]-1;
	make_root(rx);
  }
};
LCT<NN> T;
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  for(int n,m;cin>>n>>m;){
	for(int i=1;i<=n;i++) T.init(i);
	for(int i=1,v;i<=n;i++) cin>>v,T.fa[i]=v;
	for(int i=1,v;i<=n;i++){
	  cin>>v;
	  if(T.fa[i]) T.clr[i]=v;
	}
	for(int i=1,op,u,v,c;i<=m;i++){
	  switch(op){
		case 1:
		  cin>>c;
		  if(u!=v) T.link(u,v,c);
		  break;
		case 2:
		  cin>>c,T.paint(u,v,c);
		  break;
        case 3:
		  int sz,cc;
		  T.query(u,v,sz,cc);
		  printf("%d %d\n",sz,cc);
		  break;
	  }
	}
  }
  return 0;
}
		
	  
