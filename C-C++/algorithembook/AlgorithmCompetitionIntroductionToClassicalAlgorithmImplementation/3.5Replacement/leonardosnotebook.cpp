#include<bits/stdc++.h>

using namespace std;

int main(){
  const int NN=30;
  char B[NN];
  int vis[NN],cnt[NN],T;
  scanf("%d",&T);
  while(T--){
	scanf("%s",B);
	fill_n(vis,NN,0),fill_n(cnt,NN,0);
	for(int i=0;i<26;i++)
	  if(!vis[i]){
		int j=i,n=0;
		do{
		  vis[j]=1,j=B[j]-'A',n++;
		}while(j!=i);
		cnt[n]++;
	  }
	int ok=1;
	for(int i=2;i<=26;i++)
	  if(i%2==0&& cnt[i]%2==1) ok=0;
	puts(ok?"Yes":"No");
  }
  return 0;
}

