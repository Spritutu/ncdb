#pragma once
#include "afxwin.h"

class CDlgBase :
#ifdef M_DIALOG_EX
	public CDialogEx
#else
	public CDialog
#endif
{
public:
	CDlgBase(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	~CDlgBase(void);
public:
	/*-------------------- ���ΰ��� --------------------*/
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	bool SendMessageBtnOk(bool bPost = false);
	bool SendMessageBtnCancel(bool bPost = false);

	/*-------------------- ����ӿ� --------------------*/
	void EnableF4Close(bool bEnable) { bEnableF4Close = bEnable; }

public:
	operator HWND();

private:
	bool bEnableF4Close;
};
