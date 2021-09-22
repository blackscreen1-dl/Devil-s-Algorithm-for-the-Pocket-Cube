#include <bits/stdc++.h>
#include "cuben.h"
using namespace std;

#define ll long long

#define rep(x,s,e) for (int x=(s);x<(e);x++)

#define ii pair<int,int>
#define fi first
#define se second

mt19937 rng(chrono::system_clock::now().time_since_epoch().count());

int main(){
	cuben cube=cuben(4);
	
	rep(x,0,1000){
		cube.move(0,0);
		cube.move(4,0);
		
		bool can=true;
		rep(x,0,6) rep(y,0,4) rep(z,0,4){
			if (cube.arr[x][y][z]/(4*4)!=x) can=false;
		}
		
		bool can2=false;
		rep(x,0,6) rep(y,0,4) rep(z,0,4){
			if (cube.arr[x][y][z]!=x*4*4+y*4+z) can2=true;
		}
		
		if (can){
			cout<<"move: "<<x<<endl;
			cube.print();
		}
	}
}
