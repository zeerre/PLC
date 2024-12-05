#include<bits/stdc++.h>
using namespace std;

const double eps=1e-6;
int dcmp(double x){
  if(fabs(x)<eps) return 0;
  return x<0? -1 : 1;
}
const double PI=acos(-1);

struct Point{
  double x,y;
  Point(double x=0,double y=0): x(x),y(y){}
  Point& operator=(const Point& p){
	x=p.x,y=p.y;
	return *this;
  }
};
istream& operator>>(istream& is,Point& p){return is>>p.x>>p.y;}
typedef Point Vector;
Vector operator+(const Vector& A,const Vector& B)
{return Vector(A.x+B.x,A.y+B.y);}
Vector operator-(const Point& A,const Point& B)
{return Vector(A.x-B.x,A.y-B.y);}
Vector operator*(const Vector& A,double p)
{return Vector(A.x*p,A.y*p);}
Vector operator/(const Vector& A,double p)
{return Vector(A.x/p,A.y/p);}
bool operator<(const Point& a,const Point& b){
  return a.x<b.x || (a.x==b.x && a.y<b.y);
}
bool operator==(const Point& a,const Point &b){
  return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0;
}
double Dot(const Vector& A,const Vector& B)
{return A.x*B.x+A.y*B.y;}
double Length(const Vector& A){return sqrt(Dot(A,A));}
double Angle(const Vector& A,const Vector& B)
{return acos(Dot(A,B)/Length(A)/Length(B));}
double Cross(const Vector& A,const Vector& B)
{return A.x*B.y-A.y*B.x;}
Vector Rotate(const Vector& A,double rad){
  return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
}
Vector Normal(const Vector& A){
  double L=Length(A);
  return Vector(-A.y/L,A.x/L);
}
Point GetLineIntersection(const Point& P,const Point& v,
						  const Point& Q,const Point& w){
  Vector u=P-Q;
  double t=Cross(w,u)/Cross(v,w);
  return P+v*t;
}
Point GetLineProjection(const Point& P,const Point& A,const Point& B){
  Vector v=B-A;
  return A+v*(Dot(v,P-A)/Dot(v,v));
}
double DistanceToLine(const Point& P,const Point& A,const Point& B){
  Vector v1=B-A,v2=P-A;
  return fabs(Cross(v1,v2))/Length(v1);
}
struct Line{
  Point p;
  Vector v;
  Line(const Point& p,const Vector& v):p(p),v(v){}
  Point point(double t)const{
	return p+v*t;
  }
  Line move(double d) const{
	return Line(p+Normal(v)*d,v);
  }
};
struct Circle{
  Point c;
  double r;
  Circle(const Point& c,double r): c(c),r(r){}
  Point point(double a) const {
	return Point(c.x+cos(a)*r,c.y+sin(a)*r);
  }
};
Point GetLineIntersection(const Line& a,const Line& b){
  return GetLineIntersection(a.p,a.v,b.p,b.v);
}
double angle(const Vector& v){
  return atan2(v.y,v.x);
}
int getLineCircleIntersection(const Line& L,const Circle& C,
							  double& t1,double& t2,vector<Point>& sol){
  double a=L.v.x,b=L.p.x-C.c.x,c=L.v.y,d=L.p.y-C.c.y;
  double e=a*a+c*c,f=2*(a*b+c*d),g=b*b+d*d-C.r*C.r;
  double delta=f*f-4*e*g;
  if(dcmp(delta)<0) return 0;
  if(dcmp(delta)==0){
	t1=t2=-f/(2*e);sol.push_back(L.point(t1));
	return 1;
  }
  t1=(-f-sqrt(delta))/(2*e);sol.push_back(L.point(t1));
  t2=(-f+sqrt(delta))/(2*e);sol.push_back(L.point(t2));
  return 2;
}
int getCircleCircleIntersection(const Circle& C1,
								const Circle& C2,vector<Point>& sol){
  double d=Length(C1.c-C2.c);
  if(dcmp(d)==0){
	if(dcmp(C1.r-C2.r)==0) return -1;
	return 0;
  }
  if(dcmp(C1.r+C2.r-d)<0) return 0;
  if(dcmp(fabs(C1.r-C2.r)-d)>0) return 0;
  double a=angle(C2.c-C1.c);
  double da=acos((C1.r*C1.r+d*d-C2.r*C2.r)/(2*C1.r*d));
  Point p1=C1.point(a-da),p2=C1.point(a+da);
  sol.push_back(p1);
  if(p1==p2) return 1;
  sol.push_back(p2);
  return 2;
}
/****Problem 1*******/
Circle CircumscribedCircle(const Point& p1,const Point& p2,const Point& p3)
{
  double Bx=p2.x-p1.x,By=p2.y-p1.y;
  double Cx=p3.x-p1.x,Cy=p3.y-p1.y;
  double D=2*(Bx*Cy-By*Cx);
  double cx=(Cy*(Bx*Bx+By*By)-By*(Cx*Cx+Cy*Cy))/D+p1.x;
  double cy=(Bx*(Cx*Cx+Cy*Cy)-Cx*(Bx*Bx+By*By))/D+p1.y;
  Point p=Point(cx,cy);
  return Circle(p,Length(p1-p));
}
/****Problem 2*******/
Circle InscribedCircle(const Point& p1,const Point& p2,const Point& p3){
  double a=Length(p2-p3);
  double b=Length(p3-p1);
  double c=Length(p1-p2);
  Point p=(p1*a+p2*b+p3*c)/(a+b+c);
  return Circle(p,DistanceToLine(p,p1,p2));
}
/****Problem 3 *******/
//过点p做圆C的切线。v[i]是i条切线的向量，返回切线条数
int getTangents(const Point& p,const Circle& C,Vector* v){
  Vector u=C.c-p;
  double dist=Length(u);
  if(dist<C.r) return 0;
  else if(dcmp(dist-C.r)==0){
	v[0]=Rotate(u,PI/2);
	return 1;
  }else{
	double ang=asin(C.r/dist);
	v[0]=Rotate(u,-ang);
	v[1]=Rotate(u,+ang);
	return 2;
  }
}
/***** Problem 4 *******/
vector<Point> CircleThroughPointTangentToLineGivenRadius(
														 const Point& p,const Line& L,double r){
  vector<Point> ans;
  double t1,t2;
  getLineCircleIntersection(L.move(-r),Circle(p,r),t1,t2,ans);
  getLineCircleIntersection(L.move(r),Circle(p,r),t1,t2,ans);
  return ans;
}
/****** Problem 5 *******/
vector<Point> CircleTangentToLinesGivenRadius(
											  const Line& a,const Line&b,
											  double r){
  vector<Point> ans;
  Line L1=a.move(-r),L2=a.move(r);
  Line L3=b.move(-r),L4=b.move(r);
  ans.push_back(GetLineIntersection(L1,L3));
  ans.push_back(GetLineIntersection(L1,L4));
  ans.push_back(GetLineIntersection(L2,L3));
  ans.push_back(GetLineIntersection(L2,L4));
  return ans;
}
/******* Problem 6  ***************/

