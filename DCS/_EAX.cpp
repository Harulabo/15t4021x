//===================================================//
//	枝組み立て交叉(EAX)
//	制作日：2018.10.3
//	備考：
//===================================================//
#include "_EAX.hpp"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include "_RANDOM.hpp"
#include "matplotlibcpp.h"

using namespace std;

namespace plt = matplotlibcpp;

#define PB		push_back
#define RAND_01		((double)rand() / RAND_MAX)
#define RAND_N		(sqrt(-2.0 * log(RAND_01) * cos(2*PI*RAND_01)))
#define RAND_BIN	()

#define D(n,m)  city.CityDis[A[(n)%CityNums]][A[(m)%CityNums]]

//------------------------------//
#define MAX_SEARCH		10
#define MAX_INT			(1<<30)

#define MAX_CHILD		50
#define P_ABC			0.8
//------------------------------//

CITY EAX::city = CITY("TSP_sample/city11.txt");
int EAX::CityNums;

//===================================//
EAX::EAX(){
//-----------------------------------//
	//city = CITY("TSP_sample/city11.txt");
	CityNums = city.CitySize;
	city.Distance();
	city.printDis();
	city.SortDis();
	city.printSortDis();
}
EAX::EAX(string filename){
	city = CITY(filename);
	CityNums = city.CitySize;
	city.Distance();
//	city.printDis();
	city.SortDis();
//	city.printSortDis();
}
EAX::~EAX(){
}

//====================================//
// 	サイクルの評価値の計算
double EAX::Calculate(const vecint &A){
//------------------------------------//
	if(CityNums != A.size()){
		cout << "Calclate [Cycle Number Error]\n";
		cout << "size : " << A.size() << endl;
		prt(A);
		cout << endl;
	}
//	cout << "\nTour Len : " << A.size() << " " << CityNums << endl;
	//prt(A);
	double sum = .0;
	for(int i = 0;i<CityNums-1;++i){
		sum += city.CityDis[A[i]][A[i+1]];
	//	cout << i << " " << A[i] << "->" << A[i+1] << "  :   " << city.CityDis[A[i]][A[i+1]] << ":" << sum << endl;
	}
	sum += city.CityDis[A[0]][A[CityNums-1]];
//	cout << A[0] << "->" << A[CityNums-1] << "  :   " << city.CityDis[A[0]][A[CityNums-1]] << ":" << sum << endl;

	return sum;
}

//====================================//
// 	最適解の出力
void EAX::Optimization(string filename){
//------------------------------------//
	cout << filename << endl;
	auto tour = city.optimization(filename);
	cout << "min distance : ";
	cout << Calculate(tour) << endl;
	prtCycle(tour);
}
//====================================//
// 	最適解の評価値の計算
int EAX::OptSolution(string filename){
//------------------------------------//
	auto tour = city.optimization(filename);
	return Calculate(tour);
}

//===================================//
//	枝組み立て交叉(EAX-1AB)
vecdual EAX::Crossover(const vecint &A,const vecint&Best){
//	A	:	個体Aのツアー
//	Best:	最良解のツアー
//-----------------------------------//
	if(A.size() != Best.size())
		cout << " Cross Size ERROR\n";
	auto LinkA = make_double_link(A);
	auto abc = AB_Cycle(LinkA,Best);
//	auto abc2 = AB_Cycle(LinkA,Best);
//	copy(abc2.begin(),abc2.end(),back_inserter(abc));
	
	// いらないAB-Cycleを削除する
	for(auto itr = abc.begin();itr != abc.end();){
		if(itr->size() == 3) itr = abc.erase(itr);
		else ++itr;
	}

	// AB-Cycle が存在しないとき
	if(abc.size()==0)return {A};

	vecdual Child;

	for(auto eset : abc){
	//	auto single = E_Set(LinkA,{eset});//*/ 
		auto single = E_Set2(LinkA,{eset});
	/*	for(int i=0;i<50;++i){
		auto single = E_SetRand(LinkA,abc);//*/

		remake(single);
		auto child = make_single_link(single);
	//	prt(child);
		// for DEBUG
		if(CityNums != child[0].size()){
			cout << "Child [Cycle Number Error]\n";
			cout << "Before\n";
			//prt(beforeC);
			cout << endl;
			cout << "cycles num : " << child.size() << endl;
			for(auto tmp : child)cout << " num : " << tmp.size() << endl;

			cout << "ab-cycle : ";cout << endl;
			//	prt(single);
			//	cout << "child    : ";prt(child[0]);
		
			prtCycle(child);
			exit(1);
		}
		Child.push_back(child[0]);
	}

	return Child;
}

