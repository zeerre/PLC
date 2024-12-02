#include<bits/stdc++.h>
#define _for(i,a,b) for(int i=(a);i<(b);++i)
#define _rep(i,a,b) for(int i=(a);i<=(b);++i)
using namespace std;
const double EPS=1e-8,PI=acos(-1);
template<typename T>
struct Point{
  T x,y;
  Point& init(T _x=0,T _y=0){
	x=_x;y=_y;
	return *this;
  }
  Point(T x=0,T y=0):x(x),y(y){}
  Point& operator+=(const Point& p){
	x+=p.x,y+=p.y;
	return *this;
  }
  Point& operator*=(const Point& p){
	return init(x*p.x-y*p.y,x*p.y+y*p.x);
  }
};
template<typename T>
Point<T> operator+(const Point<T>& a,const Point<T>& b){
  return {a.x+b.x,a.y+b.y};
}
template<typename T>
Point<T> operator-(const Point<T>& a,const Point<T>& b){
  return (a.x-b.x,a.y-b.y);
}
template <typename T>
Point<T> operator*(const Point<T>& a,const Point<T>& b){
  return {a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x;}
}
typedef Point<double> Cplx;
bool isPowOf2(int x){return x&& !(x&(x-1));}
const int MAXN=1<<18;
valarray<Cplx> Epsilon(MAXN*2),Arti_Epsilon(MAXN*2);
void rec_fft_impl(valarray<Cplx>& A,int n,int level,
				  const valarray<Cplx>& EP){
  int m=n/2;
  if(n==1) return;
  valarray<Cplx> A0(A[slice(0,m,2)]),A1(A[slice(1,m,2)]);
  rec_fft_impl(A0,m,level+1,EP),rec_fft_impl(A1,m,level+1,EP);
  _for(k,0,m) A[k]=A0[k]+EP[k*(1<<level)]*A1[k],
	A[k+m]=A0[k]-EP[k*(1<<level)]*A1[k];
}
void init_fft(int n){
  double theta=2.0*PI/n;
  _for(i,0,n){
	Epsilon.init(cos(theta*i),sin(theta*i));
	Arti_Epsilon[i].init(Epsilon[i].x,-Epsilon[i].y);
  }
}
void idft(valarray<Cplx>& A,int n){
  rec_fft_impl(A,n,0,Arti_Epsilon);
  A*=1.0/n;
}
void fft(valarray<Cplx>& A,int n){
  rec_fft_impl(A,n,0,Epsilon);}
int main(){
  valarray<int > A(MAXN);
  valarray<Cplx> F(MAXN*2);
  for(int n,M,x;scanf("%d",&n)==1 && n;){
	int N=1;
	_for(i,0,n){
	  scanf("%d",&(A[i]));
	  while(A[i]*2>N) N*=2;
	}
	_for(i,0,N) F[i].init();
	F[0].x=1;
	_for(i,0,N) F[A[i]]=1;
	init_fft(N);
	fft(F,N),F*=F,idft(F,N);
	int ans=0;
	scanf("%d",&M);
	_for(i,0,M){
	  scanf("%d",&x);
	  if(x<N && fabs(F[x].x)>EPS) ans++;
	}
	printf("%d\n",ans);
  }
  return 0;
}
