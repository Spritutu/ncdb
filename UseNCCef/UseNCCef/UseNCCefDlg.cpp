
// UseNCCefDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UseNCCef.h"
#include "UseNCCefDlg.h"
#include "afxdialogex.h"
#include "NCCef.h"
#include "functional.h"
#pragma comment(lib, "libcef.lib")
#pragma comment(lib, "libcef_dll_wrapper.lib")
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


// CUseNCCefDlg �Ի���



CUseNCCefDlg::CUseNCCefDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUseNCCefDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUseNCCefDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUseNCCefDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, &CUseNCCefDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CUseNCCefDlg ��Ϣ�������

BOOL CUseNCCefDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	TestCef();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CUseNCCefDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CUseNCCefDlg::OnPaint()
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
HCURSOR CUseNCCefDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CUseNCCefDlg::TestCef()
{
	m_pCef = theApp.m_pCef;
	
	int nRet = 0;
	m_pCef->Parent(m_hWnd);
	m_pCef->Init(true);
	m_pCef->Create(m_hWnd);
	m_pCef->Start();
	
	//m_pCef->Load(_T("sdf"));
}



int CUseNCCefDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	/*CNCCef* pCef = theApp.m_pCef;

	int nRet = 0;
	pCef->Parent(m_hWnd);
	pCef->Init(true);
	pCef->Create(m_hWnd);*/

	return 0;
}


void CUseNCCefDlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	OutInfo(_T("OnClose"));
	if (m_pCef && !m_pCef->IsClosing())
	{
		OutInfo(_T("m_pCef->FreeBrowser"));
		m_pCef->FreeBrowser();
		m_pCef->UnInit();
	}
	else
	{
		CDialogEx::OnClose();
	}
}


void CUseNCCefDlg::OnDestroy()
{
	OutInfo(_T("OnDestroy"));
	//CDialogEx::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
}


void CUseNCCefDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	OutInfo(_T("keyDown"));
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CUseNCCefDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN
		|| pMsg->message == WM_KEYDOWN)
	{
		
		OutInfo(_T("main WM_KEYDOWN, WM_KEYUP"));
		int nKey = pMsg->wParam;
		if (nKey == VK_RETURN)
		{

			OutInfo(_T("�س���"));

			CString strEdit;
			GetDlgItemText(IDC_EDIT1, strEdit);
			m_pCef->Load(strEdit);
			return FALSE;
		}


	}
	
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CUseNCCefDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_pCef->Test();
}
