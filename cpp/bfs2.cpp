#include <bits/stdc++.h>
#include "cube.h"
using namespace std;

#define ll long long

#define rep(x,s,e) for (int x=(s);x<(e);x++)

#define ii pair<int,int>
#define fi first
#define se second

map<ll,vector<int> > moves;
queue<cube> q;

int num_moves[20];

int main(){
	ll identity=cube().get_id();
	
	moves[identity]={};
	q.push(cube());
	
	while (!q.empty()){
		cube c=q.front();
		q.pop();
		
		rep(x,0,6){
			cube c2=c;
			
			if (x==0) c2.R();
			if (x==1) c2.Rp();
			if (x==2) c2.B();
			if (x==3) c2.Bp();
			if (x==4) c2.D();
			if (x==5) c2.Dp();
			
			if (!moves.count(c2.get_id())){
				moves[c2.get_id()]=moves[c.get_id()];
				moves[c2.get_id()].push_back(x);
				q.push(c2);
			}
		}
	}
	
	cout<<moves.size()<<endl;
	
	for (auto &it:moves){
		num_moves[it.se.size()]++;
	}
	
	rep(x,0,20) cout<<x<<" "<<num_moves[x]<<endl;
}
