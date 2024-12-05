#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn=500+8;
int MOD;
struct Matrix{
  int a[maxn],n;
  Matrix(int _n=1):n(_n){fill_n(a,n+1,0);}
  Matrix operator *  (const Matrix &rhs){
	Matrix m(n);
	for(int i=0;i<n;i++)
	  for(int j=0;j<n;j++)
		(m.a[i]+=(LL)a[(i-j+n)%n]*rhs.a[j]%MOD)%=MOD;
	return m;
  }
};
Matrix fast_pow(Matrix x,int n){
  Matrix m(x.n);m.a[0]=1;
  while(n){
	if(n%2) m=m*x;
	x=x*x,n/=2;
  }
  return m;
}
int main(){
  for(int d,k,n,m;scanf("%d %d %d %d",&n,&m,&d,&k)==4;){
	MOD=m;
	Matrix x(n),y(n);
	for(int i=0;i<n;++i) scanf("%d",&x.a[i]);
	fill_n(y.a,d+1,1),fill_n(y.a+n-d,d,1);
	Matrix ans=x*fast_pow(y,k);
	for(int i=0;i<n;++i) printf("%d%c",ans.a[i],"\n"[i+1==n]);
  }
  return 0;
}

