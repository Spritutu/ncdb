
// BinVersionerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BinVersioner.h"
#include "BinVersionerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CBinVersionerDlg �Ի���




CBinVersionerDlg::CBinVersionerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBinVersionerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBinVersionerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBinVersionerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CBinVersionerDlg ��Ϣ�������


bool SetPEResource( LPCTSTR exepath, LPCTSTR type, LPCTSTR name, tagMemBlock& mb, int language /*= 0*/ )
{
	VS_FIXEDFILEINFO* pffi = NULL;
	//pffi = ������ʵλ��
	HANDLE hexe = BeginUpdateResource(exepath, FALSE);

	if (!hexe)
		return false;

	BOOL r = UpdateResource(hexe, MAKEINTRESOURCE(RT_VERSION),  MAKEINTRESOURCE(VS_VERSION_INFO), language,
		(LPVOID)mb.pMem, (DWORD)mb.dwSize);

	BOOL er = EndUpdateResource(hexe, FALSE);

	return (r && er);
}

BOOL CBinVersionerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	wstring strVersion(_T("1.2.3.50"));
	tagMemBlock mb = GetFileVersionData();
	SetPEResource(_T("e:\\person\\ncdb\\project\\BinVersioner\\Debug\\test.exe"), RT_VERSION
		, MAKEINTRESOURCE(VS_VERSION_INFO), mb, 0);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


void CBinVersionerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBinVersionerDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBinVersionerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

tagMemBlock CBinVersionerDlg::GetFileVersionData()
{
	tagMemBlock mb = {0};
	HGLOBAL hResLoad;     // handle to loaded resource 
	HMODULE hExe;        // handle to existing .EXE file 
	HRSRC hRes;         // handle/ptr. to res. info. in hExe 
	HANDLE hUpdateRes;  // update resource handle 
	void *lpResLock;    // pointer to resource data 
	BOOL result; 
	hExe = LoadLibrary(_T("e:\\person\\ncdb\\project\\BinVersioner\\Debug\\test.exe")); 
	if (!hExe) 
	{ 
		return mb;
	} 

	hRes = FindResource(hExe, MAKEINTRESOURCE(VS_VERSION_INFO), RT_VERSION); 
	if (!hRes) 
	{ 
		return mb;
	} 

	// Load the dialog box into global memory. 
	hResLoad = LoadResource(hExe, hRes); 
	if (!hResLoad) 
	{ 
		return mb;
	} 

	// Lock the dialog box into global memory. 
	lpResLock = LockResource(hResLoad); 
	mb.pMem = lpResLock;
	mb.dwSize = *(WORD*)lpResLock;
	return mb;
	//VS_VERSIONINFO* 

}
