#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
struct Stat{
  int C[9];
  Stat(){fill_n(C,9,4);}
  int index()const{
	int ans=0;
	for(int i=0;i<9;i++) ans=ans*5+C[i];
	return ans;
  }
};
const int MAXS=1953125+4;
double Ans[MAXS];
char Piles[9][4][3];
double DP(Stat& st){
  double& ans =Ans[st.index()];
  if(ans!=-1.0) return ans;
  ans=0;
  int cnt=0,empty=1;
  for(int i=0;i<9;i++){
	int& ci=st.C[i];
	if(ci<1) continue;
	empty=0;
	for(int j=i+1;j<9;j++){
	  int& cj=st.C[j];
	  if(cj<1) continue;
	  if(Piles[i][ci-1][0]==Piles[j][cj-1][0]){
		  ci-=1,cj-=1;
		  ans+=DP(st);
		  cnt++;
		  ci+=1,cj+=1;
		}
	}
  }
  if(empty) return ans=1;
  if(cnt==0) return ans=0;
  return ans/=cnt;
}
int main(){
  while(true){
	for(int i=0;i<9;i++)
	  for(int j=0;j<4;j++)
		if(scanf("%s",Piles[i][j])!=1) return 0;
	fill_n(Ans,MAXS,-1.0);
	Stat st;
	printf("%.6lf\n",DP(st));
  }
  return 0;
}

		
