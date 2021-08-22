#include <bits/stdc++.h>
#include "cuben.h"
using namespace std;

#define ll long long

#define rep(x,s,e) for (int x=(s);x<(e);x++)

#define ii pair<int,int>
#define fi first
#define se second

mt19937 rng(chrono::system_clock::now().time_since_epoch().count());

int n=4;

int main(){
	cuben cube=cuben(n);
	
	cube.print();
	
	cube.U(0);
	cube.print();
	cube.Up(0);
	
	cube.U(n-1);
	cube.print();
	cube.Up(n-1);
	
	
	cube.L(0);
	cube.print();
	cube.Lp(0);
	
	cube.L(n-1);
	cube.print();
	cube.Lp(n-1);
	
	
	cube.F(0);
	cube.print();
	cube.Fp(0);
	
	cube.F(n-1);
	cube.print();
	cube.Fp(n-1);
}
