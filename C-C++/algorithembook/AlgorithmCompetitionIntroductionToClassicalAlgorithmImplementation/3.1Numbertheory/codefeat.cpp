#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxc=9,maxk=100,LIMIT=10000;
set<int> values[maxc];
int C,X[maxc],k[maxc],Y[maxc][maxk];
void gcd(LL a,LL b,LL& d,LL& x,LL& y){
  if(!b) d=a,x=1,y=0;
  else gcd(b,a%b,d,y,x),y-=x*(a/b);
}
LL china(int n,int* a,int* m){
  LL M=1,d,y,x=0;
  for(int i=0;i<n;i++) M*=m[i];
  for(int i=0;i<n;i++){
	LL w=M/m[i];
	gcd(m[i],w,d,d,y);
	x=(x+y*w*a[i])%M;
  }
  return (x+M)%M;
}
void solve_enum(int S,int bc){
  for(int c=0;c<C;c++)
	if(c!=bc){
	  values[c].clear();
	  for(int i=0;i<k[c];i++) values[c].insert(Y[c][i]);
	}
  for(int t=0;S!=0;t++){
	for(int i=0;i<k[bc];i++){
	  LL n=(LL)X[bc]*t+Y[bc][i];
	  if(n==0) continue;
	  bool ok=true;
	  for(int c=0;c<C;c++)
		if(c!=bc)
		  if(!values[c].count(n%X[c])){
			ok=false;
			break;
		  }
	  if(ok){
		printf("%lld\n",n);
		if(--S==0) break;
	  }
	}
  }
}
int a[maxc];
vector<LL> sol;
void dfs(int dep){
  if(dep==C)
	sol.push_back(china(C,a,X));
  else
	for(int i=0;i<k[dep];i++) a[dep]=Y[dep][i],dfs(dep+1);
}
void solve_china(int S){
  sol.clear();
  dfs(0);
  sort(sol.begin(),sol.end());
  LL M=1;
  for(int i=0;i<C;i++) M*=X[i];
  vector<LL> ans;
  for(int i=0;S!=0;i++){
	for(int j=0;j<sol.size();j++){
	  LL n=M*i+sol[j];
	  if(n>0){
		printf("%lld\n",n);
		if(--S==0) break;
	  }
	}
  }
}
int main(){
  int S;
  while(scanf("%d%d",&C,&S)==2 && C){
	LL tot=1;
	int bestc=0;
	for(int c=0;c<C;c++){
	  scanf("%d%d",&X[c],&k[c]);
	  tot*=k[c];
	  for(int i=0;i<k[c];i++) scanf("%d",&Y[c][i]);
	  sort(Y[c],Y[c]+k[c]);
	  if(k[c]*X[bestc]<k[bestc]*X[c]) bestc=c;
	}
	if(tot>LIMIT)
	  solve_enum(S,bestc);
	else
	  solve_china(S);
	printf("\n");
  }
  return 0;
}
