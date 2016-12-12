
// testDllCommonDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "testDllCommon.h"
#include "testDllCommonDlg.h"
#include "afxdialogex.h"
#include "..\DllCommon\DllCommon.h"
#include "PiTypeDef.h"
#include "functional.h"
//#pragma comment(lib, "e:\\work\\svn\\nc\\output\\Bin\\NCPopWindow.lib")

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
	ON_BN_CLICKED(IDC_BTN_WARN, &CtestDllCommonDlg::OnBnClickedBtnWarn)
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
	/*TestPop();
	return;*/

	{
		//typedef bool _cdecl (*FuncSelectFileOrDir)(tagSELECT_FILE_DIR* pTag);

		
	}
	{
		typedef bool(*FuncSelectFileOrDir)(tagSELECT_FILE_DIR* pTag);
		typedef const wchar_t* (*FuncQueryFile)(int nInDex);
		typedef bool(_cdecl * FuncPopSaveDialog)(tagSELECT_FILE_DIR* pTag, wchar_t* szPath);
		

		static FuncSelectFileOrDir pFunSelect = nullptr;
		static FuncQueryFile pFunQuery = nullptr;
		static FuncPopSaveDialog pFunPopSave = nullptr;
		
		if (!pFunSelect)
		{
			HMODULE hD = LoadLibraryA("NCFileDialog.dll");
			pFunSelect = (FuncSelectFileOrDir)GetProcAddress(hD, "SelectFileOrDir");
			pFunQuery = (FuncQueryFile)GetProcAddress(hD, "QuerySelectFile");
			pFunPopSave = (FuncPopSaveDialog)GetProcAddress(hD, "PopSaveDialog");
			
		}
		/*{
			tagSELECT_FILE_DIR tagS;
			tagS.hParent = m_hWnd;
			tagS.szBtnOkName = _T("�Զ���");
			tagS.szTitle = _T("ѡ�񱣴�·��");
			tagS.szBeginDir = _T("e:\\work\\svn\\gitlwl");
			tagS.szFilter = _T("All\0*.*\0ͼƬ\0*.jpg;*.png\0\0\0");
			tagS.bCenterToParent = true;
			tstring strSelect(1024, 0);
			//int nSel = (*pFunPopSave)(&tagS, &strSelect.at(0));
			strSelect = CPIUITool::PopSaveDialog(&tagS);
			OutputDebugString(strSelect.c_str());
			return;
		}*/
		{
			CPIUITool::tagSELECT_FILE_DIR tagS;
			tagS.hParent = m_hWnd;
			tagS.szTitle = _T("ѡ���ļ�����Ŀ¼");
			tagS.szBeginDir = _T("e:\\work\\svn\\gitlwl\\MFCTest1");
			//tagS.szFilter = _T("All\0*.*\0pic\0*.jpg;*.png\0\0\0");
			/************************************************************************
					filter: display�� ϵͳ�Զ��Ѿ����ʽ�ַ������ӷ�����ʾ�ַ�������
			************************************************************************/
			//tagS.szFilter = _T("All Files (*.*)|*.*|bin files|*.exe;*.obj;*.pdb||");
			//tagS.szFilter = _T("ͼƬ|*.jpg,*.png;�ĵ�|*.doc,*.ppt");
			tagS.szBeginFileName = _T("willBeSave.txt");
			tagS.bCenterToParent = true;
			tagS.bSelectMulti = false;
			tagS.szBtnOkName = _T("���Ͱ�");
			int nSel = (*pFunSelect)(&tagS);
			//int nSel = CPIUITool::SelectFileOrDir(&tagS);
			if (!nSel)
			{
				return;
			}
			FOR_COUNT((UINT)nSel, i)
			{
				//tcpchar szPath = CPIUITool::QuerySelectFile(i);
				tcpchar szPath = (*pFunQuery)(i);
				OutInfo(szPath, _T(""));
			}
			return;
		}
		tagSELECT_FILE_DIR tagS;
		tagS.hParent = m_hWnd;
		tagS.szBtnOkName = _T("����");
		tagS.szTitle = _T("���ѡ��һ��Ŀ¼");
		tagS.szBeginDir = _T("e:\\work\\svn\\gitlwl");
		tagS.szFilter = _T("All\0*.*\0ͼƬ\0*.jpg;*.png\0\0\0");
		tagS.bCenterToParent = true;
		tagS.bSelectMulti = false;
		tstring strSelect(1024, 0);
		int nSel = (*pFunSelect)(&tagS);
		if (!nSel)
		{
			return;
		}
		FOR_COUNT((UINT)nSel, i)
		{
			tcpchar szPath = (*pFunQuery)(i);
			OutInfo(szPath, _T(""));
		}
		//FreeLibrary(hD);
	}


}

void CtestDllCommonDlg::TestPop()
{
	/*tag_CREATE tag = {0};
	tag.bBig = true;
	tag.szTitle = _T("����");
	tag.szUrl = _T("http://www.2lv.wang/tulv/index.html?clientkey=1");
	NCInitPopup(&tag);*/
}


void CtestDllCommonDlg::OnBnClickedBtnWarn()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	/*tag_CREATE tag = { 0 };
	tag.bBig = false;
	NCInitPopup(&tag);*/
}
