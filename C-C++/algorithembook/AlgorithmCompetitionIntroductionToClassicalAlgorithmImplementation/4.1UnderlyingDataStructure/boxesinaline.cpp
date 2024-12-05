#include<bits/stdc++.h>

using namespace std;

typedef long long LL ;
const int NN=1e5+4;
int Left[NN],Right[NN];
inline void link(int L,int R){Right[L]=R;Left[R]=L;}
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  for(int n,m,kase=1;cin>>n>>m;kase++){
	for(int i=1;i<=n;i++) Left[i]=i-1,Right[i]=(i+1)%(n+1);
	Right[0]=1,Left[0]=n;
	bool inv=false;
	for(int i=0,op,x,y;i<m;i++){
	  cin>>op;
	  if(op==4) inv=!inv;
	  else{
		cin>>x>>y;
		if(op==3 && Right[y]==x) swap(x,y);
		if(op!=3&&inv) op=3-op;
		if(op==1 && x==Left[y]) continue;
		if(op==2 &&x==Right[y]) continue;
		int lx=Left[x],rx=Right[x],ly=Left[y],ry=Right[y];
		if(op==1) link(lx,rx),link(ly,x),link(x,y);
		else if (op==2) link(lx,rx),link(y,x),link(x,ry);
		else if(op==3){
		  if(Right[x]==y) link(lx,y),link(y,x),link(x,ry);
		  else link(lx,y),link(y,rx),link(ly,x),link(x,ry);
		}
	  }
	}
	LL ans=0;
	for(int i=1,b=0;i<=n;i++){
	  b=Right[b];
	  if(i%2==1) ans+=b;
	}
	if(inv&&n%2==0) ans=(LL)n*(n+1)/2-ans;
	printf("Case %d: %lld\n",kase,ans);
  }
  return 0;
}

							  
