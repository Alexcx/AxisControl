#include "stdafx.h"
#include "MyAxisMoveControlThread.h"
#include "windows.h"
#include "AxisControlTestDlg.h"
CMyAxisMoveControlThread::CMyAxisMoveControlThread(State* state,int iAxisNum,CAxisControlTestDlg* dlg)
{
	m_Dlg=dlg;
	m_Mode=iAxisNum;
	m_hEventStartMove=CreateEvent(NULL,FALSE,FALSE,NULL);
	m_hEventFinishMove=CreateEvent(NULL,FALSE,TRUE,NULL);
	m_State=state;
	m_StopThread=false;
	m_ActionFinish=-1;
}

CMyAxisMoveControlThread::~CMyAxisMoveControlThread(void)
{
	StopThread(true);
	CloseHandle(m_hEventStartMove);
	delete(m_AxisMoveThread);
	delete(m_State);
}

int CMyAxisMoveControlThread::GetFinishStatus() const
{
	return m_ActionFinish;
}


void CMyAxisMoveControlThread::StartThread()
{
	 m_AxisMoveThread=new thread(&CMyAxisMoveControlThread::AxisMove,this);
}

void CMyAxisMoveControlThread::SetTrigger()//iMode��Ϊ������0ǿ�ƴ���λ��1�����˶�����
{
	WaitForSingleObject(m_hEventFinishMove,0xFFFFFFFF);
	m_ActionFinish=0;
	SetEvent(m_hEventStartMove);
}

bool CMyAxisMoveControlThread::AxisMove()
{
	WaitForSingleObject(m_hEventStartMove,0xFFFFFFFF);
	while(m_StopThread!=true)
  {
	  while(m_State->m_InsNumBefore>0||m_State->m_BufferNum>0||m_State->m_BLInsNow==2||m_State->m_PatternNow==2||m_State->m_PatternNow==1)
	{
		//WaitForSingleObject(m_hEventStartMove,0xFFFFFFFF);//һֱ����ѭ���У�ֻ�и��������źŵ�ʱ��Żᴥ����Ҳ������IO�����ƴ���
			CMyAxisMoveControl AxisHardware;
			switch(m_Mode)
			{
			case(0): 
				{
				if(m_State->m_BLInsNow==0&&m_State->m_InsNumBefore>0)
				     {
				m_Dlg->PostMessage(WM_MYMESSAGE,1,1);
				m_State->m_InsNumBefore--;
				m_Dlg->PostMessage(WM_MYMESSAGE,1,1);
				m_Dlg->PostMessage(WM_MYMESSAGE,2,1);
				Sleep(m_State->m_AxisTime*1000);
				m_Dlg->PostMessage(WM_MYMESSAGE,2,0);
				AxisHardware.MoveAxis(1,1,1);//������������
				m_ActionFinish=0;
				m_State->m_BLInsNow=1;//���״̬Ϊ1
				m_Dlg->PostMessage(WM_MYMESSAGE,3,1);
				Sleep(m_State->m_BLInsTime*1000);//�ȴ�����
				m_Dlg->PostMessage(WM_MYMESSAGE,3,2);
				m_State->m_BLInsNow=2;//���״̬��Ϊ2
				     }
				break;
			   }
			case(1): 
				{
				if(m_State->m_BLInsNow==2&&m_State->m_BufferNum<m_State->m_BufferMAxNum)
				   {
				m_Dlg->PostMessage(WM_MYMESSAGE,3,0);
				m_State->m_BLInsNow=0;//���״̬��Ϊ0
				m_Dlg->PostMessage(WM_MYMESSAGE,4,1);
				Sleep(m_State->m_AxisTime*1000);
				m_Dlg->PostMessage(WM_MYMESSAGE,4,0);
				AxisHardware.MoveAxis(1,1,1);//������Buffer��
				m_ActionFinish=1;
				Mutex.lock();
				m_State->m_BufferNum++;
				Mutex.unlock();
				m_Dlg->PostMessage(WM_MYMESSAGE,5,1);
				   }
				break;
				}
			case(2):
				{
				if(m_State->m_BufferNum>0&&m_State->m_PatternNow==0)
				  {
			    Mutex.lock();
				m_State->m_BufferNum--;
				Mutex.unlock();
				m_Dlg->PostMessage(WM_MYMESSAGE,5,1);
				m_Dlg->PostMessage(WM_MYMESSAGE,6,1);
				Sleep(m_State->m_AxisTime*1000);
				m_Dlg->PostMessage(WM_MYMESSAGE,6,0);
				AxisHardware.MoveAxis(1,1,1);//����Pattern�����
				m_State->m_PatternNow=1;//���״̬Ϊ1
				m_Dlg->PostMessage(WM_MYMESSAGE,7,1);
				Sleep(m_State->m_PatternInsTime*1000);//�ȴ�����
				m_Dlg->PostMessage(WM_MYMESSAGE,7,2);
				m_State->m_PatternNow=2;//���״̬��Ϊ2
				m_ActionFinish=2;
				  }
				break;
				}
			case(3): 
				{
				if(m_State->m_PatternNow==2)
				  {
				m_Dlg->PostMessage(WM_MYMESSAGE,7,0);
				m_State->m_PatternNow=0;//���״̬��Ϊ0
				m_Dlg->PostMessage(WM_MYMESSAGE,8,1);
				Sleep(m_State->m_AxisTime*1000);
				m_Dlg->PostMessage(WM_MYMESSAGE,8,0);
				AxisHardware.MoveAxis(1,1,1);//������������
				m_ActionFinish=1;
				m_State->m_InsNumEnd++;
				m_Dlg->PostMessage(WM_MYMESSAGE,9,1);
				   }
				break;
				}
			}
			SetEvent(m_hEventFinishMove);
	}
	  StopThread(0);
  }
	return true;
}

void CMyAxisMoveControlThread::StopThread(int iMode)
{
	m_StopThread=true;
}

void CMyAxisMoveControlThread::join()
{
	m_AxisMoveThread->join();
}