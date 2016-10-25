#ifndef _IRREGULARWINDOW_H_
#define _IRREGULARWINDOW_H_
/**
  * ����������
*/

#include <windows.h>
#include <string>
#include <tchar.h>
#include <assert.h>

#ifndef __String
	#ifdef UNICODE
		#define __String wstring
	#else
		#define __String string
	#endif
#endif


using namespace std;

const DWORD c_dwTransColor = 0x00ff00ff;

class CIrregularWindow
{
public:

	CIrregularWindow(const TCHAR* pBackImgFullPath,DWORD dwAttachWndTransColor = c_dwTransColor);

	//���Ӵ���
	bool AttachWindow(HWND hWnd);
	bool SetTransWnd(HWND hWnd);
	//����ͼƬ(ȫ·�� png)
	void SetBackground(const TCHAR* pBackImgFullPath);
	static void SetBackground(HWND hWnd, const TCHAR* pBackImgFullPath);
	static void UpdateLayeredWnd();


	//һ����� �ǲ��õ���������� ����������� 
	//�����ӵĴ�����Ӵ��� ��ʾ����ȫ����� ����Ҫ�������ֵ
	void SetAttachWndTransColor(DWORD dwColor);
	void SetTransSelf(DWORD dwColor);
	HWND GetHandle(){return m_hWnd;}

	void CenterWindow();

	static void InitGDIplus();

	static void UnInitGDIplus();
	HWND CreateBaseTransparentWnd();
	static void SetWndTransColor( HWND hWnd, COLORREF nColor);
	static bool SetLayeredStyle( HWND m_hWnd );

protected:

	virtual bool RegisterWindowClass();

	virtual bool Create();

public:

private:

	static LRESULT CALLBACK  __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual bool HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK __HookProc(int nCode,WPARAM wParam,LPARAM lParam);
	static ULONG_PTR gdiplusToken;

	static HHOOK hhk;
	static CIrregularWindow*		g_pIrrglWnd;
protected:

	HWND m_hWnd;
	//�����ӵĴ���ľ��	
	HWND m_hAttachWnd;

	DWORD m_dwAttachWndTransColor;

	//����ͼƬ(png)
	__String m_strBackImg;
};

#endif