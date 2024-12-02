#include<bits/stdc++.h>
using namespace std;

#define _for(i,a,b) for(int i=(a);i<(b);++i)
#define _rep(i,a,b) for(int i=(a);i<(b);++i)
typedef long long LL;
const int MAXN=100+4,INF=0x7f7f7f7f;
char S[MAXN];
map<char, string> M2;
inline bool match(char c1,char c2){
  return (c1=='[' && c2==']')||(c1=='(' && c2==')');
}
int D[MAXN][MAXN],N;
void init_dp(){//(i,j)<-i+1,j-1,i+1,j-1,(i,k+k+1,j)
  memset(D,0,sizeof(D));
  _rep(i,0,N-1) D[i][i]=2;
  for(int i=N-2;i>=0;i--){
	_rep(j,i+1,N-1){
	  int& d=D[i][j];
	  d=INF;
	  if(match(S[i],S[j])) d=min(d,2+D[i+1][j-1]);
	  _for(m,i,j) d=min(d,D[i][m]+D[m+1][j]);
	}
  }
}
ostream& print(ostream& os,int i, int j){
  if(i>j) return os;
  char c1=S[i],cr=S[j];
  if(i==j) return os<<M2[c1];
  int d=D[i][j];
  if(match(c1,cr) && d==D[i+1][j-1]+2)
	return print(os<<c1,i+1,j-1)<<cr;
  _for(m,i,j) if(d==D[i][m]+D[m+1][j])
	return print(print(os,i,m),m+1,j);
  return os;
}
int main(){
  int T;
  M2['[']="[]",M2['(']="()",M2[']']="[]",M2[')']="()";
  fgets(S,MAXN,stdin);
  sscanf(S,"%d",&T);
  _for(t,0,T){
	if(t) puts("");
	fgets(S,MAXN,stdin),fgets(S,MAXN,stdin);
	N=strlen(S)-1;
	init_dp();
	stringstream ss;
	print(ss,0,N-1);
	puts(ss.str().c_str());
  }
  return 0;
}
