
// testDllCommonDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "testDllCommon.h"
#include "testDllCommonDlg.h"
#include "afxdialogex.h"
#include "..\DllCommon\DllCommon.h"
#include "PiTypeDef.h"
#include "functional.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void OutInfo(tcpchar sz1, tcpchar sz2)
{
	tstring str(sz1);
	str += sz2;
	str += _T("\n");
	OutputDebugString(str.c_str());
}


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


// CtestDllCommonDlg �Ի���



CtestDllCommonDlg::CtestDllCommonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtestDllCommonDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestDllCommonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtestDllCommonDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CtestDllCommonDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CtestDllCommonDlg ��Ϣ�������

BOOL CtestDllCommonDlg::OnInitDialog()
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
	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CtestDllCommonDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CtestDllCommonDlg::OnPaint()
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
HCURSOR CtestDllCommonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtestDllCommonDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	{
		typedef bool(*FuncSelectFileOrDir)(tagSELECT_FILE_DIR* pTag, OUT wchar_t* szSelectPath);
		static FuncSelectFileOrDir pFun = nullptr;
		if (!pFun)
		{
			HMODULE hD = LoadLibraryA("DllCommon.dll");
			pFun = (FuncSelectFileOrDir)GetProcAddress(hD, "SelectFileOrDir");
		}
		
		tagSELECT_FILE_DIR tagS;
		tagS.hParent = m_hWnd;
		tagS.szBtnOkName = _T("����");
		tagS.szTitle = _T("���ѡ��һ��Ŀ¼");
		tagS.szBeginDir = _T("e:\\work\\svn\\gitlwl");
		tagS.bCenterToParent = true;

		tstring strSelect(1024, 0);
		if ((*pFun)(&tagS, &strSelect.at(0)))
		{
			AfxMessageBox(strSelect.c_str());
		}
		//FreeLibrary(hD);
	}
}
