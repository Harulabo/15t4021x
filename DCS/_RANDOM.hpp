#pragma once
#include <random>
#include <vector>

#ifndef INCLUDE_Random_h    //------
#define INCLUDE_Random_h
#define RANDOM_BIN          (mt()%2)
//	s以上t以下
#define RANDOM_RANGE(s,t)   ((mt()%(t-s+1)) + s)

static std::mt19937 mt((int)time(0));
static std::uniform_real_distribution<> randR(0, 1);

class Random{
public:
    Random();
	Random(int);
    static int bin();
    static int bin(double);
	static double real();
    static int quarter();
    static int radint(int,int);
    static std::vector<int> choice(int,int);
private:   
};

#endif  //-----------------------