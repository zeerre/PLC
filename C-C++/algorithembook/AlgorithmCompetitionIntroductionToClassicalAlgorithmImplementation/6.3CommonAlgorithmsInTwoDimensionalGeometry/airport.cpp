#include<bits/stdc++.h>
using namespace std;
struct Point{
  double x,y;
  Point(double x=0,double y=0):x(x),y(y){}
};
istream& operator>>(istream& is,Point& p){return is>>p.x>>p.y;}
ostream& operator<<(ostream& os,Point& p){return os<<p.x<<" "<<p.y;}
typedef Point Vector;
Vector operator -(const Point& A,const Point& B)
{return Vector(A.x-B.x,A.y-B.y);}
double Cross(const Vector& A,const Vector& B)
{return A.x*B.y-A.y*B.x;}
bool operator<(const Point& p1,const Point& p2)
{return p1.x<p2.x || (p1.x==p2.x && p1.y<p2.y);}
bool operator==(const Point& p1,const Point& p2)
{return p1.x==p2.x && p1.y==p2.y;}
vector<Point> ConvexHull(vector<Point> p){
  sort(p.begin(),p.end());
  p.erase(unique(p.begin(),p.end()),p.end());
  int n=p.size(),m=0;
  vector<Point> ch(n+1);
  for(int i=0;i<n;i++){
	while(m>1 && Cross(ch[m-1]-ch[m-2],p[i]-ch[m-1]) <=0) m--;
	ch[m++]=p[i];
  }
  int k=m;
  for(int i=n-2;i>=0;i--){
	while(m>k && Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2]) <=0) m--;
	ch[m++]=p[i];
  }
  if(n>1) m--;
  ch.resize(m);
  return ch;
}
void getLineGeneralEquation(const Point& p1,const Point& p2,
							double& a,double& b,double &c){
  a=p2.y-p1.y,b=p1.x-p2.x,c=-a*p1.x-b*p1.y;
}
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  int T;cin>>T;
  for(int kase=1,n;kase<=T;kase++){
	cin>>n;
	vector<Point> P;
	double sumx=0,sumy=0;
	Point pt;
	for(int i=0;i<n;i++)
	  cin>>pt,sumx+=pt.x,sumy+=pt.y,P.push_back(pt);
	vector<Point> ch=ConvexHull(P);
	int m=ch.size();
	double ans=1e9;
	if(m<=2) ans=0;
	else
	  for(size_t i=0;i<ch.size();i++){
		double a,b,c;
		getLineGeneralEquation(ch[i],ch[(i+1)%ch.size()],a,b,c);
		ans=min(ans,fabs(a*sumx+b*sumy+c*n)/sqrt(a*a+b*b));
	  }
	printf("Case #%d: %.3lf\n",kase,ans/n);
  }
  return 0;
}
