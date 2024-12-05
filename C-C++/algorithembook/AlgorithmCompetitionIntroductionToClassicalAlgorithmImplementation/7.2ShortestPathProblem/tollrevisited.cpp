#include<bits/stdc++.h>
using namespace std;
const int NN=52+10;
const long long INF=1LL<<60;
typedef long long LL;
int N,G[NN][NN],St,Ed,P,Vis[NN];
LL D[NN];
int read_node(){
  char s[9];
  scanf("%s",s);
  if(isupper(s[0])) return s[0]-'A';
  return s[0]-'a'+26;
}
char node_label(int u){return u<26 ? 'A'+u : 'a'+(u-26);}
LL forward(LL k,int u){
  if(u<26) return k-(k+19)/20;
  return k-1;
}
LL back(int u){
  if(u>=26) return D[u]+1;
  LL X=D[u]*20/19;
  while(forward(X,u)<D[u]) X++;
  return X;
}
void solve(){
  N=52;
  fill_n(Vis,N+1,0),fill_n(D,N,INF);
  D[Ed]=P,Vis[Ed]=1;
  for(int i=0;i<N;i++)
	if(i!=Ed && G[i][Ed]) D[i]=back(Ed);
  while(!Vis[St]){
	int minu=-1;
	for(int i=0;i<N;i++)
	  if(!Vis[i] && (minu<0 || D[i]<D[minu])) minu=i;
	Vis[minu] =1;
	for(int i=0;i<N;i++)
	  if(!Vis[i] && G[i][minu]) D[i]=min(D[i],back(minu));
  }
  printf("%lld\n%c",D[St],node_label(St));
  LL k=D[St];
  for(int u=St,next;u!=Ed;u=next){
	for(next=0;next<N;next++)
	  if(G[u][next] && forward(k,next)>=D[next]) break;
	k=D[next];
	printf("-%c",node_label(next));
	u=next;
  }
  puts("");
}
int main(){
  for(int kase=1;scanf("%d",&N) ==1 &&  N>=0;kase++){
	memset(G,0,sizeof(G));
	for(int i=0;i<N;i++){
	  int u=read_node(),v=read_node();
	  if(u!=v) G[u][v]=G[v][u]=1;
	}
	scanf("%d",&P);
	St=read_node(),Ed=read_node();
	printf("Case %d: \n",kase);
	solve();
  }
  return 0;
}
