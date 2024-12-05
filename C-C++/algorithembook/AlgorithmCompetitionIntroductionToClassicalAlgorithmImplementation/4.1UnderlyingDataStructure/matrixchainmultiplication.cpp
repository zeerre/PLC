#include<bits/stdc++.h>

using namespace std;
struct Matrix{
  int a,b;
  Matrix(int a=0,int b=0):a(a),b(b){}
}m[32];
int solve(const string& expr){
  stack<Matrix> s;
  int ans=0;
  for(size_t i=0;i<expr.length();i++){
	char e=expr[i];
	if(isalpha(e)) s.push(m[e-'A']);
	else if(e==')') {
	  Matrix m2=s.top();s.pop();
	  Matrix m1=s.top();s.pop();
	  if(m1.b!=m2.a) return -1;
	  ans+=m1.a*m1.b*m2.b;
	  s.push(Matrix(m1.a,m2.b));
	}
  }
  return ans;
}
int main(){
  int n;
  cin>>n;
  string s;
  for(int i=0;i<n;i++){
	cin>>s;
	cin>>m[s[0]-'A'].a>>m[s[0]-'A'].b;
  }
  while(cin>>s){
	int ans=solve(s);
	if(ans==-1) printf("error\n");
	else printf("%d\n",ans);
  }
  return 0;
}
