#pragma once
#include "MyAxisMoveControl.h"
#include <thread>
#define WM_MYMESSAGE 1010
#include <mutex>
using namespace std;

typedef struct State
{
	int m_InsNumBefore;//�����Ʒ������
	int m_BLInsTime;//���⼰�ҳ��������ʱ��
	int m_BufferMAxNum;//��������󻺴�����
	int m_BufferNum;//��������ǰ��������
	int m_InsNumEnd;//��ɼ��Ʒ������
	int m_AxisTime;//�ĸ�����˶�ʱ�䣨�����߻أ�
	int m_PatternInsTime;//pattern�����ʱ
	int m_BLInsNow;//��־λ�������⹤λ�Ƿ����ڼ��,0Ϊ�գ�1���ڼ�飬2������
	int m_PatternNow;//��־λ������pattern��鹤λ�Ƿ����ڼ�飬0Ϊ�գ�1���ڼ�飬2������
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
class CMyAxisMoveControlThread//����std::threadд��������ص��߳�
{
public:
	CMyAxisMoveControlThread(State* state,int iAxisNum,CAxisControlTestDlg* dlg);
	~CMyAxisMoveControlThread(void);
	void SetTrigger();
	void StartThread();

	int  GetFinishStatus() const;//0����axis1��λ��1����
	
	bool AxisMove();//iMode=0����λ,iMode=1����ִ�����ϵ���Ϊ
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

