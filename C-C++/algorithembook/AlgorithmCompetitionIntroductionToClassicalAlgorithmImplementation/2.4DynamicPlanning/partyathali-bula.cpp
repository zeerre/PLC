#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN=200+4;
vector<int> CH[MAXN];
int D[MAXN][2][2],VIS[MAXN][2];
int dp(const int u,const int pa){
  assert(pa==0||pa==1);
  int &d=D[u][pa][0],&cnt =D[u][pa][1];
  if(VIS[u][pa]) return d;
  VIS[u][pa]=1;
  d=0,cnt=1;
  for(size_t i=0;i<CH[u].size();i++)
	d+=dp(CH[u][i],0),cnt*= D[CH[u][i]][0][1];
  if(pa==0){
	int nd=0,c=1;
	for(size_t i=0;i<CH[u].size();i++)
	  nd+= dp(CH[u][i],1),c*=D[CH[u][i]][1][1];
	if(nd==d) cnt+=c;
	else if(nd>d) d=nd,cnt=c;
  }
  return d;
}
map<string,int> names;
int nCnt=0;
int getId(const string& s){
  if(!names.count(s)) names[s]=nCnt++;
  return names[s];
}
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  string n1,n2;
  for(int N;cin>>N&&N;){
	for(int i=0;i<N;i++) CH[i].clear();
	names.clear(),nCnt=0;
	memset(D,0,sizeof(D)),memset(VIS,0,sizeof(VIS));
	cin>>n1,names[n1]=nCnt++;
	for(int i=1;i<N;i++){
	  cin>>n1>>n2;
	  int pa=getId(n2),u=getId(n1);
	  CH[pa].push_back(u);
	}
	int ans= dp(0,0);
	printf("%d %s\n",ans,(D[0][0][1]==1?"YES":"NO"));
  }
  return 0;
}
				   
