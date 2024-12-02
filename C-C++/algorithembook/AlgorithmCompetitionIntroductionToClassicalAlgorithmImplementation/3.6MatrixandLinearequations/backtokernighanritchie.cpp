#include<bits/stdc++.h>
using namespace std;

const double eps=1e-8;
const int NN=100+10;
typedef double Matrix[NN][NN];
void gauss_jordan(Matrix A,int n){
  int i,j,k,r;
  for(i=0;i<n;i++){
	r=i;
	for(j=i+1;j<n;j++)
	  if(fabs(A[i][j])>fabs(A[r][i])) r=j;
	if(fabs(A[r][i])<eps) continue;
	if(r!=i)
	  for(j=0;j<=n;j++) swap(A[r][j],A[i][j]);
	for(k=0;k<n;k++)
	  if(k!=i)
		for(j=n;j>=i;j--) A[k][j]-=A[k][i]/A[i][i]*A[i][j];
  }
}
int main(){
  int d[NN],inf[NN];
  Matrix A;
  vector<int> pre[NN];
  for(int kase=1,n;scanf("%d",&n)==1 && n;kase++){
	memset(d,0,sizeof(d));
	for(int i=0;i<n;i++) pre[i].clear();
	for(int a,b;scanf("%d%d",&a,&b)==2 && a;pre[b].push_back(a))
	  a--,b--,d[a]++;
	memset(A,0,sizeof(A));
	for(int i=0;i<n;i++){
	  for(int j=0;j<pre[i].size();j++)
		A[i][pre[i][j]]-=1.0/d[pre[i][j]];
	  if(i==0) A[i][n]=1;
	}
  gauss_jordan(A,n);
  memset(inf,0,sizeof(inf));
  for(int i=n-1;i>=0;i--){
	if(fabs(A[i][i])<eps&&fabs(A[i][n]>eps))
	   inf[i]=1;
	   for(int j=i+1;j<n;j++)
		 if(fabs(A[i][j])>eps && inf[j])
		   inf[i]=1;
  }
  int q,u;
  scanf("%d",&q);
  printf("Case #%d:\n",kase);
  while(q--){
	scanf("%d",&u),u--;
	if(inf[u])
	  printf("infinity\n");
	else
	  printf("%.3lf\n",fabs(A[u][u])<eps ? 0.0:A[u][n]/A[u][u]);
  }
  }
  return 0;
}

			 
