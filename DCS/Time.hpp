// timeGetTime() を使った時間計測タイマー クラス
//#pragma comment(lib, "winmm.lib")
#pragma once
#include <chrono>
class Timer
{
public:
    Timer() { restart(); }
public:
    void  restart()
    {
        m_start = std::chrono::system_clock::now();      // 計測スタート時刻を保存
    }
    int  elapsed()    // リスタートからの秒数を返す
    {
        std::chrono::system_clock::time_point end = chrono::system_clock::now();      // 計測スタート時刻を保存
        auto dur = end - m_start;        // 要した時間を計算
		auto msec = chrono::duration_cast<chrono::milliseconds>(dur).count();
		//cout << msec << " milli sec \n";
		return msec;
	}
private:
    std::chrono::system_clock::time_point    m_start;    //  計測開始時間
};