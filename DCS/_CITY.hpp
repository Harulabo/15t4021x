#pragma once
#include <iostream>
#include <vector>
#include <string>


using namespace std;

typedef vector<int>		vecint;
typedef vector<vecint>	vecdin;
typedef vector<double>	vecdub;
typedef vector<vecdub>	vecdd;

class Point{
public:
	int dis;
	int index;
	Point& operator=(const Point& node){
		dis = node.dis;
		index = node.index;

		return *this;
	}
	bool operator==(const Point& pt)const{
		return (dis == pt.dis && index == pt.index);
	}

	bool operator!=(const Point& pt) const{
		return (dis != pt.dis);
	}

	bool operator<(const Point& pt)const{
		return dis < pt.dis;
	}

	bool operator>(const Point& pt)const{
		return dis > pt.dis;
	}
	void prt(){
		cout << "Dis : " << dis << "\tindex : " << index << endl;
	}
};

class CITY{
public:
	int 	CitySize;	// 街の数
	vecdd	CityPos;	// 街の位置
	vecdin	CityDis;	// 街間の距離
	vector<vector<Point> >	CityDisSort;
	
	CITY(string);
	~CITY();

	void Distance();
	void SortDis();
	void printDis();
	void printSortDis();

	vecint optimization(string);
};
