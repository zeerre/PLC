#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+8;
struct TwoSAT{
  int n;
  vector<int> G[maxn*2];
  bool mark[maxn*2];
  int S[maxn*2],c;
  bool dfs(int x){
	if(mark[x^1]) return false;
	if(mark[x]) return true;
	mark[x]=true,S[c++]=x;
	for(size_t i=0;i<G[x].size();i++)
	  if(!dfs(G[x][i])) return false;
	return true;
  }
  void init(int n){
	this->n=n;
	for(int i=0;i<n*2;i++) G[i].clear();
	fill_n(mark,2*n+1,0);
  }
  void add_clause(int x,int xval,int y,int yval){
	x=x*2+xval,y=y*2+yval;
	G[x^1].push_back(y),G[y^1].push_back(x);
  }
  bool solve(){
	for(int i=0;i<n*2;i+=2)
	  if(!mark[i] && !mark[i+1]){
		c=0;
		if(!dfs(i)){
		  while(c>0) mark[S[--c]] =false;
		  if(!dfs(i+1)) return false;
		}
	  }
	return true;
  }
};
int n,m,total_age,age[maxn];
int is_young(int x){ return age[x]*n<total_age;}
TwoSAT solver;
int main(){
  while(scanf("%d%d",&n,&m)==2 && n){
	total_age=0;
	for(int i=0;i<n;i++) scanf("%d",&age[i]),total_age+=age[i];
	solver.init(n);
	for(int i=0,a,b;i<m;i++){
	  scanf("%d%d",&a,&b),a--,b--;
	  if(a==b) continue;
	  solver.add_clause(a,1,b,1);
	  if(is_young(a)==is_young(b))
		solver.add_clause(a,0,b,0);
	}
	if(!solver.solve()){
	  puts("No solution.");
	  continue;
	}
	for(int i=0;i<n;i++){
	  if(solver.mark[i*2]) puts("C");
	  else if(is_young(i)) puts("B");
	  else puts("A");
	}
  }
  return 0;
}
