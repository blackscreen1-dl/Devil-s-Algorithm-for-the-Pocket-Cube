#include <bits/stdc++.h>
using namespace std;

#define ll long long

#define rep(x,s,e) for (int x=(s);x<(e);x++)

#define i3 tuple<int,int,int>
#define g0(x) get<0>(x)
#define g1(x) get<1>(x)
#define g2(x) get<2>(x)

struct cuben{
	int ***arr;
	int nl;
	
	cuben(int);
	
	void rotate(vector<i3>);
	void U(int);
	void Up(int);
	void L(int);
	void Lp(int);
	void F(int);
	void Fp(int);
	void move(int,int);
	void print();
};
