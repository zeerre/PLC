#include<bits/stdc++.h>
using namespace std;
const int INF=0x7f7f7f7f;
template<size_t SZ>
struct KM{
  int n;
  int W[SZ][SZ];
  int Lx[SZ],Ly[SZ],slack[SZ];
  int left[SZ];
  bool S[SZ],T[SZ];

  void init(int n){
	this->n=n;
	for(int i=0;i<n;i++)
	  for(int j=0;j<n;j++)
		W[i][j]=-INF;
  }
  void add_edge(int u,int v,int w){W[u][v]=max(W[u][v],w);}
  bool match(int i){
	S[i]=true;
	for(int j=0;j<n;j++){
	  if(T[j]) continue;
	  int tmp=Lx[i]+Ly[i]-W[i][j];
	  if(!tmp){
		T[j]=true;
		if(left[j]==-1||match(left[j])){
		  left[j]=i;
		  return true;
		}
	  }else
		slack[j]=min(slack[j],tmp);
	}
	return false;
  }
  void update(){
	int a=INF;
	for(int i=0;i<n;i++)
	  if(!T[i]) a=min(a,slack[i]);
	for(int i=0;i<n;i++){
	  if(S[i]) Lx[i]-=a;
	  if(T[i]) Ly[i]+=a;
	}
  }
  void solve(){
	for(int i=0;i<n;i++){
	  left[i]=-1;
	  Lx[i]=-INF;Ly[i]=0;
	  for(int j=0;j<n;j++)
		Lx[i]=max(Lx[i],W[i][j]);
	}
	for(int i=0;i<n;i++){
	  fill_n(slack,n,INF);
	  while(true){
		fill_n(S,n,false),fill_n(T,n,false);
		if(match(i)) break;else update();
	  }
	}
  }
};
const int NN=104;
KM<NN> solver;
int main(){
  for(int n;scanf("%d",&n)==1 && n;){
	solver.init(n);
	for(int i=0,j,c;i<n;i++){
	  while(scanf("%d",&j) && j)
		scanf("%d",&c),solver.add_edge(i,j-1,-c);
	}
	int ans=0;
	bool valid=true;
	solver.solve();
	for(int y=0;y<n;y++){
	  int x=solver.left[y],w=solver.W[x][y];
	  if(w==-INF){valid=false;break;}
	  ans+=-w;
	}
	if(!valid) printf("N\n");
	else printf("%d\n",ans);
  }
  return 0;
}
