#include <iostream>
#include <vector>
#include "_EAX.hpp"
#include "_CS.hpp"
#include "Time.hpp"
//#include "_CS.hpp"
//#include "_RANDOM.hpp"
//#include "matplotlibcpp.h"

using namespace std;

//typedef vector<int>				vecint;
//typedef vector<vector<int> >	vecdual;

//namespace plt = matplotlibcpp;
/*void prt(const vecint &);
void prt(const vecint &,char);
void prt(const vecdual &);//*/


int main(int argc , char ** argv){
	string fname = "TSP_sample/";
//	EAX(fname+argv[1]);
//	CityDisplay();
	EAX("TSP_sample/berlin52.tsp");
//	EAX::Debug_remake();
	EAX::Debug_crossover();
}

void opt_compare(){
	vecint A(EAX::CityNums);
	vecint B(EAX::CityNums);

	for(int i=0;i<EAX::CityNums;++i)A[i]=B[i]=i;

	Timer tm;

	EAX::opt2(A);
//	prt(A);
	//Display(A);

	cout << "duration = " << tm.elapsed() << "\n";

	Timer tm2;

	EAX::opt2_v2(B);
//	prt(B);
	//Display(B);

	cout << "duration = " << tm2.elapsed() << "\n";
}
/*
void prt(const vecint &A){
	cout << "[";
	for(auto t : A){
		cout << t << " ";
	}
	cout << "]\n";
}

void prt(const vecint &A,char B){
	cout << "[";
	for(auto t : A){
		cout << t << " ";
	}
	cout << "]"<<B;
}

void prt(const vecdual &A){
	cout << "[";
	for(auto t : A){
		prt(t,' ');
	}
	cout << "]\n";
}//*/