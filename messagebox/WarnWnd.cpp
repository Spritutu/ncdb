#include "stdafx.h"
#include "WarnWnd.h"
#include "NCMessageBox.h"

vector<HWND> vecWnd;
CDuiString strTitle;
HWND pForeground = NULL;

CWarnWnd::CWarnWnd(void)
	: m_pCloseBtn(nullptr)
	, m_pBtn1(nullptr)
	, m_pBtn2(nullptr)
	, m_pBtn3(nullptr)
	, m_pTitle(nullptr)
{
}

CWarnWnd::~CWarnWnd(void)
{
}

void CWarnWnd::OnFinalMessage(HWND hWnd)
{
	for (vector<HWND>::iterator it = vecWnd.begin(); it != vecWnd.end(); it++)
	{
		if (*it == hWnd){
			vecWnd.erase(it);
			break;
		}
	}
	__super::OnFinalMessage(hWnd);
}

void CWarnWnd::LvWarnWnd(LPCTSTR pTitle)
{
	pForeground = NULL;
	pForeground = GetForegroundWindow();
	strTitle = pTitle;
	CWarnWnd *s_pInstance = new CWarnWnd();
	s_pInstance->Create(NULL, _T(""), UI_WNDSTYLE_FRAME, WS_EX_TOOLWINDOW , 0, 0, 0, 0);
	//HWND pWnd = s_pInstance->Create(NULL, _T(""), WS_CAPTION | WS_POPUPWINDOW | WS_SYSMENU, WS_EX_NOACTIVATE, 0, 0, 0, 0);
	//::ShowWindow(pWnd, SW_SHOWNOACTIVATE);
	//s_pInstance->ShowWindow(true, false);
	//::ShowWindow(s_pInstance->GetHWND(), SW_SHOWNOACTIVATE);
	vecWnd.push_back(s_pInstance->GetHWND()); 	
}

//DuiLib::CDuiString CWarnWnd::GetSkinFile()
//{
//	return _T("WarnWnd.xml");
//}
//
//LPCTSTR CWarnWnd::GetWindowClassName(void) const
//{
//	return _T("MessageBoxWnd");
//}
void CWarnWnd::SetWndAttribute()
{
	SetSkinFile(_T("WarnWnd.xml"));
	ResizeClient(WND_WIDTH, WND_HEIGHT);

	//RECT rc = { 0, 0, 0, -1 };
	//m_pm.SetCaptionRect(rc);
	RECT rcSizeBox = { 0, 0, 0, 0 };
	m_pm.SetSizeBox(rcSizeBox);
	m_pm.SetMaxInfo(WND_WIDTH, WND_HEIGHT);
}

void CWarnWnd::InitWindow()
{		
	SetWndAttribute();
	//���ô��ڿ�����Ļ��Ե�����
	SetWindowLong(m_hWnd, GWL_STYLE, GetWindowLong(m_hWnd, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME);

	SetTimer(GetHWND(), ACTIVE_TIMERID, 10, NULL);
	
	m_pCloseBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("close")));
	m_pBtn1 = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn1")));
	m_pBtn2 = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn2")));
	m_pBtn3 = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn3")));
	m_pTitle = static_cast<CLabelUI*>(m_pm.FindControl(_T("title")));

	m_pTitle->SetText(strTitle);

	//����λ��
	RECT rc;   
	GetWindowRect(this->GetHWND(), &rc);

	//��ȡ��������
	RECT rt;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rt, 0);

	//���ô���һֱ����ǰ
	if (vecWnd.size()){
		RECT preRc;
		GetWindowRect(vecWnd.back(), &preRc);
		if (preRc.left > 0){
			if (preRc.top - (rc.bottom - rc.top)>0)
				SetWindowPos(GetHWND(), HWND_TOPMOST, preRc.left, preRc.top - (rc.bottom - rc.top) - 4, rc.right - rc.left, rc.bottom - rc.top, SWP_NOACTIVATE);
			else{
				SetWindowPos(GetHWND(), HWND_TOPMOST, preRc.left - (rc.right - rc.left) - 4, rt.bottom - rt.top - (rc.bottom - rc.top) - 4, rc.right - rc.left, rc.bottom - rc.top, SWP_NOACTIVATE);
			}
		}
		else{
			SetWindowPos(GetHWND(), HWND_TOPMOST, rt.right - rt.left - (rc.right - rc.left) - 4, rt.bottom - rt.top - (rc.bottom - rc.top) - 4, rc.right - rc.left, rc.bottom - rc.top, SWP_NOACTIVATE);
		}
	}
	else{
		SetWindowPos(GetHWND(), HWND_TOPMOST, rt.right - rt.left - (rc.right - rc.left) - 4, rt.bottom - rt.top - (rc.bottom - rc.top) - 4, rc.right - rc.left, rc.bottom - rc.top, SWP_NOACTIVATE);
	}

}

void CWarnWnd::Notify(TNotifyUI &msg)
{
	if (msg.sType == DUI_MSGTYPE_CLICK){
		if (msg.pSender == m_pCloseBtn){
			Close(MSGID_CANCEL);
			SetWndPos();		
		}
			
	}
	return WindowImplBase::Notify(msg);
}

LRESULT CWarnWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (uMsg == WM_MOUSEMOVE){

	}
	else if (uMsg == WM_TIMER){
		OnTimer((UINT_PTR)wParam);
	}
	bHandled = FALSE;
	return 0;
}

LRESULT CWarnWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (WM_NCLBUTTONDBLCLK != uMsg)
		return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
	else
		return 0;
}

void CWarnWnd::OnTimer(UINT_PTR idEvent)
{
	if (idEvent != ACTIVE_TIMERID)
		return;
	KillTimer(GetHWND(), ACTIVE_TIMERID);
	
	if (pForeground){
		SetActiveWindow(pForeground);
		//SetForegroundWindow(pForeground);
		//SetFocus(pForeground);
		//BringWindowToTop(pForeground);
	}
}

//void CWarnWnd::OnMoveWndTimer(UINT_PTR idEvent)
//{
//	if (idEvent != CLOSE_TIMERID)
//		return;
//	KillTimer(GetHWND(), CLOSE_TIMERID);
//
//	RECT rc;
//	GetWindowRect(GetHWND(), &rc);
//	MoveWindow(GetHWND(), rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, true);
//}

void CWarnWnd::SetWndPos()
{
	int index = 0;
	for (auto hWnd : vecWnd){
		if (hWnd == GetHWND())
			break;
		index++;
	}
	int iSize = vecWnd.size();
	for (int i = iSize; i > index; i--){
		RECT rcWnd;
		if (i > 1){
			GetWindowRect(vecWnd[i - 2], &rcWnd);
			MoveWindow(vecWnd[i - 1], rcWnd.left, rcWnd.top, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top, true);
		}
	}
}