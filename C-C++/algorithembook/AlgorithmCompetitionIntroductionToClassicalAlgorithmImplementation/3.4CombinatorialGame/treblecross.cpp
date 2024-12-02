#include<bits/stdc++.h>

using namespace std;

const int NN=200;
int g[NN+10];
bool winning(const char* state){
  int n=strlen(state);
  for(int i=0;i<n-2;i++)
	if(state[i]=='X' && state[i+1]=='X' && state[i+2]=='X')
	  return false;
  int no[NN+1];
  fill_n(no,NN+1,0);
  no[n]=1;
  for(int i=0;i<n;i++){
	if(state[i]!='X') continue;
	for(int d=-2;d<=2;d++)
	  if(i+d>=0 && i+d<n){
		if(d!=0 && state[i+d]=='X')
		  return true;
		no[i+d]=1;
	  }
  }
  int sg=0;
  for(int i=0,start=-1;i<=n;i++){
	if(start<0 && !no[i]) start=i;
	if(no[i] && start>=0) sg^=g[i-start];
	if(no[i]) start=-1;
  }
  return sg!=0;
}
int mex(vector<int>& s){
  if(s.empty()) return 0;
  sort(s.begin(),s.end());
  if(s[0]!=0) return 0;
  for(int i=1;i<s.size();i++)
	if(s[i]>s[i-1]+1) return s[i-1]+1;
  return s[s.size()-1]+1;
}
void init(){
  g[0]=0,g[1]=g[2]=g[3]=1;
  for(int i=4;i<=NN;i++){
	vector<int> s;
	s.push_back(g[i-3]);
	s.push_back(g[i-4]);
	if(i>=5) s.push_back(g[i-5]);
	for(int j=3;j<i-3;j++)
	  s.push_back(g[j-2]^g[i-j-3]);
	g[i]=mex(s);
  }
}
int main(){
  init();
  int T;
  scanf("%d",&T);
  while(T--){
	char state[NN+10];
	scanf("%s",state);
	int n=strlen(state);
	if(!winning(state)){
	  puts("LOSING\n");
	  continue;
	}
	puts("WINNING");
	vector<int> moves;
	for(int i=0;i<n;i++)
	  if(state[i]=='.'){
		state[i]='X';
		if(!winning(state)) moves.push_back(i+1);
		state[i]='.';
	  }
	printf("%d",moves[0]);
	for(int i=1;i<moves.size();i++ ) printf(" %d",moves[i]);
	puts("");
  }
  return 0;
}
