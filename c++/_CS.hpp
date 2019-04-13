#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "_EAX.hpp"

using namespace std;

typedef vector<int> vecint;

class Cuckoo{
public:
	double fitness;
	vecint cycle;
	/*Cuckoo(double fit,vecint c){
		fitness = fit;
		cycle = c;
	}//*/
	Cuckoo& operator=(const Cuckoo& node){
		fitness = node.fitness;
		cycle = node.cycle;

		return *this;
	}
	bool operator==(const Cuckoo& pt)const{
		return (fitness == pt.fitness);// && index == pt.index);
	}

	bool operator!=(const Cuckoo& pt) const{
		return (fitness != pt.fitness);
	}

	bool operator<(const Cuckoo& pt)const{
		return fitness < pt.fitness;
	}

	bool operator>(const Cuckoo& pt)const{
		return fitness > pt.fitness;
	}
	void prt(){
		cout << "cycle : [";
		for(int t : cycle)
			cout << t << " ";
		cout << "]\n";
		cout << "Dis : " << fitness << endl;
	}
	void prtfit(){
		cout << "Dis : " << fitness;
	}
};


class CS{
public:
	//	メンバ変数
	Cuckoo best;
	vector<Cuckoo> Nest;

	int CityNum;		// 街の数
	int Num;			// 個体数（巣数）
	double Pa;			// 廃棄率

	double pa;

	vecint UpdateC;

	//	メンバ関数
	CS();
	CS(int num);
	~CS(){}

	void init_nest();
	void iterator();
	void result();

	void simulation(int,int,int);

	void get_cuckoo();
	void get_cuckoo2();
	void evaluation();
	void abandon();
	vecint greedy_init();

	void analyze();
	void file_out(const vecdual &);

	// For Debug
	Cuckoo minChild(const vecdual &);
	Cuckoo minChild2(const vecdual &);
	void Debug();

private:

};

vecint sequence(int n);
