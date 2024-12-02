#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int NN=100010,LN=20;
struct Edge{
  int v,next;
}ES[NN*2];
int Next[NN],EC=0;
void add_edge(int x,int y){
  ES[++EC]={y,Next[x]};
  Next[x]=EC;
}
stack<int> Stk;
int Dep[NN],fa[NN][NN],BlkId[NN],BLOCK,BlkCnt=0,
  C[NN],CNT[NN],VIS[NN],MC=0,QC=0,CBak[NN];
LL V[NN],W[NN],CurAns=0,Ans[NN];
void dfs(int x){
  Dep[x]=Dep[fa[x][0]]+1;
  for(int i=1;(1<<i)<=Dep[x];i++) fa[x][i]=fa[fa[x][i-1]][i-1];
  size_t now=Stk.size();
  for(int i=Next[x];i;i=ES[i].next){
	int v=ES[i].v;
	if(v==fa[x][0]) continue;
	fa[v][0]=x;
	dfs(v);
	if(Stk.size()-now>BLOCK){
	  BlkCnt++;
	  while(Stk.size()>now) BlkId[Stk.top()]=BlkCnt,Stk.pop();
	}
  }
  Stk.push(x);
  if(x==1){
	BlkCnt++;
	while(!Stk.empty()) BlkId[Stk.top()] = BlkCnt,Stk.pop();
  }
}
int LCA(int x,int y){
  if(Dep[x]<Dep[y]) swap(x,y);
  for(int i=LN;i>=0;i--)
	if((1<<i)<=Dep[x]-Dep[y]) x=fa[x][i];
  if(x==y) return x;
  for(int i=LN;i>=0;i--)
	if(Dep[x]>=(1<<i) && fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
  return fa[x][0];
}
struct Modify{
  int pos,color,old_color;
}MS[NN];
struct Query{
  int x,y,time,id;
  bool operator<(const Query& b) const{
	if(BlkId[x]!=BlkId[b.x]) return BlkId[x]<BlkId[b.x];
	if(BlkId[y]!=BlkId[b.y]) return BlkId[y]<BlkId[b.y];
	return time<b.time;
  }
}QS[NN];
inline void add_pos(int u){CurAns+=W[++CNT[C[u]]]*V[C[u]];}
inline void del_pos(int u){CurAns-=W[CNT[C[u]]--]*V[C[u]];}
inline void modify(int u,int c){
  if(VIS[u])
	del_pos(u),C[u]=c,add_pos(u);
  else
	C[u]=c;
}
inline void invert(int u){
  if(VIS[u])
	VIS[u]=0,del_pos(u);
  else
	VIS[u]=1,add_pos(u);
}
inline void mark(int u,int l){
  for(int x=u;x!=l;x=fa[x][0]) invert(x);
}
int main(){
  int N,M,Q;
  scanf("%d%d%d",&N,&M,&Q);
  BLOCK=(int)(pow(N,2.0/3)/2);
  for(int i=1;i<=M;i++) scanf("%lld",&V[i]);
  for(int i=1;i<=N;i++) scanf("%lld",&W[i]);
  for(int i=1,u,v;i<N;i++)
	scanf("%d%d",&u,&v),add_edge(u,v),add_edge(v,u);
  for(int i=1;i<=N;i++) scanf("%d",&C[i]),CBak[i]=C[i];
  dfs(1);
  for(int i=1,op;i<=Q;i++){
	scanf("%d",&op);
	if(op==0){
	  Modify& m=MS[++MC];
	  scanf("%d%d",&m.pos,&m.color);
	  m.old_color=C[m.pos],C[m.pos]=m.color;
	}else{
	  Query& q=QS[++QC];
	  scanf("%d%d",&q.x,&q.y),q.time=MC,q.id=QC;
	  if(BlkId[q.x]>BlkId[q.y]) swap(q.x,q.y);
	}
  }
  sort(QS+1,QS+1+QC);
  for(int i=1;i<=N;i++) C[i]=CBak[i];
  int X=1,Y=1;
  QS[0].time=0;
  for(int i=1;i<=QC;i++){
	const Query& q=QS[i];
	int l=LCA(q.x,X),l2=LCA(q.y,Y),last=QS[i-1].time;
	mark(X,1),mark(q.x,1),mark(Y,l2),mark(q.y,l2);
	X=q.x,Y=q.y,l=LCA(X,Y);
	invert(l);
	for(int t=last+1;t<=q.time;t++) modify(MS[t].pos,MS[t].color);
	for(int t=last;t>q.time;t--) modify(MS[t].pos,MS[t].old_color);
	Ans[q.id]=CurAns;
	invert(l);
  }
  for(int i=1;i<=QC;i++) printf("%lld\n",Ans[i]);
  return 0;
}
