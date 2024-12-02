#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
#define _for(i,a,b) for(int i=(a);i<(b);++i)
map<int ,int> sums;
void readTree(int pos){
  int root;
  scanf("%d",&root);
  if(root==-1)return;
  sums[pos]+=root,readTree(pos-1),readTree(pos+1);
}
int main(){
  for(int t=1;true;t++){
	sums.clear(),readTree(0);
	if(sums.empty()) break;
	printf("Case %d:\n",t);
	int i=0;
	for(auto p:sums){
	  if(i++) printf(" ");
	  printf("%d",p.second);
	}
	puts("\n");
  }
  return 0;
}
