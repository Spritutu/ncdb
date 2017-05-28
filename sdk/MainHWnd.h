#pragma once

#ifndef _CWINDOW_ITERATOR_ZWF_H_  
#define _CWINDOW_ITERATOR_ZWF_H_  
//////////////////////////////////////////////////////////////////////////  
#include <vector>  
using namespace std;  
//////////////////////////////////////////////////////////////////////////  
class CWindowIterator  
{  
public:  
	// ������������  
	CWindowIterator();  
	~CWindowIterator();  

public:  
	// �ӿں���  
	void EnumWnds();                        // ö�ٴ���  
	unsigned long GetWndCounts();           // ��ô�������  
	HWND First();                           // ��õ�һ�����ھ��  
	HWND Next();                            // �����һ�����ھ��  
	HWND GetHWnd(unsigned long wndIndex);   // ����������ô��ھ��         

protected:  
	vector<HWND> m_hWndArray;               // ���ö�ٵõ��Ĵ��ھ��  
	unsigned long m_nCurrentWndIndex;       // ��ǰ���ھ��  

	// ö�ٴ��ڻص�����  
	static BOOL CALLBACK EnumWndProc(HWND hwnd, LPARAM lp);  

	// virtual enumerator  
	virtual BOOL AddWnd(HWND hwnd);  

	// override to filter different kinds of windows  
	virtual BOOL IsTargetWnd(HWND hwnd) {return TRUE;}  

};  
//////////////////////////////////////////////////////////////////////////  
//////////////////////////////////////////////////////////////////////////  
// �������������ֻࣨ��ȡ���̵������ڣ�  
class CMainHWnd : public CWindowIterator  
{  
public:  
	// ������������  
	CMainHWnd();  
	CMainHWnd(unsigned long pid);  
	~CMainHWnd();  

public:  
	// �ӿں���  
	void EnumWndsByPid(DWORD pid, const BOOL& bVisible = TRUE, const BOOL& top = TRUE);  
	void EnumWndsByTitle(const std::wstring& title, const std::wstring& classname, const BOOL& bVisible = TRUE, const BOOL& top = TRUE);  
protected:  
	DWORD m_pid; 
	BOOL  m_bVisible, m_bTop;
	std::wstring m_strTitle;
	std::wstring m_strClassName;
	virtual BOOL IsTargetWnd(HWND hwnd);  

};  
//////////////////////////////////////////////////////////////////////////  
#endif
