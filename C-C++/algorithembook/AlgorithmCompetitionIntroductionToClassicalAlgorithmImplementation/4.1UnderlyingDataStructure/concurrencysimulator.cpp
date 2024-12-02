#include<bits/stdc++.h>

using namespace std;

#define _for(i,a,b) for(int i=a;i<(int)(b);++i)
const int NN=1000+4;
deque<int> readyQ;
queue<int> blockQ;
int N,Quantum,C[5],Var[26],IP[NN];
bool locked;
string Stats[NN];
void run(int pid){
  int q=Quantum;
  while(q>0){
	const string& p=Stats[IP[pid]];
	switch(p[2]){
	case '=':
	  Var[p[0]-'a']=isdigit(p[5])?(p[4]-'0') *10+p[5]-'0':p[4]-'0';
	  q-=C[0];
	  break;
	case 'i':
	  cout<<pid+1<<":"<< Var[p[6]-'a']<<endl;
	  q-=C[1];
	  break;
	case 'c':
	  if(locked){blockQ.push(pid);return;}
	  locked=true;
	  q-=C[2];
	  break;
	case 'l':
	  locked=false;
	  if(!blockQ.empty()){
		int pid2=blockQ.front();blockQ.pop();
		readyQ.push_front(pid2);
	  }
	  q-=C[3];
	  break;
	case 'd':
	  return;
	}
	IP[pid]++;
  }
  readyQ.push_back(pid);
}
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  int T;cin>>T;
  while(T--){
	cin>>N;
	_for(i,0,5) cin>>C[i];
	cin>>Quantum;
	fill_n(Var,26,0);
	int line=0;
	_for(i,0,N){
	  getline(cin,Stats[line++]);
	  IP[i]=line-1;
	  while(Stats[line-1][2]!='d') getline(cin,Stats[line++]);
	  readyQ.push_back(i);
	}
	locked=false;
	while(!readyQ.empty()){
	  int pid=readyQ.front();readyQ.pop_front();
	  run(pid);
	}
	if(T) cout<<endl;
  }
  return 0;
}

	  
	  
	  
	  
