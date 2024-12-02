#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
struct Node{
  Node *left,*right;
  int val;
  Node():left(nullptr),right(nullptr){}
  ~Node(){
	if(left) delete left;
	if(right) delete right;
	left=right=nullptr;
  }
};
const int MAXN=10000+4;
int In[MAXN] ,Post[MAXN],N;
int parse(const string &str,int *p){
  stringstream ss(str);
  int n=0,x;
  while(ss>>x) p[n++]=x;
  return n;
}
Node *parseTree(int i1,int i2,int p1,int p2){//In[i1,i2],Post[p1,p2]
  assert(i1<=i2&& p1<=p2);
  Node *p=new Node();
  int m=Post[p2];
  p->val=m;
  if(i1==i2){
	assert(p1==p2&&In[i1]==Post[p2]);
	return p;
  }
  int ri=find(In+i1,In+i2+1,m)-In,
	lLen=ri-i1;
  if(i1<=ri-1) p->left=parseTree(i1,ri-1,p1,p1+lLen-1);
  if(ri+1<i2) p->right=parseTree(ri+1,i2,p1+lLen,p2-1);
  return p;
}
ostream &operator<<(ostream &os,Node *pn){
  if(pn->left) os<<"("<<pn->left<<")";
  os<<pn->val;
  if(pn->right) os<<"("<<pn->right<<")";
  return os;
}
void dfs(int sum,Node *p,int &minSum,int &minLeaf){
  assert(p);
  if(p->left || p->right){
	if(p->left && sum+p->left->val<=minSum)
	  dfs(sum+p->left->val,p->left,minSum,minLeaf);
	if(p->right && sum+p->right->val<=minSum)
	  dfs(sum+p->right->val,p->right,minSum,minLeaf);
  }else{
	if(sum<minSum)
	  minSum=sum,minLeaf=p->val;
	else if(sum==minSum)
	  minLeaf=min(p->val,minLeaf);
  }
}
int main(){
  string l1,l2;
  while(getline(cin,l1) && getline(cin,l2)){
	N=parse(l1,In);
	assert(N==parse(l2,Post));
	Node *pTree=parseTree(0,N-1,0,N-1);
	int minSum=INT_MAX,minLeaf=INT_MAX;
	dfs(pTree->val,pTree,minSum,minLeaf);
	delete pTree;
	cout<<minLeaf<<endl;
  }
  return 0;
}
