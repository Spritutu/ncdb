
// MFCTest1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCTest1.h"
#include "MFCTest1Dlg.h"
#include "afxdialogex.h"
#include "PiWindowPack.h"
#include "functional.h"
#include "UI/PiFileDialog.h"

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
	virtual BOOL OnInitDialog();

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

BOOL CAboutDlg::OnInitDialog()
{
	OutInfo(_T("abdout wnd show"));
	::ShowWindow(m_hWnd, SW_SHOWNOACTIVATE);
	return TRUE;
}


// CMFCTest1Dlg �Ի���



CMFCTest1Dlg::CMFCTest1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCTest1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bDraging = false;
}

void CMFCTest1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_btn1);
}

BEGIN_MESSAGE_MAP(CMFCTest1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CMFCTest1Dlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCTest1Dlg::OnBnClickedButton1)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CMFCTest1Dlg ��Ϣ�������

BOOL CMFCTest1Dlg::OnInitDialog()
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

	const wchar_t pszFilter[] = _T("EXE File (*.txt)|*.txt|All Files (*.*)|*.*||");
	/*CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		pszFilter, this);

	dlg.m_ofn.lpstrInitialDir = _T("c:\\WINDOWS\\");  //���öԻ���Ĭ�ϳ��ֵ�·��

	if (dlg.DoModal() == IDOK)
	{
		CString strFilePath = dlg.GetPathName();
		/ *����ж���ļ�,��
		for(POSITION pos = dlg.GetStartPosition(); pos!=NULL; )
		{
		CString strFilePathName = dlg.GetNextPathName(pos);
		* /
	}*/

	

		
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFCTest1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCTest1Dlg::OnPaint()
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
HCURSOR CMFCTest1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCTest1Dlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CAboutDlg* pDlg = new CAboutDlg;
	pDlg->Create(IDD_ABOUTBOX, this);
	//pDlg->ShowWindow(SW_SHOW);
	CPiWindowPack::MoveWindow(pDlg->GetSafeHwnd(), 700, 700);
}


void CMFCTest1Dlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TestOleDrag();
	{
		CFileDialog fileDialog(TRUE, _T("*.*"), NULL, NULL, NULL);

		if (fileDialog.DoModal() != IDOK)
			return ;

		CString str = fileDialog.GetFileExt();
		str = _T(".") + str;

		SHFILEINFO   sfi;
		SHGetFileInfo(str, 0, &sfi, sizeof(sfi), SHGFI_ICON | SHGFI_LARGEICON | SHGFI_USEFILEATTRIBUTES);

		int i = sfi.iIcon;
		CStatic* pStatic = (CStatic*)GetDlgItem(IDC_STATIC);
		HICON hIcon = sfi.hIcon;
		pStatic->SetIcon(hIcon);

		m_btn1.ModifyStyle(0, BS_ICON); //����Icon����
		m_btn1.SetIcon(hIcon); //����ͼ��
		return;

	}
	tstring strFilter = _T("All Files (*.*)|*.*|txt Files (*.txt)|*.txt|bin Files (*.exe)|*.exe;*.obj||");

	CPiFileDialog dlgFile(_T("ѡ�����ļ�(Ŀ¼)"), strFilter.c_str());
	if (!dlgFile.Popup())
	{
		return;
	}
	tstring strOut;
	CWnd* pEdit = GetDlgItem(IDC_EDIT_OUTPUT);
	pEdit->SetWindowText(strOut.c_str());

	ARR_STRING lstSel = dlgFile.GetSelect();
	for (auto& strSel : lstSel)
	{
		strOut += strSel;
		strOut += _T("\r\n");
	}
	pEdit->SetWindowText(strOut.c_str());
	return;
}

void CMFCTest1Dlg::TestOleDrag()
{	
	
}


void CMFCTest1Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	BeginDrag();

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCTest1Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMFCTest1Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DragIng();
	CDialogEx::OnMouseMove(nFlags, point);
}

bool CMFCTest1Dlg::BeginDrag()
{
	if (m_bDraging)
	{
		return true;
	}
	m_bDraging = true;

	return true;
}

void CMFCTest1Dlg::DragIng()
{
	if (!m_bDraging)
	{
		return;
	}
	{
		COleDataSource*	pSource = new COleDataSource();
		CSharedFile	sf(GMEM_MOVEABLE | GMEM_DDESHARE | GMEM_ZEROINIT);
		CString iText;

		//	lets move our text
		GetWindowText(iText);

		//	write name to clipboard
		sf.Write(iText, iText.GetLength());

		HGLOBAL hMem = sf.Detach();
		if (!hMem)
			return;
		pSource->CacheGlobalData(CF_TEXT, hMem);

		//	Do drag and drop!
		pSource->DoDragDrop();

		//	free source
		delete pSource;
		return;
	}
	COleDataSource*  pOleDataSource = new COleDataSource;

	OutInfo(_T("drag begin"));
	tstring strDragData(_T("e:\\work\\html\\prompt.htm"));
	HGLOBAL        hMemData = NULL;
	DWORD		uBufferSize = sizeof(DROPFILES) + strDragData.size() * sizeof(TCHAR) + 1;

	hMemData = GlobalAlloc(GPTR, uBufferSize);
	ASSERT(hMemData != NULL);
	LPDROPFILES lpDropFiles = (LPDROPFILES)GlobalLock(hMemData); //����֮,��������س�Ա
	ASSERT(lpDropFiles != NULL);
	lpDropFiles->pFiles = sizeof(DROPFILES);

#ifdef _UNICODE
	lpDropFiles->fWide = TRUE;
#else
	lpDropFiles->fWide = FALSE;
#endif

	/************************************************************************
	����Ҫ�Ϸŵ�����
	************************************************************************/

	LPTSTR pszStart = (LPTSTR)((LPBYTE)lpDropFiles + sizeof(DROPFILES));
	pszStart = lstrcpy(pszStart, strDragData.c_str());
	pszStart = _tcsrchr(pszStart, '\0') + 1; //�´ε���ʼλ������һ�ν�β+1

	pOleDataSource->Empty();
	pOleDataSource->CacheGlobalData(CF_TEXT, hMemData);

	DROPEFFECT dwRet = pOleDataSource->DoDragDrop(DROPEFFECT_MOVE | DROPEFFECT_COPY);
	delete pOleDataSource;
	OutInfo(_T("drag ing, ret"), dwRet);
}
