#include <bits/stdc++.h>
#include "cube.h"
using namespace std;

#define ll long long

#define rep(x,s,e) for (int x=(s);x<(e);x++)

#define ii pair<int,int>
#define fi first
#define se second

mt19937 rng(chrono::system_clock::now().time_since_epoch().count());

string moves[3700000];
map<ll,int> id;

ll get_id(int *i){
	ll res=0;
	ll curr=1;
	rep(x,0,24){
		res+=curr*(i[x]/4);
		curr*=6;
	}
	return res;
}

void conv(int *i,int *j,int *res){
	int temp[24];
	
	rep(x,0,24) temp[x]=i[j[x]];
	rep(x,0,24) res[x]=temp[x];
}

void shortest_moves(int *i,int *j,vector<int> &ans){
	int inv_i[24],temp[24];
	
	rep(x,0,24) inv_i[i[x]]=x;
	conv(inv_i,j,temp);
	
	string s=moves[id[get_id(temp)]];
	for (auto it:s) ans.push_back(it-'0');
}

int states[3700000][24];

int group[3700000];

bool vis[1100000];

void dfs(cube c,vector<int> &ans){
	vis[group[id[c.get_id()]]]=true;
	
	rep(x,0,6){
		cube c2=c;
		c2.move(x);
		
		if (!vis[group[id[c2.get_id()]]]){
			ans.push_back(x);
			dfs(c2,ans);
			ans.push_back(x^1);
		}
	}
}

int main(){
	ifstream in("states.txt");
	
	//permutations
	int IDX=0;
	
	while (getline(in,moves[IDX])){
		cube c=cube();
		
		for (auto ch:moves[IDX]){
			c.move(ch-'0');
		}
		
		rep(x,0,6) rep(y,0,4) states[IDX][x*4+y]=c.arr[x][y];
		id[c.get_id()]=IDX;
		IDX++;
	}
	
	int best=1e9;
	int element[24]; //shortest with order 36
	
	int IDX2=0;
	rep(x,0,IDX){
		int curr[24];
		iota(curr,curr+24,0);
		
		int ord=0;
		while (true){
			conv(curr,states[x],curr);
			ord++;
			
			bool identity=true;
			rep(x,0,24) if (curr[x]!=x) identity=false;
			
			if (identity) break;
		}
		
		if (ord==36 && moves[x].size()<best){
			best=moves[x].size();
			rep(y,0,24) element[y]=states[x][y];
		}
	}
	
	cout<<best<<endl;
	
	int GIDX=0;
	memset(group,-1,sizeof(group));
	
	rep(x,0,IDX) if (group[x]==-1){
		int curr[24];
		rep(y,0,24) curr[y]=states[x][y];
		
		while (true){
			ll temp=get_id(curr);
			group[id[temp]]=GIDX;
			
			conv(element,curr,curr); //order matters here!
			
			bool identity=true;
			rep(y,0,24) if (curr[y]!=states[x][y]) identity=false;
			
			if (identity) break;
		}
		
		GIDX++;
	}
	
	cout<<GIDX<<" "<<GIDX*36<<endl;
	
	memset(vis,false,sizeof(vis));
	
	vector<int> ans;
	
	dfs(cube(),ans);
	
	cout<<ans.size()<<endl;
	
	int arr[24];
	rep(x,0,24) arr[x]=x;
	shortest_moves(arr,element,ans);
	
	cout<<ans.size()<<endl;
	
	//dump moves to a textfile
	ofstream out("devil.txt");
	for (auto it:ans) out<<it;
	out.close();
}
