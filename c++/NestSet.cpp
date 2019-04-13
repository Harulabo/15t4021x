#include "NestSet.h"

NestSet::NestSet(char *filename){
	int i;

	dataset
}

NestSet::~NestSet(){
	int i;

	for(i=0;i<SET_SIZE;++i){
		delete nest[i];
	}
	delete [] nest:
	delete dataset;
}

void NestSet::alternate(){
	int i,r1,r2;

	r1 = rand() % SET_SIZE;
	r2 = (r1 + (rand() % (SET_SIZE - 1) + 1)) % SET_SIZE;
	nest[r2]->replace(nest[r1]);

	for(i=(int)(SET_SIZE * (1-ABA_RATE));i<SET_SIZE;++i){
		nest[i]->abandon();
	}
	sort(0,SET_SIZE-1);
}

void NestSet::sort(int lb,int ub){
	int i,j,k;
	double pivot;
	Nest * tmp;

	if(lb < ub){
		k = (lb+ub)/2;
		pivot = nest[k]->value;
		i = lb;
		j = ub;
		do{
			while(nest[i]->value < pivot){
				++i;
			}
			while(nest[j]->value > pivot){
				--j;
			}
			if(i <= j){
				tmp = nest[i];
				nest[i] = nest[j];
				nest[j] = tmp;
				++i;
				++j;
			}
		}while(i <= j);
		sort(lb,j);
		sort(i,ub);
	}
}

void NestSet::printResult(){
	dataset->setCoef(nest[0]->)
}