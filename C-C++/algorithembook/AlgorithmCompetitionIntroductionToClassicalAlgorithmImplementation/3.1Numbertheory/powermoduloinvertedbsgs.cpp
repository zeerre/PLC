#include<bits/stdc++.h>
using namespace std;

#define _for(i,a,b) for(int i=(a);i<(b);++i)
#define _rep(i,a,b) for(int i=(a);i<=(b);++i)
typedef long long LL;
LL gcd(LL a,LL b){return b==0?a:gcd(b,a%b);}
void gcd(LL a,LL b,LL& d, LL& x,LL& y){
  if(b==0)
	d=a,x=1,y=0;
  else
	gcd(b,a%b,d,y,x),y-=x*(a/b);
}
LL mul_mod(LL a,LL b,LL n){return a*b%n;};
LL pow_mod( LL a,LL p, LL n){
  if(p==0) return 1;
  LL ans=pow_mod(a,p/2,n);
  ans=mul_mod(ans,ans,n);
  if(p%2==1) ans=mul_mod(ans,a,n);
  return ans;
}
LL inv(LL a,LL n){
  LL d,x,y;
  gcd(a,n,d,x,y);
  return d==1?(x+n)%n:-1;
}
LL solve(const LL a,const LL c, LL b,const LL p){
  LL m=(LL) ceil(sqrt(p)),e=c;
  map<LL,int> indice;
  indice[e]=0;
  _for(i,1,m){
	e=mul_mod(e,a,p);
	if(!indice.count(e)) indice[e]=i;
  }
  LL iA=inv(pow_mod(a,m,p),p);
  _for(i,0,m){
	if(indice.count(b)) return i*m+indice[b];
	b=mul_mod(b,iA,p);
  }
  return -1;
}
bool simplify(const LL& a,LL& b,LL& p,LL& c,LL& cnt){
  c=1,cnt=0;
  while(true){
	LL d=gcd(a,p);
	if(d==1) return true;
	if(b%d!=0) return false;
	b/=d,p/=d,c=mul_mod(c,a/d,p),cnt++;
  }
  return false;
}
int main(){
  LL a,b,p,ans;
  while(cin>>a>>p>>b&& a&&b&& p){
	a%=p,b%=p,ans=-1;
	LL c,cnt,e=1;
	_for(i,0,50){
	  if(e==b){
		ans=i;
		break;
	  }
	  e=mul_mod(e,a,p);
	}
	if(ans==-1&& simplify(a,b,p,c,cnt)) ans=solve(a,c,b,p)+cnt;
	if(ans==-1)
	  cout<<"No Solution"<<endl;
	else
	  cout<<ans<<endl;
  }
  return 0;
}

