// NCTreeList.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "NCTreeList.h"
#include "MainWnd.h"

void initDuilib()
{
	CPaintManagerUI::SetInstance(GetModuleHandle(NULL));
	// ��ʼ����Դ
	CDuiString path = CPaintManagerUI::GetResourcePath();
	CDuiString strResourcePath = CPaintManagerUI::GetInstancePath();
	strResourcePath += _T("..\\Skins\\Default\\TreeListSkin\\");
	CPaintManagerUI::SetResourcePath(strResourcePath.GetData());
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);    //CRT����Ƿ����ڴ�й©���������output�������
}
// ���ǵ���������һ��ʾ����
NCTREELIST_API void fnNCTreeList(void)
{
	initDuilib();
	CMainWnd* pFrame = new CMainWnd();
	if (pFrame == NULL) return;
	pFrame->Create(NULL, _T("TreeListWnd"), UI_WNDSTYLE_FRAME, 0L, 0, 0, 0, 0);
	pFrame->CenterWindow();
}