// EAX-RAND
vecdual EAX::Crossover_R(const vecint &A,const vecint &Best,double pa){
	if(A.size() != Best.size())
		cout << " Cross Size ERROR\n";
	auto LinkA = make_double_link(A);
	auto abc = AB_Cycle(LinkA,Best);
//	auto abc2 = AB_Cycle(LinkA,Best);
//	copy(abc2.begin(),abc2.end(),back_inserter(abc));
	
	// いらないAB-Cycleを削除する
	for(auto itr = abc.begin();itr != abc.end();){
		if(itr->size() == 3) itr = abc.erase(itr);
		else ++itr;
	}

	// AB-Cycle が存在しないとき
	if(abc.size()==0)return {A};

	vecdual Child;

	for(int i=0;i<MAX_CHILD;++i){
		// 確率で選択する
		auto single = E_SetPaRand(LinkA,abc,pa);

		remake(single);
		auto child = make_single_link(single);
		// for DEBUG
		if(CityNums != child[0].size()){
			cout << "Child [Cycle Number Error]\n";
			cout << "Before\n";
			//prt(beforeC);
			cout << endl;
			cout << "cycles num : " << child.size() << endl;
			for(auto tmp : child)cout << " num : " << tmp.size() << endl;

			cout << "ab-cycle : ";cout << endl;
			//	prt(single);
			//	cout << "child    : ";prt(child[0]);
		
			prtCycle(child);
			exit(1);
		}
		Child.push_back(child[0]);
	}
	return Child;
}

