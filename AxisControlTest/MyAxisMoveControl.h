#pragma once
class CMyAxisMoveControl
{
public:
	CMyAxisMoveControl(void);
	~CMyAxisMoveControl(void);
	double GetCurrentpostion();
	bool MoveAxis(int iDirection,int iXe,int iYe);//移动方向及x和y的大小,iDerection=0为负向，1为正向
	bool ZeroPosition();//直接复位到0位置
	int AixsWarnning();//异常情况下报警，1代表发生移动失败
private:
	double m_Position;//当前位置	
};

