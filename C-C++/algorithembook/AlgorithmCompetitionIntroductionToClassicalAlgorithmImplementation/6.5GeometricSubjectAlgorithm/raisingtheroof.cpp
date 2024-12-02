#include<bits/stdc++.h>
using namespace std;

#define rep(i,n) for(int i=0;i<(n);++i)
const double eps=1e-8;
int dcmp(double x){
  if(fabs(x)<eps) return 0;
  return x<0 ? -1:1;
}
struct Point3{
  int x,y,z;
  Point3(int x=0,int y=0,int z=0):x(x),y(y),z(z){}
};
typedef Point3 Vector3;
Vector3 operator - (const Point3& A,const Point3& B){
  return Vector3(A.x-B.x,A.y-B.y,A.z-B.z);
}
int Dot(const Vector3& A,const Vector3& B){
  return A.x*B.x+A.y*B.y+A.z*B.z;
}
double Length(const Vector3& A){ return sqrt(Dot(A,A));}
Vector3 Cross(const Vector3& A,const Vector3& B){
  return Vector3(A.y*B.z-A.z*B.y,A.z*B.x-A.x*B.z,A.x*B.y-A.y*B.x);
}

//
const int maxn=300+10,maxt=1000+10;
Point3 p[maxn];
int n,m;
int t[maxt][3];
Vector3 normal[maxt];
double d[maxt];
double area_ratio[maxt];
void init(){
  for(int i=0;i<m;i++){
	Point3 p0=p[t[i][0]],p1=p[t[i][1]],p2=p[t[i][2]];
	normal[i]=Cross(p1-p0,p2-p0);
	d[i]=Dot(normal[i],p0);
	if(normal[i].z!=0)
	  area_ratio[i]=fabs((double)Length(normal[i])/normal[i].z);
  }
}
inline double getTriangleZ(int idx,double x,double y){
  return (d[idx]-normal[idx].x*x-normal[idx].y*y)/normal[idx].z;
}
struct Event{
  int id;
  double y;
  Event(int id,double y):id(id),y(y){}
  bool operator<(const Event& rhs)const{return y<rhs.y;}
};
double solve(){
  vector<double> sx;
  for(int i=1;i<=n;i++) sx.push_back(p[i].x);
  rep(i,m)	rep(j,m)	rep(a,3)	rep(b,3){
	Point3 pa=p[t[i][a]];
	Point3 pb=p[t[i][(a+1)%3]];
	Point3 qa=p[t[j][b]];
	Point3 qb=p[t[j][(b+1)%3]];
	int dpx=pb.x-pa.x;
	int dpy=pb.y-pa.y;
	int dqx=qb.x-qa.x;
	int dqy=qb.y-qa.y;
	int deno=dpx*dqy-dpy*dqx;
	if(deno==0) continue;
	double t=(double)(dqy*(qa.x-pa.x)+dqx*(pa.y-qa.y))/deno;
	double s=(double)(dpy*(qa.x-pa.x)+dpx*(pa.y-qa.y))/deno;
	if(t>1 || t<0 || s>1 || s<0) continue;
	sx.push_back(pa.x+t*dpx);
  }
  sort(sx.begin(),sx.end());
  sx.erase(unique(sx.begin(),sx.end()),sx.end());
  double ans=0;
  for(int i=0;i<sx.size()-1;i++){
	double xx=(sx[i]+sx[i+1])/2;
	vector<Event> events;
	rep(j,m) if(normal[j].z !=0) rep(a,3){
		Point3 pa=p[t[j][a]],pb=p[t[j][(a+1)%3]];
		if(pa.x==pb.x) continue;
		if(!(min(pa.x,pb.x)<=sx[i] && max(pa.x,pb.x)>=sx[i+1]))
		  continue;
		double y=pa.y+(pb.y-pa.y)*(xx-pa.x)/(pb.x-pa.x);
		events.push_back(Event(j,y));
	  }
	if(events.empty()) continue;
	int inside[maxt];
	fill_n(inside,maxt,0),sort(events.begin(),events.end());
	for(int j=0;j<events.size()-1;j++){
	  inside[events[j].id]^=1;
	  if(fabs(events[j].y-events[j+1].y)<eps)
		continue;
	  double proj_are=(sx[i+1]-sx[i])*(events[j+1].y-events[j].y);
	  int top=-1;
	  double topz=-1e9,yy=(events[j].y+events[j+1].y)/2;
	  for(int k=0;k<m;k++)
		if(inside[k]){
		  double zz=getTriangleZ(k,xx,yy);
		  if(zz>topz) topz=zz,top=k;
		}
	  if(top>=0) ans+=area_ratio[top]*proj_are;
	}
  }
  return ans;
}
int main(){
  int kase=0;
  while(scanf("%d%d",&n,&m)==2 && n>0){
	for(int i=1;i<n;i++)
	  scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].z);
	for(int i=0;i<m;i++) scanf("%d%d%d",&t[i][0],&t[i][1],&t[i][2]);
	init();
	double ans=solve();
	printf("Case %d: %.2lf\n\n",++kase,ans);
  }
  return 0;
}