//===================================//
vecdual EAX::make_double_link(const vecint & A){
//-----------------------------------//
	#ifdef DEBUG
		cout << "  MAKE DOUBLE " << endl;
	#endif
	if(CityNums != A.size()){
		cout << "Make Double [Cycle Number Error]\n";
	}
	vecdual Link{A.size(),{0,0} };
	for(int i=0;i<A.size();++i){
		Link[A[i]][0] = A[(i+A.size()-1)%A.size()];
		Link[A[i]][1] = A[(i+1)%A.size()];
	}

	return Link;
}
//===================================//
int EAX::check_ab(vecint &list){
//	list	:	
//	s		: 	
//-----------------------------------//
	int count = 0;
	int s = list.size()-1;
	for(int i=s-1;i>=0;--i){
		count++;
		if(list[i] == list[s] && count%2 == 0)
			return i;
	}
	return -1;
}
//===================================//
vecdual EAX::AB_Cycle(const vecdual & CLinkA,const vecint &Best){
//	CLinkA	:	one cycle
//	Best	:	best cycle
//-----------------------------------//
	#ifdef DEBUG
	cout << " AB_Cycle make" << endl;
	#endif 
	unsigned int Length = Best.size();
	vecdual LinkA{Length,{0,0} };
	vecdual LinkB = make_double_link(Best);

	vecdual AB_C;	// AB_Cycle
	vecint restNum(Length,2);
	int restcnt = Length;
	int s=0;
	bool finish = false;
	int edgecnt = 2 * Length;
	
	while(restcnt){
		vecint P;	// 探索点
		int index = Random::radint(0,restcnt-1);
	// パターンA	
		int e;
		int Ve;
		for(int i=0;i<Length;++i){
			if(restNum[i]==0)continue;
			if(index <= 0){Ve = i;break;}
			index--;
		}
	// パターンB	愚直なやり方	
		P.PB(Ve);
		while(true){
			if(s % 2 == 0){
				int t = Random::bin();
				e = CLinkA[Ve][t];
				if(LinkA[Ve][t] == -1){
					t = (++t)%2;
					e = CLinkA[Ve][t];
				}
				LinkA[Ve][t] = -1;
				if(e == -1){cout << "e ERROR\n";exit(1);}
				LinkA[e][(t+1)%2] = -1;
				restNum[Ve]--;restNum[e]--;
				if(restNum[Ve]==0)restcnt--;
				if(restNum[e]==0)restcnt--;
			}
			else{
				int t = Random::bin();
				e = LinkB[Ve][t];
				if(e == -1){
					t = (++t)%2;
					e = LinkB[Ve][t];
				}
				LinkB[Ve][t] = -1;
				if(e == -1){cout << "e ERROR\n";exit(1);}
				LinkB[e][(t+1)%2] = -1;
			}
			Ve = e;
			s++;
			P.PB(Ve);
			int abt = check_ab(P);
			if(abt >= 0){
				vecint C;
				if (s%2 == 0){
					copy(P.begin()+abt,P.begin()+s+1,back_inserter(C));
				}else{
					copy(P.begin()+abt+1,P.begin()+s+1,back_inserter(C));
					C.PB(P[abt+1]);
				}//*/
				AB_C.PB(C);
				for(int i=0;i<(s-abt);++i)
					P.pop_back();
				s = abt;
			}
			if(s<=0) break;
		}//end while
	}//end while
	return AB_C;
}
//===================================//
//	双方向リストAからAB_Cycleの差分をとる
vecdual EAX::E_Set(vecdual &A,const vecdual&AB){
//	A	:	親個体A
//	AB	:	AB_Cycle(複数可)
//-----------------------------------//
//	前提としてAB_CycleはAの辺から始まる
	/*cout << "================" << endl;
	cout << " E_SET " << endl;
	cout << "A : \t";
	prt(A);
	cout << "AB: \t";
	prt(AB);//*/

	for(const auto cycle : AB){
		// DELETE	親Aの辺を削除
		for(int j=1;j<cycle.size();j+=2){
			//cout << " j : " << j << " " << cycle[j-1] << " " << cycle[j] << endl;
			//cout << "\t" << A[cycle[j-1]][0] << " " << A[cycle[j-1]][1] << endl;
			//cout << "\t" << A[cycle[j]][0] << " " << A[cycle[j]][1] << endl;
			
			if(A[cycle[j-1]][0] == cycle[j])
				A[cycle[j-1]][0] = -1;
			else
				A[cycle[j-1]][1] = -1;
			if(A[cycle[j]][0] == cycle[j-1])
				A[cycle[j]][0] = -1;
			else
				A[cycle[j]][1] = -1;

			//prt_dual(A);
			//cout << "\n";
		}
		//cout << "--------" << endl;
		// ADD	親Bの辺を追加
		for(int j=2;j<cycle.size();j+=2){
			//cout << " j : " << j << " [" << cycle[j-1] << " " << cycle[j] << "]" << endl;
			//cout << "\t" << A[cycle[j-1]][0] << " " << A[cycle[j-1]][1] << endl;
			//cout << "\t" << A[cycle[j]][0] << " " << A[cycle[j]][1] << endl;
		
			if(A[cycle[j-1]][0] == -1)	A[cycle[j-1]][0] = cycle[j];
			else	A[cycle[j-1]][1] = cycle[j];
			if(A[cycle[j]][0] == -1)A[cycle[j]][0] = cycle[j-1];
			else 				A[cycle[j]][1] = cycle[j-1];

			//prt_dual(A);
			//cout << "\n";
		}
		//prt_dual(A);
	}
	//cout << "===== E_SET RESULT =====" << endl;
	//prt(A);
	return A;
}
//===================================//
//	双方向リストAからAB_Cycleの差分をとる
//  改善版（引数を変更せずに行う）
vecdual EAX::E_Set2(const vecdual &A,const vecdual&AB){
//	A	:	親個体A
//	AB	:	AB_Cycle(複数可)
//-----------------------------------//
//	前提としてAB_CycleはAの辺から始まる
	vecdual B(A.size());
	copy(A.begin(),A.end(),B.begin());
	for(const auto cycle : AB){
		// DELETE	親Aの辺を削除
		for(int j=1;j<cycle.size();j+=2){
			if(B[cycle[j-1]][0] == cycle[j])
				B[cycle[j-1]][0] = -1;
			else
				B[cycle[j-1]][1] = -1;
			if(B[cycle[j]][0] == cycle[j-1])
				B[cycle[j]][0] = -1;
			else
				B[cycle[j]][1] = -1;
		}
		// ADD	親Bの辺を追加
		for(int j=2;j<cycle.size();j+=2){
			if(B[cycle[j-1]][0] == -1)	B[cycle[j-1]][0] = cycle[j];
			else	B[cycle[j-1]][1] = cycle[j];
			if(B[cycle[j]][0] == -1)B[cycle[j]][0] = cycle[j-1];
			else 				B[cycle[j]][1] = cycle[j-1];
		}
	}
	return B;
}
//===================================//
// AB-Cycle をランダムに選択する
vecdual EAX::E_SetRand(const vecdual &A,const vecdual&AB){
	vecdual B(A.size());
	copy(A.begin(),A.end(),B.begin());

	for(const auto cycle : AB){
		if(Random::bin() == 1){
			// DELETE	親Aの辺を削除
			for(int j=1;j<cycle.size();j+=2){
				if(B[cycle[j-1]][0] == cycle[j])
					B[cycle[j-1]][0] = -1;
				else
					B[cycle[j-1]][1] = -1;
				if(B[cycle[j]][0] == cycle[j-1])
					B[cycle[j]][0] = -1;
				else
					B[cycle[j]][1] = -1;
			}
			// ADD	親Bの辺を追加
			for(int j=2;j<cycle.size();j+=2){
				if(B[cycle[j-1]][0] == -1)	B[cycle[j-1]][0] = cycle[j];
				else	B[cycle[j-1]][1] = cycle[j];
				if(B[cycle[j]][0] == -1)B[cycle[j]][0] = cycle[j-1];
				else 				B[cycle[j]][1] = cycle[j-1];
			}
		}
	}
	return B;
}
vecdual EAX::E_SetPaRand(const vecdual &A,const vecdual &AB,double pa){
	vecdual B(A.size());
	copy(A.begin(),A.end(),B.begin());

	for(const auto cycle : AB){
		if(Random::real() < pa){
			// DELETE	親Aの辺を削除
			for(int j=1;j<cycle.size();j+=2){
				if(B[cycle[j-1]][0] == cycle[j])
					B[cycle[j-1]][0] = -1;
				else
					B[cycle[j-1]][1] = -1;
				if(B[cycle[j]][0] == cycle[j-1])
					B[cycle[j]][0] = -1;
				else
					B[cycle[j]][1] = -1;
			}
			// ADD	親Bの辺を追加
			for(int j=2;j<cycle.size();j+=2){
				if(B[cycle[j-1]][0] == -1)	B[cycle[j-1]][0] = cycle[j];
				else	B[cycle[j-1]][1] = cycle[j];
				if(B[cycle[j]][0] == -1)B[cycle[j]][0] = cycle[j-1];
				else 				B[cycle[j]][1] = cycle[j-1];
			}
		}
	}
	return B;
}
//===================================//
//	双方向リストから単方向リストを作成
vecdual EAX::make_single_link(const vecdual &A){
//	A	:	双方向リスト
//-----------------------------------//
	vecdual single;	// 単方向リスト
	vecint list(A.size(),1 );	// 使用リスト 0,1

	for(int i=0;i<A.size();++i){
		if(list[i] == 0) continue;
		int s=i,p=i,next;
		vecint cycle;
		next = A[s][0];
		list[s]--;
		cycle.PB(s);
		while(s != next){
			list[next]--;
			cycle.PB(next);
		//	cout << "p : " << p << "\tnext : " << next << endl;
			int tmp = p;
			p = next;
			next = (A[next][0] != tmp) ? A[next][0] : A[next][1];
		}
	//	cout << "cycle \t";
	//	prt(cycle);
		single.PB(cycle);
	}
//	cout << " === MAKE SINGLE RESULT ===\n";
//	prt(single);
	return single;
}
//===================================//
//	ソート済みリストにインデックスを追加する
void EAX::add_index_list(){
//-----------------------------------//

}
//===================================//
//	緩和個体から島を修正する(受け取った双方向リストで修正して返す)
void EAX::remake(vecdual &A){
//	A	:	修正するリスト(双方向リスト)
//-----------------------------------//
	if(CityNums != A.size()){
		cout << "Remake [Cycle Number Error]\n";
	}

	auto recycles = make_single_link(A);

	int SimaNum = recycles.size();	// 島の数
	// 修正なしで終わり
	if(SimaNum==1)return;

	if(SimaNum > 100){
		cout << "\nSimaNum : "<<SimaNum<<endl;
	}
	// 各島のサイズ
	vecint SimaLen(SimaNum);
	for(int i=0;i<SimaNum;++i)SimaLen[i] = recycles[i].size();
	vecint numbering(CityNums);
	vecint Simabering(SimaNum);
	for(int i=0;i<SimaNum;++i)for(int p : recycles[i])numbering[p]=i;
	for(int i=0;i<SimaNum;++i)Simabering[i]=i;

	while(SimaNum > 1){
		// minIsl : 最小の島の要素番号
		int minIsl = distance(SimaLen.begin(),min_element(SimaLen.begin(),SimaLen.end()));

		// 最小のつなぎになる組み合わせ
		vecint best(4,0);
		double bestfit = (1<<30);
		int bestNum;

		for(int i=0;i<Simabering.size();++i){
			if(Simabering[i] == minIsl){
				// 探索スタート
				// e1 : 最小の島の点
				for(int e1 : recycles[i]){
					bool DisConnect = true;
					for(int j = 1;j <= MAX_SEARCH;++j){
						auto tmp = city.CityDisSort[e1][j];
						int e2 = tmp.index;
						if(numbering[e1] == numbering[e2]) continue;
						DisConnect = false;
						// e3 : e1に隣接する点
						for(int e3 : A[e1]){
							int nextsima = numbering[e2];
							// e4 : e2に隣接する点
							for(int e4 : A[e2]){
								double e1e2,e1e3,e2e4,e3e4;
								e1e2 = city.CityDis[e1][e2];
								e1e3 = city.CityDis[e1][e3];
								e2e4 = city.CityDis[e2][e4];
								e3e4 = city.CityDis[e3][e4];
								double diff = ((e1e2+e3e4) - (e1e3+e2e4));
								if(diff < bestfit){
									best[0]=e1,best[1]=e2,best[2]=e3,best[3]=e4,bestfit=diff;
									bestNum = nextsima;
								}
							}//End of e4
						}// End of e3
					}
					// 離島で接続できない時
					if(DisConnect){
						int k;
						for(k=MAX_SEARCH;k<CityNums && numbering[city.CityDisSort[e1][k].index]==numbering[e1];k++)
							;
					//	cout << e1 << endl;
						int e2 = city.CityDisSort[e1][k].index;
						for(int e3 : A[e1]){
							int nextsima = numbering[e2];
							// e4 : e2に隣接する点
							for(int e4 : A[e2]){
								double e1e2,e1e3,e2e4,e3e4;
								e1e2 = city.CityDis[e1][e2];
								e1e3 = city.CityDis[e1][e3];
								e2e4 = city.CityDis[e2][e4];
								e3e4 = city.CityDis[e3][e4];
								double diff = ((e1e2+e3e4) - (e1e3+e2e4));
								if(diff < bestfit){
									best[0]=e1,best[1]=e2,best[2]=e3,best[3]=e4,bestfit=diff;
									bestNum = nextsima;
								}
							}//End of e4
						}// End of e3
					}// End of if DisConnect
				}// End of for e1
			}// End of if 探索中の島
		}// End of Select
		
		if(best[0]+best[1]+best[2]+best[3]==0){
			cout << "Remake\nNo Points\n";
			cout << "DISCONNECT\n";
		}
		// 島の統一
		for(int i=0;i<Simabering.size();++i){
			if(Simabering[i] == minIsl){
				for(int t : recycles[i])numbering[t]=bestNum;
				Simabering[i] = bestNum;
			}
		}
		SimaLen[bestNum] += SimaLen[minIsl];
		SimaLen[minIsl] = MAX_INT;
		// A の要素を書き換える
		if(A[best[0]][0]==best[2]) A[best[0]][0]= best[1];
		else 			A[best[0]][1] = best[1];
		if(A[best[2]][0]==best[0]) A[best[2]][0]= best[3];
		else 			A[best[2]][1] = best[3];
		if(A[best[1]][0]==best[3]) A[best[1]][0]= best[0];
		else 			A[best[1]][1] = best[0];
		if(A[best[3]][0]==best[1]) A[best[3]][0]= best[2];
		else 			A[best[3]][1] = best[2];
		SimaNum--;
	}// End of While //*/
}

