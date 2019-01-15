#pragma once
#include "MyAxisMoveControl.h"
#include <thread>
#define WM_MYMESSAGE 1010
#include <mutex>
using namespace std;

typedef struct State
{
	int m_InsNumBefore;//待检查品的数量
	int m_BLInsTime;//背光及灰尘检查所需时间
	int m_BufferMAxNum;//缓冲区最大缓存数量
	int m_BufferNum;//缓冲区当前缓存数量
	int m_InsNumEnd;//完成检查品的数量
	int m_AxisTime;//四个轴控运动时间（来或者回）
	int m_PatternInsTime;//pattern检查用时
	int m_BLInsNow;//标志位，代表背光工位是否正在检查,0为空，1正在检查，2检查完成
	int m_PatternNow;//标志位，代表pattern检查工位是否正在检查，0为空，1正在检查，2检查完成
};

class CAxisControlTestDlg;
enum
{
  AxisoneZero=0,
  AxisOneMove=1,
  AxisTwoZero=2,
  AxisTwoMove=3,
  
};

#define AxisNum 1
enum
{
	WorkMode=0,
	ZeroMode=1,
};
class CMyAxisMoveControlThread//基于std::thread写的用于轴控的线程
{
public:
	CMyAxisMoveControlThread(State* state,int iAxisNum,CAxisControlTestDlg* dlg);
	~CMyAxisMoveControlThread(void);
	void SetTrigger();
	void StartThread();

	int  GetFinishStatus() const;//0代表axis1复位，1代表
	
	bool AxisMove();//iMode=0代表复位,iMode=1代表执行上料等行为
	void StopThread(int iStopSignal);
	 void join();
private:
	bool m_StopThread;
	int m_Mode;
	HANDLE m_hEventStartMove;
	HANDLE m_hEventFinishMove;
	thread* m_AxisMoveThread;
	int m_ActionFinish;
    State* m_State;
	CAxisControlTestDlg* m_Dlg;
	mutex Mutex;

};

