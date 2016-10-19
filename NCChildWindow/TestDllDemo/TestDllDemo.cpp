// TestDllDemo.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "TestDllDemo.h"
#include "CMainWnd.h"


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	HRESULT Hr = ::CoInitialize(NULL);
	if (FAILED(Hr)) return 0;
	// ��ʼ��UI������
	CPaintManagerUI::SetInstance(hInstance);
	// ��ʼ����Դ
	CDuiString strResourcePath = CPaintManagerUI::GetInstancePath();
	strResourcePath += _T("DemoSkin\\");
	CPaintManagerUI::SetResourcePath(strResourcePath.GetData());

	CMainWnd* pFrame = new CMainWnd();
	if (pFrame == NULL) return 0;
	pFrame->Create(NULL, _T("LogIn"), UI_WNDSTYLE_FRAME, 0L, 0, 0, 0, 0);
	pFrame->CenterWindow();


	CPaintManagerUI::MessageLoop();
	::CoUninitialize();
	return 0;
}

