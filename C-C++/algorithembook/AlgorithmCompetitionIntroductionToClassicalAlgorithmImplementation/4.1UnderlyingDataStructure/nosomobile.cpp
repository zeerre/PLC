#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
bool readTree(LL& w){
  LL wl,dl,wr,dr;
  bool bl=true,br=true;
  cin>>wl>>dl>>wr>>dr;
  if(wl==0) bl=readTree(wl);
  if(wr==0)br=readTree(wr);
  w=wl+wr;
  return bl&&br&&(wl*dl==wr*dr);
}
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  int T;
  cin>>T;
  for(int t=0;t<T;++t){
	if(t) cout<<endl;
	LL w;
	bool ans=readTree(w);
	cout<<(ans?"YES":"NO")<<endl;
  }
  return 0;
}
