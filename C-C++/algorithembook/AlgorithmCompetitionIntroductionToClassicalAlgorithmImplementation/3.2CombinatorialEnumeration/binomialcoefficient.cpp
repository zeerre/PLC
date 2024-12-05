#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL,LL> LPair;
typedef map<LL,set<LL>>::iterator MIT;
LL gcd(LL a,LL b){
  return b==0?a:gcd(b,a%b);
}
int binomial_cmp(LL n,LL k,LL m){
  LL C=1;
  for(int i=1;i<=k;i++){
	LL g=gcd(n-i+1,i),b=(n-i+1)/g;
	C/=(i/g);
	if(C>LONG_MAX/b) return 1;
	C*=b;
	if(C>m) return 1;
  }
  if(C==m) return 0;
  return -1;
}
void solve(LL M,map<LL ,set<LL>>& ans,int& sz){
  ans.clear();
  sz=0;
  if(M==2){
	ans[2].insert(1),sz=1;
	return;
  }
  int k=2;
  while(true){
	LL L=2*k,R=M,n=0;
	if(binomial_cmp(L,k,M)>0) break;
	while(L<R && !n){
	  LL mid=L+(R-L)/2;
	  int cmp=binomial_cmp(mid,k,M);
	  if(cmp==0)
		n=mid;
	  else if(cmp<0)
		L=mid+1;
	  else if(cmp>0)
		R=mid;
	}
	if(n) ans[n].insert(k),ans[n].insert(n-k);
	k++;
  }
  ans[M].insert(1),ans[M].insert(M-1);
  for(MIT p=ans.begin();p!=ans.end();p++) sz+=p->second.size();
}
int main(){
  int T;
  scanf("%d\n",&T);
  map<LL,set<LL>> ans;
  for(LL M;scanf("%lld\n",&M) ==1;){
	int sz=0;
	solve(M,ans,sz);
	printf("%d\n",sz);
	int cnt=0;
	for(MIT p=ans.begin();p!=ans.end();p++){
	  const set<LL> s=p->second;
	  for(set<LL>::iterator it=s.begin();it!=s.end();it++){
		if(cnt++) printf(" ");
		printf("(%lld,%lld)",p->first,*it);
	  }
	}
	puts("");
  }
  return 0;
}

	  
