#include "stdafx.h"
#include "MyAxisMoveControlThread.h"
#include "windows.h"
CMyAxisMoveControlThread::CMyAxisMoveControlThread(void)
{

	m_hEventStartMove=CreateEvent(NULL,FALSE,FALSE,NULL);
	m_StopThread=false;
	m_Mode=0;

}

CMyAxisMoveControlThread::~CMyAxisMoveControlThread(void)
{
	StopThread(true);
	CloseHandle(m_hEventStartMove);
	delete(m_AxisMoveThread);
}

void CMyAxisMoveControlThread::StartThread()
{
	 m_AxisMoveThread=new thread(&CMyAxisMoveControlThread::AxisMove,this);
}

void CMyAxisMoveControlThread::SetTrigger(int iMode)
{
	m_Mode=iMode;
	SetEvent(m_hEventStartMove);
}

bool CMyAxisMoveControlThread::AxisMove()
{
	while(m_StopThread!=true)
	{
		WaitForSingleObject(m_hEventStartMove,0xFFFFFFFF);//一直处于循环中，只有给到触发信号的时候才会触发，也可以由IO卡控制触发
		for(int i=0;i<AxisNum-1;i++)
		{
			CMyAxisMoveControl AxisHardware;
			switch(m_Mode)
			{
			case(0): AxisHardware.ZeroPosition();//复位
			case(1): AxisHardware.MoveAxis(0,0,1);//上料
			}
		}

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