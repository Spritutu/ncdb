#pragma once
//////////////////////////////////////////////////////////////////////////
///
#define MOVEWND_TIMERID	    UIMSG_USER+3 
#define ACTIVE_TIMERID	    UIMSG_USER+2  
#define WND_HEIGHT          130                   //���ڸ߶�
#define WND_WIDTH           335                   //���ڿ��
#define GAP_WIDTH           4                     //���ڼ����
#define GAP_HEIGHT          4                     //���ڼ��߶�
class CWarnWnd : public CBaseWnd
{
public:
	CWarnWnd(void);
	~CWarnWnd(void);
public:
	virtual void OnFinalMessage(HWND);
	//virtual CDuiString GetSkinFile();
	//virtual LPCTSTR GetWindowClassName(void) const;
	virtual void Notify(TNotifyUI &msg);
	virtual void InitWindow();
	static void LvWarnWnd(LPCTSTR pTitle);
	LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void OnTimer(UINT_PTR idEvent);
	void OnMoveWndTimer(UINT_PTR idEvent);
	void SetWndAttribute();
	void SetWndPos();
private:
	CButtonUI* m_pCloseBtn;
	CButtonUI* m_pBtn1;
	CButtonUI* m_pBtn2;
	CButtonUI* m_pBtn3;
	CLabelUI* m_pTitle;
	int wndHeight;
	int oneStepLength;   //�����ƶ�һ������
	int wndDistance;     //�����ڼ����
	HWND overStepWnd;
	int closeIndex;     //�رմ��ڵ�����
	int topIndex;       //���ر���������һ������������������ر������Ϸ�û�д��ڣ���Ϊǰһ�����Ϸ���
};