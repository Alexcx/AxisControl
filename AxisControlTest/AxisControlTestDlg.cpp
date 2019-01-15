
// AxisControlTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AxisControlTest.h"
#include "AxisControlTestDlg.h"
#include "afxdialogex.h"
#include "MyAxisMoveControl.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
	
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAxisControlTestDlg 对话框



CAxisControlTestDlg::CAxisControlTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAxisControlTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_State=new State;
	m_State->m_InsNumBefore=10;//待检查品的数量
	m_State->m_BLInsTime=1;//背光及灰尘检查所需时间
	m_State->m_BufferNum=0;//缓冲区当前缓存数量
	m_State->m_InsNumEnd=0;//完成检查品的数量
	m_State->m_AxisTime=1;//四个轴控运动时间（来或者回）
	m_State->m_PatternInsTime=3;//pattern检查用时
	m_State->m_BufferMAxNum=1;
	m_State->m_PatternNow=0;
	m_State->m_BLInsNow=0;

	AxisThread1=new CMyAxisMoveControlThread(m_State,0,this);
	AxisThread2=new CMyAxisMoveControlThread(m_State,1,this);
	AxisThread3=new CMyAxisMoveControlThread(m_State,2,this);
	AxisThread4=new CMyAxisMoveControlThread(m_State,3,this);
	AxisThread1->StartThread();
	AxisThread2->StartThread();
	AxisThread3->StartThread();
	AxisThread4->StartThread();
}

void CAxisControlTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAxisControlTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CAxisControlTestDlg::OnBnClickedOk)
	ON_MESSAGE(WM_MYMESSAGE,&CAxisControlTestDlg::OnThreadMessage)
END_MESSAGE_MAP()


// CAxisControlTestDlg 消息处理程序

BOOL CAxisControlTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString szValue;
	szValue.Format(_T("%d"),m_State->m_InsNumBefore);
	GetDlgItem(IDC_Shangliao)->SetWindowTextW(szValue);
	szValue.Format(_T("%d"),m_State->m_BufferNum);
	GetDlgItem(IDC_Buffer)->SetWindowTextW(szValue);
	szValue.Format(_T("%d"),m_State->m_InsNumEnd);
	GetDlgItem(IDC_Xialiao)->SetWindowTextW(szValue);
	GetDlgItem(IDC_BLIns)->SetWindowTextW(_T("等待检查"));
	GetDlgItem(IDC_PatternIns)->SetWindowTextW(_T("等待检查"));

	GetDlgItem(IDC_Axis1)->SetWindowTextW(_T("等待检查"));
	GetDlgItem(IDC_Axis2)->SetWindowTextW(_T("等待检查"));
	GetDlgItem(IDC_Axis3)->SetWindowTextW(_T("等待检查"));
	GetDlgItem(IDC_Axis4)->SetWindowTextW(_T("等待检查"));
	
	
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAxisControlTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAxisControlTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAxisControlTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAxisControlTestDlg::OnBnClickedOk()
{	
	  AxisThread1->SetTrigger();
	  AxisThread2->SetTrigger();
	  AxisThread3->SetTrigger();
	  AxisThread4->SetTrigger();
}

LRESULT CAxisControlTestDlg::OnThreadMessage(WPARAM w,LPARAM l)
{
	int HardWareNUm=w;
	int Action=l;
	CString szValue;
	   switch(w)
	   {
	   case(1):
		   {
			  szValue.Format(_T("%d"),m_State->m_InsNumBefore);
		      GetDlgItem(IDC_Shangliao)->SetWindowTextW(szValue);
			   break;
		   } 
	   case(2):
		   {
			if(l==1) 
				   GetDlgItem(IDC_Axis1)->SetWindowTextW(_T("运行中"));
			   else GetDlgItem(IDC_Axis1)->SetWindowTextW(_T("等待运行"));
			   break;
		   }
	   case(3):
		   {
			   if(l==1) GetDlgItem(IDC_BLIns)->SetWindowTextW(_T("检查中"));
			   else if(l==2) GetDlgItem(IDC_BLIns)->SetWindowTextW(_T("检查完成"));
			   else GetDlgItem(IDC_BLIns)->SetWindowTextW(_T("等待"));   
			   break;
		   } 
	   case(4):
		   {
			   if(l==1) 
				   GetDlgItem(IDC_Axis2)->SetWindowTextW(_T("运行中"));
			   else GetDlgItem(IDC_Axis2)->SetWindowTextW(_T("等待运行"));
			   break;
		   }
	   case(5):
		   {
			   szValue.Format(_T("%d"),m_State->m_BufferNum);
			   GetDlgItem(IDC_Buffer)->SetWindowTextW(szValue);
			   break;
		   } 
	   case(6):
		   {
			   if(l==1) 
				   GetDlgItem(IDC_Axis3)->SetWindowTextW(_T("运行中"));
			   else GetDlgItem(IDC_Axis3)->SetWindowTextW(_T("等待运行"));
			   break;
		   }
	   case(7):
		   {
			   if(l==1) GetDlgItem(IDC_PatternIns)->SetWindowTextW(_T("检查中"));
			   else if(l==2) GetDlgItem(IDC_PatternIns)->SetWindowTextW(_T("检查完成"));
			   else GetDlgItem(IDC_PatternIns)->SetWindowTextW(_T("等待"));   
			   break;
		   } 
	   case(8):
		   {
			   if(l==1) 
				   GetDlgItem(IDC_Axis4)->SetWindowTextW(_T("运行中"));
			   else GetDlgItem(IDC_Axis4)->SetWindowTextW(_T("等待运行"));
			   break;
		   }
	   case(9):
		   {
			   szValue.Format(_T("%d"),m_State->m_InsNumEnd);
			   GetDlgItem(IDC_Xialiao)->SetWindowTextW(szValue);
			   break;
		   } 
	   }
	return 0;
}