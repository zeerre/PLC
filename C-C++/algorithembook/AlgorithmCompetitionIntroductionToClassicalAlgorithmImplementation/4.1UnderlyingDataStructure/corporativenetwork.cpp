#include<bits/stdc++.h>

using namespace std;

const int NN=20000+10;
int pa[NN],d[NN];
int findset(int x){
  int &p=pa[x];
  if(p==x) return x;
  int r=findset(p);
  d[x]+=d[p];
  return p=r;
}
int main(){
  int T;
  cin>>T;
  for(int t=0,n,u,v;t<T;t++){
	string cmd;
	cin>>n;
	for(int i=1;i<=n;i++) pa[i]=i,d[i]=0;
	while(cin>>cmd&& cmd[0]!='O'){
	  if(cmd[0]=='E') cin>>u,findset(u),cout<<d[u]<<endl;
	  if(cmd[0]=='I') cin>>u>>v,pa[u]=v,d[u]=abs(u-v)%1000;
	}
  }
  return 0;
}

		 
