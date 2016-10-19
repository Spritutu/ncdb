#pragma once
//////////////////////////////////////////////////////////////////////////
///
//#include "NCChildWindow.h"
class CBaseWnd : public WindowImplBase
{
public:
	CBaseWnd();
	~CBaseWnd(void);
	static CBaseWnd *getInstance(HWND pWnd,char* caption,char* path,bool *btnStatus);
public:
	virtual void OnFinalMessage(HWND);
	virtual CDuiString GetSkinFile();
	virtual LPCTSTR GetWindowClassName(void) const;
	virtual void Notify(TNotifyUI &msg);
	virtual void InitWindow();
	virtual void SetWndSize(int cx,int cy);
	LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void SetAttr(char* temp);
private:
 	char* caption;
	char* path;
	bool sbClose;
	bool sbMax;
	bool sbMin;
	bool sbFeedback;
	bool sbOther;
	CControlUI* m_pLogo;
	CLabelUI* m_pTitle;
	CButtonUI* m_pFeedBack;
	CButtonUI* m_pMin;
	CButtonUI* m_pMax;
	CButtonUI* m_pClose;
	static CBaseWnd *s_pInstance;
};

static CDuiString CharToDuiString(const char* ch)
{
	CDuiString result;
	int num = MultiByteToWideChar(0, 0, ch, -1, NULL, 0);
	wchar_t *buffer = new wchar_t[num];
	MultiByteToWideChar(0, 0, ch, -1, buffer, num);
	result = buffer;
	delete[] buffer;
	buffer = NULL;
	return result;
}