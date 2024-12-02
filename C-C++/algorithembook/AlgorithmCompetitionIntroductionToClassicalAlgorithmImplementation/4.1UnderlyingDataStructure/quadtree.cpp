#include<bits/stdc++.h>

using namespace std;

#define _for(i,a,b) for(int i=(a);i<(b);++i)
#define _rep(i,a,b) for(int i=(a);i<=(b);++i)

const int len=32,NN=1024+4;
char s[NN];
int buf[len][len],cnt,DR[]={0,0,1,-1},DC[]={1,0,0,1};
void draw(const char* s,int &p,int r,int c, int w){
  char ch=s[p++];
  if(ch=='p'){
	w/=2;
	_for(i,0,4) draw(s,p,r+DR[i]*w,c+DC[i]*w,w);
  }else if(ch=='f'){
	_for(i,r,r+w) _for(j,c,c+w) if(buf[i][j]==0)
	  buf[i][j]=1,cnt++;
  }
}
int main(){
  int T;
  scanf("%d",&T);
  while(T--){
	memset(buf,0,sizeof(buf));
	cnt=0;
	for(int i=0;i<2;i++){
	  scanf("%s",s);
	  int p=0;
	  draw(s,p,0,0,len);
	}
	printf("There are %d black pixels.\n",cnt);
  }
  return 0;
}
