#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
const double EPS=0.0001;
struct Point3{
  double x,y,z;
  Point3(double _x=0,double _y=0,double _z=0):x(_x),y(_y),z(_z){}
};
typedef Point3 Vector3;
Vector3 operator+(const Vector3& A,const Vector3& B){
  return Vector3(A.x+B.x,A.y+B.y,A.z+B.z);
}
Vector3 operator-(const Point3& A,const Point3& B){
  return Vector3(A.x-B.x,A.y-B.y,A.z-B.z);
}
Vector3 operator*(const Vector3& A,double p){
  return Vector3(A.x*p,A.y*p,A.z*p);
}
double dot(const Point3& A,const Point3& B){
  return A.x*B.x+ A.y*B.y+A.z*B.z;
}
double length(const Point3& A){return sqrt(dot(A,A));}
Point3 LinePlaneIntersection(const Point3& p1,const Point3& p2,
							 const Vector3& PV,double D){
  double v1=dot(p1,PV)-D,v2=dot(p2,PV)-D,denom=v1-v2;
  return p1*(-v2/denom)+p2*(v1/denom);
}
double area_under(const vector<Point3>& ps,const Vector3& PV,double D){
  vector<Point3> poly;
  for(size_t i=0;i<ps.size();i++){
	const Point3 &p=ps[i],&np=ps[(i+1)%ps.size()];
	double v=dot(PV,p)-D,nv=dot(PV,np)-D;
	if(v<=EPS) poly.push_back(p);
	if(v*nv<EPS && fabs(v)>EPS && fabs(nv)>EPS)
	  poly.push_back(LinePlaneIntersection(np,p,PV,D));
  }
  double s=0;
  for(size_t j=1;j+1<poly.size();j++){
	Point3 v1=poly[j]-poly[0],v2=poly[j+1]-poly[0];
	s+=v1.x*v2.y-v2.x*v1.y;
  }
  return fabs(s)/2.0;
}
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  Point3 VS[8];
  Vector3 PV;
  double D,L,W,H;
  int T;cin>>T;
  for(int t=1,N;t<=T;t++){
	cin>>N>>L>>W>>H;
	cin>>PV.x>>PV.y>>PV.z>>D;
	for(int i=0;i<8;i++){
	  Point3& p=VS[i];
	  if(i & 1) p.z=H;
	  if(i & 2) p.y=W;
	  if(i & 4) p.x=L;
	}
	vector<Point3> top_vs={VS[1],VS[3],VS[7],VS[5]},
	  bottom_vs={VS[0],VS[2],VS[6],VS[4]};
	double top_area=all_of(top_vs.begin(),top_vs.end(),
						   [&](const Point3 & p){return dot(PV,p)>=D;})
	  ?0.0 : area_under(top_vs,PV,D);
	double bottom_area=all_of(bottom_vs.begin(),bottom_vs.end(),
							  [&](const Point3 & p){return dot(PV,p)<=D;})
	  ?L*W : area_under(bottom_vs,PV,D);
	double cos_phi=PV.z/length(PV);
	double ans=top_area+(bottom_area-top_area)/cos_phi;
	printf("%d %.01f\n",t,ceil(ans));
  }
  return 0;
}
