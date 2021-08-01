#include <bits/stdc++.h>
#include "cube.h"
using namespace std;

#define ll long long

#define rep(x,s,e) for (int x=(s);x<(e);x++)

#define ii pair<int,int>
#define fi first
#define se second

mt19937 rng(chrono::system_clock::now().time_since_epoch().count());

int main(){
	ifstream in("devil.txt");
	
	string st;
	in>>st;
	
	cout<<st.size()<<endl;
	
	cube c=cube();
	set<ll> s;
	
	rep(x,0,36){
		for (auto ch:st){
			s.insert(c.get_id());
			c.move(ch-'0');
		}
	}
	
	cout<<s.size()<<endl;
}
