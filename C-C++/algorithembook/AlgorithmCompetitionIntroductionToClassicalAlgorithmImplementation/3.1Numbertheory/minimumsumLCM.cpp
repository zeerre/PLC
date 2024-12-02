#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

LL solve(int n){
  if(n==1) return 2;
  int maxp=floor(sqrt(n)+0.5),pf=0;
  LL ans=0;
  for(int i=2;i<maxp;i++){
	if(n%i) continue;
	int x=1;
	while(n%i==0) n/=i,x*=i;
	ans+=x,pf++;
  }
  if(n>1) pf++,ans+=n;
  if(pf<=1) ans++;
  return ans;
}
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  for(int n,kase=1;cin>>n && n;kase++)
	cout<<"Case" << kase<< ": "<<solve(n)<<"\n";
  return 0;
}
