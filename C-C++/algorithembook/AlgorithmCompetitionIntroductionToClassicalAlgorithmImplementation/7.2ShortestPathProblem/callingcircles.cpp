#include<bits/stdc++.h>
using namespace std;

#define _for(i,a,b) for(int i=(a);i<(b);++i)
#define _rep(i,a,b) for(int i=(a);i<=(int)(b);++i)
typedef long long LL;
const int NN=32;
int N,M,G[NN][NN],VIS[NN];
vector<string> names;
map<string,int> indice;
int getID(const string& s){
  if(!indice.count(s)) indice[s]=names.size(),names.push_back(s);
  return indice[s];
}
int main(){
  string A,B;
  for(int t=1;cin>>N>>M && N;t++){
	if(t>1) cout<<endl;
	names.clear(),indice.clear();
	memset(G,0,sizeof(G)),fill_n(VIS,N+1,false);
	_for(i,0,M) cin>>A>>B,G[getID(A)][getID(B)]=1;
	assert(names.size()<=N);
	_for(k,0,N) _for(i,0,N) _for(j,0,N)
	  G[i][j]=G[i][j] || (G[i][k] && G[k][j]);
	cout<<"Calling circles for data set "<< t<< ":" <<endl;
	_for(u,0,N){
	  if(VIS[u]) continue;
	  cout<<names[u],VIS[u]=1;
	  _for(v,0,N) if(G[u][v] && G[v][u] && !VIS[v])
		VIS[v]=1,cout<<", "<<names[v];
	  cout<<endl;
	}
  }
  return 0;
}
