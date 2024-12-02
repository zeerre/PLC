#include<bits/stdc++.h>
using namespace std;

const int maxn=1000+4,SZ=256;
int pa[SZ];
int findset(int x){return pa[x]!=x ? pa[x] = findset(pa[x]) : x ;}
int used[SZ],deg[SZ];
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  int T,n;
  string s;
  cin>>T;
  while(T--){
	cin>>n,fill_n(used,SZ,0),fill_n(deg,SZ,0);
	int cc=26;
	for(int i=0;i<n;i++){
	  cin>>s;
	  char c1=s[0],c2=s[s.size()-1];
	  deg[c1]++,deg[c2]--,used[c1]=used[c2]=1;
	  int s1=findset(c1),s2=findset(c2);
	  if(s1!=s2) pa[s1]=s2,cc--;
	}
	vector<int> d;
	for(int ch='a';ch<='z';ch++){
	  if(!used[ch]) cc--;
	  else if(deg[ch]!=0) d.push_back(deg[ch]);
	}
	if(cc==1 && (d.empty() || (d.size()==2 && (d[0]==1 || d[0]== -1))))
	  cout<<"Ordering is possible."<<endl;
	else
	  cout<<"The door cannot be opened."<<endl;
  }
  return 0;
}
