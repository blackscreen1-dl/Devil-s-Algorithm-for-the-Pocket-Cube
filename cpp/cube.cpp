#include <bits/stdc++.h>
#include "cube.h"
using namespace std;

#define ll long long

#define rep(x,s,e) for (int x=(s);x<(e);x++)

#define ii pair<int,int>
#define fi first
#define se second

cube::cube(){
	rep(x,0,6) rep(y,0,4){
		arr[x][y]=x*4+y;
	}
}

void cube::rotate(vector<ii> v){
	rep(x,0,v.size()-1){
		swap(arr[v[x].fi][v[x].se],arr[v[x+1].fi][v[x+1].se]);
	}
}

void cube::U(){
	rotate({ {0,3}, {0,2}, {0,1}, {0,0} });
	rotate({ {1,0}, {2,0}, {3,0}, {4,0} });
	rotate({ {1,1}, {2,1}, {3,1}, {4,1} });
}

void cube::Up(){
	rotate({ {0,0}, {0,1}, {0,2}, {0,3} });
	rotate({ {4,0}, {3,0}, {2,0}, {1,0} });
	rotate({ {4,1}, {3,1}, {2,1}, {1,1} });
}

void cube::L(){
	rotate({ {1,3}, {1,2}, {1,1}, {1,0} });
	rotate({ {4,2}, {5,0}, {2,0}, {0,0} });
	rotate({ {4,1}, {5,3}, {2,3}, {0,3} });
}

void cube::Lp(){
	rotate({ {1,0}, {1,1}, {1,2}, {1,3} });
	rotate({ {0,0}, {2,0}, {5,0}, {4,2} });
	rotate({ {0,3}, {2,3}, {5,3}, {4,1} });
}

void cube::F(){
	rotate({ {2,3}, {2,2}, {2,1}, {2,0} });
	rotate({ {1,2}, {5,1}, {3,0}, {0,3} });
	rotate({ {1,1}, {5,0}, {3,3}, {0,2} });
}

void cube::Fp(){
	rotate({ {2,0}, {2,1}, {2,2}, {2,3} });
	rotate({ {0,3}, {3,0}, {5,1}, {1,2} });
	rotate({ {0,2}, {3,3}, {5,0}, {1,1} });
}

void cube::move(int dir){
	if (dir==0) U();
	if (dir==1) Up();
	if (dir==2) L();
	if (dir==3) Lp();
	if (dir==4) F();
	if (dir==5) Fp();
}

ll cube::get_id(){
	ll res=0;
	ll curr=1;
	
	rep(x,0,6) rep(y,0,4){
		res+=curr*(arr[x][y]/4);
		curr*=6;
	}
	return res;
}
