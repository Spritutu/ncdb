#include "StdAfx.h"
#include "..\..\DuiLib\UIlib.h"
#include "UIComboEx.h"


void CComboWndEx::Notify(TNotifyUI& msg)
{
	if (msg.sType == _T("windowinit"))
	{
		EnsureVisible(m_iOldSel);
	}
	else if(msg.sType == _T("click")) {
		::PostMessage(::GetParent(GetHWND()), WM_LBUTTONUP, (WPARAM)msg.pSender, 0L);
	}
}

void CComboWndEx::Init(CComboUIEx* pOwner)
{
	m_bHitItem = false;
	m_pOwner = pOwner;
	m_pLayout = NULL;
	m_iOldSel = m_pOwner->GetCurSel();

	// Position the popup window in absolute space
	SIZE szDrop = m_pOwner->GetDropBoxSize();
	RECT rcOwner = pOwner->GetPos();
	RECT rc = rcOwner;
	rc.top = rc.bottom;		// ������left��bottomλ����Ϊ�����������
	rc.bottom = rc.top + szDrop.cy;	// ���㵯�����ڸ߶�
	if( szDrop.cx > 0 ) rc.right = rc.left + szDrop.cx;	// ���㵯�����ڿ��

	SIZE szAvailable = { rc.right - rc.left, rc.bottom - rc.top };
	int cyFixed = 0;
	for( int it = 0; it < pOwner->GetCount(); it++ ) {
		CControlUI* pControl = static_cast<CControlUI*>(pOwner->GetItemAt(it));
		if( !pControl->IsVisible() ) continue;
		SIZE sz = pControl->EstimateSize(szAvailable);
		cyFixed += sz.cy;
	}
	cyFixed += 4; // CVerticalLayoutUI Ĭ�ϵ�Inset ����
	rc.bottom = rc.top + MIN(cyFixed, szDrop.cy);

	::MapWindowRect(pOwner->GetManager()->GetPaintWindow(), HWND_DESKTOP, &rc);

	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
	CDuiRect rcWork = oMonitor.rcWork;
	if( rc.bottom > rcWork.bottom ) {
		rc.left = rcOwner.left;
		rc.right = rcOwner.right;
		if( szDrop.cx > 0 ) rc.right = rc.left + szDrop.cx;
		rc.top = rcOwner.top - MIN(cyFixed, szDrop.cy);
		rc.bottom = rcOwner.top;
		::MapWindowRect(pOwner->GetManager()->GetPaintWindow(), HWND_DESKTOP, &rc);
	}

	Create(pOwner->GetManager()->GetPaintWindow(), NULL, WS_POPUP, WS_EX_TOOLWINDOW, rc);
	// HACK: Don't deselect the parent's caption
	HWND hWndParent = m_hWnd;
	while( ::GetParent(hWndParent) != NULL ) hWndParent = ::GetParent(hWndParent);
	::ShowWindow(m_hWnd, SW_SHOW);
	::SendMessage(hWndParent, WM_NCACTIVATE, TRUE, 0L);
}

LPCTSTR CComboWndEx::GetWindowClassName() const
{
	return _T("ComboWnd");
}

void CComboWndEx::OnFinalMessage(HWND hWnd)
{
	m_pOwner->m_pWindow = NULL;
	m_pOwner->m_uButtonState &= ~ UISTATE_PUSHED;
	m_pOwner->Invalidate();
	delete this;
}

bool CComboWndEx::IsHitItem(POINT ptMouse)
{
	CControlUI* pControl = m_pm.FindControl(ptMouse);
	if(pControl != NULL) {
		LPVOID pInterface = pControl->GetInterface(DUI_CTR_SCROLLBAR);
		if(pInterface) return false;

		while(pControl != NULL) {
			IListItemUI* pListItem = (IListItemUI*)pControl->GetInterface(DUI_CTR_LISTITEM);
			if(pListItem != NULL ) {
				return true;
			}
			pControl = pControl->GetParent();
		}
	}
		
	return false;
}

