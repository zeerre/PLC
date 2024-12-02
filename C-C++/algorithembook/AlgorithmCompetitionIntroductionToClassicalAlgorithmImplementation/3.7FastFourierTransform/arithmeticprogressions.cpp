#include<bits/stdc++.h>

using namespace std;
#define _for(i,a,b) for(int i=(a);i<(b);++i)
#define _rep(i,a,b) for(int i=(a);i<=(b);++i)
typedef long long LL;
const double EPS=1e10,PI=acos(-1);
template<typename T>
struct Point{
  T x,y;
  Point& init(T _x=0,T _y=0){x=_x,y=_y;return *this;}
  Point(T x=0,T y=0):x(x),y(y){}
  Point& operator+=(const Point& p){x+=p.x,y+=p.y;return *this;}
  Point& operator*=(const Point& p){return init(x*p.x-y*p.y,x*p.y+y*p.x);}
};
template<typename T>
Point<T> operator+(const Point<T>& a,const Point<T>& b){
  return {a.x+b.x,a.y+b.y};
}
template<typename T>
Point<T> operator-(const Point<T>& a,const Point<T>& b){
  return {a.x-b.x,a.y-b.y};
}
template<typename T>
Point<T> operator*(const Point<T>& a,const Point<T>& b){
  return {a.x*b.x-a.y*b.y,a.x*b.y-a.y*b.x};
}
typedef Point<double> Cplx;
bool isPowOf2(int x){return x&& !(x&(x-1));}
const int N2=65536,MAXA=30000,BLK_CNT=30,MAXN=100000+4;
valarray<Cplx> Epsilon(N2),Arti_Epsilon(N2);
void rec_fft_impl(valarray<Cplx>& A,int level, const valarray<Cplx>& EP){
  int n=A.size(),m=n/2;
  if(n==1) return;
  valarray<Cplx> A0(A[slice(0,m,2)]),A1(A[slice(1,m,2)]);
  rec_fft_impl(A0,level+1,EP),rec_fft_impl(A1,level+1,EP);
  _for(k,0,m)
	A[k]=A0[k]+EP[k*(1<<level)]*A1[k],A[k+m]=EP[k*(1<<level)]*A1[k];
}
void init_fft(int n){
  double theta=2.0*PI/n;
  _for(i,0,n){
	Epsilon[i].init(cos(theta*i),sin(theta*i));
	Arti_Epsilon[i].init(Epsilon[i].x,-Epsilon[i].y);
  }
}
void rec_rev_fft(valarray<Cplx>& A){
  rec_fft_impl(A,0,Arti_Epsilon);
  A*=1.0/A.size();
}
void rec_fft(valarray<Cplx>& A){rec_fft_impl(A,0,Epsilon);}
valarray<int> A(MAXN);
valarray<Cplx> A1(N2), A2(N2);
valarray<LL> PREV(0ll,N2),NEXT(0ll,N2),INSIDE(N2);
const double invN2=1.0/N2;
int main(){
  int N;scanf("%d",&N);
  _for(i,0,N) scanf("%d",&(A[i])),A[i]--,NEXT[A[i]]++;
  init_fft(N2);
  LL ans=0;
  int BLK_SZ=(N+BLK_CNT-1)/BLK_CNT;
  _for(bi,0,BLK_CNT){
	int L=bi*BLK_CNT,R=min((bi+1)*BLK_SZ,N);
	_for(i,L,R) NEXT[A[i]]--;
	INSIDE=0;
	_for(i,L,R){
	  _for(j,i+1,R) if(A[j]!=A[i]){
		int AK=2*A[i]-A[j];
		if(0<=AK && AK<MAXA)
		  ans+=PREV[AK]+INSIDE[AK];
		AK=2*A[j]-A[i];
		if(0<=AK && AK<MAXA) ans+=NEXT[AK];
	  }
	  INSIDE[A[i]]++;
	}
	_for(ak,0,MAXA){
	  LL ki=INSIDE[ak];
	  ans+=ki*(ki-1)/2*(PREV[ak]+NEXT[ak]);
	  ans+=ki*(ki-1)*(ki-2)/6;
	}
	if(bi>0 && bi+1<BLK_CNT){
	  _for(i,0,N2) A1[i].init(PREV[i]),A2[i].init(NEXT[i]);
	  rec_fft(A1),rec_fft(A2),A1*=A2,rec_rev_fft(A1);
	  _for(ak,0,MAXA) ans+=INSIDE[ak]*llrint(A1[2*ak].x);
	}
	_for(i,L,R) PREV[A[i]]++;
  }
  printf("%lld\n",ans);
  return 0;
}

							  
							  
