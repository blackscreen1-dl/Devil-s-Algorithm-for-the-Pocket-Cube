#include <bits/stdc++.h>
using namespace std;

#define ll long long

#define rep(x,s,e) for (int x=(s);x<(e);x++)

#define ii pair<int,int>
#define fi first
#define se second

struct cube{
	int arr[6][4];
	
	cube();
	
	void rotate(vector<ii> v);
	void U();
	void Up();
	void L();
	void Lp();
	void F();
	void Fp();
	void move(int);
	ll get_id();
};
