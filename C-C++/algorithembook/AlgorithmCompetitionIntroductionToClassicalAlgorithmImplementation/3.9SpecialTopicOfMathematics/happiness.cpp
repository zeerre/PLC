#include <bits/stdc++.h>

using namespace std;
const int maxm=500;
const int maxn=500;
const double INF=1e100,eps=1e-10;
struct Simplex{
  int n;
  int m;
  double a[maxm][maxn];
  int B[maxm],N[maxn];
  void pivot(int r,int c){
	swap(N[c],B[r]);
	a[r][c]=1/a[r][c];
	for(int j=0;j<=n;j++) if(j!=c) a[r][j]*=a[r][c];
	for(int i=0;i<=m;i++) if(i!=r){
		for(int j=0;j<=n;j++) if(j!=c) a[i][j]-=a[i][c]*a[r][c];
	  }
  }
  bool feasible(){
	for(;;){
	  int r,c;
	  double p=INF;
	  for(int i=0;i<m;i++) if(a[i][n]<p) p=a[r=i][n];
	  if(p>-eps) return true;
	  p=0;
	  for(int i=0;i<n;i++) if(a[r][i]<p) p=a[r][c=i];
	  if(p>-eps) return false;
	  p=a[r][n]/a[r][c];
	  for(int i=r+1;i<m;i++) if(a[i][c]>eps){
		  double v=a[i][n]/a[i][c];
		  if(v<p) {r=i;p=v;}
		}
	  pivot(r,c);
	}
  }
  int simplex(int n,int m,double x[maxn],double& ret){
	this->n=n;
	this->m=m;
	for(int i=0;i<n;i++) N[i]=i;
	for(int i=0;i<m;i++) B[i]=n+i;
	if(!feasible()) return 0;
	for(;;){
	  int r,c;
	  double p=0;
	  for(int i=0;i<n;i++) if(a[m][i]>p) p=a[m][c=i];
	  if(p<eps){
		for(int i=0;i<n;i++) if(N[i]<n) x[N[i]]=0;
		for(int i=0;i<m;i++) if(B[i]<n) x[B[i]]=a[i][n];
		ret=-a[m][n];
		return 1;
	  }
	  p=INF;
	  for(int i=0;i<m;i++) if(a[i][c]>eps){
		  double v=a[i][n]/a[i][c];
		  if(v<p){r=i;p=v;}
		}
	  if(p==INF) return -1;
	  pivot(r,c);
	}
  }
};
Simplex solver;
int main(){
  for(int n,m;scanf("%d%d",&n,&m)==2;){
	for(int i=0;i<n;i++) scanf("%lf",&solver.a[m][i]);
	solver.a[m][n]=0;
	for(int i=0;i<m;i++)
	  for(int j=0;j<n+1;j++)
		scanf("%lf",&solver.a[i][j]);
	double ans,x[maxn];
	assert(solver.simplex(n,m,x,ans)==1);
	ans*=m;
	printf("Nasa can spend %d taka.\n",(int)floor(ans+1-eps));
  }
  return 0;
}

		   
