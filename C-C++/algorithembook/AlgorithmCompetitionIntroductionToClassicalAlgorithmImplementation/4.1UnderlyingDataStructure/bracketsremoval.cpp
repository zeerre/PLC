#include<bits/stdc++.h>

using namespace std;

const int MAXN=1024;

struct Node{
  char ch;
  Node *left,*right;
  bool enclose;
  int priority;
  Node(char c=0):ch(c),left(NULL),right(NULL),enclose(false),priority(0){
	if(ch=='*' ||ch=='/') priority=2;
	else if(ch=='+' || ch=='-') priority=1;
  }
  bool isop() const{return !islower(ch);}
  ~Node(){
	if(left) delete left;
	if(right) delete right;
  }
};
  typedef Node* PNode;
  string ex;
  PNode pRoot;
  ostream& operator<<(ostream& os,const PNode p){
	if(!p) return os;
	if(p->enclose) os<<'(';
	os<<p->left<<p->ch<<p->right;
	if(p->enclose) os<<')';
	return os;
  }
  void reverse(PNode p){
	assert(p);
	assert(p->isop());
	char c=p->ch;
	switch (c){
	case '+' : p->ch='-';break;
	case '-' : p->ch='+';break;
	case '*' : p->ch='/';break;
	case '/' : p->ch='*';break;
	default:
	  assert(false);
	}
	PNode p1=p->left,pr=p->right;
	if(p1&&p1->isop() && p1->priority==p->priority) reverse(p1);
	if(pr && pr->isop() && !pr->enclose && pr->priority == p->priority)
	  reverse(pr);
  }
  void proc(PNode p){
	assert(p);
	if(!p->isop()) return;
	PNode p1=p->left,pr=p->right;
	if(p1 && p1->isop()){
	  if(p1->priority>=p->priority) p1->enclose=false;
	  proc(p1);
	}
	if(pr&&pr->isop()){
	  if(pr->priority>p->priority) pr->enclose=false;
	  else if(pr->priority==p->priority){
		if((p->ch=='/' || p->ch=='-') && pr->enclose)
		  pr->enclose=false,reverse(pr);
		pr->enclose=false;
	  }
	  proc(pr);
	}
  }
  PNode parse(int l,int r){
	assert(l<=r);
	char lc=ex[l];
	if(l==r) return new Node(lc);
	int p=0,c1=-1,c2=-1;
	for(int i=1;i<=r;i++){
	  switch (ex[i]){
	  case'(' : p++;break;
	  case')' : p--;break;
	  case'+' : case'-': if(!p) c1=i;break;
	  case'*' : case'/': if(!p) c2=i;break;
	  }
	}
	if(c1<0) c1=c2;
	if(c1<0){
	  PNode ans=parse(l+1,r-1);
	  ans->enclose=true;
	  return ans;
	}
	PNode ans= new Node(ex[c1]);
	PNode ln=ans->left=parse(l,c1-1),rn=ans->right=parse(c1+1,r);
	assert(ans->priority);
	if(!ln->isop()) ln->enclose=false;
	if(!rn->isop()) rn->enclose=false;
	return ans;
  }
  int main(){
	while(cin>>ex){
	  pRoot=parse(0,ex.size()-1);
	  pRoot->enclose=false;
	  proc(pRoot);
	  cout<<pRoot<<endl;
	  delete pRoot;
	}
	return 0;
  }
