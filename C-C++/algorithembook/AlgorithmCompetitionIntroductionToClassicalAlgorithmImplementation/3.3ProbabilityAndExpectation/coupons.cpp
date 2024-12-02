#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

LL gcd(LL a, LL b){return b==0?a:gcd(b,a%b);}
struct Rational{
  LL a, b;
  Rational& operator+=(const Rational& r){
	LL na=a*r.b+b*r.a,nb=b*r.b;
	a=na,b=nb;
	reduce();
	return *this;
  }
  void reduce(){
	LL g=gcd(a,b);
	a/=g,b/=g;
  }
};
int lenof(LL x){
  static char buf[32];
  sprintf(buf,"%lld",x);
  return strlen(buf);
}
ostream& operator<<(ostream& os,const Rational& r){
  if(r.b==1) return os<<r.a;
  LL a= r.a%r.b,b=r.b,k=r.a/r.b;
  int la=lenof(a),lb=lenof(b),lk=lenof(k);
  lk=k=0?0:lk+1,la=max(la,lb);
  if(lk)
	for(int i=0;i<lk;++i) os<<" ";
  os<<a<<endl;
  for(int i=0;i<la;++i) os<<"-";
  os<<endl;
  if(lk)
	for(int i=0;i<lk;++i) os<<" ";
  return os<<b;
}
int main(){
  for(int n;scanf("%d",&n)==1;){
	Rational r={n,n};
	for(int i=1;i<n;i++) r+=(Rational){n,i};
	cout<<r<<endl;
  }
  return 0;
}

  
