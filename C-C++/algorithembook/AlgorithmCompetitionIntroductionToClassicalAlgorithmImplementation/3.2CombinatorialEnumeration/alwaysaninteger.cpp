#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
struct Polynomial{
  vector<int> a,p;
  void parse_polynomial(string expr){
	int i=0,len=expr.size();
	while(i<len){
	  int sign=1,v=0;
	  if(expr[i]=='+') i++;
	  if(expr[i]=='-') sign=-1,i++;
	  while(i<len && isdigit(expr[i])) v=v*10+expr[i++]-'0';
	  if(i==len){
		a.push_back(v),p.push_back(0);
		continue;
	  }
	  assert(expr[i]=='n');
	  if(v==0) v=1;
	  v*=sign;
	  if(expr[++i]=='^'){
		a.push_back(v),v=0;
		i++;
		while(i<len && isdigit(expr[i])) v=v*10+expr[i++]-'0';
		p.push_back(v);
	  }else
		a.push_back(v),p.push_back(1);
	}
  }
  int mod(int x,int MOD){
	int ans=0;
	for(size_t i=0;i<a.size();i++){
	  int m=a[i];
	  for(int j=0;j<p[i];j++) m=(LL)m*x%MOD;
	  ans=((LL)ans+m)%MOD;
	}
	return ans;
  }
};
bool check(string expr){
  int p=expr.find('/');
  Polynomial poly;
  poly.parse_polynomial(expr.substr(1,p-1));
  int D=atoi(expr.substr(p+1).c_str());
  for(int i=1;i<=poly.p[0]+1;i++)
	if(poly.mod(i,D)!=0) return false;
  return true;
}
int main(){
  string expr;
  for(int kase=1;cin>>expr;kase++){
	if(expr[0]=='.') break;
	printf("Case %d: ",kase);
	if(check(expr))
	  puts("Alaways an integer");
	else
	  puts("Not always an integer");
  }
  return 0;
}
