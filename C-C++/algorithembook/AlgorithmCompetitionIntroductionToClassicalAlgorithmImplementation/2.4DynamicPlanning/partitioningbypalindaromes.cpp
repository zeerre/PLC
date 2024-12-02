#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN=1024;
int N,isPa[MAXN][MAXN],D[MAXN];
string S;
int dp(int k){
  int &d=D[k];
  if(d!=-1) return d;
  d=MAXN;
  if(isPa[0][k]) return d=1;
  for(int i=1;i<=k;i++)
	if(isPa[i][k]) d=min(1+dp(i-1),d);
  return d;
}
int main(){
  int T;
  cin>>T;
  while(T--){
	cin>>S,N=S.length();
	memset(isPa,0,sizeof(isPa)),memset(D,-1,sizeof(D));
	for(int i=0;i<N;i++){
	  int l=i,r=i;
	  while(l>=0&&r<N&& S[l]==S[r]) isPa[l--][r++] =1;
	  l=i,r=i+1;
	  while(l>=0&&r<N&&S[l]==S[r]) isPa[l--][r++] =1;
	}
	int ans=dp(N-1);
	printf("%d\n",ans);
  }
  return 0;
}
