// NCGifSmiley.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "NCGifSmiley.h"
#include "MainWnd.h"


// ���ǵ���������һ��ʾ��
NCGIFSMILEY_API int nNCGifSmiley=0;

// ���ǵ���������һ��ʾ����
NCGIFSMILEY_API int fnNCGifSmiley(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� NCGifSmiley.h
CNCGifSmiley::CNCGifSmiley()
{
	return;
}

CDuiString path;
void initDuilib()
{
	CPaintManagerUI::SetInstance(GetModuleHandle(NULL));
	// ��ʼ����Դ
	path = CPaintManagerUI::GetResourcePath();
	CDuiString strResourcePath = CPaintManagerUI::GetInstancePath();
	strResourcePath += _T("..\\Skins\\Default\\GifSkin\\");
	CPaintManagerUI::SetResourcePath(strResourcePath.GetData());
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);    //CRT����Ƿ����ڴ�й©���������output�������
}


NCGIFSMILEY_API void CShowGifWindow()
{
	initDuilib();
	CMainWnd* pFrame = new CMainWnd();
	if (pFrame == NULL) return;
	pFrame->Create(NULL, _T("T2Lv"), UI_WNDSTYLE_FRAME, 0L, 0, 0, 0, 0);
	pFrame->CenterWindow();
	pFrame->ShowWindow();
	//if (!path.IsEmpty())
	//	CPaintManagerUI::SetResourcePath(path.GetData());
}