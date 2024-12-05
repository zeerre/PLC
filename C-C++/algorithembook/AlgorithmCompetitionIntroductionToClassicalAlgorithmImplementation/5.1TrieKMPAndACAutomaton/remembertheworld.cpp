#include<bits/stdc++.h>
using namespace std;
const int MAXN=4000*100+10,SIGMA=26;

struct Trie{
  int ch[MAXN][SIGMA],val[MAXN],sz;
  void clear(){sz=1,fill_n(ch[0],SIGMA,0);}
  int idx(char c){return c-'a';}
  void insert(const char *s,int v){
	int u=0,n=strlen(s);
	for(int i=0;i<n;i++){
	  int c=idx(s[i]);
	  if(!ch[u][c])
		fill_n(ch[sz],SIGMA,0),val[sz]=0,ch[u][c]=sz++;
	  u=ch[u][c];
	}
	val[u]=v;
  }
  void find_prefixes(const char *s,int len,vector<int> &ans){
	int u=0;
	for(int i=0;i<len;i++){
	  if(s[i]=='\0') break;
	  int c=idx(s[i]);
	  if(!ch[u][c]) break;
	  u=ch[u][c];
	  if(val[u] !=0) ans.push_back(val[u]);
	}
  }
};
const int TL=3e5+4,WC=4000+4,MOD=20071027;
int D[TL],WLen[WC];
Trie trie;
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  string text,word;
  for(int kase=1,S;cin>>text>>S;kase++){
	trie.clear();
	for(int i=1;i<=S;i++)
	  cin>>word,WLen[i]=word.length(),trie.insert(word.c_str(),i);
	int L=text.length();
	fill_n(D,L,0),D[L]=1;
	for(int i=L-1;i>=0;i--){
	  vector<int > p;
	  trie.find_prefixes(text.c_str()+i,L-i,p);
	  for(size_t j=0;j<p.size();j++)
		(D[i]+=D[i+WLen[p[j]]])%=MOD;
	}
	printf("Case %d: %d\n",kase,D[0]);
  }
  return 0;
}
