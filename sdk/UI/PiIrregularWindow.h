#pragma once
#include "PiTypeDef.h"

class CPiIrregularWindow
{
public:
	CPiIrregularWindow(void);
	~CPiIrregularWindow(void);
	/************************************************************************
			�麯��
	************************************************************************/
protected:
	/*------------------------------------------------------------
		fun:	��ʾǰ����, ��ʹ��m_hdcMem��������Ҫ��ʾ������
		ret:	
		param: 
		remark:	
	------------------------------------------------------------*/
	virtual bool OnBeginDrawLayer();

public:
	bool CreateIrregularWindow(tcpchar szPic);
	bool CreateIrregularWindow(UINT nCX, UINT nCY);
	bool DestroyIrregularWindow();
	bool UpdateLayeredWnd();
	bool Update();

	HDC HdcTrans() const { return m_hdcMem; }
	operator HWND(){return m_hWnd;}
protected:
	//����false, ��������Ϣ��Ĭ�ϴ�����
	virtual DWORD HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandle);
	bool SetTransWnd( HWND hWnd, LPCTSTR szPic = NULL);
	bool SetLayeredStyle( HWND hWnd );
	bool BeginDrawLayer();
	bool CreateMemDC();
	virtual bool RegisterWindowClass();
	virtual bool _Create();
	static LRESULT CALLBACK  __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
protected:
	HWND		m_hWndDist;	//͸���Ĵ�����
	HDC			m_hdcMem;	//Ҫ���Ƶ����������dc
	
	HBITMAP		m_bmMem;

	
	SIZE		m_sizeWindow;	
	RECT		m_rcWindow;		
	tstring		m_strPicBk;			//����ͼ, ÿ�λ��ƶ����Ȼ�����

	HWND m_hWnd;

};