LRESULT CComboWndEx::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if( uMsg == WM_CREATE ) {
		m_pm.SetForceUseSharedRes(true);
		m_pm.Init(m_hWnd);
		// The trick is to add the items to the new container. Their owner gets
		// reassigned by this operation - which is why it is important to reassign
		// the items back to the righfull owner/manager when the window closes.
		m_pLayout = new CVerticalLayoutUI;
		m_pLayout->SetManager(&m_pm, NULL, true);
		LPCTSTR pDefaultAttributes = m_pOwner->GetManager()->GetDefaultAttributeList(_T("VerticalLayout"));
		if( pDefaultAttributes ) {
			m_pLayout->ApplyAttributeList(pDefaultAttributes);
		}
		m_pLayout->SetInset(CDuiRect(1, 1, 1, 1));
		m_pLayout->SetBkColor(0xFFFFFFFF);
		m_pLayout->SetBorderColor(0xFFC6C7D2);
		m_pLayout->SetBorderSize(1);
		m_pLayout->SetAutoDestroy(false);
		m_pLayout->EnableScrollBar();
		m_pLayout->ApplyAttributeList(m_pOwner->GetDropBoxAttributeList());
		for( int i = 0; i < m_pOwner->GetCount(); i++ ) {
			m_pLayout->Add(static_cast<CControlUI*>(m_pOwner->GetItemAt(i)));
		}
		m_pm.AttachDialog(m_pLayout);
		m_pm.AddNotifier(this);
		return 0;
	}
	else if( uMsg == WM_CLOSE ) {
		m_pOwner->SetManager(m_pOwner->GetManager(), m_pOwner->GetParent(), false);
		RECT rcNull = { 0 };
		for( int i = 0; i < m_pOwner->GetCount(); i++ ) static_cast<CControlUI*>(m_pOwner->GetItemAt(i))->SetPos(rcNull);
		m_pOwner->SetFocus();
	}
	else if( uMsg == WM_LBUTTONDOWN ) {
		POINT pt = { 0 };
		::GetCursorPos(&pt);
		::ScreenToClient(m_pm.GetPaintWindow(), &pt);
		m_bHitItem = IsHitItem(pt);
	}
	else if( uMsg == WM_LBUTTONUP ) {
		POINT pt = { 0 };
		::GetCursorPos(&pt);
		::ScreenToClient(m_pm.GetPaintWindow(), &pt);
		if(m_bHitItem && IsHitItem(pt)) {
			PostMessage(WM_KILLFOCUS);
		}
		m_bHitItem = false;
	}
	else if( uMsg == WM_KEYDOWN ) {
		switch( wParam ) {
		case VK_ESCAPE:
			m_pOwner->SelectItem(m_iOldSel, true);
			EnsureVisible(m_iOldSel);
		case VK_RETURN:
			PostMessage(WM_KILLFOCUS);
			break;
		default:
			TEventUI event;
			event.Type = UIEVENT_KEYDOWN;
			event.chKey = (TCHAR)wParam;
			m_pOwner->DoEvent(event);
			EnsureVisible(m_pOwner->GetCurSel());
			return 0;
		}
	}
	else if( uMsg == WM_MOUSEWHEEL ) {
		int zDelta = (int) (short) HIWORD(wParam);
		TEventUI event = { 0 };
		event.Type = UIEVENT_SCROLLWHEEL;
		event.wParam = MAKELPARAM(zDelta < 0 ? SB_LINEDOWN : SB_LINEUP, 0);
		event.lParam = lParam;
		event.dwTimestamp = ::GetTickCount();
		if(m_pOwner->GetScrollSelect()) {
			m_pOwner->DoEvent(event);
			EnsureVisible(m_pOwner->GetCurSel());
			return 0;
		}
		else {
			m_pLayout->DoEvent(event);
			return 0;
		}
	}
	else if( uMsg == WM_KILLFOCUS ) {
		if( m_hWnd != (HWND) wParam ) PostMessage(WM_CLOSE);
	}

	LRESULT lRes = 0;
	if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

void CComboWndEx::EnsureVisible(int iIndex)
{
	if( m_pOwner->GetCurSel() < 0 ) return;
	m_pLayout->FindSelectable(m_pOwner->GetCurSel(), false);
	RECT rcItem = m_pLayout->GetItemAt(iIndex)->GetPos();
	RECT rcList = m_pLayout->GetPos();
	CScrollBarUI* pHorizontalScrollBar = m_pLayout->GetHorizontalScrollBar();
	if( pHorizontalScrollBar && pHorizontalScrollBar->IsVisible() ) rcList.bottom -= pHorizontalScrollBar->GetFixedHeight();
	int iPos = m_pLayout->GetScrollPos().cy;
	if( rcItem.top >= rcList.top && rcItem.bottom < rcList.bottom ) return;
	int dx = 0;
	if( rcItem.top < rcList.top ) dx = rcItem.top - rcList.top;
	if( rcItem.bottom > rcList.bottom ) dx = rcItem.bottom - rcList.bottom;
	Scroll(0, dx);
}

void CComboWndEx::Scroll(int dx, int dy)
{
	if( dx == 0 && dy == 0 ) return;
	SIZE sz = m_pLayout->GetScrollPos();
	m_pLayout->SetScrollPos(CDuiSize(sz.cx + dx, sz.cy + dy));
}

#if(_WIN32_WINNT >= 0x0501)
UINT CComboWndEx::GetClassStyle() const
{
	return __super::GetClassStyle() | CS_DROPSHADOW;
}
#endif
////////////////////////////////////////////////////////
IMPLEMENT_DUICONTROL(CComboUIEx)

CComboUIEx::CComboUIEx() 
	:m_pWindow(NULL)
{
}

bool CComboUIEx::Activate()
{
	if( !CControlUI::Activate() ) return false;
	if( m_pWindow ) return true;
	m_pWindow = new CComboWndEx();
	ASSERT(m_pWindow);
	m_pWindow->Init(this);
	if( m_pManager != NULL ) m_pManager->SendNotify(this, DUI_MSGTYPE_DROPDOWN);
	Invalidate();
	return true;
}
