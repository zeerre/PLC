#include<bits/stdc++.h>
using namespace std;

/*
  求解方程组的整数解的e个数：
  p*s+d=x   (1)
  q*s+d=y   (2)
  r*s+d=z   (3)
  其中，s代表缩放系数，d代表平移量
  解：联立方程（1）（2），得到(p-q)*s=x-y
  i)如果p-q=0,则必须有x==y,否则无解
  ii)如果p-q!=0,则s=(x-y)/(p-q).如果s不是整数，则无解，否则s是一个解
  类似的，还应联立方程(2),(3)和方程(3),(1)求解。
  i)如果求出了多个s，他们必须相同
  ii)如果一个s都没有得到，说明有无穷多组解（返回2就可以了）
  iii)如果s=0,根据题意，也无解
*/
int solve(int p,int q,int r,int x,int y,int z){
  int a[]={p,q,r};
  int b[]={x,y,z};
  vector<int > ans;
  for(int i=0;i<3;i++){
	int P=a[i],Q=a[(i+1)%3],X=b[i],Y=b[(i+1)%3];
	if(P==Q){if(X!=Y) return 0;}
	else if((X-Y)%(P-Q)!=0) return 0;
	else ans.push_back((X-Y)/(P-Q));
  }
  if(ans.empty()) return 2;
  sort(ans.begin(),ans.end());
  if(ans[0]!=ans.back() || ans[0]==0) return 0;
  return 1;
}
int x[3],y[3];
int x2[3],y2[3];
int ix[3],iy[3];
int main(){
  int kase=0;
  for(;;){
	int ok=0;
	for(int i=0;i<3;i++){
	  scanf("%d%d",&x[i],&y[i]);
	  if(x[i]!=0  || y[i]!=0) ok=1;
	}
	if(!ok) break;
	for(int i=0;i<3;i++) scanf("%d%d",&x2[i],&y2[i]);
	int ans=0;
	//枚举旋转方式，注意，旋转180度等价于缩放（-1,-1），所以只枚举40个点而不是80个点
	for(int i=0;i<40;i++){
	  int rx,ry;
	  if(i<20){rx=10;ry=i-10;}
	  else{rx=30-i;ry=10;}
	  double len=sqrt(rx*rx+ry*ry);
	  double cosa=rx/len;
	  double sina=ry/len;
	  int ix[3],iy[3];
	  for(int j=0;j<3;j++){
		ix[j]=(int)floor(x[j]*cosa-y[j]*sina+0.5);
		iy[j]=(int)floor(x[j]*sina+y[j]*cosa+0.5);
	  }
	  int p[3]={0,1,2};
	  do{
		int cnt1=solve(ix[0],ix[1],ix[2],x2[p[0]],x2[p[1]],x2[p[2]]);
		int cnt2=solve(iy[0],iy[1],iy[2],y2[p[0]],y2[p[1]],y2[p[2]]);
		ans+=cnt1*cnt2;
	  }while(next_permutation(p,p+3));
	}
	printf("Case %d: ",++kase);
	if(ans==0) printf("no solution\n");
	else if(ans==1) printf("eqivalent solutions\n");
	else printf("inconsistent solutions\n");
  }
  return 0;
}
