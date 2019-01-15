
// AxisControlTestDlg.h : 头文件
//

#pragma once
#include "MyAxisMoveControlThread.h"
#include "resource.h"




// CAxisControlTestDlg 对话框
class CAxisControlTestDlg : public CDialogEx
{
// 构造
public:
	CAxisControlTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AXISCONTROLTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
