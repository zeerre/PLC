#include<bits/stdc++.h>
using namespace std;

const double eps=5*1e-13;
int dcmp(double x){
  if(fabs(x)<eps) return 0;
  return x<0?-1:1;
}
const double PI=acos(-1),TWO_PI=PI*2;
double NormalizeAngle(double rad,double center=PI){
  return rad-TWO_PI*floor((rad+PI-center)/TWO_PI);
}
struct Point{
  double x,y;
  Point(double x=0,double y=0):x(x),y(y){}
};
istream& operator>>(istream& is,Point& p)
{return is>>p.x>>p.y;}
typedef Point Vector;
Vector operator+(const Vector& A,const Vector& B){
  return Vector(A.x+B.x,A.y+B.y);
}
Vector operator-(const Point&A,const Point&B){
  return Vector(A.x-B.x,A.y-B.y);
}
Vector operator*(const Vector& A,double p){
  return Vector(A.x*p,A.y*p);
}
Vector operator/(const Vector& A,double p){
  return Vector(A.x/p,A.y/p);
}
double Dot(const Vector& A,const Vector& B){
  return A.x*B.x+A.y*B.y;
}
double Length(const Vector& A){return sqrt(Dot(A,A));}
double angle(const Vector& v){return atan2(v.y,v.x);}
void getCircleCircleIntersection(const Point&c1,double r1,const Point&c2,
								 double r2,vector<double>& rad){
  double d=Length(c1-c2);
  if(dcmp(d)==0) return;
  if(dcmp(r1+r2-d)<0) return;
  if(dcmp(fabs(r1-r2)-d)>0) return;
  double a=angle(c2-c1),da=acos((r1*r1+d*d-r2*r2)/(2*r1*d));
  rad.push_back(NormalizeAngle(a-da));
  rad.push_back(NormalizeAngle(a+da));
}
const int maxn=100+5;
int N;
Point center[maxn];
double radius[maxn];
bool vis[maxn];
int topmost(const Point& p){
  for(int i=N-1;i>=0;i--)
	if(Length(center[i]-p)<radius[i]) return i;
  return -1;
}
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  while(cin>>N && N){
	for(int i=0;i<N;i++) cin>>center[i]>>radius[i];
	fill_n(vis,N+1,0);
	for(int i=0;i<N;i++){
	  vector<double> rad;
	  rad.push_back(0),rad.push_back(TWO_PI);
	  for(int j=0;j<N;j++)
		getCircleCircleIntersection(center[i],radius[i],center[j],radius[j],rad);
	  sort(rad.begin(),rad.end());
	  for(size_t j=0;j<rad.size();j++){
		double mid=(rad[j]+rad[j+1])/2.0;
		for(int side=-1;side<=1;side+=2){
		  double r2=radius[i]-side*eps;
		  int t=topmost(Point(center[i].x+cos(mid)*r2,center[i].y+sin(mid)*r2));
		  if(t>=0) vis[t]=true;
		}
	  }
	}
	int ans=0;
	for(int i=0;i<N;i++) if(vis[i]) ans++;
	cout<<ans<<"\n";
  }
  return 0;
}
