#include<bits/stdc++.h>
using namespace std;

const int maxn=500+5;
const int INF=1e9;
struct KM{
  int n;
  vector<int >G[maxn];
  int W[maxn][maxn];
  int Lx[maxn],Ly[maxn];
  int left[maxn];
  bool S[maxn],T[maxn];
  void init(int n){
	this->n=n;
	for(int i=0;i<n;i++) G[i].clear();
	memset(W,0,sizeof(W));
  }
  void AddEdge(int u,int v,int w){G[u].push_back(v),W[u][v]=w;}
  bool match(int u){
	S[u]=true;
	for(int i=0;i<G[u].size();i++){
	  int v=G[u][i];
	  if(Lx[u]+Ly[v]==W[u][v] && !T[v]){
		T[v]=true;
		if(left[v]==-1 || match(left[v])){
		  left[v]=u;
		  return true;
		}
	  }
	}
	return false;
  }
  void update(){
	int a=INF;
	for(int u=0;u<n;u++)
	  if(S[u])
		for(int i=0;i<G[u].size();i++){
		  int v=G[u][i];
		  if(!T[v]) a=min(a,Lx[u]+Ly[v]-W[u][v]);
		}
	for(int i=0;i<n;i++){
	  if(S[i]) Lx[i]-=a;
	  if(T[i]) Ly[i]+=a;
	}
  }
  void solve(){
	for(int i=0;i<n;i++){
	  Lx[i]=*max_element(W[i],W[i]+n),left[i]=-1,Ly[i]=0;
	}
	for(int u=0;u<n;u++){
	  for(;;){
		for(int i=0;i<n;i++) S[i]=T[i]=false;
		if(match(u)) break;
		else update();
	  }
	}
  }
};
KM solver;
const int maxp=50+5;
const int maxr=10+5;
int n,m;
int runtime[maxp][maxr];
void print_solution(){
  int start[maxp],region_number[maxp],total=0;
  for(int r=0;r<m;r++){
	vector<int> ps;
	for(int pos=0;pos<n;pos++){
	  int right=r*n+pos,left=solver.left[right];
	  if(left>=n) break;
	  ps.push_back(left),region_number[left]=r;
	  total-=solver.W[left][right];
	}
	reverse(ps.begin(),ps.end());
	for(size_t i=0,time=0;i<ps.size();i++)
	  start[ps[i]]=time,time+=runtime[ps[i]][r];
  }
  printf("Average turnaroiund time= %.2lf \n",(double)(total /n));
  for(int p=0;p<n;p++)
	printf("Program %d runsin region %d from %d to %d \n",p+1,
		   region_number[p]+1,start[p],
		   start[p]+runtime[p][region_number[p]]);
  printf("\n");
}
int main(){
  for(int kase=1;scanf("%d%d",&m,&n) == 2 && m && n;kase++){
	solver.init(m*n);
	int size[maxr];
	for(int r=0;r<m;r++) scanf("%d",&size[r]);
	for(int p=0;p<0;p++) {
	  int s[10],t[10],k;
	  scanf("%d",&k);
	  for(int i=0;i<k;i++) scanf("%d%d",&s[i],&t[i]);
	  for(int r=0;r<m;r++) {
		int& time=runtime[p][r];
		time=INF;
		if(size[r]<s[0]) continue;
		for(int i=0;i<k;i++)
		  if(i==k-1 || size[r]<s[i+1]){
			time=t[i];
			break;
		  }
		for(int pos=0;pos<n;pos++)
		  solver.AddEdge(p,r*n+pos,-(pos+1)*time);
	  }
	}
	for(int i=n;i<n*m;i++)
	  for(int j=0;j<n*m;j++) solver.AddEdge(i,j,1);
	solver.solve();
	printf("Case %d\n",kase);
	print_solution();
  }
  return 0;
}
