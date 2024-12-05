#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int NN=10000+4;
int N,S,T[NN],C[NN],Q[NN],G[NN],D[NN];
inline double f(int k,int i){
  return (double)(D[k]-D[i])/(Q[k]-Q[i]);
}
int main(){
  scanf("%d%d",&N,&S);
  Q[N+1]=G[N+1]=D[N+1]=0;
  for(int i=1;i<=N;i++) scanf("%d%d",&(T[i]),&(C[i]));
  deque<int > q;
  q.push_back(N+1);
  for(int i=N;i>=1;i--){
	Q[i]=T[i]+Q[i+1],G[i]=C[i]+G[i+1];
	while(q.size()>=2&&f(q[0],q[1])<(double)G[i])
	  q.pop_front();
	D[i]=D[q[0]]+(S+Q[q[0]])*G[i];
	while(q.size()>=2&&f(q[q.size()-2],q.back())>f(q.back(),i))
	  q.pop_back();
	q.push_back(i);
  }
  printf("%d\n",D[1]);
  return 0;
}
