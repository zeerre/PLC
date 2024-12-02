#include<bits/stdc++.h>
using namespace std;
#define _for(i,a,b) for(int i=(a);i<(b);++i)
#define _rep(i,a,b) for(int i=(a);i<=(b);++i)
typedef long long LL;
const int MAXN=20,MAXV=(1<<MAXN)+4,INF=0X7f7f7f7f;
struct HeapNode{
  int d,u;
  HeapNode(int _d,int _u):d(_d),u(_u){}
  bool operator<(const HeapNode& rhs) const{return d>rhs.d;}
};
int N,M,D[MAXV];
bitset<MAXV> Done;
struct Patch{
  int present,absent,introduce,remove,time;
  bool canApply(int u)const{
	return (present & u)==present && (absent & u) == 0;
  }
  int apply(int u) const {
	return (u|introduce) & (~remove) & ((1<<N)-1);
  }
};
vector<Patch> patches;
void toInt(const char* s,int& i1,int& i2){
  i1=0,i2=0;
  _for(i,0,N){
	if(s[i]=='+') i1|=(1<<i);
	if(s[i]=='-') i2|=(1<<i);
  }
  //assert(0<=i1 && i1<(1<<N));
  //assert(0<=i2 && i2<(1<<N));
}
int solve(){
  int V=1<<N,st=V-1;
  priority_queue<HeapNode> Q;
  Done.reset();
  fill_n(D,V,INF);
  D[st]=0,Q.push(HeapNode(0,st));
  while(!Q.empty()){
	HeapNode nd=Q.top();
	Q.pop();
	int u=nd.u;
	if(Done[u]) continue;
	Done.set(u);
	for(size_t pi=0;pi<patches.size();pi++){
	  const Patch& p=patches[pi];
	  if(!p.canApply(u)) continue;
	  int v=p.apply(u);
	  if(D[v]>D[u]+p.time)
		D[v]=D[u]+p.time,Q.push(HeapNode(D[u]+p.time,v));
	}
  }
  return D[0];
}
int main(){
  char buf1[MAXN+4],buf2[MAXN+4];
  for(int t=1;scanf("%d%d",&N,&M)==2 && N && M;t++){
	patches.clear();
	Patch p;
	_for(i,0,M){
	  scanf("%d%s%s",&(p.time),buf1,buf2);
	  toInt(buf1,p.present,p.absent),toInt(buf2,p.introduce,p.remove);
	  patches.push_back(p);
	}
	int ans=solve();
	printf("Product %d\n",t);
	if(ans==INF)
	  puts("Bugs cannot be fixed.");
	else
	  printf("Fastest sequence takes %d seconds.\n",ans);
	puts("");
  }
  return 0;
}
