#include<bits/stdc++.h>
using namespace std;

const int NN=1e5+8;
typedef long long LL;
int Low[NN],Pre[NN],DfsClock,IsCut[NN],BccNo;
vector<int > G[NN],Bcc[NN];

stack<int> S;
void init(int &n){
  for(int i=1;i<=n;++i)
	G[i].clear(),Pre[i]=0,IsCut[i]=0;
  n=BccNo=DfsClock=0;
}
void tarjan(int u,int root){
  Pre[u]=Low[u]=++DfsClock,S.push(u);
  int child=0;
  for(auto v:G[u]){
	if(!Pre[v]){
	  tarjan(v,root);
	  Low[u]=min(Low[u],Low[v]),child++;
	  if(Low[v]==Pre[u]){
		Bcc[++BccNo].clear();
		for(int x=0;x!=v;S.pop()) Bcc[BccNo].push_back(x=S.top());
		Bcc[BccNo].push_back(u);
	  }
	  if(u!=root&&Low[v]>=Pre[u]) IsCut[u]=1;
	}
	else
	  Low[u]=min(Low[u],Pre[v]);
  }
  if(u==root && child>1) IsCut[u]=1;
}
int main(){
  for(int kase=1,n,m;scanf("%d",&m) ==1 && m;++kase){
	init(n);
	for(int i=1,x,y;i<=m;++i){
	  scanf("%d%d",&x,&y),n=max(n,max(x,y));
	  G[x].push_back(y),G[y].push_back(x);
	}
	for(int i=1;i<=n;++i) if(!Pre[i]) tarjan(i,i);
	printf("Case %d: ",kase);
	LL ans1=0,ans2=1;
	for(int i=1;i<=BccNo;++i){
	  int cutCnt=0,sz=Bcc[i].size();
	  for(int vi=0;vi<sz;vi++) if(IsCut[Bcc[i][vi]]) cutCnt++;
	  if(cutCnt==0) ans1+=2,ans2*=1LL*sz*(sz-1)/2;
	  else if(cutCnt==1) ans1++ ,ans2*=sz-1;
	}
	printf(" %lld %lld\n",ans1,ans2);
  }
  return 0;
}
