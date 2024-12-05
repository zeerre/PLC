#include<bits/stdc++.h>

using namespace std;

const int maxn=32;
#define _for(i,a,b) for(int i=(a);i<(b);++i)
#define _rep(i,a,b) for(int i=(a);i<=(b);++i)
typedef long long LL;
struct Block{
  int x,y,z;
  int H[3],TP[3][2];
  void init(){
	H[0]=x;
	TP[0][0]=min(y,z),TP[0][1]=max(y,z);
	H[1]=y;
	TP[1][0]=min(x,z),TP[1][1]=max(x,z);
	H[2]=z;
	TP[2][0]=min(x,y),TP[2][1]=max(x,y);
  }
};
int n,D[maxn][3];
Block blocks[maxn];
int dp(int k,int h){
  assert(0<=h&&h<3);
  int& d=D[k][h];
  if(d!=-1) return d;
  const Block& bk=blocks[k];
  d=bk.H[h];
  int x=bk.TP[h][0],y=bk.TP[h][1];
  _for(i,0,n){
	const Block& b=blocks[i];
	_for(hi,0,3)
	  if(b.TP[hi][0]<x && b.TP[hi][1]<y) d=max(d,bk.H[h]+dp(i,hi));
  }
  return d;
}
int main(){
  for(int t=1;scanf("%d",&n)==1&&n;t++){
	_for(i,0,n){
	  Block& b=blocks[i];
	  scanf("%d%d%d",&(b.x),&(b.y),&(b.z));
	  b.init();
	}
	memset(D,-1,sizeof(D));
	int ans=-1;
	_for(i,0,n) _for(hi,0,3) ans=max(ans,dp(i,hi));
	printf("Case %d: maximum height = %d\n",t,ans);
  }
  return 0;
}
