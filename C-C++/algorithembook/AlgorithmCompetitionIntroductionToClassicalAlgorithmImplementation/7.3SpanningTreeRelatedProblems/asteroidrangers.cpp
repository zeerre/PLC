#include<bits/stdc++.h>
using namespace std;

const int maxn=50+5,maxks=maxn*(maxn+1)/2;
const double eps=1e-8;;
struct Event{
  double t;
  int newks,oldks;
  Event(double t=0,int newks=0,int oldks=0):
	t(t),newks(newks),oldks(oldks){}
  bool operator<(const Event& rhs) const{return t-rhs.t<0;}
};
int n,nks;
vector<Event> ES;
struct KineticPoint{
  double x,y,z;
  double dx,dy,dz;
  void read(){scanf("%lf%lf%lf%lf%lf%lf",&x,&y,&z,&dx,&dy,&dz);}
}kp[maxn];
struct KineticSegment{
  double a,b,c;
  int u,v;
  bool operator<(const KineticSegment& rhs) const{
	return c-rhs.c<0;
  }
}ks[maxks];
inline double sqr(double x){return x*x;}
int pa[maxn];
void init_ufset(){
  for(int i=0;i<n;i++) pa[i]=i;
}
int findset(int x){return pa[x]!=x ? pa[x]=findset(pa[x]):x;}
void make_segments(){
  nks=0;
  for(int i=0;i<n;i++)
	for(int j=i+1;j<n;j++){
	  ks[nks].a=sqr(kp[i].dx-kp[j].dx)+sqr(kp[i].dy-kp[j].dy)+
		sqr(kp[i].dz-kp[j].dz);
	  ks[nks].b=2*((kp[i].dx-kp[j].dx)*(kp[i].x-kp[j].x)+
				   (kp[i].dy-kp[j].dy)*(kp[i].y-kp[j].y)+
				   (kp[i].dz-kp[j].dz)*(kp[i].z-kp[j].z));
	  ks[nks].c=sqr(kp[i].x-kp[j].x)+sqr(kp[i].y-kp[j].y)+
		sqr(kp[i].z-kp[j].z);
	  ks[nks].u=i;
	  ks[nks].v=j;
	  nks++;
	}
  sort(ks,ks+nks);
}
void make_events(){
  ES.clear();
  for(int i=0;i<nks;i++)
	for(int j=i+1;j<nks;j++){
	  int s1=i,s2=j;
	  if(ks[s1].a-ks[s2].a<0)
		s1=j,s2=i;
	  double a=ks[s1].a-ks[s2].a;
	  double b=ks[s1].b-ks[s2].b;
	  double c=ks[s1].c-ks[s2].c;
	  if(fabs(a)<eps){
		if(fabs(b)<eps) continue;
		if(b>0){
		  swap(s1,s2);
		  b=-b;
		  c=-c;
		}
		if(c>0) ES.push_back(Event(-c/b,s1,s2));
		continue;
	  }
	  double delta=b*b-4*a*c;
	  if(delta<eps) continue;
	  delta=sqrt(delta);
	  double t1=-(b+delta)/(2*a);
	  double t2=(delta-b)/(2*a);
	  if(t1>0) ES.push_back(Event(t1,s1,s2));
	  if(t2>0) ES.push_back(Event(t2,s2,s1));
	}
  sort(ES.begin(),ES.end());
}
int solve(){
  int pos[maxks];
  int e[maxn];
  init_ufset();
  for(int i=0;i<nks;i++) pos[i]=0;
  int idx=0;
  for(int i=0;i<nks;i++){
	int u=findset(ks[i].u),v=findset(ks[i].v);
	if(u!=v){
	  e[pos[i]= ++idx]=i;
	  pa[u]=v;
	}
	if(idx==n-1) break;
  }
  int ans=1;
  for(int i=0;i<ES.size();i++){
	if(pos[ES[i].oldks] && (!pos[ES[i].newks])){
	  init_ufset();
	  int oldpos=pos[ES[i].oldks];
	  for(int j=1;j<n;j++)
		if(j!=oldpos){
		  int u=findset(ks[e[j]].u),v=findset(ks[e[j]].v);
		  if(u!=v) pa[u]=v;
		}
	  int u=findset(ks[ES[i].newks].u),v=findset(ks[ES[i].newks].v);
	  if(u!=v){
		ans++;
		pos[ES[i].newks]=oldpos,e[oldpos]=ES[i].newks,pos[ES[i].oldks]=0;
	  }
	}
  }
  return ans;
}
int main(){
  for(int kase=1;scanf("%d",&n) ==1;kase++){
	for(int i=0;i<n;i++) kp[i].read();
	make_segments(),make_events();
	int ans=solve();
	printf("Case %d: %d\n",kase,ans);
  }
  return 0;
}
