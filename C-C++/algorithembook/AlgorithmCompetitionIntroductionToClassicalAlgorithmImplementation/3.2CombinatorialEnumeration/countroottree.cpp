#include<bits/stdc++.h>
using namespace std;

const int MOD=1e9+7,MAXN=1024;
typedef long long LL;
LL A[MAXN];
void init(){
  A[1]=A[2]=1;
  for(int i=3;i<MAXN;++i){
	LL& a=A[i];
	a=0;
	for(int j=1;j<i;j++)
	  if((i-1)%j==0) (a+=A[j])%=MOD;
  }
}
int main(){
  init();
  for(int n,t=1;scanf("%d",&n)==1;t++)
	printf("Case %d: %lld\n",t,A[n]);
  return 0;
}
