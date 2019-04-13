#include "_RANDOM.hpp"
#include <iostream>

using namespace std;

Random::Random(){
    mt = mt19937((int)time(0));
}
Random::Random(int seed){
	mt = mt19937(seed);
}

int Random::bin(){
    return RANDOM_BIN;
}
int Random::bin(double p){
    return randR(mt) > p;
}
int Random::quarter(){
    return RANDOM_BIN|RANDOM_BIN;
}
int Random::radint(int s,int t){
    return RANDOM_RANGE(s,t);
}
double Random::real(){
	return randR(mt);
}
vector<int> Random::choice(int size,int k){
    vector<int> tmp(size);
    for(int i=0;i<size;++i)
        tmp[i]=i;
    for(int i=0;i<k;++i){
        int t = radint(i,size-1);
        swap(tmp[i],tmp[t]);
    }
    return tmp;
}