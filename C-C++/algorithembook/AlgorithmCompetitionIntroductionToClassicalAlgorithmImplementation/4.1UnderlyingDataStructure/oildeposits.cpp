#include<bits/stdc++.h>
using namespace std;

const int NN =100+4;
char pic[NN][NN];
int M,N,C[NN][NN];
#define _for(i,a,b) for(int i=(a);i<(b);++i)

void dfs(int r,int c,int id){
  if(r<0 || r>=M || c<0 ||c>=N) return ;
  if(C[r][c]>0 || pic[r][c]!='@') return;
  C[r][c]=id;
  for(int dr=-1;dr<=1;dr++)
	for(int dc=-1;dc<=1;dc++)
	  if(dr!=0 || dc!=0) dfs(r+dc,c+dc,id);
}
int main(){
  while(scanf("%d%d",&M,&N)==2 && M && N){
	_for(i,0,M) scanf("%s",pic[i]);
	memset(C,0,sizeof(C));
	int cnt=0;
	_for(i,0,M) _for(j,0,N) if(C[i][j]==0&& pic[i][j]=='@')
	  dfs(i,j,++cnt);
	printf("%d\n",cnt);
  }
  return 0;
}
