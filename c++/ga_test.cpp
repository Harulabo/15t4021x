#include <iostream>
#include "_RANDOM.hpp"
#include "_GA.hpp"
#include "_EAX.hpp"
#include <vector>
#include <chrono>


using namespace std;

#define	MAX_ITERATION	100
#define MAX_POPULATION	300

void OneTry();

int main(int argc,char **argv){
	cout << " TEST " << endl;
	// シード値 固定
	//Random(123);

	// プログラム実行確認用
	if(argc == 1){
		EAX("TSP_sample/city11.txt");
	}
	// ファイル指定　一回実行
	// [問題指定]
	else if(argc == 2){
		string fname = "TSP_sample/";
		EAX(fname+argv[1]);
		OneTry();
	}
}

void OneTry(){
	GA ga(MAX_POPULATION);
	#ifdef TIME
		// Time Start
		auto start = chrono::system_clock::now();      // 計測スタート時刻を保存
	#endif
	ga.init();
	for(int i=0;i<MAX_ITERATION;++i){
	//	cout << "==== " << i << " ====\n";
		cout << i << "\t : ";
		ga.iterator();
	}
	#ifdef TIME
		// Time End
		auto end = chrono::system_clock::now();      // 計測スタート時刻を保存
		auto dur = end - start;        // 要した時間を計算
		auto msec = chrono::duration_cast<chrono::milliseconds>(dur).count();
		// 要した時間をミリ秒（1/1000秒）に変換して表示
		cout << " Time " << endl;
		cout << msec << " milli sec \n";
	#endif

	ga.result();
	prtCycle(ga.best.cycle);//*/
}
