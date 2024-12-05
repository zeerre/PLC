#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define _for(i,a,b) for(int i=(a);i<(int)(b);++i)
#define _rep(i,a,b) for(int i=(a);i<=(int)(b);++i)

const int NN=200010,MM=10010;
int N,M,D,NodeId[NN],root,cmp_dim,BLOCK;
struct Point{int x,y;} PS[NN];
struct Query{
  int l,r,id;
  bool operator<(const Query& q) const{
	if(l/BLOCK!=q.l/BLOCK) return l/BLOCK<q.l/BLOCK;
	return r<q.r;
  }
}QS[MM];
LL Ans[MM];
inline bool inRange(int x,int l,int r){return l<=x && x<=r;}
struct KDTree{
  int xy[2],xyMax[2],xyMin[2],CH[2],cnt,cntSum,fa;
  bool operator<(const KDTree& k) const{return xy[cmp_dim]<k.xy[cmp_dim];}
  inline int query(int x1,int x2,int y1,int y2);
  inline void update();
  inline void init(int i);
}Tree[NN];
inline int KDTree::query(int x1,int x2,int y1,int y2){
  int k=0;
  if(xyMin[0]>x2||xyMax[0]<x1 || xyMin[1]>y2 || xyMax[1]<y1 ||0==cntSum)
	return 0;
  if(x1<=xyMin[0]&& xyMax[0]<=x2 && y1<=xyMin[1] && xyMax[1]<=y2)
	return cntSum;
  if(inRange(xy[0],x1,x2) && inRange(xy[1],y1,y2))
	k+=cnt;
  _for(i,0,2) if(CH[i])
	k+=Tree[CH[i]].query(x1,x2,y1,y2);
  return k;
}
inline void KDTree::update(){
  _for(i,0,2) if(CH[i]) _for(j,0,2){
	  xyMax[j]=max(xyMax[j],Tree[CH[i]].xyMax[j]);
	  xyMin[j]=min(xyMin[j],Tree[CH[i]].xyMin[j]);
	}
}
inline void KDTree::init(int i){
  NodeId[fa]=i;
  _for(j,0,2) xyMax[j]=xyMin[j]=xy[j];
  cnt=cntSum=0;
  CH[0]=CH[1]=0;
}
int build(int l,int r,int dim,int fa){
  int mid=(l+r)/2;
  cmp_dim=dim;nth_element(Tree+l+1,Tree+mid+1,Tree+r+1);
  KDTree& n=Tree[mid];
  n.init(mid),NodeId[n.fa]=mid,n.fa=fa;
  if(l<mid) n.CH[0]=build(l,mid-1,!dim,mid);
  if(r>mid) n.CH[1]=build(mid+1,r,!dim,mid);
  n.update();
  return mid;
}
LL curAns;
inline void addPos(int i){
  curAns +=Tree[root].query(PS[i].x-D,PS[i].x+D,PS[i].y-D,PS[i].y+D);
  int ti=NodeId[i];
  Tree[ti].cnt=1;
  while(ti) Tree[ti].cntSum++,ti=Tree[ti].fa;
}
inline void delPos(int i){
  int ti=NodeId[i];
  Tree[ti].cnt=0;
  while(ti) Tree[ti].cntSum--,ti=Tree[ti].fa;
  curAns-=Tree[root].query(PS[i].x-D,PS[i].x+D,PS[i].y-D,PS[i].y+D);
}
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  for(int t=1,x,y;cin>>N>>D>>M;t++){
	printf("Case %d:\n",t);
	BLOCK=(int)sqrt(N+0.5);
	_rep(i,1,N){
	  KDTree &nd=Tree[i];
	  cin>>x>>y;
	  nd.xy[0]=PS[i].x=x+y,nd.xy[1]=PS[i].y=x-y,Tree[i].fa=i;
	}
	root=build(1,N,0,0);
	_rep(i,1,M) cin>>QS[i].l>>QS[i].r,QS[i].id=i;
	sort(QS+1,QS+M+1);
	int curL=1,curR=0;
	curAns=0;
	_rep(i,1,M){
	  while(curR<QS[i].r) addPos(++curR);
	  while(curR>QS[i].r) delPos(curR--);
	  while(curL<QS[i].l) delPos(curL++);
	  while(curL>QS[i].l) addPos(--curL);
	  Ans[QS[i].id]=curAns;
	}
	_rep(i,1,M) printf("%lld\n",Ans[i]);
  }
  return 0;
}
