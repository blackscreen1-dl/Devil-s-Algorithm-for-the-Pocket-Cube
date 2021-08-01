#include <bits/stdc++.h>
#include "cube.h"
using namespace std;

#define ll long long

#define rep(x,s,e) for (int x=(s);x<(e);x++)

#define ii pair<int,int>
#define fi first
#define se second

mt19937 rng(chrono::system_clock::now().time_since_epoch().count());

int states[3700000][24];
int rotations[24][24];

void conv(int *i,int *j,int *res){
	int temp[24];
	
	rep(x,0,24) temp[x]=i[j[x]];
	rep(x,0,24) res[x]=temp[x];
}

int max_ord[4000000][24];

map<ll,int> id;
int group[3700000];

vector<ii> edges;

ll get_id(int *i){
	ll res=0;
	ll curr=1;
	rep(x,0,24){
		res+=curr*i[x];
		curr*=6;
	}
	return res;
}

int main(){
	ifstream in("states.txt");
	
	//permutations
	string state;
	int IDX=0;
	
	while (getline(in,state)){
		cube c=cube();
		
		for (auto ch:state){
			c.move(ch-'0');
		}
		
		rep(x,0,6) rep(y,0,4) states[IDX][x*4+y]=c.arr[x][y];
		id[get_id(states[IDX])]=IDX;
		IDX++;
	}
	
	//rotations
	cube c=cube();
	rep(i,0,4){
		c.U(),c.Dp();
		
		rep(j,0,6){
			rep(x,0,6) rep(y,0,4) rotations[i*6+j][x*4+y]=c.arr[x][y];
			
			if (j==0 || j==5) c.L(),c.Rp();
			if (j==1) c.U(),c.Dp();
			if (j==4) c.D(),c.Up();
			if (j==2 || j==3) c.B(),c.Fp();
		}
	}
	
	int IDX2=0;
	rep(x,0,IDX) rep(y,0,24){
		int element[24];
		conv(states[x],rotations[y],element);
		
		int curr[24];
		iota(curr,curr+24,0);
		
		int ord=0;
		while (true){
			conv(curr,element,curr);
			ord++;
			
			bool identity=true;
			rep(x,0,24) if (curr[x]!=x) identity=false;
			
			if (identity) break;
		}
		
		if (ord==45){
			rep(z,0,24) max_ord[IDX2][z]=element[z];
			IDX2++;
		}
	}
	
	int GIDX=0;
	
	rep(tries,0,1){
		int element[24];
		int idx=rng()%IDX2;
		rep(x,0,24) element[x]=max_ord[idx][x];
		
		memset(group,-1,sizeof(group));
		
		rep(x,0,IDX) if (group[x]==-1){
			int curr[24],curr2[24];
			rep(y,0,24) curr[y]=states[x][y];
			
			while (true){
				rep(y,0,24){
					conv(curr,rotations[y],curr2);
					ll temp=get_id(curr2);
					if (id.count(temp)){
						group[id[temp]]=GIDX;
						break;
					}
				}
				
				conv(curr,element,curr);
				
				bool identity=true;
				rep(y,0,24) if (curr[y]!=states[x][y]) identity=false;
				
				if (identity) break;
			}
			
			GIDX++;
		}
	}
	
	cout<<GIDX<<" "<<GIDX*45<<endl;
}
