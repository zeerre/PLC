#include<bits/stdc++.h>
using namespace std;

#define _for(i,a,b) for(int i=(a);i<(b);++i)
typedef long long LL;

struct Node{
  Node *left,*right;
  int val;
  bool hasValue;
  Node():left(nullptr),right(nullptr),val(0),hasValue(false){}
  ~Node(){
	if(left) delete left;
	if(right) delete right;
  }
};
typedef Node* PNode;
bool insert(PNode p,int val,const char* path){
  assert(p);
  int len=strlen(path);
  _for(i,0,len){
	char c=path[i];
	if(c=='L'){
	  if(!p->left) p->left=new Node();
	  p=p->left;
	}else if(c=='R'){
	  if(!p->right) p->right=new Node();
	  p=p->right;
	}
  }
  p->val=val;
  if(p->hasValue) return false;
  return p->hasValue=true;
}
bool bfs(PNode p,vector<int>& ans){
  queue<PNode> Q;
  ans.clear(),Q.push(p);
  while(!Q.empty()){
	p=Q.front();Q.pop();
	if(!p->hasValue) return false;
	ans.push_back(p->val);
	if(p->left) Q.push(p->left);
	if(p->right) Q.push(p->right);
  }
  return true;
}
int main(){
  char s[512];
  int v;
  vector<int> ans;
  while(true){
	Node nd,*root=&nd;
	bool valid=true;
	while(true){
	  if(scanf("%s",s)!=1) return 0;
	  if(strcmp(s,"()")==0) break;
	  sscanf(s+1,"%d",&v);
	  if(!insert(root,v,strchr(s,',')+1)) valid=false;
	}
	if(valid&& bfs(root,ans))
	  for(size_t i=0;i<ans.size();i++)
		printf("%d%s",ans[i],(i==ans.size()-1?"\n":" "));
	else
	  //puts("not complete!");
	  puts("-1");
  }
  return 0;
}
