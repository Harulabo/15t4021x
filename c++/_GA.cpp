#include "_GA.hpp"
#include "_RANDOM.hpp"

using namespace std;


GA::GA(int n){
	popsize = n;
}
GA::~GA(){
}

//==================================//
void GA::init(){					//
//----------------------------------//
	popu.resize(popsize);
	child.resize(popsize);
	for(int i = 0;i<popsize;++i){
		popu[i].cycle = sequence(EAX::CityNums);
		EAX::opt2(popu[i].cycle);
		//prt(popu[i].cycle);
	}
	best.fitness = (1<<20);
	evaluation();
}

void GA::iterator(){
//	selection();
	crossover();
	mutation();
	evaluation();
	analyze();
}

//=================================//
void GA::result(){
//---------------------------------//
	cout << "  ==== RESULT ====\n";
	cout << " BEST\t";
	best.prtfit();
}
//---------------------------------//

//==================================//
void GA::selection(){				//
// 面倒だからトーナメント
//----------------------------------//
	//cout << "selection"<<endl;
	const int Tsize = 2;
	vecint shaffle(popsize);
	for(int i=0;i<popsize;++i)shaffle[i]=i;
	
	for(int itr=0;itr<popsize;++itr){
		for(int i=0;i<Tsize;++i){
			swap(shaffle[i],shaffle[Random::radint(i,popsize-1)]);
		}
		auto minp = min(popu[shaffle[0]],popu[shaffle[1]]);
		for(int i=2;i<Tsize;++i)minp = min(minp,popu[shaffle[i]]);
		child[itr] = minp;
	}
}

//==================================//
void GA::crossover(){				//
//----------------------------------//
	//cout << "crossover" << endl;
	auto perm = sequence(popu.size());
	GENE tmp = popu[perm[0]];
	
	//tmp.prt();
	for(int itr = 0;itr < popu.size()-1;++itr){
		auto c = EAX::Crossover(popu[perm[itr]].cycle,popu[perm[itr+1]].cycle);
		popu[perm[itr]].cycle = minChild(c);
	}
	//tmp.prt();
	auto c = EAX::Crossover(popu[perm[popu.size()-1]].cycle,tmp.cycle);
	popu[perm[popu.size()-1]].cycle = minChild(c);
}

//==================================//
void GA::mutation(){				//
//----------------------------------//
	//cout << "mutation" << endl;
	const double Pa = 0.05;
	for(auto &p : popu){
		if(Random::real() < Pa){
			auto rpoint = Random::choice(EAX::CityNums,2);
			//printf("[%d:%d]\n",rpoint[0],rpoint[1]);
			swap(p.cycle[rpoint[0]],p.cycle[rpoint[1]]);
		}
	}
}

//============================================//

//==================================//
void GA::evaluation(){				//
//----------------------------------//
	for(auto & t : popu){
		t.fitness = EAX::Calculate(t.cycle);
	}
	auto t = *min_element(popu.begin(),popu.end());
	if(t.fitness < best.fitness){
		best = t;
	}
}

void GA::analyze(){
	int minl=(1<<20),maxl=-(1<<20);
	double suml=0.0;
	for(auto p : popu){
		suml += p.fitness;
		maxl = max(maxl,p.fitness);
		minl = min(minl,p.fitness);
	}
//	cout << "best : " << best.fitness << "\t";
//	cout << "min : " << minl << "\tmax : " << maxl;
//	cout << "\taverage : " << (suml/popsize) << endl;
	printf("best : %d\t",best.fitness);
	printf("min : %d\tmax : %d\tave : %lf\n",minl,maxl,(suml/popsize));
}

vecint GA::minChild(const vecdual &A){
	GENE b;
	b.cycle = A[0];
	b.fitness = EAX::Calculate(b.cycle);

	for(int i=1;i<A.size();++i){
		double fit = EAX::Calculate(A[i]);
		if(fit < b.fitness){
			b.fitness = fit;
			b.cycle   = A[i];
		}
	}
	return b.cycle;
}

//=================================//
//	ランダムな順列を生成
vecint sequence(int n){
	int maxl = n;
	vecint tmp(n);
	for(int i=0;i<n;++i)tmp[i]=i;
	for(int i=0;i<maxl;++i){
		int t = Random::radint(0,n-1);
		//cout << " t : " << t << "  n : " << n << endl;
		swap(tmp[t],tmp[n-1]);
		n--;
	}
	//prt(tmp);
	return tmp;
}