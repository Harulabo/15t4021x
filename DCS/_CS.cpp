#include "_CS.hpp"
#include "_RANDOM.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

typedef long long ll;

CS::CS(){
	cout << " demonstration\n";
	CityNum = EAX::CityNums;
	Num = 10;
	Pa = 0.1;
}
CS::CS(int num){
	cout << "\n\n Cuckoo Search\n";
	CityNum = EAX::CityNums;
	//cout << CityNum << endl;
	Num = num;
	Pa = 0.2;
	pa = 0.5;
	UpdateC.resize(100);
	for(int i=0;i<100;++i)UpdateC[i]=0;
}

//=================================//
void CS::init_nest(){
//---------------------------------//
	Nest.resize(Num);
	pa = 0.5;
	for(int i=0;i<Num;++i){
		Nest[i].cycle = sequence(CityNum);
	//	Nest[i].cycle = greedy_init();
	//	EAX::opt2(Nest[i].cycle);
		EAX::opt2_v2(Nest[i].cycle);
		Nest[i].fitness = EAX::Calculate(Nest[i].cycle);
	}
	best.fitness = (1<<20);
	evaluation();
}

//=================================//
void CS::iterator(){
//---------------------------------//
	get_cuckoo();
	abandon();
	evaluation();//*/


	/*get_cuckoo2();
	evaluation();//*/

	//cout << " BEST \n";
	//best.prt();
	analyze();
}

//=================================//
void CS::result(){
//---------------------------------//
	cout << "  ==== RESULT ====\n";
	cout << "Prameta\n";cout << "Num : " << Num << "\t";
	cout << "Pa : " << Pa << endl;
	cout << " BEST\t";
//	best.prt();
	best.prtfit();
//	Plot(UpdateC);
}
//---------------------------------//

//=================================//
void CS::simulation(int Traials,int MaxItr,int opt){
//---------------------------------//
	vecint fitvec(Traials,0);
	double timesum = 0;
	int OptCnt = 0;
	int OptNearCnt = 0;
	vecdual Data(Traials,vecint(MaxItr,0));
	double diff = pa / ((double)MaxItr*0.6);
	//cout << "diff : " << diff << endl;

	for(int cnt=0;cnt < Traials;++cnt){
// =====// 計測開始 ==============================//
		auto start = chrono::system_clock::now();
		// 初期化
		init_nest();
		//Debug();
		// 探索
		for(int itr=0;itr < MaxItr;++itr){
		//	ParaUpdate(itr,MaxItr);
			get_cuckoo();
			abandon();//*/
			evaluation();
			Data[cnt][itr] = best.fitness;
			// for get_cuckoo2 
			//pa -= diff;
			//cout << "pa : " << pa << endl;
		}
		//Debug();
		auto end = chrono::system_clock::now();      // 計測スタート時刻を保存
		auto dur = end - start;        // 要した時間を計算
		auto msec = chrono::duration_cast<chrono::milliseconds>(dur).count();
// =====// 計測終了 ==============================//
		// 結果の表示
		cout << " " << cnt << " : ";
		result();
		cout << "\tTime \t";
		cout << msec << " milli sec \n";
		fitvec[cnt] = best.fitness;
		timesum += (double)msec/Traials;
		cout << "PD : " << ((double)(best.fitness-opt)/opt)*100 << endl;
		if(best.fitness == opt) OptCnt++;
		if(0.01 > ((double)(best.fitness-opt)/opt)) OptNearCnt++;
	}
	cout << "\n---- FINISH ----\n";
	double avefit = ((double)accumulate(fitvec.begin(), fitvec.end(), 0) / Traials);
	int minfit = *min_element(fitvec.begin(), fitvec.end());
	int maxfit = *max_element(fitvec.begin(), fitvec.end());
	double SD = 0.0;
	for(auto t : fitvec)SD += pow((double)t-avefit,2);
	SD = (double)sqrt(SD)/(Traials-1);

	cout << Traials << " trys\n";
	cout << "Prameta\n";cout << "Num : " << Num << "\t";
	cout << "Pa : " << Pa << endl;
	cout << "Iteration : " << MaxItr << endl;
	cout << endl << "RESULT" << endl;
	cout << "Ave : " << avefit << endl;
	cout << "min : " << minfit;
	cout << "\tmax : " << maxfit << endl;
	cout << "Ave Time : " << timesum << endl;
	cout << "SD    : " << SD << endl << endl;
	if(opt != -1){
		cout << "opt : " << opt << endl;
		cout << "Opt solutions : " << OptCnt << " / " << OptNearCnt << " / " << Traials << " [cnt]\n";
		cout << "PD    : " << ( (double)(minfit - opt)/opt*100 ) << "[\%]" << endl;
		cout << "PDave : " << ( (double)(avefit - opt)/opt*100 ) << "[\%]" << endl;	
	}
	file_out(Data);
	Plot(Data);
}
//---------------------------------//


//============================================//
//============================================//

