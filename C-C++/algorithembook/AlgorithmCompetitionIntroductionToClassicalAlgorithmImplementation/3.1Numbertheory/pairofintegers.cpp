#include<bits/stdc++.h>
using namespace std;

#define _for(i,a,b) for(int i=(a);i<(b);++i)
#define _rep(i,a,b) for(int i=(a);i<=(b);++i)
typedef long long LL;
void gcd(LL a,LL b, LL& d,LL& x,LL& y){
  if(!b)
	d=a,x=1,y=0;
  else
	gcd(b,a%b,d,y,x),y-=x*(a/b);
}
const int MAXD=10;
LL P10[MAXD];
inline int lenof(LL x){return to_string(x).size();}
void solve(LL N,map<LL, LL>& ans){
  ans.clear();
  int D=lenof(N);
  if(N%P10[D-1]==0) ans[N]=0;
  _for(i,0,D){
	_for(d,0,10)
	  if(N>d*P10[i]){
		LL x,y,g,a=P10[i]*11,b=2,c=N-d*P10[i];
		gcd(a,b,g,x,y);
		if(c%g) continue;
		LL k=c/g;
		a/=g,b/=g,x*=k,y*=k;
		for(LL step=1<<30;step>=1;step>>=1){
		  if(y>=step*a) y-=step*a,x+=step*b;
		  if(y<-step*a) y+=step*a,x-=step*b;
		}
		while(y<0) y+=a,x-=b;
		if(y>=0 && x+y==N) ans[x]=x;
  }
}
}

int main(){
  P10[0]=1;
  _for(i,1,MAXD) P10[i]=10*P10[i-1];
  int T,N;
  scanf("%d",&T);
  map<LL,LL> ans;
  for(int t=0;scanf("%d",&N)==1;t++){
	if(t) puts("");
	solve(N,ans);
	printf("%lu\n",ans.size());
	for(auto p:ans)
	  printf("%lld+ %0*lld= %d\n",p.first,lenof(p.first)-1,p.second,N);
  }
  return 0;
}
