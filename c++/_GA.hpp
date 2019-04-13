#include <iostream>
#include <vector>
#include "_EAX.hpp"

using namespace std;


class GENE{
public:
	int fitness;
	vecint cycle;
	GENE& operator=(const GENE& node){
		fitness = node.fitness;
		cycle = node.cycle;

		return *this;
	}
	bool operator==(const GENE& pt)const{
		return (fitness == pt.fitness);// && index == pt.index);
	}

	bool operator!=(const GENE& pt) const{
		return (fitness != pt.fitness);
	}

	bool operator<(const GENE& pt)const{
		return fitness < pt.fitness;
	}

	bool operator>(const GENE& pt)const{
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
		cout << "Dis : " << fitness << endl;
	}
};


class GA{
public:
	vector<GENE> popu;
	vector<GENE> child;
	GENE best;

	int popsize;
	int chdsize;

	GA(int n = 10);
	~GA();

	void init();

	void iterator();
	void result();

	void selection();
	void crossover();
	void mutation();

	void evaluation();
	void analyze();
	vecint minChild(const vecdual &A);

private:
};

vecint sequence(int);