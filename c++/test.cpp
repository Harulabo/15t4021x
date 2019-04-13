#include <iostream>
#include "_RANDOM.hpp"
#include "_CS.hpp"
#include "_EAX.hpp"
#include <vector>
#include <chrono>


using namespace std;

#define	MAX_ITERATION	100
#define MAX_POPULATION	20

void OneTry();
void ManiTry(int,int,int);

int main(int argc,char **argv){
	cout << " TEST " << endl;
	// シード値 固定
	//Random(123);

	// プログラム実行確認用
	if(argc == 1){
		EAX("TSP_sample/city11.txt");
		CityDisplay();
	}
	// ファイル指定　一回実行
	// [問題指定]
	else if(argc == 2){
		string fname = "TSP_sample/";
		EAX(fname+argv[1]);
		OneTry();
	}
	// 問題の最適解の結果出力
	// [問題指定　最適解ファイル]
	else if(argc == 3){
		cout << "opt" << endl;
		string fname = "TSP_sample/";
		EAX(fname+argv[1]);
		cout << "FILE CITY FIN\n";
		CityDisplay();
		EAX::Optimization(fname+argv[2]);
	}
	// [問題指定　実行回数　試行回数]
	else if(argc == 4){
		string fname = "TSP_sample/";
		EAX(fname+argv[1]);
		int n = stoi(argv[2]);
		int m = stoi(argv[3]);
		ManiTry(n,m,-1);
	}
	// 試行錯誤中
	// [問題指定　・・・]
	else if(argc == 5){
		string fname = "TSP_sample/";
		EAX(fname+argv[1]);
		//int opt = EAX::OptSolution(fname+argv[2]);
		int n = stoi(argv[3]);
		int m = stoi(argv[4]);
		int opt = stoi(argv[2]);
		ManiTry(n,m,opt);
	}
	// 想定外
	else{
		for(int i=0;i<argc;++i)
			cout << argv[i] << endl;
		cout << "OVER ARGV\n";
		exit(1);
	}
}

void OneTry(){
	CS cs(MAX_POPULATION);
//	CS cs(200);
	#ifdef TIME
		// Time Start
		auto start = chrono::system_clock::now();      // 計測スタート時刻を保存
	#endif
	cs.init_nest();
	for(int i=0;i<MAX_ITERATION;++i){
	//	cout << "==== " << i << " ====\n";
		cout << i << "\t : ";
		cs.iterator();
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

	cs.result();
	prtCycle(cs.best.cycle);//*/

}

void ManiTry(int n,int m,int opt){
	CS cs(MAX_POPULATION);
//	CS cs(1);
	cs.simulation(n,m,opt);
}