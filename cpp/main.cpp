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
int al[110000][6];

int group[3700000];

bool vis[110000];

const int FWD=1;
const int FWD_SZ=pow(6,FWD)+0.5;

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
	
	for (int trials=0;trials<1;trials++){
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
				al[group[x]][y]=group[id[c.get_id()]];
				c.move(y^1);
			}
		}
		
		cout<<"precomputation done"<<endl;
		
		memset(vis,false,sizeof(vis));
		
		int g0=group[IDX-1];
		vis[g0]=true;
		vector<int> chain={g0};
		set<int> adj;
		
		rep(x,0,6) rep(y,0,6) adj.insert(al[al[g0][x]][y]);
		
		while (chain.size()!=102060 || !adj.count(chain.back())){
			while (true){
				bool deadend=true;
				
				vector<int> v(FWD_SZ);
				iota(v.begin(),v.end(),0);
				shuffle(v.begin(),v.end(),rng);
				
				int best=0;
				int nxt=-1;
				
				for (int x:v){
					int temp=x%6;
					
					int num=0;
					int curr=chain.back();
					rep(y,0,FWD){
						curr=al[curr][x%6]; x/=6;
						if (vis[curr]) break;
						num++;
					}
					
					if (num>best){
						best=num;
						nxt=temp;
						
						if (best==FWD) break;
					}
				}
				
				if (nxt!=-1){
					int temp=al[chain.back()][nxt];
					chain.push_back(temp);
					vis[temp]=true;
					deadend=false;
				}
				
				if (deadend) break;
			}
			
			vector<int> v;
			int b2=chain[chain.size()-2],b=chain[chain.size()-1];
			rep(x,0,6) if (al[b][x]!=b2) v.push_back(x);
			
			int cut=v[rng()%5];
			int idx=-1; rep(x,0,chain.size()) if (chain[x]==al[b][cut]) idx=x;
			reverse(chain.begin()+idx+1,chain.end());
		}
		
		cout<<"debug: "<<chain.size()<<endl;
		
		cout<<chain.front()<<" "<<group[IDX-1]<<endl;
		
		vector<int> ans;
		
		cube c=cube();
		rep(x,1,chain.size()){
			rep(y,0,6){
				c.move(y);
				if (group[id[c.get_id()]]==chain[x]){
					ans.push_back(y);
					break;
				}
				c.move(y^1);
			}
		}
		
		int pow_element[36][24];
		rep(x,0,24) pow_element[0][x]=x;
		rep(x,1,36) conv(pow_element[x-1],element,pow_element[x]);
		
		int best=1;
		
		rep(x,0,36) if (__gcd(x,36)==1){
			vector<int> temp;
			shortest_moves(states[id[c.get_id()]],pow_element[x],temp);
			if (temp.size()==2) best=x;
		}
		
		shortest_moves(states[id[c.get_id()]],pow_element[best],ans);
		
		cout<<"size of devils algorithm: "<<ans.size()<<endl;
		
		//dump moves to a textfile
		ofstream out("devil.txt");
		for (auto it:ans) out<<it;
		out.close();
	}
}
