#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int NN=2e5+8;
struct Point{
  LL x,y;
  int c,id;
}Ps[NN];
istream& operator>>(istream& is,Point& p){return is>>p.x>>p.y>>p.c;}
bool cmpx(const Point& p1,const Point& p2){return p1.x<p2.x;}
bool cmpy(const Point& p1,const Point& p2){return p1.y<p2.y;}
LL dist(const Point& a,const Point& b){
  return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
bool Div[NN];
void build(int l,int r){
  if(l>r) return;
  int m=(l+r)/2;
  Point *p1=Ps+l,*pr=Ps+r+1;
  pair<Point*,Point*> px=minmax_element(p1,pr,cmpx),
	py=minmax_element(p1,pr,cmpy);
  Div[m]=px.second->x-px.first->x>=py.second->y-py.first->y;
  nth_element(p1,Ps+m,pr,Div[m]?cmpx:cmpy);
  build(l,m-1),build(m+1,r);
}
void nearest(int l,int r,const Point& p,LL& min_d,int& id){
  if(l>r) return;
  int m=(l+r)/2;
  const Point& pm=Ps[m];
  LL d=dist(p,pm);
  if(pm.c<=p.c){
	if(d<min_d) min_d=d,id=m;
	else if (d==min_d&& pm.id<Ps[id].id) id=m;
  }
  d=Div[m]?(p.x-pm.x):(p.y-pm.y);
  if(d<=0){
	nearest(1,m-1,p,min_d,id);
	if(d*d<min_d) nearest(m+1,r,p,min_d,id);
  }else{
	nearest(m+1,r,p,min_d,id);
	if(d*d<min_d) nearest(1,m-1,p,min_d,id);
  }
}
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  int id,n,m,T;
  cin>>T;
  while(T--){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>Ps[i],Ps[i].id=i;
	build(1,n);
	Point p;
	while(m--){
	  cin>>p;
	  LL min_d=1LL<<60;
	  nearest(1,n,p,min_d,id);
	  printf("%lld %lld %d\n",Ps[id].x,Ps[id].y,Ps[id].c);
	}
  }
  return 0;
}

