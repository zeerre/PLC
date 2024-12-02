#include<bits/stdc++.h>
using namespace std;

int k,cnt;
char p[2][6][9],ans[9];
const int SIGMA=26;
bool dfs(int col){
  if(col==5){
	if(++cnt==k){
	  ans[col]='\0',puts(ans);
	  return true;
	}
	return false;
  }
  bool vis[2][SIGMA];
  memset(vis,0,sizeof(vis));
  for(int i=0;i<2;i++)
	for(int j=0;j<6;j++)
	  vis[i][p[i][j][col]-'A']=true;
  for(int i=0;i<SIGMA;i++)
	if(vis[0][i] && vis[1][i]){
	  ans[col]='A'+i;
	  if(dfs(col+1)) return true;
	}
  return false;
}
int main(){
  int T;
  scanf("%d",&T);
  while(T--){
	scanf("%d",&k);
	for(int i=0;i<2;i++)
	  for(int j=0;j<6;j++)
		scanf("%s",p[i][j]);
	cnt=0;
	if(!dfs(0)) puts("NO");
  }
  return 0;
}
