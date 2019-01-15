#include "stdafx.h"
#include "MyAxisMoveControl.h"


CMyAxisMoveControl::CMyAxisMoveControl(void)
{
}


CMyAxisMoveControl::~CMyAxisMoveControl(void)
{
}

double CMyAxisMoveControl::GetCurrentpostion()
{
	return m_Position;
}

bool CMyAxisMoveControl::MoveAxis(int iDirection,int iXe,int iYe)
{
	return true;
}

bool CMyAxisMoveControl::ZeroPosition()
{
	return true;
}

int CMyAxisMoveControl::AixsWarnning()
{
	return 0;
}