#include<bits/stdc++.h>
using namespace std;

#define _for(i,a,b) for(int i=(a);i<(int)(b);++i)
#define _rep(i,a,b) for(int i=(a);i<=(int)(b);++i)

const int SZ=10005,MAXC=1e6+4;
int BLOCK,Color[SZ],CurColor[SZ],CNT[MAXC],Ans[SZ];
struct Query{
  int l,r,id,c;
  bool operator<(const Query &rhs) const{
	if(l/BLOCK==rhs.l/BLOCK){
	  if(r/BLOCK==rhs.r/BLOCK) return id<rhs.id;
	  return r<rhs.r;
	}
	return l<rhs.l;
  }
};
struct Change{
  int pos,old_color,color;
  void apply();
  void revert();
};
Query Q[SZ];
Change Changes[SZ];
int curAns,curL,curR;
void add_pos(int a){
  if(++CNT[a]==1) curAns++;
}
void del_pos(int a){
  if(--CNT[a]==0) curAns--;
}
void Change::apply(){
  if(curL<=pos && pos<=curR) del_pos(old_color),add_pos(color);
  Color[pos]=color;
}
void Change::revert(){
  if(curL<=pos && pos<=curR) del_pos(color),add_pos(old_color);
  Color[pos]=old_color;
}
int main(){
  int N,M,c1=0,c2=0;
  cin>>N>>M;
  BLOCK=pow(N,2.0/3.0);
  _rep(i,1,N) cin>> Color[i],CurColor[i]=Color[i];
  char opt[4];
  _rep(i,1,M){
	cin>>opt;
	if(opt[0]=='Q'){
	  Query &q=Q[c1];
	  cin>>q.l>>q.r,q.id=c1++,q.c=c2;
	}else{
	  Change &ch=Changes[c2++];
	  cin>>ch.pos>>ch.color;
	  ch.old_color=CurColor[ch.pos],CurColor[ch.pos]=ch.color;
	}
  }
  sort(Q,Q+c1);
  curL=1,curR=1,curAns=0;
  int last_c=0;
  add_pos(Color[1]);
  _for(i,0,c1){
	while(last_c<Q[i].c) Changes[last_c++].apply();
	while(last_c>Q[i].c) Changes[--last_c].revert();
	while(curR<Q[i].r) add_pos(Color[++curR]);
	while(curR>Q[i].r) del_pos(Color[curR--]);
	while(curL>Q[i].l) add_pos(Color[--curL]);
	while(curL<Q[i].l) del_pos(Color[curL++]);
	Ans[Q[i].id]=curAns;
  }
  _for(i,0,c1) cout<<Ans[i]<<endl;
  return 0;
}
