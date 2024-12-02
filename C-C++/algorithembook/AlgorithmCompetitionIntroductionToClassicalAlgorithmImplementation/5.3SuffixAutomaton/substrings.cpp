#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

template<int SZ,int SIG=32>
struct Suffix_Automaton{
  int link[SZ],len[SZ],isterminal[SZ],next[SZ][SIG],last,sz;
  inline void init(){ sz=0,last=new_node();}
  inline int new_node(){
	assert(sz+1<SZ);
	int nd=sz++;
	fill_n(next[nd],SIG,0),link[nd]=-1,len[nd]=0,isterminal[nd]=0;
	return nd;
  }
  inline int idx(char c){return c-'a';}
  inline void insert(char c){
	int p=last,cur=new_node(),x=idx(c);
	len[last=cur]=len[p]+1,isterminal[cur]=1;
	while(p!=-1 && !next[p][x]) next[p][x]=cur,p=link[p];
	if(p==-1){link[cur]=0; return;}
	int q=next[p][x];
	if(len[p]+1==len[q]){link[cur]=q; return;}
	int nq=new_node();
	copy(next[q],next[q]+SIG,next[nq]);
	link[nq]=link[q],len[nq]=len[p]+1,link[cur]=link[q]=nq;
	while(p>=0 && next[p][x]==q) next[p][x]=nq,p=link[p];
  }
  inline void build(const char* s){while (*s) insert(*s++);}
};
const int NN=250000+4;
vector<int >G[NN*2];
Suffix_Automaton<NN*2> sam;
int F[NN];
int dfs(int u){
  int s=sam.isterminal[u];
  for(size_t vi=0;vi<G[u].size();vi++) s+=dfs(G[u][vi]);
  F[sam.len[u]]=max(F[sam.len[u]],s);
  return s;
}
char S[NN];
int main(){
  scanf("%s",S);
  int N=strlen(S);
  sam.init(),sam.build(S);
  for(int u=1;u<sam.sz;u++) G[sam.link[u]].push_back(u);
  dfs(0);
  for(int l=1;l<=N;l++) printf("%d\n",F[l]);
  return 0;
}
