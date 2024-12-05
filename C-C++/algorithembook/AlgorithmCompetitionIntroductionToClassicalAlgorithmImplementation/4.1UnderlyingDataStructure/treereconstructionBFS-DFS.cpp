#include<bits/stdc++.h>

using namespace std;

#define _for(i,a,b) for(int i=(a);i<(b);++i)
#define _rep(i,a,b) for(int i=(a);i<=(b);++i)

typedef vector<int> IVec;
typedef long long LL;
const int NN=1004;
int N,B[NN],D[NN],BIdx[NN];
IVec G[NN];
void solve(int l,int r){
  int u=D[l],i=l+1,lasti=i;;
  assert(l<=r);
  if(l==r) return;
  G[u].push_back(D[i++]);
  while(i<=r){
	int lastv=G[u].back(),v=D[i];
	if(v>lastv && BIdx[lastv]+1==BIdx[v])
	  solve(lasti,i-1),G[u].push_back(v),lasti=i;
	++i;
  }
  solve(lasti,i-1);
}
int main(){
  while(scanf("%d",&N)==1){
	_rep(i,1,N) scanf("%d",&(B[i])),BIdx[B[i]]=i,G[i].clear();
	_rep(i,1,N) scanf("%d",&(D[i]));
	solve(1,N);
	_rep(i,1,N){
	  printf("%d:",i);
	  for(size_t vi=0;vi<G[i].size();vi++)
		printf(" %d",G[i][vi]);
	  puts("");
	}
  }
  return 0;
}
