#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int NN=1000+4;
vector<int >G[NN];
stack<int> S;
int N,B,BCnt,BId[NN],Cap[NN];
void dfs(int u,int fa){
  size_t sz=S.size();
  for(auto v:G[u]){
	if(v==fa) continue;
	dfs(v,u);
	if(S.size()>=sz+B){
	  Cap[++BCnt]=u;
	  while(S.size()>sz) BId[S.top()]=BCnt,S.pop();
	}
  }
  S.push(u);
  if(u==1)
	while(!S.empty()) BId[S.top()]=BCnt,S.pop();
}
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  cin>>N>>B,BCnt=0;
  for(int i=1,u,v;i<N;i++){
	cin>>u>>v;
	G[u].push_back(v),G[v].push_back(u);
  }
  dfs(1,-1);
  cout<<BCnt<<endl;
  for(int i=1;i<=N;i++) cout<<BId[i]<<(i==N?"\n":" ");
  for(int i=1;i<=BCnt;i++) cout<<Cap[i]<<(i==BCnt?"\n": " ");
  return 0;
}