//=================================//
void CS::get_cuckoo(){
//---------------------------------//
//	auto pbest = *min_element(Nest.begin(),Nest.end());
	for(int i=0;i<Nest.size();++i){
		// Best 1AB
		auto t = EAX::Crossover(best.cycle,Nest[i].cycle);
		// best 0.1AB
		//auto t = EAX::Crossover_R(best.cycle,Nest[i].cycle,0.9);
		// Rand AB
		//auto t = EAX::Crossover_R(Nest[i].cycle,best.cycle);
		// Rand 0.1 AB
		//auto t = EAX::Crossover_R(Nest[i].cycle,best.cycle);
		auto chd = minChild2(t);
		//if(Nest[i].fitness > chd.fitness){
			Nest[i].fitness = chd.fitness;
			Nest[i].cycle = chd.cycle;
		//}
	}
	// 更新
	for(int i=0;i<Nest.size();++i)
		best = min(best,Nest[i]);
}
//=================================//
void CS::get_cuckoo2(){
// AB-Cycleの割合を減少させる
//---------------------------------//
	for(int i=0;i<Nest.size();++i){
		vecdual t;
		if(pa < 0.01){
			// Best 1AB
			t = EAX::Crossover(best.cycle,Nest[i].cycle);
		}else{
			// best 0.1AB
			t = EAX::Crossover_R(best.cycle,Nest[i].cycle,pa);
		}
		auto chd = minChild2(t);
		//if(Nest[i].fitness > chd.fitness){
			Nest[i].fitness = chd.fitness;
			Nest[i].cycle = chd.cycle;
		//}
	}
	// 更新
	for(int i=0;i<Nest.size();++i)
		best = min(best,Nest[i]);
}

//=================================//
void CS::evaluation(){
//---------------------------------//
//	cout << " evaluation\n";
	for(auto & t : Nest){
		t.fitness = EAX::Calculate(t.cycle);
	}
	auto t = *min_element(Nest.begin(),Nest.end());
	if(t.fitness < best.fitness){
		best = t;
	}
}

//=================================//
void CS::abandon(){
//---------------------------------//
//	cout << "\n abandon \n";
	for(auto &p : Nest){
	//	if(Random::real() < Pa){
		//	prt(p.cycle);
			vecint chgp = sequence(EAX::CityNums);
		//	prt(chgp);
			int chgnum = (int)EAX::CityNums*Pa;
		//	cout << "Pa : " << Pa << "\tnum : " << chgnum << endl;
			vecint indent = sequence(chgnum);
		//	prt(indent);
			for(int i=0;i<chgnum;++i){
		//		cout << p.cycle[chgp[indent[i]]] << " ";
				indent[i] = p.cycle[chgp[indent[i]]];
			}
		//	cout << endl;
		//	prt(indent);
			for(int i=0;i<chgnum;++i){
				p.cycle[chgp[i]] = indent[i];
			}
		//	cout << "\nAFTER\n";
		//	prt(p.cycle);

		//	cout << endl;
			EAX::opt2_v2(p.cycle);
	//	}
	}
}
//---------------------------------//


//=================================//
vecint CS::greedy_init(){
//---------------------------------//
	int start = Random::radint(0,CityNum-1);
	vecint tour(CityNum,0);
	tour[0] = start;
	vector<bool> flag(CityNum,0);
	flag[start] = 1;

	for(int i=1;i<CityNum;++i){
		auto Dis = EAX::city.CityDisSort[tour[i-1]];
		for(int j=1;j<CityNum;++j){
			if(flag[Dis[j].index] == 0){
				tour[i] = Dis[j].index;
				flag[Dis[j].index] = 1;
				break;
			}
		}
	}

	return tour;
}

//=================================//
void CS::analyze(){
//---------------------------------//
	double minl=(1<<20),maxl=-(1<<20),suml=0.0;
	for(auto p : Nest){
		suml += p.fitness;
		maxl = max(maxl,p.fitness);
		minl = min(minl,p.fitness);
	}
	cout << "best : " << best.fitness << "\t";
	cout << "min : " << minl << "\tmax : " << maxl;
	cout << "\taverage : " << (suml/Num) << endl;

}

// ファイルにデータ更新をファイルに記録する
void CS::file_out(const vecdual &A){
	string filename;
	ofstream ofs("result.csv");
	if(!ofs){
		cout << "File Output ERROR\n";
		exit(1);
	}
	ofs << "CityNum,"<<CityNum<<endl;
	ofs << "Traials,"<<A.size()<<endl;
	ofs << "Iteration,"<<A[0].size()<<endl;
	ofs << "n,"<<Num<<endl;
	ofs << "Pa,"<<Pa<<endl;

	for(int i=0;i<A.size();++i){
		ofs << A[i][0];
		for(int j=1;j<A[i].size();++j){
			ofs << "," << A[i][j];
		}
		ofs << endl;
	}
}


//=================================//
//	生成された子から最良解を選ぶ
Cuckoo CS::minChild(const vecdual &A){
	Cuckoo b;
	b.cycle = A[0];
	b.fitness = EAX::Calculate(b.cycle);

	for(int i=1;i<A.size();++i){
		double fit = EAX::Calculate(A[i]);
		if(fit < b.fitness){
			b.fitness = fit;
			b.cycle   = A[i];
		}
	}
	return b;
}

Cuckoo CS::minChild2(const vecdual &A){
	vecint fits(A.size());
	for(int i=0;i<A.size();++i)
		fits[i] = EAX::Calculate(A[i]);

	int minl = distance(fits.begin(),min_element(fits.begin(),fits.end()));

	Cuckoo b;
	b.fitness = fits[minl];b.cycle = A[minl];
	int indexU = (int)(100*minl/A.size());
//	cout <<"["<<indexU<<"]";
	UpdateC[indexU]++;

	return b;
}


void CS::Debug(){
	for(auto t : Nest){
		t.prt();
	}
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
