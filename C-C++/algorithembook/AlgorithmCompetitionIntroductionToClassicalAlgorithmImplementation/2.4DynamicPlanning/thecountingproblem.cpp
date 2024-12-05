#include<bits/stdc++.h>
using namespace std;

#define _for(i,a,b) for(int i=(a);i<(b);++i)
#define _rep(i,a,b) for(int i=(a);i<=(b);++i)
typedef long long LL;
typedef valarray<int> TRes;

int P10[9];
TRes solve(int N){
  TRes ans(0,10);
  if(N==0){
	ans[0]=1;
	return ans;
  }
  auto S=to_string(N);
  int W=S.size();
  _for(k,1,W){
	if(k==1){
	  ans+=1;
	  continue;
	}
	_rep(d,1,9) ans[d]+=P10[k-1];
	ans+=9*P10[k-1]*(k-1);
  }
  _for(i,0,W-1){
	int sd=i==0?1:0;
	_for(d,sd,S[i]-'0'){
	  int l=W-i-1;
	  _for(j,0,i) ans[S[j]-'0']+=P10[l];
	  ans[d]+=P10[l];
	  ans+=P10[l-1]*l;
	}
  }
  _rep(d,0,S[W-1]-'0'){
	_for(j,0,W-1) ans[S[j]-'0']++;
	ans[d]++;
  }
  return ans;
}
TRes solve(int a,int b){
  if(a>b) swap(a,b);
  const TRes &ta=solve(a-1),&tb=solve(b);
  return tb-ta;
}
int main(){
  P10[0]=1;
  _for(i,1,9) P10[i]=10*P10[i-1];
  for(int a,b;scanf("%d%d",&a,&b) ==2&& a&&b;){
	const auto& ans=solve(a,b);
	_for(i,0,10) printf("%d%s",ans[i],i==9?"\n":" ");
  }
  return 0;
}
