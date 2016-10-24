#include "stdafx.h"
#include "CMainWnd.h"
#include "CInsertWnd.h"
#include "..\NCChildWindow\NCChildWindow.h"
#pragma comment(lib, "..\\Lib\\NCChildWindow.lib")
#include "..\NCMessageBox\NCMessageBox.h"
#pragma comment(lib, "..\\Lib\\NCMessageBox.lib")

CMainWnd::CMainWnd(void)
	:m_pTestBtn(nullptr)
	, m_pTest2Btn(nullptr)
	, m_pTest3Btn(nullptr)
	, m_pTest4Btn(nullptr)
	, m_pEdit(nullptr)
{
}

CMainWnd::~CMainWnd(void)
{
}

void CMainWnd::OnFinalMessage(HWND hWnd)
{
	__super::OnFinalMessage(hWnd);
	delete this;
}

DuiLib::CDuiString CMainWnd::GetSkinFile()
{
	return _T("main.xml");
}

LPCTSTR CMainWnd::GetWindowClassName(void) const
{
	return _T("MainWnd");
}

void CMainWnd::SetWndSize(int cx, int cy)
{
	ResizeClient(cx, cy);
}
void CMainWnd::InitWindow()
{	
	m_pTestBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("testBtn")));
	m_pTest2Btn = static_cast<CButtonUI*>(m_pm.FindControl(_T("test2Btn")));
	m_pTest3Btn = static_cast<CButtonUI*>(m_pm.FindControl(_T("test3Btn")));
	m_pTest4Btn = static_cast<CButtonUI*>(m_pm.FindControl(_T("test4Btn")));
	m_pEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("edit")));
}
typedef	int(*TCFormInitCallBack)(const HWND AFormHandle, const int AWidth, int AHeight);
int InitCallBack(const HWND AFormHandle, const int AWidth, int AHeight)
{
	CInsertWnd* pFrame = new CInsertWnd();
	if (pFrame == NULL) return 0;
	pFrame->Create(AFormHandle, _T("Insert"), UI_WNDSTYLE_CHILD, 0L, 0, 0, 0, 0);
	//pFrame->CenterWindow();
	RECT rc, prc;   //����λ��  ������λ��
	GetWindowRect(pFrame->GetHWND(), &rc);
	GetWindowRect(AFormHandle, &prc);
	MoveWindow(pFrame->GetHWND(), 0, 28, prc.right - prc.left, prc.bottom - prc.top - 28, true);
	//MessageBox(NULL, _T(""), _T(""), MB_OK);
	return 0;
}

void CMainWnd::Notify(TNotifyUI &msg)
{
	if (msg.sType == DUI_MSGTYPE_CLICK){
		if (msg.pSender == m_pTestBtn)
		{
			TCFormFrame frame;
			frame.caption = "������zzzzzz    ��һ������";
			frame.path = "Logo.png";
			frame.pWnd = GetHWND();
			frame.formTag = "��һ������";
			frame.isOnly = true;
			frame.isShowModal = false;
			TCFormSysButton button;
			button.sbClose = true;
			button.sbMax = false;
			button.sbFeedback = false;
			button.sbMin = true;
			button.sbOther = false;
			TCFormInitCallBack callback;
			callback = InitCallBack;
			CShowChildWindow(frame, button, callback);	
		}
		else if (msg.pSender == m_pTest2Btn){
			TCFormFrame frame;
			frame.caption = "������sssssss       �ڶ�������";
			frame.path = "Logo.png";
			frame.pWnd = GetHWND();
			frame.formTag = "�ڶ�������";
			frame.isOnly = true;
			frame.isShowModal = false;
			TCFormSysButton button;
			button.sbClose = true;
			button.sbMax = false;
			button.sbFeedback = false;
			button.sbMin = false;
			button.sbOther = false;
			TCFormInitCallBack callback;
			callback = InitCallBack;
			CShowChildWindow(frame, button, callback);	
		}
		else if (msg.pSender == m_pTest3Btn){
			int result = NCMessageBox(GetHWND(), _T("���������������ȵȵȵȵ��������ȵȵ������޵ĵȵȵȽ�Ƚ��ƽϾ��õ�"), _T("������"), BTN_YESRETRYCANCEL, NCICON_ERROR, {-1,-1},true);
			//int result = NCMessageBox(GetHWND(), _T("��������������������������������������������������������������������eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee����������������������������������������������������������������������������������������ԼԼ����ԼԼ����ԼԼ����ԼԼ����ԼԼ����ԼԼ����ԼԼ����ԼԼ����ԼԼ����ԼԼ����ԼԼ����ԼԼ����ԼԼ����ԼԼ����ԼԼ����ԼԼ������������������eeeeeeeeeeeeeeeeeeeeee�ȵȵȵȵȵȵȵȵȵȵȵȵȵȵ����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������޵ȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵ�vvvvvvv�ȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵ�vvvvvvv�ȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵȵ�vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv��"), _T("������"));
		}
		else if (msg.pSender == m_pTest4Btn){
			WCHAR buf[16];
			wsprintfW(buf, L"%d", i);
			CDuiString title = _T("������   ����");
			title += buf;

			NCWarnWnd(title);
			i++;
		}
	}
	//else if (msg.sType == DUI_MSGTYPE_TEXTCHANGED){
	//	WCHAR buf[16];
	//	wsprintfW(buf, L"%d", i);
	//	CDuiString title = _T("������   ����");
	//	title += buf;

	//	NCWarnBox(title);
	//	i++;
	//}
	return WindowImplBase::Notify(msg);
}

LRESULT CMainWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (uMsg == WM_MOUSEMOVE){

	}
	else if (uMsg == WM_DESTROY)
	{
		::PostQuitMessage(0L);
		bHandled = TRUE;
		return 0;
	}
	else if (uMsg == WM_LBUTTONDOWN){
		
	}
	bHandled = FALSE;
	return 0;
}

LRESULT CMainWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (WM_NCLBUTTONDBLCLK != uMsg)
		return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
	else
		return 0;
}