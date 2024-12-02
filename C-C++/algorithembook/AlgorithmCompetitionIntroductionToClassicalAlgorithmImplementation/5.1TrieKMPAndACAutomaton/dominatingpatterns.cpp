#include<bits/stdc++.h>
using namespace std;

const int SIGMA=26,MAXN=11000,MAXS=150+10;
map<string,int > ms;
struct AhoCorasickAutomata{
  int ch[MAXN][SIGMA];
  int f[MAXN];
  int val[MAXN];
  int last[MAXN];
  int cnt[MAXS],sz;
  void init(){
	sz=1,fill_n(ch[0],SIGMA,0),fill_n(cnt,MAXS,0),ms.clear();
  }
  int idx(char c){return c-'a';}
  void insert(char* s,int v){
	int u=0,n=strlen(s);
	for(int i=0;i<n;i++){
	  int c=idx(s[i]);
	  if(!ch[u][c]) fill_n(ch[sz],SIGMA,0),val[sz]=0,ch[u][c]=sz++;
	  u=ch[u][c];
	}
	val[u]=v,ms[string(s)]=v;
  }
  void print(int j){
	if(j) cnt[val[j]]++,print(last[j]);
  }
  void find(char* T){
	int n=strlen(T),j=0;
	for(int i=0;i<n;i++){
	  int c=idx(T[i]);
	  while(j && !ch[j][c]) j=f[j];
	  j=ch[j][c];
	  if(val[j])
		print(j);
	  else if(last[j])
		print(last[j]);
	}
  }
  void getFail(){
	queue<int> q;
	f[0]=0;
	for(int c=0;c<SIGMA;c++){
	  int u=ch[0][c];
	  if(u) f[u]=0,q.push(u),last[u]=0;
	}
	while(!q.empty()){
	  int r=q.front();
	  q.pop();
	  for(int c=0;c<SIGMA;c++){
		int u=ch[r][c];
		if(!u) continue;
		q.push(u);
		int v=f[r];
		while(v && !ch[v][c]) v=f[v];
		f[u]=ch[v][c],last[u]=val[f[u]]?f[u]:last[f[u]];
	  }
	}
  }
};
AhoCorasickAutomata ac;
char text[1000001],P[MAXS][80];
int main(){
  for(int n;scanf("%d",&n)==1 && n;){
	ac.init();
	for(int i=1;i<=n;i++) scanf("%s",P[i]),ac.insert(P[i],i);
	ac.getFail();
	scanf("%s",text),ac.find(text);
	int best=*max_element(ac.cnt+1,ac.cnt+n+1);
	printf("%d\n",best);
	for(int i=1;i<=n;i++)
	  if(ac.cnt[ms[string(P[i])]]==best) printf("%s\n",P[i]);
  }
  return 0;
}
