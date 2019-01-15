
// AxisControlTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AxisControlTest.h"
#include "AxisControlTestDlg.h"
#include "afxdialogex.h"
#include "MyAxisMoveControl.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CAxisControlTestDlg �Ի���



CAxisControlTestDlg::CAxisControlTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAxisControlTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_State=new State;
	m_State->m_InsNumBefore=10;//�����Ʒ������
	m_State->m_BLInsTime=1;//���⼰�ҳ��������ʱ��
	m_State->m_BufferNum=0;//��������ǰ��������
	m_State->m_InsNumEnd=0;//��ɼ��Ʒ������
	m_State->m_AxisTime=1;//�ĸ�����˶�ʱ�䣨�����߻أ�
	m_State->m_PatternInsTime=3;//pattern�����ʱ
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


// CAxisControlTestDlg ��Ϣ�������

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
	GetDlgItem(IDC_BLIns)->SetWindowTextW(_T("�ȴ����"));
	GetDlgItem(IDC_PatternIns)->SetWindowTextW(_T("�ȴ����"));

	GetDlgItem(IDC_Axis1)->SetWindowTextW(_T("�ȴ����"));
	GetDlgItem(IDC_Axis2)->SetWindowTextW(_T("�ȴ����"));
	GetDlgItem(IDC_Axis3)->SetWindowTextW(_T("�ȴ����"));
	GetDlgItem(IDC_Axis4)->SetWindowTextW(_T("�ȴ����"));
	
	
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAxisControlTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
				   GetDlgItem(IDC_Axis1)->SetWindowTextW(_T("������"));
			   else GetDlgItem(IDC_Axis1)->SetWindowTextW(_T("�ȴ�����"));
			   break;
		   }
	   case(3):
		   {
			   if(l==1) GetDlgItem(IDC_BLIns)->SetWindowTextW(_T("�����"));
			   else if(l==2) GetDlgItem(IDC_BLIns)->SetWindowTextW(_T("������"));
			   else GetDlgItem(IDC_BLIns)->SetWindowTextW(_T("�ȴ�"));   
			   break;
		   } 
	   case(4):
		   {
			   if(l==1) 
				   GetDlgItem(IDC_Axis2)->SetWindowTextW(_T("������"));
			   else GetDlgItem(IDC_Axis2)->SetWindowTextW(_T("�ȴ�����"));
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
				   GetDlgItem(IDC_Axis3)->SetWindowTextW(_T("������"));
			   else GetDlgItem(IDC_Axis3)->SetWindowTextW(_T("�ȴ�����"));
			   break;
		   }
	   case(7):
		   {
			   if(l==1) GetDlgItem(IDC_PatternIns)->SetWindowTextW(_T("�����"));
			   else if(l==2) GetDlgItem(IDC_PatternIns)->SetWindowTextW(_T("������"));
			   else GetDlgItem(IDC_PatternIns)->SetWindowTextW(_T("�ȴ�"));   
			   break;
		   } 
	   case(8):
		   {
			   if(l==1) 
				   GetDlgItem(IDC_Axis4)->SetWindowTextW(_T("������"));
			   else GetDlgItem(IDC_Axis4)->SetWindowTextW(_T("�ȴ�����"));
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