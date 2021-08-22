#include <bits/stdc++.h>
#include "cuben.h"
using namespace std;

#define ll long long

#define rep(x,s,e) for (int x=(s);x<(e);x++)

#define i3 tuple<int,int,int>
#define g0(x) get<0>(x)
#define g1(x) get<1>(x)
#define g2(x) get<2>(x)

cuben::cuben(int layer){
	nl=layer;
	arr=new int**[6];
	
	rep(x,0,6){
		arr[x]=new int*[nl];
		rep(y,0,nl){
			arr[x][y]=new int[nl];
		}
	}
	
	rep(x,0,6) rep(y,0,nl) rep(z,0,nl) arr[x][y][z]=(x*nl*nl+y*nl+z);
}

void cuben::rotate(vector<i3> v){
	rep(x,0,v.size()-1){
		swap(arr[g0(v[x])][g1(v[x])][g2(v[x])],
				arr[g0(v[x+1])][g1(v[x+1])][g2(v[x+1])]);
	}
}

void cuben::U(int l){
	if (l==0){
		rep(x,0,(nl+1)/2) rep(y,0,nl/2){
			rotate({ {0,x,y}, {0,nl-1-y,x}, {0,nl-1-x,nl-1-y}, {0,y,nl-1-x} }); 
		}
	}
	if (l==nl-1){
		rep(x,0,(nl+1)/2) rep(y,0,nl/2){
			rotate({ {5,x,y}, {5,y,nl-1-x}, {5,nl-1-x,nl-1-y}, {5,nl-1-y,x} }); 
		}
	}
	
	rep(x,0,nl)
		rotate({ {1,l,x}, {2,l,x}, {3,l,x}, {4,l,x} });
}

void cuben::Up(int l){
	U(l);
	U(l);
	U(l);
}

void cuben::L(int l){
	if (l==0){
		rep(x,0,(nl+1)/2) rep(y,0,nl/2){
			rotate({ {1,x,y}, {1,nl-1-y,x}, {1,nl-1-x,nl-1-y}, {1,y,nl-1-x} }); 
		}
	}
	if (l==nl-1){
		rep(x,0,(nl+1)/2) rep(y,0,nl/2){
			rotate({ {3,x,y}, {3,y,nl-1-x}, {3,nl-1-x,nl-1-y}, {3,nl-1-y,x} }); 
		}
	}
	
	rep(x,0,nl)
		rotate({ {0,x,l}, {4,nl-1-x,nl-1-l}, {5,x,l}, {2,x,l} });
}

void cuben::Lp(int l){
	L(l);
	L(l);
	L(l);
}

void cuben::F(int l){
	if (l==0){
		rep(x,0,(nl+1)/2) rep(y,0,nl/2){
			rotate({ {2,x,y}, {2,nl-1-y,x}, {2,nl-1-x,nl-1-y}, {2,y,nl-1-x} }); 
		}
	}
	if (l==nl-1){
		rep(x,0,(nl+1)/2) rep(y,0,nl/2){
			rotate({ {4,x,y}, {4,y,nl-1-x}, {4,nl-1-x,nl-1-y}, {4,nl-1-y,x} }); 
		}
	}
	
	rep(x,0,nl)
		rotate({ {0,nl-1-l,x}, {1,nl-1-x,nl-1-l}, {5,l,nl-1-x}, {3,x,l} });
}

void cuben::Fp(int l){
	F(l);
	F(l);
	F(l);
}

void cuben::move(int dir,int layer){
	if (dir==0) U(layer);
	if (dir==1) Up(layer);
	if (dir==2) L(layer);
	if (dir==3) Lp(layer);
	if (dir==4) F(layer);
	if (dir==5) Fp(layer);
}

void cuben::print(){
	int fw=3;
	
	rep(x,0,nl){
		rep(y,0,nl) cout<<string(fw,' ')<<" ";
		rep(y,0,nl) cout<<setw(fw)<<arr[0][x][y]<<" ";
		cout<<endl;
	}
	rep(x,0,nl){
		rep(z,1,5) rep(y,0,nl) cout<<setw(fw)<<arr[z][x][y]<<" ";
		cout<<endl;
	}
	rep(x,0,nl){
		rep(y,0,nl) cout<<string(fw,' ')<<" ";
		rep(y,0,nl) cout<<setw(fw)<<arr[5][x][y]<<" ";
		cout<<endl;
	}
	cout<<endl;
}