vector<Point> CircleTangentToTwoDisjointCirclesWithRadius(
														  const Circle& c1,
														  const Circle& c2,
														  double r){
  vector<Point> ans;
  Vector v=c2.c-c1.c;
  double dist=Length(v);
  int d=dcmp(dist-c1.r-c2.r-r*2);
  if(d>0) return ans;
  getCircleCircleIntersection(Circle(c1.c,c1.r+r),Circle(c2.c,c2.r+r),ans);
  return ans;
}
//规整化
double lineAngleDegree(const Vector& v){
  double ang=angle(v)*180.0/PI;
  while(dcmp(ang)<0) ang+=360.0;
  while(dcmp(ang-180)>=0) ang-=180.0;
  return ang;
}
void format(Circle c){
  printf("(%.6lf,%.6lf,%.6lf)\n",c.c.x,c.c.y,c.r);
}
void format(vector<double> ans){
  int n=ans.size();
  sort(ans.begin(),ans.end());
  printf("[");
  if(n){
	printf("%.6lf",ans[0]);
	for(int i=1;i<n;i++) printf(",%.61f",ans[i]);
  }
  printf("]\n");
}
void format(vector<Point> ans){
  int n=ans.size();
  sort(ans.begin(),ans.end());
  printf("[");
  if(n){
	printf("(%.6lf,%.6lf)",ans[0].x,ans[0].y);
	for(int i=1;i<n;i++)
	  printf(",(%.6lf,%.6lf)",ans[1].x,ans[1].y);
  }
  printf("]\n");
}
Line getLine(const Point& p1,const Point& p2){
  return Line(p1,p2-p1);
}
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  for(string cmd;cin>>cmd;){
	double r1,r2,r;
	Point p1,p2,p3,p4,pc,pp;
	if(cmd=="CircumscribedCircle"){
	  cin>>p1>>p2>>p3;
	  format(CircumscribedCircle(p1,p2,p3));
	}
	if(cmd=="InscribedCircle"){
	   cin>>p1>>p2>>p3;
	   format(InscribedCircle(p1,p2,p3));
	}
	if(cmd=="TangentLineThroughPoint"){
	  cin>>pc>>r>>pp;
	  Vector v[2];
	  vector<double> ans;
	  int cnt=getTangents(pp,Circle(pc,r),v);
	  for(int i=0;i<cnt;i++) ans.push_back(lineAngleDegree(v[i]));
	  format(ans);
	}
	if(cmd=="CircleThroughAPointAndTangentToALineWithRadius"){
	  cin>>pp>>p1>>p2>>r;
	  format(CircleThroughPointTangentToLineGivenRadius(pp,getLine(p1,p2),r));
	}
	if(cmd=="CircleTangentToTwoLinesWithRadius"){
	  cin>>p1>>p2>>p3>>p4>>r;
	  format(CircleTangentToLinesGivenRadius(getLine(p1,p2),getLine(p3,p4),r));
	}
	if(cmd=="CircleTangentToTwoDisjointCirclesWithRadius"){
	  cin>>p1>>r1>>p2>>r2>>r;
	  Circle c1(p1,r1),c2(p2,r2);
	  format(CircleTangentToTwoDisjointCirclesWithRadius(c1,c2,r));
	}
  }
  return 0;
}  
