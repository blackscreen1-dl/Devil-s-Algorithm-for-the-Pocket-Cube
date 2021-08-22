#include <bits/stdc++.h>
#include "cuben.h"
using namespace std;

#define ll long long

#define rep(x,s,e) for (int x=(s);x<(e);x++)

#define ii pair<int,int>
#define fi first
#define se second

mt19937 rng(chrono::system_clock::now().time_since_epoch().count());

ll __lcm(ll i,ll j){
	return i*j/__gcd(i,j);
}

ll ord(vector<int> v){
	vector<bool> vis(v.size(),false);
	
	ll res=1;
	
	rep(x,0,v.size()) if (!vis[x]){
		int curr=x;
		int cnt=0;
		
		do{
			vis[curr]=true;
			
			cnt++;
			curr=v[curr];
		} while (curr!=x);
		res=__lcm(res,cnt);
	}
	
	return res;
}

int main(){
	int n=2;
	
	vector<int> v(3000,0);
	
	rep(x,0,100000){
		cuben cube=cuben(n);
		
		int temp=1000+rng()%1000;
		rep(y,0,temp){
			cube.move(rng()%6,0);
		}
		
		vector<int> pos;
		rep(x,0,6) rep(y,0,n) rep(z,0,n) pos.push_back(cube.arr[x][y][z]);
		v[ord(pos)]++;
		
		if (ord(pos)>2000){
			cout<<"epic "<<ord(pos)<<endl;
		}
	}
	
	//dump ord to a textfile
	ofstream out("../dump/ord2_100000.txt");
	rep(x,0,3000) out<<x<<" "<<v[x]<<endl;
	out.close();
}
