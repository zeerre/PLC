#include<bits/stdc++.h>
using namespace std;

template<int SZ,int SIG=32>
struct Suffix_Automaton{
  int link[SZ],len[SZ],last,sz;
  map<char,int>next[SZ];
  inline void init(){sz=0,last=new_node();}
  inline int new_node(){
	assert(sz+1<SZ);
	int nd=sz++;
	next[nd].clear(),link[nd]=-1,len[nd]=0;
	return nd;
  }
  inline void insert(char x){
	int p=last,cur=new_node();
	len[last=cur]=len[p]+1;
	while(p!=-1 && next[p].count(x)) next[p][x]=cur,p=link[p];
	if(p==-1) {link[cur]=0;return;}
	int q=next[p][x];
	if(len[p]+1==len[q]){ link[cur]=q;return;}
	int nq=new_node();
	next[nq]=next[q];
	link[nq]=link[q],len[nq]=len[p]+1,link[cur]=link[q]=nq;
	while(p>=0 && next[p][x]==q) next[p][x]=nq,p=link[p];
  }
  inline void build(const char* s){while (*s) insert(*s++);}
};
const int NN=5e5+5;
Suffix_Automaton<NN> sam;
int lcs(char* s){
  int p=0,l=0,ans=0;
  map<char,int>* nxt=sam.next;
  while(*s){
	char x=*s++;
	if(nxt[p].count(x)) p=nxt[p][x],l++;
	else{
	  while(p!=-1 && !nxt[p].count(x)) p=sam.link[p];
	  if(p!=-1) l=sam.len[p]+1,p=nxt[p][x];
	  else p=0,l=0;
	}
	ans=max(ans,l);
  }
  return ans;
}
char S[NN];
int main(){
  scanf("%s",S),sam.init(),sam.build(S);
  scanf("%s",S),printf("%d",lcs(S));
  return 0;
}
