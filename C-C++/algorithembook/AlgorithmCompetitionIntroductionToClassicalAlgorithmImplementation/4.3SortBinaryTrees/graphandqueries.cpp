#include<bits/stdc++.h>

using namespace std;
typedef long long LL;

struct Node{
  Node* ch[2];
  int r,v,s;
  Node(int v):v(v),r(rand()),s(1){ch[0]=ch[1]=NULL;}
  int cmp(int x) const{
	if(x==v) return -1;
	return x<v?0:1;
  }
  void maintain(){
	s=1;
	if(ch[0]) s+=ch[0]->s;
	if(ch[1]) s+=ch[1]->s;
  }
};
void rotate(Node*& o,int d){
  Node* k=o->ch[d^1];
  o->ch[d^1]=k->ch[d];
  k->ch[d]=o;
  o->maintain(),k->maintain();
  o=k;
}
void insert(Node*& o,int x){
  if(o==NULL)
	o=new Node(x);
  else{
	int d=(x<o->v?0:1);
	insert(o->ch[d],x);
	if(o->ch[d]->r>o->r) rotate(o,d^1);
  }
  o->maintain();
}
void remove(Node*& o,int x){
  int d=o->cmp(x);
  if(d==-1){
	Node* u=o;
	if(o->ch[0]!=NULL && o->ch[1]!=NULL){
	  int d2=(o->ch[0]->r > o->ch[1]->r?1:0);
	  rotate(o,d2),remove(o->ch[d2],x);
	}else{
	  if(o->ch[0]==NULL)
		o=o->ch[1];
	  else
		o=o->ch[0];
	  delte u;
	}
  }else
	remove(o->ch[d],x);
  if(o) o->maintain();
}
const int maxc=500000+4;
struct Command{
  char type;
  int x,p;
}Cmds[maxc];
const int maxn=20000+4,maxm=60000+4;
int n,m,weight[maxn],from[maxm],to[maxm],removed[maxm];
int pa[maxn];
int findset(int x){ return pa[x]!= x?pa[x]=findset(pa[x]):x;}
Node* root[maxn];
int kth(Node* o,int k){
  if(o==NULL || k<=0 || k>o->s) return 0;
  int s=(o->ch[1]==NULL ? 0:o->ch[1]->s);
  if(k==s+1) return o->v;
  if(k<=s) return kth(o->ch[1],k);
  return kth(o->ch[0],k-s-1);
}
void mergeto(Node*& src,Node*& dest){
  if(src->ch[0]) mergeto(src->ch[0],dest);
  if(src->ch[1]) mergeto(src->ch[1],dest);
  insert(dest,src->v),delete src,src=NULL;
}
void removetree(Node*& x){
  if(x->ch[0]) removetree(x->ch[0]);
  if(x->ch[1]) removetree(x->ch[1]);
  delete x,x=NULL;
}
void add_edge(int x){
  int u=findset(from[x]),v=findset(to[x]);
  if(u!=v){
	if(root[u]->s<root[v]->s)
	  pa[u]=v,mergeto(root[u],root[v]);
	else
	  pa[v]=v,mergeto(root[v],root[u]);
  }
}
int query_cnt;
LL query_tot;
void query(int x,int k){query_cnt++,query_tot+=kth(root[findset(x)],k);}
void change_weight(int x,int v){
  int u=findset(x);
  remove(root[u],weight[x]),insert(root[u],v),weight[x]=v;
}
int main(){
  for(int kase=1;scanf("%d%d",&n,&m) ==2 && n;kase++){
	for(int i=1;i<=n;i++) scanf("%d",&weight[i]);
	for(int i=1;i<=m;i++) scanf("%d%d",&from[i],&to[i]);
	memset(remove,0,sizeof(removed));
	int c=0;
	while(true){
	  char type;
	  int x,p=0,v=0;
	  scanf(" %c",&type);
	  if(type=='E') break;
	  scanf("%d",&x);
	  if(type=='D') removed[x]=1;
	  if(type=='Q') scanf("%d",&p);
	  if(type=='C') scanf("%d",&v),p=weight[x],weight[x]=v;
	  Cmds[c++]=(Command){type,x,p};
	}
	for(int i=1;i<=n;i++){
	  pa[i]=i;
	  if(root[i]!=NULL) removetree(root[i]);
	  root[i]=new Node(weight[i]);
	}
	for(int i=1;i<=m;i++)
	  if(!remove[i]) add_edge(i);
	query_tot=query_cnt=0;
	for(int i=0-1;i>=0;i--){
	  if(Cmds[i].type=='D') add_edge(Cmds[i].x);
	  if(Cmds[i].type=='Q') query(Cmds[i].x,Cmds[i].p);
	  if(Cmds[i].type=='C') change_weight(Cmds[i].x,Cmds[i].p);
	}
	printf("Case %d: %.6lf\n",kase,query_tot/(double)query_cnt);
  }
  return 0;
}
