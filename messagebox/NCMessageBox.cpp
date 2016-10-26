// NCMessageBox.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "NCMessageBox.h"
#include "MessageBoxWnd.h"
#include "WarnWnd.h"

CDuiString path;
void initDuilib()
{
	CPaintManagerUI::SetInstance(GetModuleHandle(NULL));
	// ��ʼ����Դ
	path= CPaintManagerUI::GetResourcePath();
	CDuiString strResourcePath = CPaintManagerUI::GetInstancePath();
	strResourcePath += _T("..\\Skins\\Default\\MessageBoxSkin\\");
	CPaintManagerUI::SetResourcePath(strResourcePath.GetData());
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);    //CRT����Ƿ����ڴ�й©���������output�������
}

NCMESSAGEBOX_API int NCMessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType, UINT uIcon, POINT pPosition, BOOL bCheck)
{
	initDuilib();
	int result = CMessageBoxWnd::LvMessageBox(hWnd, lpText, lpCaption, uType, uIcon, pPosition, bCheck);
	if (!path.IsEmpty())
		CPaintManagerUI::SetResourcePath(path.GetData());
	return result;
}

NCMESSAGEBOX_API void NCWarnWnd(LPCTSTR lpCaption)
{
	initDuilib();
	CWarnWnd::LvWarnWnd(lpCaption);
	if (!path.IsEmpty())
		CPaintManagerUI::SetResourcePath(path.GetData());
}
