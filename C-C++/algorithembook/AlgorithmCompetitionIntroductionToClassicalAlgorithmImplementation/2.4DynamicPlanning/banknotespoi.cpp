#include<bits/stdc++.h>
using namespace std;

const int NN=210,MM=20010,INF=0x3f3f3f3f;
typedef pair<int,int> IPair;
int N,A[NN],C[NN],M,F[MM];
struct Item{int fk,k;};
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  cin>>N;
  memset(F,0x3f,sizeof(F));F[0]=0;
  for(int i=1;i<=N;++i) cin>>A[i];
  for(int i=1;i<=N;++i) cin>>C[i];
  cin>>M;
  deque<Item> Q;
  for(int i=1;i<=N;++i){
	int a=A[i];
	for(int r=0;r<a;++r){
	  Q.clear();
	  /*
		f(i,r+xa)=min(f(i-1,r+ya)+x-y),y<x<y+c[i]
		f(i,r+xa)-x=min(f(i-1,r+ya)-y)
	  */
	  for(int k=0;k*a+r<=M;++k){
		int x=k*a+r;
		while(!Q.empty() && k-Q.front().k>C[i]) Q.pop_front();
		while(!Q.empty() && F[x]-k<=Q.front().fk) Q.pop_back();
		Q.push_back({F[x]-k,k});
		F[x]=min(F[x],Q.front().fk+k);
	  }
	}
  }
  cout<<F[M]<<endl;
  return 0;
}
