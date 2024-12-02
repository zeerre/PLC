#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn=10000+5;

struct Ant{
	int id;	//输入顺序
	int p;	//位置
	int d;	//朝向。-1：左；0：转身中；1：右
	bool operator<(const Ant& a) const{
		 return p<a.p;
	}
}before[maxn],after[maxn];
const char dirName[][10]={"L","Turning","R"};
int main(){
	int K;
	scanf("%d",&K);
	for(int kase=1;kase<=K;kase++){
		int L,T,n;
		printf("Case #%d:\n",kase);
		scanf("%d%d%d",&L,&T,&n);
		for(int i=0;i<n;i++){
			int p,d;
			char c;
			scanf("%d %c",&p,&c);
			d=(c=='L'? -1:1);
			before[i]=(Ant){i,p,d};
			after[i]=(Ant){0,p+T*d,d};
		}
		sort(before,fefore+n);
		for(int i=0;i<n;i++)
			order[before[i].id]=i;
		sort(after,after+n);
		for(int i=0;i<n-1;i++)
			if(after[i].p==after[i+1].p) after[i].d=after[i+1].d==0;
		for(int i=0;i<n;i++){
			int a=order[i];
			if(after[a].p<0 || after[a].p>L) printf("Fell off\n");
			else printf("%d %s\n",after[a].p,dirName[after[a].d+1]);
		}
		printf("\n");
	}
	return 0;
}