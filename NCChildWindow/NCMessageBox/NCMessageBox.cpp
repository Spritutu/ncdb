// NCMessageBox.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "NCMessageBox.h"
#include "MessageBoxWnd.h"

NCMESSAGEBOX_API int NCMessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType, UINT uIcon, POINT pPosition, BOOL bCheck)
{
	CPaintManagerUI::SetInstance(GetModuleHandle(NULL));
	// ��ʼ����Դ
	CDuiString strResourcePath = CPaintManagerUI::GetInstancePath();
	strResourcePath += _T("MessageBoxSkin\\");
	CPaintManagerUI::SetResourcePath(strResourcePath.GetData());
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);    //CRT����Ƿ����ڴ�й©���������output�������
	
	return CMessageBoxWnd::LvMessageBox(hWnd, lpText, lpCaption, uType, uIcon, pPosition, bCheck);
}