// NCMessageBox.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "NCMessageBox.h"
#include "MessageBoxWnd.h"

NCMESSAGEBOX_API int NCMessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType, UINT uIcon,POINT pPosition)
{
	CPaintManagerUI::SetInstance(GetModuleHandle(NULL));
	// ��ʼ����Դ
	CDuiString strResourcePath = CPaintManagerUI::GetInstancePath();
	strResourcePath += _T("MessageBoxSkin\\");
	CPaintManagerUI::SetResourcePath(strResourcePath.GetData());

	
	return CMessageBoxWnd::LvMessageBox(hWnd, lpText, lpCaption, uType, uIcon, pPosition);
}