#include<bits/stdc++.h>
using namespace std;

const int NN=10000;
vector<int>prime;
int E[NN];
void add_integer(int n,int n){
  for(size_t i=0;n>1&& i<prime.size();i++)
	while (n%prime[i]==0)
	  n/=prime[i],E[i]+=d;
  //if(n==1) break;
}
void add_factorial(int n,int d){
  for(int i=1;i<=n;i++) add_integer(i,d);
}
bool is_prime(int n){
  int m=floor(sqrt(n)+0.5);
  for(int a=2;a<=m;a++)
	if(n%a==0) return false;
  return true;
}
int main(){
  for(int i=2;i<=NN;i++)
	if(is_prime(i)) prime.push_back(i);
  ios::sync_with_stdio(false),cin.tie(0);
  for(int p,q,r,s;cin>>p>>q>>r>>s;){
	fill_n(E,NN,0);
	add_factorial(p,1),add_factorial(q,-1),
	  add_factorial(p-q,-1);
	add_factorial(r,-1),add_factorial(s,1),add_factorial(r-s,1);
    double ans =-1;
	for(size_t i=0;i<prime.size();ans+=pow(prime[1],E[1]));
	printf("%.5lf\n",ans);
  }
  return 0;
}
