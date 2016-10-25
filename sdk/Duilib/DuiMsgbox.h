#pragma once
#include "duilib\duibase.h"
#include "DataStruct\PiRect.h"

class CDuiMsgbox :
	public CDuiBase
{
public:
	enum ENUM_ICON_TYPE
	{
		t_done		= 0,
		t_warn			,
		t_error			,
	};
	enum ENUM_BTN_TYPE
	{
		bt_ok				= 0,	//ȷ��
		bt_ok_cancel			,	//ȷ��ȡ��
		bt_yes_no				,		//�Ƿ�
		bt_full
	};
	typedef map<CDuiMsgbox::ENUM_ICON_TYPE, LPCTSTR> MAP_PIC;

	CDuiMsgbox(LPCTSTR szTitle, LPCTSTR szContent, ENUM_ICON_TYPE enType, ENUM_BTN_TYPE enBtnType, HWND hParent = NULL);
	~CDuiMsgbox(void);
public:
	/*------------------------------------------------------------
			fun:	��ʼ��ͼƬ, ���õ���ʱ��Ҫ�Ƚ��г�ʼ��
			ret:	
			param: 
			remark:	
	------------------------------------------------------------*/
	static void InitPic(const MAP_PIC& mapPic);
	/*------------------------------------------------------------
			fun:	
			ret:	�����û�����İ�ťID
			param: 
			remark:	
	------------------------------------------------------------*/
	static UINT Popup(LPCTSTR szTitle, LPCTSTR szContent, ENUM_ICON_TYPE enType, ENUM_BTN_TYPE enBtnType, HWND hParent = NULL);
	static UINT PopupFull( LPCTSTR szBkImg, LPCTSTR szText, HWND hParent = NULL);
	void SetFull( LPCTSTR szBkImg, LPCTSTR szText);

	void AdjustBtnClose();
	void SetContentCx( int nCx );
	void SetSize( CDuiSize szWnd );
private:
	virtual void OnShow(BOOL bShow, int nState);
	virtual void InitWindow();

	void ChangeTwoBtnPos();

	virtual void OnClick(TNotifyUI& msg);
	/*------------------------------------------------------------
			fun:	������Сʱ�Զ�����һЩ�̶��ؼ�(��رհ�ť)��λ��
			ret:	
			param: 
			remark:	
	------------------------------------------------------------*/
	void ChangeSize( int nCx, int nCy );
	CControlUI* CreateControl(LPCTSTR pstrClass);
	CDuiString		m_strTitle;
	CDuiString		m_strContent1;
	CDuiString		m_strFullPic;

	ENUM_ICON_TYPE		m_enIconType;
	ENUM_BTN_TYPE		m_enBtnType;
	int					m_nContentCx;
	CDuiSize			m_szWindow;
};
