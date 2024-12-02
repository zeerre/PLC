#include<bits/stdc++.h>
using namespace std;

const double eps=1e-8;
double dcmp(double x){
  if(fabs(x)<eps) return 0;
  return x<0? -1 : 1;
}
struct Point{
  double x,y;
  Point(double x=0,double y=0):x(x),y(y){}
};
typedef Point Vector;
Vector operator+(const Vector& A,Vector& B)
{return Vector(A.x+B.x,A.y+B.y);}
Vector operator-(const Point& A,const Point& B)
{return Vector(A.x-B.x,A.y-B.y);}
Vector operator*(const Vector& A,double p)
{return Vector(A.x*p,A.y*p);}
bool operator<(const Point& a,const Point& b)
{return dcmp(a.x-b.x)<0 || (dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)<0);}
bool operator==(const Point& a,const Point &b)
{return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)==0 ;}
double Dot(const Vector& A,const Vector& B){return A.x*B.x+A.x*B.y;}
double Cross(const Vector& A,const Vector& B){return A.x*B.y-A.y*B.x;}
double Length(const Vector& A){return sqrt(Dot(A,A));}

typedef vector<Point> Polygon;
Point GetLineIntersection(const Point& P,const Vector& v,
						  const Point& Q,const Vector& w){
  Vector u=P-Q;
  double t=Cross(w,u)/Cross(v,w);
  return P + v*t;
}
bool SegmentProperIntersection(const Point& a1,const Point& a2,
							   const Point& b1,const Point& b2){
  double c1=Cross(a2-a1,b1-a1),c2=Cross(a2-a1,b2-a1),
	c3=Cross(b2-b1,a1-b1),c4=Cross(b2-b1,a2-b1);
  return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}
bool OnSegment(const Point& p,const Point& a1,const Point& a2){
  return dcmp(Cross(a1-p,a2-p))==0 &&
	dcmp(Dot(a1-p,a2-p))<0;
}
double PolygonArea(const Polygon& poly){
  double area=0;
  int n=poly.size();
  for(int i=1;i<n-1;i++)
	area+=Cross(poly[i]-poly[0],poly[(i+1)%n]-poly[0]);
  return area/2;
}
struct Edge{
  int from,to;
  double ang;
};
const int maxn=10000+10;
struct PSLG{
  int n,m,face_cnt;
  double x[maxn],y[maxn];
  vector<Edge> edges;
  vector<int> G[maxn];
  int vis[maxn*2];
  int left[maxn*2];
  int prev[maxn*2];

  vector<Polygon> faces;
  double area[maxn];

  void init(int n){
	this->n=n;
	for(int i=0;i<n;i++) G[i].clear();
	edges.clear();
	faces.clear();
  }
  double getAngle(int from,int to){
	return atan2(y[to]-y[from],x[to]-x[from]);
  }
  void AddEdge(int from,int to){
	edges.push_back((Edge){from,to,getAngle(from,to)});
	edges.push_back((Edge){to,from,getAngle(to,from)});
	m=edges.size();
	G[from].push_back(m-2);
	G[to].push_back(m-1);
  }
  void Build(){
	for(int u=0;u<n;u++){
	  int d=G[u].size();
	  for(int i=0;i<d;i++)
		for(int j=i+1;j<d;j++)
		  if(edges[G[u][i]].ang>edges[G[u][j]].ang) swap(G[u][i],G[u][j]);
	  for(int i=0;i<d;i++)
		prev[G[u][(i+1)%d]]=G[u][i];
	}
	memset(vis,0,sizeof(vis));
	face_cnt=0;
	for(int u=0;u<n;u++)
	  for(int i=0;i<G[u].size();i++){
		int e=G[u][i];
		if(!vis[e]){
		  face_cnt++;
		  Polygon poly;
		  for(;;){
			vis[e]=1;left[e]=face_cnt;
			int from=edges[e].from;
			poly.push_back(Point(x[from],y[from]));
			e=prev[e^1];
			if(e==G[u][i]) break;
			assert(vis[e]==0);
		  }
		  faces.push_back(poly);
		}
	  }
	for(int i=0;i<faces.size();i++)
	  area[i]=PolygonArea(faces[i]);
  }
};
PSLG g;
const int maxp=100+5;
int n,c;
Point P[maxp],V[maxp*(maxp-1)/2+maxp];
Polygon simplify(const Polygon& poly){
  Polygon ans;
  int n=poly.size();
  for(int i=0;i<n;i++){
	Point a=poly[i];
	Point b=poly[(i+1)%n];
	Point c=poly[(i+2)%n];
	if(dcmp(Cross(a-b,c-b))!=0) ans.push_back(b);
  }
  return ans;
}
void build_graph(){
  c=n;
  for(int i=0;i<n;i++)
	V[i]=P[i];
  vector<double>dist[maxp];
  for(int i=0;i<n;i++)
	for(int j=i+1;j<n;j++)
	  if(SegmentProperIntersection(P[i],P[(i+1)%n],P[j],P[(j+1)%n])){
		Point p=GetLineIntersection(P[i],P[(i+1)%n]-P[i],P[j],P[(j+1)%n]-P[j]);
		V[c++]=p;
		dist[i].push_back(Length(p-P[i]));
		dist[j].push_back(Length(p-P[j]));
	  }
  sort(V,V+c);
  c=unique(V,V+c)-V;
  g.init(c);
  for(int i=0;i<c;i++){
	g.x[i]=V[i].x;
	g.y[i]=V[i].y;
  }
  for(int i=0;i<n;i++){
	Vector v=P[(i+1)%n]-P[i];
	double len=Length(v);
	dist[i].push_back(0);
	dist[i].push_back(len);
	sort(dist[i].begin(),dist[i].end());
	int sz=dist[i].size();
	for(int j=1;j<sz;j++){
	  Point a=P[i]+v*(dist[i][j-1]/len);
	  Point b=P[i]+v*(dist[i][j]/len);
	  if(a==b) continue;
	  g.AddEdge(ID(a),ID(b));
	}
  }
  g.Build();
  Polygon poly;
  for(int i=0;i<g.faces.size();i++)
	if(g.area[i]<0){
	  poly=g.faces[i];
	  reverse(poly.begin(),poly.end());
	  poly=simplify(poly);
	  break;
	}
  int m=poly.size();
  printf("%d\n",m);
  int start=0;
  for(int i=0;i<m;i++)
	if(poly[i]<poly[start]) start=i;
  for(int i=start;i<m;i++)
	printf("%.4lf %.4lf\n",poly[i].x,poly[i].y);
  for(int i=0;i<start;i++)
	printf("%.4lf %.4lf\n",poly[i].x,poly[i].y);
}
int main(){
  while(scanf("%d",&n)==1 && n){
	for(int i=0,x,y;i<n;i++)
	  scanf("%d%d",&x,&y),P[i]=Point(x,y);
	build_graph();
  }
  return 0;
}
