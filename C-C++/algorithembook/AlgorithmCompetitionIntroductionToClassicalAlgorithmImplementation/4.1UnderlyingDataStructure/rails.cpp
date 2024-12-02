#include<bits/stdc++.h>
using namespace std;
#define _for(i,a,b) for(int i=(a);i<(b);++i)
#define _rep(i,a,b) for(int i=(a);i<=(b);++i)
const int MAXN=1000+4;
int N,B[MAXN];
int main(){
  ios::sync_with_stdio(false),tie.cin(0);
  while(cin>>N && N){
	while(cin>>B[1] && B[1]){
	  _rep(i,2,N) cin>>B[i];
	  stack<int> s;
	  int ai=1,bi=1;
	  while(bi<=N){
		if(ai==B[bi]) ai++,bi++;
		else if(!a.empty()&& s.top()==B[bi]) ++bi,s.pop();
		else if(ai<N) s.push(ai++);
		else break;
	  }
	  cout<<((bi==N+1)?"Yes":"No")<<endl;
	}
	cout<<endl;
  }
  return 0;
}
