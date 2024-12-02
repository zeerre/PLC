#include<bits/stdc++.h>
using namespace std;
const int maxn=500+5;
struct BPM{
  int n,m;
  int G[maxn][maxn];
  int left[maxn];
  bool T[maxn];
  void init(int n,int m){
	this->n=n,this->m=m;
	memset(G,0,sizeof(G));
  }
  bool match(int u){
	for(int v=0;v<m;v++)
	  if(G[u][v] && !T[v]){
		T[v]=true;
		if(left[v]==-1 || match(left[v])){
		  left[v]=u;
		  return true;
		}
	  }
	return false;
  }
  int solve(){
	fill_n(left,m+1,-1);
	int ans=0;
	for(int u=0;u<n;u++){
	  fill_n(T,m+1,false);
	  if(match(u)) ans++;
	}
	return ans;
  }
};
BPM solver;
int X1[maxn],Y1[maxn],X2[maxn],Y2[maxn],T1[maxn],T2[maxn];
inline int dist(int a,int b,int c,int d){return abs(a-c)+abs(b-d);}
int main(){
  int T;
  scanf("%d",&T);
  for(int t=0,n;t<T;t++){
	scanf("%d",&n);
	for(int i=0,h,m;i<n;i++){
	  scanf("%d:%d%d%d%d%d",&h,&m,&X1[i],&Y1[i],&X2[i],&Y2[i]);
	  T1[i]=h*60+m,T2[i]=T1[i]+dist(X1[i],Y1[i],X2[i],Y2[i]);
	}
	solver.init(n,n);
	for(int i=0;i<n;i++)
	  for(int j=i+1;j<n;j++)
		if(T2[i]+dist(X2[i],Y2[i],X1[j],Y1[j])<T1[j])
		  solver.G[i][j]=1;
	printf("%d\n",n-solver.solve());
  }
  return 0;
}
