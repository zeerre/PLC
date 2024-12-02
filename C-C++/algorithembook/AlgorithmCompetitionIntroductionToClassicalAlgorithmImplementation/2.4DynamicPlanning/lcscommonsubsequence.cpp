#include<bits/stdc++.h>
//#include<algorithm>
//#include<cmath>
//#include<cstdio>
//#include<cstring>
using namespace std;
const int NN=1000;
char s1[NN],s2[NN];
int dp[NN][NN];
int main(){
  while(scanf("%s %s",s1,s2)==2){
	int L1=strlen(s1),L2=strlen(s2);
	memset(dp,0,sizeof(dp));
	for(int i=0;i<L1;i++)
	  for(int j=0;j<L2;j++)
		if(s1[i]==s2[j])
		  dp[i+1][j+1]=dp[i][j]+1;
		else
		  dp[i+1][j+1]=max(dp[i][j+1],dp[i+1][j]);
	printf("%d\n",dp[L1][L2]);
  }
  return 0;
}
