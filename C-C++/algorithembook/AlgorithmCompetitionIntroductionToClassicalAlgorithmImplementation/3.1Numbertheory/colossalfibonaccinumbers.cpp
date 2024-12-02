#include<bits/stdc++.h>
using namespace std;

const int NN = 1000+8;
typedef unsigned long long ULL;
int F[NN][NN*6],period[NN];
int pow_mod(ULL a,ULL b,int MOD){
  if(!b) return 1;
  int k=pow_mod(a,b/2,MOD);
  k=k*k%MOD;
  if(b%2) k=k*a%MOD;
  return k;
}
int solve(ULL a,ULL b,int MOD){
  if(a==0 || MOD ==1) return 0;
  int p=pow_mod(a%period[MOD],b,period[MOD]);
  return F[MOD][p];
}
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  for(int n=2;n<=1000;n++){
	F[n][0]=0,F[n][1]=1;
	for(int i=2;;i++){
	  F[n][i]=(F[n][i-1]+F[n][i-2])%n;
	  if(F[n][i-1]==0&&F[n][i]==1){
		period[n]=i-1;
		break;
	  }
	}
  }
  ULL a,b;
  int T;
  cin>> T;
  for(int t=0,n;t<T;t++)
	cin>>a>>b>>n,cout<<solve(a,b,n)<<endl;
  return 0;
}
