#include<bits/stdc++.h>

using namespace std;

const double eps=1e-8;
int dcmp(double x){
  if(fabs(x)<eps) return 0;else return x<0? -1 : 1;
}
struct Point3{
  double x,y,z;
  Point3(double x=0,double y=0,double z=0):x(x),y(y),z(z){}
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
Vector3 operator/(const Vector3& A,double p){
  return Vector3(A.x/p,A.y/p,A.z/p);
}
double Dot(const Vector3& A,const Vector3& B){
  return A.x*B.x+ A.y*B.y+A.z*B.z;
}
double Length(const Vector3& A){return sqrt(Dot(A,A));}
double Angle(const Vector3& A,const Vector3& B){
  return acos(Dot(A,B)/Length(A)/Length(B));
}
Vector3 Cross(const Vector3& A,const Vector3& B){
  return Vector3(A.y*B.z-A.z*B.y,A.z*B.x-A.x*B.z,A.x*B.y-A.y*B.x);
}
double Area2(const Point3& A,const Point3& B,const Point3& C){
  return Length(Cross(B-A,C-A));
}
double Volume6(const Point3& A,const Point3& B,const Point3& C,const Point3& D){
  return Dot(D-A,Cross(B-A,C-A));
}
bool read_point3(Point3& p){
  if(scanf("%lf%lf%lf%lf",&p.x,&p.y,&p.z)!=3) return false;
  return true;
}
double DistanceToPlane(const Point3& p,const Point3& p0,
					   const Vector3& n){
  return fabs(Dot(p-p0,n));
}
Point3 GetPlaneProjection(const Point3& p,const Point3& p0,
						  const Vector3& n){
  return p-n*Dot(p-p0,n);
}
double DistanceToLine(const Point3& P,const Point3& A,const Point3& B){
  Vector3 v1=B-A,v2=P-A;
  return Length(Cross(v1,v2))/Length(v1);
}
bool SameSide(const Point3& p1,const Point3& p2,
			  const Point3& a,const Point3& b){
  return dcmp(Dot(Cross(b-a,p1-a),Cross(b-a,p2-a)))>=0;
}
bool PointInTri(const Point3& P,const Point3& P0,
				const Point3& P1,const Point3& P2){
  return SameSide(P,P0,P1,P2)&& SameSide(P,P1,P0,P2) && SameSide(P,P2,P0,P1);
}
Point3 Gentroid(const Point3& A,const Point3& B,
				const Point3& C,const Point3& D){
  return (A+B+C+D)/4.0;
}
bool InsideWithMinDistance(const Point3& P,const Point3& A,const Point3& B,
						   const Point3& C,double mindist){
  if(!PointInTri(P,A,B,C)) return false;
  if(DistanceToLine(P,A,B)<mindist) return false;
  if(DistanceToLine(P,B,C)<mindist) return false;
  if(DistanceToLine(P,C,A)<mindist) return false;
  return true;
}
bool InsideWithMinDistance(const Point3& P,const Point3& A,const Point3& B,
						   const Point3& C,const Point3& D,double mindist){
  if(!PointInTri(P,A,B,C)) return false;
  if(!PointInTri(P,C,D,A)) return false;
  if(DistanceToLine(P,A,B)<mindist) return false;
  if(DistanceToLine(P,B,C)<mindist) return false;
  if(DistanceToLine(P,C,D)<mindist) return false;
  if(DistanceToLine(P,D,A)<mindist) return false;
  return true;
}
int main(){
  for(int kase=1;;kase++){
	Point3 P[5],F;
	for(int i=0;i<5;i++)
	  if(!read_point3(P[i])) return 0;
	read_point3(F);
	Point3 c1=Centroid(P[0],P[1],P[2],P[3]);
	Point3 c2=Centroid(P[0],P[1],P[2],P[4]);
	double vol1=fabs(Volume6(P[0],P[1],P[2],P[3]))/6.0;
	double vol2=fabs(Volume6(P[0],P[1],P[2],P[4]))/6.0;
	Point3 centroid=(c1*vol1+c2*vol2)/(vol1+vol2);
	double mindist=1e9,maxdist=-1e9;
	for(int i=0;i<5;i++)
	  for(int j=i+1;j<5;j++)
		for(int k=j+1;k<5;k++){
		  int vis[5]={0};
		  vis[i]=vis[j]=vis[k]=1;
		  int a,b;
		  for(a=0;a<5;a++) if(!vis[a]) {b=10-i-j-k-a;break;}
		  int d1=dcmp(Volume6(P[i],P[j],P[k],P[a]));
		  int d2=dcmp(Volume6(P[i],P[j],P[k],P[b]));
		  Vector3 n=Cross(P[j]-P[i],P[k]-P[i]);
		  n=n/Length(n);
		  Point3 proj=GetPlaneProjection(centroid,P[i],n);
		  bool ok=InsideWithMindDistance(proj,P[i],P[j],P[k],0.2);
		  if(!ok) {
			if(d1==0){
			  if(!InsideWithMindDistance(proj,P[i],P[j],P[k],0.2))
				continue;
			}else if(d2==0){
			  if(!InsideWithMindDistance(proj,P[i],P[k],P[j],P[b],0.2))
				continue;
			}else
			  continue;
		  }
		  double dist=DistanceToPlane(F,P[i],n);
		  mindist=min(mindist,dist);
		  maxdist=max(maxdist,dist);
		}
	printf("Case %d: %.5lf %.5lf\n",kase,mindist,maxdist);
  }
  return 0;
}
