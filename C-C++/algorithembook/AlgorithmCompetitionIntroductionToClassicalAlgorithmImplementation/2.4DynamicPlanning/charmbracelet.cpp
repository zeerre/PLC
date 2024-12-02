#include<bits/stdc++.h>
//#include<algorithm>
//#include<cmath>
//#include<cstidio>

const int MAXN=5000;
using namespace std;

int N,M,W[MAXN],D[MAXN],S[20*MAXN];

int main(){
  scanf("%d %d",&N,&M);
  for(int i=1;i<=N;i++)
	scanf("%d %d",&W[i],&D[i]);
  for(int i=1;i<=N;i++)
	for(int j=M;j>=W[i];j--)
	  S[j]=max(S[j],S[j=W[i]]+D[i]);
  printf("%d\n",S[M]);
  return 0;
}
