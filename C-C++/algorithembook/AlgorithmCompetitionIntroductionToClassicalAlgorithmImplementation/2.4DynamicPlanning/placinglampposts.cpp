#include<bits/stdc++.h>
using namespace std;

const int NN=1000+8,BASE=2000;
vector<int > G[NN];
int Vis[NN][2],D[NN][2],N,M;
int dp(int i,int j,int f){
  if(Vis[i][j]) return D[i][j];
  Vis[i][j]=1;
  int& ans=D[i][j];
  ans=BASE;
  for(int k=0;k<G[i].size();k++)
	if(G[i][k]!=f)
	  ans+=dp(G[i][k],1,i);
  if(!j&& f>=0) ans++;
  if(j||f<0){
	int sum=0;
	for(int k=0;k<G[i].size();k++)
	  if(G[i][k]!=f) sum+=dp(G[i][k],0,i);
	if(f>=0) sum++;
	ans = min(ans,sum);
  }
  return ans;
}
int main(){
  int T,a,b;
  scanf("%d",&T);
  while(T--){
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++) G[i].clear();
	for(int i=0,a,b;i<M;i++)
	  scanf("%d%d",&a,&b),G[a].push_back(b),G[b].push_back(a);
	memset(Vis,0,sizeof(Vis));
	int ans=0;
	for(int i=0;i<N;i++)
	  if(!Vis[i][0]) ans+=dp(i,0,-1);
	printf("%d %d %d\n",ans/BASE,M-ans%BASE,ans%BASE);
  }
  return 0;
}
