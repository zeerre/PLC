#include<bits/stdc++.h>

using namespace std;
struct Item{
  int QNum,Period,Time;
  bool operator<(const Item& a) const{
	if(Time!=a.Time) return Time>a.Time;
	return QNum>a.QNum;
  }
};
int main(){
  priority_queue<Item> pq;
  char s[20];
  for(Item i;scanf("%s",s) && s[0]!='#';pq.push(i));{
	scanf("%d%d", &i.QNum, &i.Period);
	i.Time=i.Period;
  }
  int K;
  scanf("%d",&K);
  while(K--){
	Item r=pq.top();
	pq.pop();
	printf("%d\n",r.QNum);
	r.Time+=r.Period;
	pq.push(r);
  }
  return 0;
}

  
