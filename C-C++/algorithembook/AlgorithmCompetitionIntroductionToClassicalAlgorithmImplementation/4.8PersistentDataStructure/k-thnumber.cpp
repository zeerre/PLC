#include<bits/stdc++.h>
using namespace std;
#define _for(i,a,b) for(int i=(a);i<(int)(b);++i)
const int MAXN=100000+4;
struct Node;
typedef Node* PNode;
struct Node{
  int count;
  PNode left,right;
  Node(int count=0,PNode left=NULL,PNode right=NULL)
	:count(count),left(left),right(right){}
  PNode insert(int l,int r,int w);
};
const PNode Null=new Node();
PNode Node::insert(int l,int r,int w){
  if(l<=w && w<r){
	if(l+1==r) return new Node(count+1,Null,Null);
	int m=(l+r)/2;
	return new Node(count+1,left->insert(l,m,w),right->insert(m,r,w));
  }
  return this;
}
int query(PNode a,PNode b,int l,int r,int k){
  if(l+1==r) return l;
  int m=(l+r)/2;
  int count=a->left->count-b->left->count;
  if(count>=k) return query(a->left,b->left,l,m,k);
  return query(a->right,b->right,m,r,k-count);
}
int A[MAXN],RM[MAXN];
PNode VER[MAXN];
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  Null->left=Null->right=Null;
  int n,m,maxa=0;
  cin>>n>>m;
  map<int,int> M;
  _for(i,0,n) cin>>A[i],M[A[i]]=0;
  for(map<int ,int>::iterator p=M.begin();p!=M.end();p++)
	p->second=maxa,RM[maxa]=p->first,maxa++;
  VER[0]=Null;
  _for(i,0,n) VER[i+1]=VER[i]->insert(0,maxa,M[A[i]]);
  for(int i=0,u,v,k;i<m;i++){
	cin>>u>>v>>k;
	int ans=query(VER[v],VER[u-1],0,maxa,k);
	cout<<RM[ans]<<endl;
  }
  return 0;
}
