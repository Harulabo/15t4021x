#include "Nest.hpp"

class Nest;

class NestSet
{
public:
	NestSet(char *fileName);
	~NestSet();
	void alternate();
	void printResult();

	Dataset *dataset;
	Nest ** nest;

private:
	void sort(int lb,int ub);
};