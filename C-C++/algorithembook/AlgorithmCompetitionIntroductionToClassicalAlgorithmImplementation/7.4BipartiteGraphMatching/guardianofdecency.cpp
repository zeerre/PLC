#include<bits/stdc++.h>
using namespace std;
const int maxn=500+5;

struct BPM{
  int n,m;
  int G[maxn][maxn];
  int left[maxn];
  bool T[maxn];
  void init(int n,int m){
	this->n=n,this->m=m;
	memset(G,0,sizeof(G));
  }
  bool match(int u){
	for(int v=0;v<m;v++) if(G[u][v] && !T[v]){
		T[v]=true;
		if(left[v]==-1 || match(left[v])){
		  left[v]=u;
		  return true;
		}
	  }
	return false;
  }
  int solve(){
	int ans=0;
	fill_n(left,m+1,-1);
	for(int u=0;u<n;u++){
	  fill_n(T,m+1,false);
	  if(match(u)) ans++;
	}
	return ans;
  }
};
BPM solver;
struct Student{
  int h;
  string music,sport;
  Student(int h=0,const string& music="",const string& sport =""):
	h(h),music(music),sport(sport){}
};
bool conflict(const Student& a,const Student& b){
  return abs(a.h-b.h)<=40 && a.music==b.music && a.sport!=b.sport;
}
int main(){
  int T;cin>>T;
  for(int t=0,n;cin>>n,t<T;t++){
	vector<Student> male,female;
	Student s;
	for(int i=0;i<n;i++){
	  string gender;
	  cin>>s.h>>gender>>s.music>>s.sport;
	  if(gender[0]='M') male.push_back(s);
	  else female.push_back(s);
	}
	int x=male.size(),y=female.size();
	solver.init(x,y);
	for(int i=0;i<x;i++)
	  for(int j=0;j<y;j++)
		if(conflict(male[i],female[j])) solver.G[i][j]=1;
	printf("%d\n",x+y-solver.solve());
  }
  return 0;
}
