#include<bits/stdc++.h>
using namespace std;
#define _for(i,a,b) for(int i=(a);i<(b);++i)
typedef long long LL;
typedef vector<int> IVec;
LL MOD;
template<typename T>
T mul_mod(T a,T b){return (((LL)a)*b)%MOD;}
template<typename T>
T pow_mod(T a,T b){
  LL ans=1;
  while(b>0){
	if(b&1) ans = mul_mod((T)ans,a);
	a=mul_mod(a,a),b/=2;
  }
  return ans;
}
const int MAXN=500000;
const vector<int > Primes={7,5,3,2};
int getGen(int P){
  set<int> set;
  _for(g,1,P){
	set.clear();
	int pm=g;
	_for(ex,1,P){
	  if(set.count(pm)) break;
	  set.insert(pm),pm=(pm*g)%P;
	}
	if(set.size()==P-1){
	  assert(pm==g);
	  return g;
	}
  }
  return -1;
}
IVec vslice(const IVec& A,int start,int step,int count){
  assert(start>=0);
  assert(step>0);
  IVec ans;
  for(size_t i=max(start,0);i<A.size() && count>0; i+=step,count--)
	ans.push_back(A[i]);
  return ans;
}
void fft_impl(IVec& F,int w,const IVec& D,int level=0){
  int n=F.size();
  if(n<=1) return;
  int p=D[level],m=n/p,wp=pow_mod(w,p),wi=1;
  vector<IVec> frs;
  _for(r,0,p){
	frs.push_back(vslice(F,r,p,m));
	fft_impl(frs.back(),wp,D,level+1);
  }
  _for(i,0,n){
	F[i]=0;
	_for(r,0,p) (F[i]+=mul_mod(pow_mod(wi,r),frs[r][i%m]))%=MOD;
	wi=mul_mod(wi,w);
  }
}
void FFT(IVec& A,int gen,const IVec& D){fft_impl(A,gen,D);}
void IDFT(IVec& A,int gen,const IVec& D){
  int n=A.size(),nRev=pow_mod(n,n-1);
  fft_impl(A,pow_mod(gen,n-1),D);
  _for(i,0,A.size()) A[i]=mul_mod(A[i],nRev);
}
int main(){
  IVec A(MAXN),B(MAXN),C(MAXN),D;
  for(int n,cn,x;cin>>n>>cn;){
	cn=cn%n,MOD=n+1;
	A.clear(),B.clear();
	_for(i,0,n) cin>>x,A.push_back(x);
	_for(i,0,n) cin>>x,B.push_back(x);
	D.clear();
	int tmp=n;
	_for(i,0,Primes.size()){
	  while(tmp%Primes[i]==0) D.push_back(Primes[i]),tmp/=Primes[i];
	}
	int G=getGen(MOD);
	FFT(A,G,D),FFT(B,G,D);
	C.resize(n);
	_for(i,0,n) C[i]=(B[i]==0)?0:mul_mod(A[i],pow_mod(B[i],cn));
	IDFT(C,G,D);
	_for(i,0,n) printf("%d\n",C[i]);
  }
  return 0;
}
