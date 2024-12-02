#include<bits/stdc++.h>

using namespace std;

typedef long long LL;
const int MAXN =1e5+4;
int Pa[MAXN];
int findPa(int u){return Pa[u]==u?u:(Pa[u]=findPa(Pa[u]));}

int main(){
  while(true){
	for(int i=0;i<=MAXN;i++) Pa[i]=i;
	int ans=0,u,v;
	while(true){
	  if(scanf("%d",&u)!=1)return 0;
	  if(u==-1)break;
	  scanf("%d",&v),u=findPa(u),v=findPa(v);
	  if(u==v) ans++;
	  else Pa[u]=v;
	}
	printf("%d\n",ans);
  }
  return 0;
}
