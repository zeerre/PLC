#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
struct Node{
  LL sum,maxp;
  Node *left,*right;
  int val;
  inline bool isleaf(){return !left && !right;}
  inline void init(){memset(this,0,sizeof(Node));}
  inline void delchildren(){
	if(left) delete left;
	if(right) delete right;
	left=right=nullptr;
  }
  ~Node(){delchildren();}
};
typedef Node* PN;
int N;
PN root;
void maintain(Node& p){
  p.sum=p.left->sum+p.right->sum;
  p.maxp=max(p.left->maxp,p.left->sum+p.right->maxp);
}
void setval(Node& p,int v ,int L,int R){
  assert(L<=R);
  p.sum=(LL)(p.val=v)*(R-L+1);
  p.maxp=max(0LL,p.sum);
  p.delchildren();
}
void pushdown(Node& p,int L ,int R){
  int M=(L+R)/2;
  p.left=new Node(),p.right=new Node();
  setval(*(p.left),p.val,L,M),setval(*(p.right),p.val,M+1,R);
}
void modify(int l,int r,int v,Node& p=*root,int nL=1,int nR=N){
  int M=(nL+nR)/2;
  if(l<=nL&&nR<=r){
	setval(p,v,nL,nR);
	return;
  }
  if(p.isleaf()) pushdown(p,nL,nR);
  if(l<=M) modify(l,r,v,*(p.left),nL,M);
  if(r>M) modify(l,r,v,*(p.right),M+1,nR);
  maintain(p);
}
int query(LL h,Node& p=*root,int L=1,int R=N){
  if(h>=p.maxp) return R;
  if(p.isleaf()) return L+(h/p.val)-1;
  int M=(L+R)/2;
  Node& p1=*(p.left);
  return h>=p1.maxp?query(h-p1.sum,*(p.right),M+1,R) : query(h,p1,L,M);
}
void dbgprint(Node& p=*root,int L=1,int R=N){
  if(p.isleaf()){
	for(int i=L;i<=R;i++) printf("%d ",p.val);
	return;
  }
  int M=(L+R)/2;
  dbgprint(*(p.left),L,M),dbgprint(*(p.right),M+1,R);
}
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  cin>>N;
  string s;
  root=new Node();
  for(int a,b,d,h;cin>>s&&s[0]!='E';){
	if(s[0]=='I') cin>>a>>b>>d,modify(a,b,d);
	else cin>>h,cout<<query(h)<<endl;
  }
  delete root;
  return 0;
}
