#include<bits/stdc++.h>
#include<ext/rope>
using namespace std;
using namespace _gnu_cxx;
crope ro,version[50100];

int main(){
  int n,d=0,ver=1;
  string buf;
  cin>>n;
  for(int i=0,opt,p,c,v;i<n;i++){
	cin>>opt;
	switch(opt){
	case 1:
	  cin>>p>>buf,p-=d;
	  ro.insert(p,buf.c_str()),version[ver++]=ro;
	  break;
	case 2:
	  cin>>p>>c,p-=d,c-=d;
	  ro.erase(p-1,c),version[ver++]=ro;
	  break;
	default:
	  cin>>v>>p>>c;
	  v-=d,p-=d,c-=d;
	  const crope& tmp=version[v].substr(p-1,c);
	  for(size_t i=0;i<tmp.size();i++){
		char c=tmp[i];
		d+=(c=='c'),cout<<c;
	  }
	  cout<<endl;
	  break;
	}
  }
  return 0;
}
