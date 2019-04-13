#include "_CITY.hpp"
#include <fstream>
#include <cmath>

using namespace std;

// 指定されたファイルから街情報を読み取る
CITY::CITY(string filename){
	ifstream ifs(filename);
	if(ifs.fail()){
		cout << filename << endl;
		cout << "File Read Fialed" << endl;
		exit(-1);
	}
	// 読み飛ばし
	string buff;
	while(ifs >> buff){
		if(buff == "NODE_COORD_SECTION")
			break;
	}
	// 街情報を読み取る
	string number;
	double a,b;
	while(ifs >> number >> a >> b){
		if(number == "EOF")break;
		//cout << number << " " << a << " " << b << endl;
		CityPos.push_back({a,b});
	}
	CitySize = CityPos.size();
	//Distance();
	//SortDis();
}
CITY::~CITY(){
}

// 街間の距離を計算する
void CITY::Distance(){
	#ifdef DEBUG
		cout << "CITY DISTANCE\n";
	#endif
	for(int i=0;i<CityPos.size();++i){
		//cout << i << ".";
		vecint dis(CityPos.size());
	//	vecdub dis(CityPos.size());
		for(int j=0;j<CityPos.size();++j){
			dis[j] = round(sqrt( pow(CityPos[i][0]-CityPos[j][0],2) + pow(CityPos[i][1]-CityPos[j][1],2) ) );
		//	cout << "[" << dis[j] << "]";
		}
		CityDis.push_back(dis);
	//}
	//	cout << endl;
	}
}
// 街の距離のをソートする
void CITY::SortDis(){
	#ifdef DEBUG
		cout << "CITY DIS SORT\n";
	#endif
	for(auto dis : CityDis){
		vector<Point> sortDis(CityDis.size());
		for(int i=0;i<dis.size();++i){
			sortDis[i].dis = dis[i];
			sortDis[i].index = i;
		}
		sort(sortDis.begin(),sortDis.end());
		CityDisSort.push_back(sortDis);
	}
}


void CITY::printDis(){
	for(int i=0;i<CityPos.size();++i){
		cout << i << " : [";
		for(auto d : CityDis[i]){
			printf("%7d ",d);
		}
		cout << "]\n";
	}
}

void CITY::printSortDis(){
	for(int i=0;i<CityDisSort.size();++i){
		cout << i << " : ";
		for(auto d : CityDisSort[i]){
			//cout << "[" << d.dis << ":" << d.index << "]";
			printf("[%7d:%d]",d.dis,d.index);
		}
		cout << "]\n";
	}
}

// 最適解のファイルを読み取る
vecint CITY::optimization(string filename){
	ifstream ifs(filename);
	if(ifs.fail()){
		cout << filename << endl;
		cout << "File Read Fialed" << endl;
		exit(-1);
	}
	// 読み飛ばす
	string buff;
	while(ifs >> buff){
		if(buff == "TOUR_SECTION")
			break;
	}
	// 最適解のツアーを読み取る
	int number;
	vecint tour(CitySize,-1);
	//cout << "file opt input\n";
	cout << "CitySize : " << CitySize << endl;
	for(int i=0;ifs >> number;++i){
	//	cout << i << " " << number << endl;
		if(number == -1) break;
		tour[i] = number-1;
	}
	//cout << "file opt input fin\n";
	if(tour[CitySize-1] == -1) cout << "FILE OPT ERROR\n";

	return tour;
}

