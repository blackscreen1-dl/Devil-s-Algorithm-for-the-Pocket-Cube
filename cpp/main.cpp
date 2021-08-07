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
int al[3700000][6];

int group[3700000];

bool vis[1100000];

const int FWD=3;
const int FWD_SZ=pow(6,FWD)+0.5;

const int NUM_ROUNDS=100;
const int SHOTS_TIME=10; //in seconds

void dfs(int i,vector<int> &ans){
	ans.push_back(i);
	vis[group[i]]=true;
	
	vector<int> v(FWD_SZ);
	iota(v.begin(),v.end(),0);
	shuffle(v.begin(),v.end(),rng);
	
	int best=0;
	int nxt=-1;
	
	for (int x:v){
		int temp=x%6;
		
		int num=0;
		int curr=i;
		rep(y,0,FWD){
			curr=al[curr][x%6]; x/=6;
			if (vis[group[curr]]) break;
			num++;
		}
		
		if (num>best){
			best=num;
			nxt=temp;
			
			if (best==FWD) break;
		}
	}
	
	if (nxt!=-1) dfs(al[i][nxt],ans);
}

void dfs2(int i,vector<int> &ans){
	vis[group[i]]=true;
	
	rep(x,0,6) if (!vis[group[al[i][x]]]){
		ans.push_back(x);
		dfs2(al[i][x],ans);
		ans.push_back(x^1);
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
	
	vector<int> meo;
	
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
		
		if (ord==36){
			meo.push_back(x);
		}
	}
	
	for (int trials=0;trials<1000;trials++){
		int element[24]; //element of meo
		int meo_idx=rng()%meo.size();
		
		rep(x,0,24) element[x]=states[meo[meo_idx]][x];
		
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
		
		
		//precompute adjacentcy list to make runtime faster
		rep(x,0,IDX){
			cube c=cube();
			
			for (auto ch:moves[x]){
				c.move(ch-'0');
			}
			
			rep(y,0,6){
				c.move(y);
				al[x][y]=id[c.get_id()];
				c.move(y^1);
			}
		}
		
		memset(vis,false,sizeof(vis));
		
		vis[IDX-1]=1;
		
		vector<int> unused(IDX-1);
		iota(unused.begin(),unused.end(),0);
		
		vector<vector<int> > chain;
		for (int rounds=0;rounds<NUM_ROUNDS;rounds++){
			vector<int> best;
			
			auto start = std::chrono::system_clock::now();
			while (((std::chrono::duration<double>)(std::chrono::system_clock::now()-start)).count()<SHOTS_TIME){
				int source=unused[rng()%unused.size()];
				vector<int> temp;
				dfs(source,temp);
				reverse(temp.begin(),temp.end());
				temp.pop_back();
				dfs(source,temp);
				
				for (auto it:temp) vis[group[it]]=false;
				
				if (temp.size()>best.size()) best=temp;
			}
			
			cout<<best.size()<<endl;
			for (auto it:best){
				vis[group[it]]=true;
			}
			
			vector<int> temp;
			for (auto it:unused) if (!vis[group[it]]) temp.push_back(it);
			
			swap(unused,temp);
			
			chain.push_back(best);
		}
		
		rep(x,0,chain.size()) swap(chain[x],chain[rng()%(x+1)]);
		
		vector<int> ans;
		
		dfs2(IDX-1,ans);
		shortest_moves(states[IDX-1],states[chain[0].front()],ans);
		rep(x,0,NUM_ROUNDS){
			rep(y,0,chain[x].size()-1){
				dfs2(chain[x][y],ans);
				
				int nxt=-1;
				rep(z,0,6) if (al[chain[x][y]][z]==chain[x][y+1]){
					nxt=z;
				}
				ans.push_back(nxt);
			}
			
			dfs2(chain[x].back(),ans);
			if (x!=NUM_ROUNDS-1) shortest_moves(states[chain[x].back()],states[chain[x+1].front()],ans);
			else shortest_moves(states[chain[x].back()],element,ans);
		}
		
		cout<<"size of devils algorithm: "<<ans.size()<<endl;
		
		//dump moves to a textfile
		ofstream out("../devil/"+to_string(ans.size())+".txt");
		for (auto it:ans) out<<it;
		out.close();
	}
}
