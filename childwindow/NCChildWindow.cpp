// NCChildWindow.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "NCChildWindow.h"
#include "CMainWnd.h"


// ���ǵ���������һ��ʾ��
NCCHILDWINDOW_API int nNCChildWindow=0;

// ���ǵ���������һ��ʾ����
NCCHILDWINDOW_API int fnNCChildWindow(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� NCChildWindow.h
CNCChildWindow::CNCChildWindow()
{
	return;
}

NCCHILDWINDOW_API HWND CShowChildWindow(TCFormFrame frame, TCFormSysButton button, TCFormInitCallBack callback)
{
	// ��ʼ��UI������
	CPaintManagerUI::SetInstance(GetModuleHandle(NULL));
	// ��ʼ����Դ
	CDuiString strResourcePath = CPaintManagerUI::GetInstancePath();
	strResourcePath += _T("..\\Skins\\Default\\ChildWndSkin\\");
	CPaintManagerUI::SetResourcePath(strResourcePath.GetData());

	//CBaseWnd* pFrame = new CBaseWnd(frame, button);
	//if (pFrame == NULL) return NULL;
	//pFrame->Create(frame.pWnd, _T("BaseWnd"), UI_WNDSTYLE_FRAME, 0L, 0, 0, 0, 0);
	//pFrame->CenterWindow();
	bool btnStatus[5] = {0};
	btnStatus[0] = button.sbClose;
	btnStatus[1] = button.sbFeedback;
	btnStatus[2] = button.sbMax;
	btnStatus[3] = button.sbMin;
	btnStatus[4] = button.sbOther;
	CMainWnd* pFrame = CMainWnd::getInstance(frame.pWnd, frame.caption, frame.path, btnStatus, frame.formTag, frame.isOnly, frame.isShowModal);
	if (pFrame){
		RECT rc;   //����λ��  ������λ��
		GetWindowRect(pFrame->GetHWND(), &rc);
		callback(pFrame->GetHWND(), rc.right - rc.left, rc.bottom - rc.top);
		return pFrame->GetHWND();
	}
	return NULL;
	
}
