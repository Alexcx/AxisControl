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
class CMyAxisMoveControlThread//����std::threadд��������ص��߳�
{
public:
	CMyAxisMoveControlThread(void);
	~CMyAxisMoveControlThread(void);
	void SetTrigger(int iMode);
	void StartThread();
	bool AxisMove();//iMode=0����λ,iMode=1����ִ�����ϵ���Ϊ
	void StopThread(int iStopSignal);
	 void join();
private:
	bool m_StopThread;
	int m_Mode;
	HANDLE m_hEventStartMove;
	thread* m_AxisMoveThread;
};