//===================================//
void EAX::opt2(vecint & A){
//-----------------------------------//
	for (int fImproved = 1; fImproved ; ) {
		fImproved = 0;
		for (int i = 0; i < CityNums-2; i++) {
			//cout << i << endl;
			for (int j = i+2; j < CityNums; j++) {
				//cout << "\t" << j << endl;
				if (D(i,j) + D(i+1,j+1) < D(i,i+1) + D(j,j+1)) {
					// 部分経路を逆順に並び替える
					for (int k = 0; k < (int)(j-i)/2; k++) {
						swap(A[i+1+k],A[j-k]);	//, i+1+k, j-k);
					}
					fImproved = 1;   // 改善した
				}
			}
		}
	}
}

int EAX::IndexOf(int curr, int id, const vecint &Tour) {
	for (int i = 1; i < CityNums; ++i) {
		if (curr-i >= 0 && Tour[curr-i] == id) return curr-i;
		if (curr+i < CityNums && Tour[curr+i] == id) return curr+i;
	}
	return -1;
}
//===================================//
void EAX::opt2_v2(vecint & A){
//-----------------------------------//
	const int Max_Search = 30;
	for (int fImproved = 1; fImproved; ) {
		fImproved = 0;
		for (int i = 0; i < CityNums-2; i++) {
			int idCurr = A[i];
			for (int k = 0; k < Max_Search && k < CityNums; k++) {
				int j = IndexOf(i, city.CityDisSort[idCurr][k].index, A);   // 経路上の位置を探す
				if (j > i+1 && D(i,j) + D(i+1,j+1) < D(i,i+1) + D(j,j+1)) {
					//Reverse(&Tour[i+1], &Tour[j]);
					for (int itr = 0; itr < (int)(j-i)/2; itr++) {
						swap(A[i+1+itr],A[j-itr]);	//, i+1+k, j-k);
					}
					fImproved = 1;   // 改善した
				}
			}
		}
	}
}

