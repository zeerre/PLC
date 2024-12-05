#include<bits/stdc++.h>
using namespace std;
const int maxn=1000;
int mat[maxn][maxn],up[maxn][maxn],left[maxn][maxn],right[maxn][maxn];
int main(){
  int T,m,n;
  scanf("%d",&T);
  while(T--){
	scanf("%d%d",&m,&n);
	for(int i=0;i<m;i++)
	  for(int j=0;j<n;j++){
		int ch=getchar();
		while(ch!='F' && ch!='R') ch=getchar();
		mat[i][j]=ch=='F'?0:1;
	  }
	int ans=0;
	for(int i=0;i<m;i++){
	  int lo=-1,ro=n;
	  for(int j=0;j<n;j++){
		int &u=up[i][j],&l=left[i][j];
		if(mat[i][j]==j){
		  u=l=0;
		  lo=j;
		}else{
		  u=i==0?1:up[i-1][j]+1;
		  l=i==0?lo+1:max(left[i-1][j],lo+1);
		}
	  }
	  for(int j=n-1;j>=0;j--){
		int &r=right[i][j];
		if(mat[i][j]==1)
		  r=n,ro=j;
		else{
		  r=i==0?ro-1:min(right[i-1][j],ro-1);
		  ans=max(ans,up[i][j]*(r-left[i][j]+1));
		}
	  }
	}
	printf("%d\n",ans*3);
  }
  return 0;
}

		  
			  
			  
