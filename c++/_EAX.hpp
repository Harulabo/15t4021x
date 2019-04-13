#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "_CITY.hpp"


using namespace std;

typedef vector<int>				vecint;
typedef vector<vector<int> >	vecdual;


class EAX{
public:
	static int CityNums;		// 街の数
	static CITY city;

	EAX();
	EAX(string);
	~EAX();
	//static void TSP_Init();
	static vecdual Crossover(const vecint&,const vecint&);			// As Main
	static vecdual Crossover_R(const vecint&,const vecint&,double);

	static double Calculate(const vecint&);
	static void Optimization(string);
	static int OptSolution(string);
	
	static void opt2(vecint &);
	static void opt3(vecint &);
	static void opt2_v2(vecint &);

	static void Debug_remake();
	static void Debug_crossover();

private:
	static vecdual make_double_link(const vecint&);	// 双方向リスト作成
	static int check_ab(vecint &);			// AB-Cycleができるか判定する
	static vecdual AB_Cycle(const vecdual&,const vecint&);						// GABからAB-Cycleを作成する
	static vecdual E_Set(vecdual&,const vecdual&);							// 
	static vecdual E_Set2(const vecdual&,const vecdual&);							// 
	static vecdual E_SetRand(const vecdual&,const vecdual&);
	static vecdual E_SetPaRand(const vecdual&,const vecdual&,double);
	static vecdual make_single_link(const vecdual&);	// 単方向リスト作成
	static void add_index_list();					// 距離をソートする用
	static void remake(vecdual&);				// 複数の島を連結させる

	static int IndexOf(int,int,const vecint &);

};

void prt(const vecint &A);
void prt(const vecdual &A);
void prtCycle(const vecint &);
void prtCycle(const vecdual &);
void CityDisplay();
void Plot(const vecint &);
void Plot(const vecdual &);