//===================================//
void EAX::opt3(vecint & A){
//-----------------------------------//

}

void EAX::Debug_remake(){
	//			  0     1     2     3     4     5     6      7     8     9      10
	vecdual A = {{1,2},{2,0},{0,1},{4,5},{5,3},{4,3},{7,10},{8,6},{9,7},{10,8},{6,9}};

	auto before = make_single_link(A);
	//	prtCycle(before);
	remake(A);
	auto B = make_single_link(A);
	prt(B);
}
vecint Shaffle(int n);
void EAX::Debug_crossover(){
	// sample11
	vecint A = Shaffle(52);
	vecint B = Shaffle(52);
	auto child = Crossover(A,B);
	cout << endl;
//	prt(A);
	cout << "A : " << Calculate(A) << endl;
//	prt(B);
	cout << "B : " << Calculate(B) << endl;
	cout << "CHILD\n";
	for(auto t : child){
//		prt(t);
		cout << Calculate(t) << endl;
		//prtCycle(t);
	}//*/
}


// for Debug
void prt(const vecint &A){
	for(auto tmp : A)
		cout << tmp << ",";
	cout << endl;
}
void prt(const vecdual &A){
	for(auto tmp : A){
		cout << "{"<<tmp[0];
		for(int i=1;i<tmp.size();++i)
			cout << "," << tmp[i];
		cout << "},";
	}
	cout << endl;
}
void prtCycle(const vecint &A){
	cout << "\nGraph Display\n";
	vector<double> X(A.size()+1);
	vector<double> Y(A.size()+1);

	for(int i=0;i<A.size();++i){
		Y[i] = EAX::city.CityPos[A[i]][0];
		X[i] = EAX::city.CityPos[A[i]][1];
	}
	Y[A.size()]=EAX::city.CityPos[A[0]][0];
	X[A.size()]=EAX::city.CityPos[A[0]][1];
	plt::plot(X,Y,".-b");
	plt::show();
}
void prtCycle(const vecdual &A){
	cout << "\nGraph Display\n";
	for(auto cycle : A){
		vector<double> X(cycle.size()+1);
		vector<double> Y(cycle.size()+1);

		for(int i=0;i<cycle.size();++i){
			X[i] = EAX::city.CityPos[cycle[i]][0];
			Y[i] = EAX::city.CityPos[cycle[i]][1];
		}
		X[cycle.size()]=EAX::city.CityPos[cycle[0]][0];
		Y[cycle.size()]=EAX::city.CityPos[cycle[0]][1];
		plt::plot(X,Y,".-b");
	}
	plt::show();
}
void CityDisplay(){
	int i=0;
	cout << EAX::CityNums << endl;
	cout << EAX::city.CityPos.size() << endl;
	for(const vector<double> p : EAX::city.CityPos){
		//cout << ++i << endl;
		plt::plot({p[1]},{p[0]},".-b");
	}
	plt::show();
}
void Plot(const vecint &A){
	vecint X(A.size());
	vecint Y(A.size());

	for(int i=0;i<A.size();++i){
		Y[i] = A[i];
		X[i] = i;
	}
	plt::plot(X,Y);
	plt::show();
}
void Plot(const vecdual &A){
	for(auto cycle : A){
		vecint X(cycle.size());
		vecint Y(cycle.size());

		for(int i=0;i<cycle.size();++i){
			X[i] = i;
			Y[i] = cycle[i];
		}
		plt::plot(X,Y);
	}
	plt::show();
}
vecint Shaffle(int n){
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