#pragma once
#include "PiTypeDef.h"

class CPiIrregularWindow
{
public:
	CPiIrregularWindow(void);
	~CPiIrregularWindow(void);
	bool UpdateLayeredWnd();
	bool SetTransWnd( HWND hWnd, LPCTSTR szPic = NULL);
	bool BeginDrawLayer();
	HDC HdcTrans() const { return m_hdcMem; }
	bool CreateIrregularWindow(tcpchar szPic);
	bool DestroyIrregularWindow();
	bool SetLayeredStyle( HWND hWnd );
	operator HWND(){return m_hWnd;}
protected:
	virtual bool RegisterWindowClass();
	virtual bool Create();
	static LRESULT CALLBACK  __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
private:
	HWND		m_hWndDist;	//͸���Ĵ�����
	HDC			m_hdcMem;
	
	HBITMAP		m_bmMem;

	SIZE		m_sizeWindow;	//ͼƬ����
	RECT		m_rcWindow;		
	tstring		m_strPicBk;			//����ͼ, ÿ�λ��ƶ����Ȼ�����

	HWND m_hWnd;

};
