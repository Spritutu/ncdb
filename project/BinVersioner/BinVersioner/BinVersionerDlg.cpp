
// BinVersionerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BinVersioner.h"
#include "BinVersionerDlg.h"
#include "PathLight.h"
#include "System\PiDebugUnit.h"

#pragma comment(lib, "Version.lib")

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


int AlignMem(int pTemp, int nByte, DWORD& dwMove)
{
	int nResidual = ((int)pTemp % nByte);
	if (nResidual)
	{
		dwMove = nByte - nResidual;
		return pTemp + dwMove;
	}
	//return pTemp + (nResidual ? dwMove : 0);
	dwMove = 0;
	return pTemp;
}

bool SetPEResource( LPCTSTR exepath, LPCTSTR type, LPCTSTR name, tagMemBlock& mb, int language /*= 0*/ )
{
	int nAlignByte = 4;
	DWORD dwMove = 0;
	//test
	{
		int nBeging = 7;
		int nEnd = AlignMem(nBeging, nAlignByte, dwMove);
		nBeging = 16;
		nEnd = AlignMem(nBeging, nAlignByte, dwMove);
		nEnd = 0;
	}
	VS_FIXEDFILEINFO* pffi = NULL;
	//pffi = ������ʵλ��
	int pTemp = ((int)mb.pMem + 2 + 2 + 2 + _countof("VS_VERSION_INFO") * 2);
	pTemp = AlignMem(pTemp, nAlignByte, dwMove);
	int pFixFI = pTemp;
	int pStringFileInfo = pTemp + sizeof(VS_FIXEDFILEINFO);

	int pStringTabel = AlignMem(pStringFileInfo + 2 + 2 + 2 + _countof("StringFileInfo") * sizeof(wchar_t), nAlignByte, dwMove);
	DWORD dwTableEnd = pStringTabel + *(WORD*)pStringTabel;
	int pStringS = AlignMem(((int)pStringTabel + 2 + 2 + 2 + 8 * sizeof(wchar_t)), nAlignByte, dwMove);
	void* pResourceDataNew = NULL;
	while (pStringS < dwTableEnd && (pStringS = AlignMem(pStringS, nAlignByte, dwMove))
		&& *(char*)pStringS)
	{
		;
		int pData = 0;
		int nStringNext = pStringS;
		wstring strStrData;
		wstring pInfoName = (wchar_t*)(pStringS + 6);

		pData = AlignMem(pStringS + 6 + (pInfoName.length() + 1) * sizeof(wchar_t), nAlignByte, dwMove);
		strStrData.assign((wchar_t*)pData, *(WORD*)(pStringS + 2));
		CPiDebugUnit::OutFormat(_T("field:<%s>, data:<%s>"), pInfoName.c_str(), strStrData.c_str());

		if (pInfoName == L"FileVersion")
		{
			
			//strStrData = _T("1.0.0.9");
			pResourceDataNew = new char[mb.dwSize];
			memcpy((void*)pResourceDataNew, mb.pMem, mb.dwSize);

			VS_FIXEDFILEINFO* pFFI = (VS_FIXEDFILEINFO*)((int)pResourceDataNew + (pFixFI - (int)mb.pMem));
			pFFI->dwFileVersionLS = 0x00040032;
			pFFI->dwFileVersionMS = 0x00020003;
			/*void* pDest = (void*)((int(pResourceDataNew) + (pData - (int)mb.pMem)));
			memcpy(pDest, strStrData.c_str(), strStrData.length() * sizeof(wchar_t));*/
			//break;
			//TODO:�޸İ汾���ַ�������
			//�����ڴ�
		}
		
		nStringNext += 6;
		nStringNext += (pInfoName.length() + 1) * sizeof(wchar_t);
		AlignMem(nStringNext, nAlignByte, dwMove);
		pStringS += *(WORD*)pStringS;
		strStrData = L"";
	}
	//get language id
	struct
	{
		WORD wLanguage;
		WORD wCodePage;
	} *lpTranslate;
	UINT nSizeOut = 0;

	{
		DWORD dwSize = 0;
		dwSize = GetFileVersionInfoSize(exepath, NULL);
		void* pDataVer = new char[dwSize];
		memset(pDataVer, 0, dwSize);
		GetFileVersionInfo(exepath, NULL, dwSize, pDataVer);
		VerQueryValue(pDataVer, _T("\\VarFileInfo\\Translation"), (LPVOID*)&lpTranslate, &nSizeOut);
	}

	HANDLE hexe = BeginUpdateResource(exepath, TRUE);

	if (!hexe)
		return false;
	if (!pResourceDataNew)
	{
		pResourceDataNew = mb.pMem;
	}
	BOOL r = UpdateResource(hexe, RT_VERSION, MAKEINTRESOURCE(VS_VERSION_INFO), lpTranslate->wLanguage,
		(LPVOID)pResourceDataNew, (DWORD)mb.dwSize);

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

	CPathLight path;
	path = path.GetSelfModuleFolder();
	tstring strPathSrc = (path + _T("test.exe")).GetPath();

	wstring strVersion(_T("1.2.3.50"));
	tagMemBlock mb = GetFileVersionData(strPathSrc);
	if(!mb.pMem)
	{
		return FALSE;
	}
	tstring strPathDist = (path + _T("test.exe")).GetPath();

	SetPEResource(strPathDist.c_str(), RT_VERSION
		, MAKEINTRESOURCE(VS_VERSION_INFO), mb, 0);
	delete []mb.pMem;
	mb.pMem = NULL;
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

tagMemBlock CBinVersionerDlg::GetFileVersionData(const tstring& strPath)
{
	
	
		
	//GetModule
	tagMemBlock mb = {0};
	HGLOBAL hResLoad;     // handle to loaded resource 
	HMODULE hExe;        // handle to existing .EXE file 
	HRSRC hRes;         // handle/ptr. to res. info. in hExe 
	HANDLE hUpdateRes;  // update resource handle 
	void *lpResLock;    // pointer to resource data 
	BOOL result; 
	hExe = LoadLibrary(strPath.c_str());
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
	mb.dwSize = *(WORD*)lpResLock;
	mb.pMem = new char[mb.dwSize];
	memcpy(mb.pMem, lpResLock, mb.dwSize);
	result = FreeResource(hExe);
	FreeLibrary(hExe);
	return mb;
	//VS_VERSIONINFO* 

}
