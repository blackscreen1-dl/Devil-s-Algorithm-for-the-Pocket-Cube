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
			c2.move(x);
			
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
	
	
	//dump everything into states.txt
	ofstream out;
	out.open("states.txt");
	for (auto state:moves){
		for (auto it:state.se) out<<it;
		out<<endl;
	}
	out.close();
}
