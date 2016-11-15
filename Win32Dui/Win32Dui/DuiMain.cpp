#include "DuiMain.h"
#include "PiHeadKernel.h"
#include "UI\PiUITool.h"


CDuiMain::CDuiMain()
{
	//m_SkinFolder	= _T("34");
	m_SkinFile		= _T("skin.xml");
	m_WndClassName		= _T("CN_TestMain");
}


CDuiMain::~CDuiMain()
{
}

LRESULT CDuiMain::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if ((m_pSendEdit != NULL) && m_pSendEdit->IsFocused()
		&& (uMsg == WM_KEYDOWN) && (wParam == 'V') && (lParam & VK_CONTROL))	// ������Ϣ���Ctrl+V��Ϣ
	{
		m_pSendEdit->Paste();
		return TRUE;
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

void CDuiMain::InitWindow()
{
	m_pSendEdit = static_cast<CRichEditUI*>(m_pm.FindControl(_T("richSend")));

}

void CDuiMain::OnClick(TNotifyUI& msg)
{
	CDuiString strName = msg.pSender->GetName();
	if (strName == _T("btn_test"))
	{
		tstring strPath = CPIUITool::SelectDirectory(GetHWND(), _T("e:\\work\\svn\\nc\\src\\"), _T("��ѡ���"));
		OutInfo(_T("select dir:"), strPath);
		MessageBox(NULL, strPath.c_str(), _T("�û�ѡ����"), NULL);

	}
}
