
// AxisControlTestDlg.h : ͷ�ļ�
//

#pragma once
#include "MyAxisMoveControlThread.h"
#include "resource.h"




// CAxisControlTestDlg �Ի���
class CAxisControlTestDlg : public CDialogEx
{
// ����
public:
	CAxisControlTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AXISCONTROLTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg LRESULT OnThreadMessage(WPARAM w,LPARAM l);
private:
	State* m_State;
	CMyAxisMoveControlThread* AxisThread1;
	CMyAxisMoveControlThread* AxisThread2;
	CMyAxisMoveControlThread* AxisThread3;
	CMyAxisMoveControlThread* AxisThread4;
};
