
// testDllCommonDlg.cpp : 实现文件
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


// CtestDllCommonDlg 对话框



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


// CtestDllCommonDlg 消息处理程序

BOOL CtestDllCommonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CtestDllCommonDlg::OnPaint()
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
HCURSOR CtestDllCommonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CtestDllCommonDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
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
			tagS.szBtnOkName = _T("自定义");
			tagS.szTitle = _T("选择保存路径");
			tagS.szBeginDir = _T("e:\\work\\svn\\gitlwl");
			tagS.szFilter = _T("All\0*.*\0图片\0*.jpg;*.png\0\0\0");
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
			tagS.szTitle = _T("选择文件或者目录");
			tagS.szInitialDir = _T("e:\\work\\svn\\gitlwl\\MFCTest1");
			//tagS.szFilter = _T("All\0*.*\0pic\0*.jpg;*.png\0\0\0");
			/************************************************************************
					filter: display： 系统自动把具体格式字符串增加放入显示字符串后面
			************************************************************************/
			//tagS.szFilter = _T("All Files (*.*)|*.*|bin files|*.exe;*.obj;*.pdb||");
			//tagS.szFilter = _T("图片|*.jpg,*.png;文档|*.doc,*.ppt");
			tagS.szInitialFileName = _T("willBeSave.txt");
			tagS.bCenterToParent = true;
			tagS.bSelectMulti = true;
			tagS.szBtnOkName = _T("发送吧");
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
		tagS.szBtnOkName = _T("发送");
		tagS.szTitle = _T("随便选择一个目录");
		tagS.szInitialDir = _T("e:\\work\\svn\\gitlwl");
		tagS.szFilter = _T("All\0*.*\0图片\0*.jpg;*.png\0\0\0");
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
	tag.szTitle = _T("标题");
	tag.szUrl = _T("http://www.2lv.wang/tulv/index.html?clientkey=1");
	NCInitPopup(&tag);*/
}


void CtestDllCommonDlg::OnBnClickedBtnWarn()
{
	// TODO:  在此添加控件通知处理程序代码
	/*tag_CREATE tag = { 0 };
	tag.bBig = false;
	NCInitPopup(&tag);*/
}
