#include "stdafx.h"
#include "CMainWnd.h"
#include "NCChildWindow.h"

CMainWnd *CMainWnd::s_pInstance = NULL;
struct WndTag
{
	char* wndString;
	HWND pWnd;
};
vector<WndTag> vecWndTag;
CMainWnd *CMainWnd::getInstance(HWND pWnd, char* caption, char* path, bool *btnStatus, char* formTag, bool isOnly, bool isShowModal)
{
	s_pInstance = new CMainWnd();
	s_pInstance->caption = caption;
	s_pInstance->path = path;
	s_pInstance->sbClose = btnStatus[0];
	s_pInstance->sbFeedback = btnStatus[1];
	s_pInstance->sbMax = btnStatus[2];
	s_pInstance->sbMin = btnStatus[3];
	s_pInstance->sbOther = btnStatus[4];
	s_pInstance->isOnly = isOnly;
	s_pInstance->formTagString = formTag;

	if (isOnly){
		for (auto wndTag : vecWndTag){
			if (wndTag.wndString == formTag){
				SwitchToThisWindow(wndTag.pWnd, true);
				return NULL;
			}
		}
	}
	s_pInstance->Create(pWnd, CharToDuiString(caption), UI_WNDSTYLE_FRAME, 0L, 0, 0, 0, 0);
	if (isOnly){
		WndTag tag;
		tag.wndString = formTag;
		tag.pWnd = s_pInstance->GetHWND();
		vecWndTag.push_back(tag);
	}
	s_pInstance->CenterWindow();
	if (isShowModal)
		s_pInstance->ShowModal();
	return s_pInstance;
}

CMainWnd::CMainWnd()
	: m_pLogo(nullptr)
	, m_pTitle(nullptr)
	, m_pFeedBack(nullptr)
	, m_pMin(nullptr)
	, m_pMax(nullptr)
	, m_pRestore(nullptr)
	, m_pClose(nullptr)
{
}

CMainWnd::~CMainWnd(void)
{
}

void CMainWnd::OnFinalMessage(HWND hWnd)
{
	if (isOnly){
		for (vector<WndTag>::iterator it = vecWndTag.begin(); it != vecWndTag.end(); it++)
		{
			if ((*it).wndString == formTagString){
				vecWndTag.erase(it);
				break;
			}			
		}
	}
	__super::OnFinalMessage(hWnd);
	s_pInstance = NULL;
}
//
//DuiLib::CDuiString CMainWnd::GetSkinFile()
//{
//	return _T("base.xml");
//}
//
//LPCTSTR CMainWnd::GetWindowClassName(void) const
//{
//	return _T("BaseWnd");
//}

void CMainWnd::SetWndSize(int cx, int cy)
{
	ResizeClient(cx, cy);
}
void CMainWnd::InitWindow()
{	
	SetWndAttribute();
	//���ô��ڿ�����Ļ��Ե�����
	SetWindowLong(m_hWnd, GWL_STYLE, GetWindowLong(m_hWnd, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME);    

	m_pLogo = static_cast<CControlUI*>(m_pm.FindControl(_T("logo")));
	m_pTitle = static_cast<CLabelUI*>(m_pm.FindControl(_T("title")));
	m_pFeedBack = static_cast<CButtonUI*>(m_pm.FindControl(_T("feedbackbtn")));
	m_pMin = static_cast<CButtonUI*>(m_pm.FindControl(_T("minbtn")));
	m_pMax = static_cast<CButtonUI*>(m_pm.FindControl(_T("maxbtn")));
	m_pRestore = static_cast<CButtonUI*>(m_pm.FindControl(_T("restorebtn")));
	m_pClose = static_cast<CButtonUI*>(m_pm.FindControl(_T("closebtn")));

	//m_pLogo->SetBkImage(CharToDuiString(path));
	m_pTitle->SetText(CharToDuiString(caption));
	m_pFeedBack->SetVisible(sbFeedback);
	m_pMin->SetVisible(sbMin);
	m_pClose->SetVisible(sbClose);
	m_pMax->SetVisible(sbMax);
	m_pRestore->SetVisible(sbMax);
	
}

void CMainWnd::Notify(TNotifyUI &msg)
{
	if (msg.sType == DUI_MSGTYPE_CLICK){
	}
	else if (msg.sType == DUI_MSGTYPE_VALUECHANGED)
	{

	}
	return WindowImplBase::Notify(msg);
}

LRESULT CMainWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (uMsg == WM_MOUSEMOVE){

	}
	else if (uMsg == WM_LBUTTONDOWN){
		
	}
	else if (uMsg == WM_SIZE){
		//RECT rc, prc;   //����λ��  ������λ��
		//GetWindowRect(pChildWnd, &rc);
		//GetWindowRect(this->GetHWND(), &prc);
		//MoveWindow(pChildWnd, (prc.left + prc.right) / 2 - (rc.right - rc.left) / 2, (prc.top + prc.bottom) / 2 - (rc.bottom - rc.top) / 2, rc.right - rc.left, rc.bottom - rc.top, true);
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

void CMainWnd::SetWndAttribute()
{
	SetSkinFile(_T("main.xml"));
	ResizeClient(450, 400);
	
	RECT rcSizeBox = { 0, 0, 0, 0 };
	m_pm.SetSizeBox(rcSizeBox);
	m_pm.SetMaxInfo(450, 400);
}