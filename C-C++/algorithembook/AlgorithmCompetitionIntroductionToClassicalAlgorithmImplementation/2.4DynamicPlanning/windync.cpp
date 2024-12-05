#include<bits/stdc++.h>

using namespace std;

#define _for(i,a,b) for(int i=(a);i<(b);++i)
#define _rep(i,a,b) for(int i=(a);i<=(b);++i)

int F[20][20];
void init(){
  _for(i,0,10) F[1][i]=1;
  _rep(i,2,10) _for(j,0,10) _for(k,0,10) if(abs(j-k)>=2){
	F[i][j]+=F[i-1][k];
  }
}
int solve(int x){
  int ans=0,len=0,b[20];
  while(x>0) b[++len]=x%10,x/=10;
  b[len+1]=-1;
  _for(i,1,len) _for(j,1,10) ans+=F[i][j];
  for(int i=len-1;i>0;i--){
	_for(j,0,b[i]) if(abs(j-b[i+1])>=2) ans+=F[i][j];
	if(abs(b[i]-b[i+1])<2) break;
  }
  return ans;
}
typedef long long LL;
int main(){
  init();
  ios::sync_with_stdio(false),cin.tie(0);
  for(int x,y;cin>>x>>y;)
	cout<<solve(y+1)-solve(x)<<endl;
  return 0;
}
