#pragma once
class CMyAxisMoveControl
{
public:
	CMyAxisMoveControl(void);
	~CMyAxisMoveControl(void);
	double GetCurrentpostion();
	bool MoveAxis(int iDirection,int iXe,int iYe);//�ƶ�����x��y�Ĵ�С,iDerection=0Ϊ����1Ϊ����
	bool ZeroPosition();//ֱ�Ӹ�λ��0λ��
	int AixsWarnning();//�쳣����±�����1�������ƶ�ʧ��
private:
	double m_Position;//��ǰλ��	
};

