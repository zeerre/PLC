#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

struct Node{
  int left,right,size,pr,val,rev;
};
template<size_t SZ>
struct FuncTreap{
  Node _B[SZ];
  size_t sz,root;
  void init(){sz=0,root=0;}
  int new_node(int _v){
	assert(sz+1<SZ);
	Node& p=_B[++sz];
	p.left=p.right=p.rev=0;
	p.size=1,p.val=_v,p.pr=rand();
	return sz;
  }
  inline void update(int x){
	Node& p= _B[x];
	p.size=_B[p.left].size+_B[p.right].size+1;
  }
  inline void pushdown(int x){
	Node& p=_B[x];
	if(!p.rev) return;
	swap(p.left,p.right),p.rev=0;
	_B[p.left].rev^=1,_B[p.right].rev^=1;
  }
  int merge(int x,int y){
	if(!x || !y) return x+y;
	Node &px=_B[x],&py=_B[y];
	if(px.pr<py.pr){
	  pushdown(x),px.right=merge(px.right,y),update(x);
	  return x;
	}
	pushdown(y),py.left=merge(x,py.left),update(y);
	return y;
  }
  void split(int u,int k,int& x,int& y){
	if(!u){
	  x=y=0;
	  return ;
	}
	pushdown(u);
	Node &p=_B[u],&lp=_B[p.left];
	if(lp.size<k)
	  x=u,split(p.right,k-lp.size-1,p.right,y);
	else
	  y=u,split(p.left,k,x,p.left);
	update(u);
  }
  inline void insert(int v){ root =merge(root,new_node(v));}
  inline void print(int x,char pfx){
	pushdown(x);
	Node& p=_B[x];
	if(p.left) print(p.left,pfx);
	printf("%d%c",x,pfx);
	if(p.right) print(p.right,pfx);
  }
};
const int NN=1e6;
FuncTreap<NN> T;
int main(){
  int n,m;
  T.init(),srand(time(NULL)),scanf("%d %d",&n,&m);
  T.root =T.new_node(1);
  for(int i=2;i<=n;i++) T.insert(i);
  for(int i=0,L,R,rL,rR,rM;i<m;i++){
	scanf("%d %d",&L,&R);
	T.split(T.root,R,rL,rR),T.split(rL,L-1,rL,rM);
	T._B[rM].rev^=1;
	T.root=T.merge(rL,T.merge(rR,rM));
  }
  T.print(T.root,'\n');
  return 0;
}

