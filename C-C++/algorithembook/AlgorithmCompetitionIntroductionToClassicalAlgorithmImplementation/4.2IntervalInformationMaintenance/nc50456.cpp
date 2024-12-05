#include<bits/stdc++.h>

using namespace std;
typedef long long LL;

template<typename T=int,int SZ=10004>
struct SegTree{
  struct Node{T max,sum;};
  Node NS[SZ *3];
  int qL,qR;
  void init(int o,int L,int R,const T* A){
	assert(o<3*SZ);
	Node& nd=NS[o];
	if(L==R){
	  nd.max=nd.sum=A[L];
	  return;
	}
	int M=L+(R-L)/2,lc=2*o,rc=2*o+1;
	init(lc,L,M,A),init(rc,M+1,R,A);
	nd.max=max(NS[lc].max,NS[rc].max),nd.sum=NS[lc].sum+NS[rc].sum;
  }
  T querySum(int o,int L,int R){
	const Node& nd=NS[o];
	if(qL<=L && qR>=R) return nd.sum;
	int M=(L+R)/2,lc=2*o,rc=2*o+1;
	T ans=0;
	if(qL<=M) ans+=querySum(lc,L,M);
	if(qR>M) ans+=querySum(rc,M+1,R);
	return ans;
  }
  void make_sqrt(int o,int L,int R){
	Node& nd=NS[o];
	if(nd.max<=1) return;
	if(L==R){
	  nd.max=floor(sqrt(nd.max)),nd.sum=floor(sqrt(nd.sum));
	  return;
	}
	int M=(L+R)/2,lc=2*o,rc=2*o+1;
	if(qL<=M) make_sqrt(2*o,L,M);
	if(qR>M) make_sqrt(2*o+1,M+1,R);
	nd.max=max(NS[lc].max,NS[rc].max),nd.sum=NS[lc].sum+NS[rc].sum;
  }
};
const int NN=1e5+4;
SegTree<LL,NN> st;
int N,M;
LL A[NN];
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  cin>>N;
  for(int i=1;i<=N;i++) cin>>A[i];
  st.init(1,1,N,A);
  cin>>M;
  for(int i=1,x,l,r;i<=M;i++){
	cin>>x>>st.qL>>st.qR;
	if(x==1)
	  cout<<st.querySum(1,1,N)<<endl;
	else
	  st.make_sqrt(1,1,N);
  }
  return 0;
}
