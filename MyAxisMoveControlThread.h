#pragma once
#include "MyAxisMoveControl.h"
#include <thread>

using namespace std;

#define AxisNum 2
enum
{
	WorkMode=0,
	ZeroMode=1,
};
class CMyAxisMoveControlThread//基于std::thread写的用于轴控的线程
{
public:
	CMyAxisMoveControlThread(void);
	~CMyAxisMoveControlThread(void);
	void SetTrigger(int iMode);
	void StartThread();
	bool AxisMove();//iMode=0代表复位,iMode=1代表执行上料等行为
	void StopThread(int iStopSignal);
	 void join();
private:
	bool m_StopThread;
	int m_Mode;
	HANDLE m_hEventStartMove;
	thread* m_AxisMoveThread;
};

