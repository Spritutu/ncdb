#include "StdAfx.h"
#include "MainHWnd.h"



/******************************************************************** 
created:    2010/03/09 
created:    9:3:2010   10:10 
file base:  CWindowIterator 
file ext:   cpp 
author:     zhangwf 

purpose:    ��װö�ٴ����� 
*********************************************************************/  
//////////////////////////////////////////////////////////////////////////  
#include <Windows.h>  
#include "MainHWnd.h"
//////////////////////////////////////////////////////////////////////////  
// ���캯��  
CWindowIterator::CWindowIterator()  
{  
	// ��ʼ������  
	m_hWndArray.clear();  
	m_nCurrentWndIndex = 0;  
}  

// ��������  
CWindowIterator::~CWindowIterator()  
{  

}  

//////////////////////////////////////////////////////////////////////////  
// �ӿں���  
// ��ô�������  
unsigned long CWindowIterator::GetWndCounts()  
{  
	return m_hWndArray.size();  
}  

// ��õ�һ�����ھ��  
HWND CWindowIterator::First()  
{  
	if (m_hWndArray.size() != 0)  
	{  
		m_nCurrentWndIndex = 0;  
		return m_hWndArray[m_nCurrentWndIndex];  
	}  

	return NULL;  
}  

// �����һ�����ھ��  
HWND CWindowIterator::Next()  
{  
	if (m_nCurrentWndIndex+1 < m_hWndArray.size())  
	{  
		m_nCurrentWndIndex += 1;  
		return m_hWndArray[m_nCurrentWndIndex];  
	}  

	return NULL;  
}  

// ����������ô��ھ��  
HWND CWindowIterator::GetHWnd(unsigned long wndIndex)  
{  
	if (wndIndex < m_hWndArray.size())  
	{  
		return m_hWndArray[wndIndex];  
	}  

	return NULL;  
}  

void CWindowIterator::EnumWnds()  
{  
	// ����ϴ�����  
	m_hWndArray.clear();  

	// ö�����д���  
	::EnumWindows(EnumWndProc, (LPARAM)this);  
}  

//////////////////////////////////////////////////////////////////////////  
// �ǽӿں���  
// ö�ٴ��ڻص�����  
BOOL CALLBACK CWindowIterator::EnumWndProc(HWND hwnd, LPARAM lp)  
{  
	return ((CWindowIterator*)lp)->AddWnd(hwnd);  
}  

// virtual enumerator  
BOOL CWindowIterator::AddWnd(HWND hwnd)  
{  
	if (IsTargetWnd(hwnd) == TRUE)  
	{  
		m_hWndArray.push_back(hwnd);          
	}  

	return TRUE;  
}  
//////////////////////////////////////////////////////////////////////////  
//////////////////////////////////////////////////////////////////////////  
// �����������ھ����  
// ���캯��  
CMainHWnd::CMainHWnd()  
:CWindowIterator()  
{  
	m_pid = 0;  
	m_bTop = FALSE;
	m_strTitle.clear();
	m_strClassName.clear();
	m_bVisible = FALSE;
}  

// ���ι��캯��  
CMainHWnd::CMainHWnd(unsigned long pid)  
:CWindowIterator()  
{  
	m_pid = pid;  
	m_strTitle.clear();
	m_strClassName.clear();
	m_bVisible = FALSE;
	m_bTop = FALSE;
	EnumWnds();  
}  

// ��������  
CMainHWnd::~CMainHWnd()  
{  

}  

//////////////////////////////////////////////////////////////////////////  
// �ӿں���  
void CMainHWnd::EnumWndsByPid(DWORD pid, const BOOL& bVisible, const BOOL& top)  
{  
	m_pid = pid;  
	m_bVisible = bVisible;
	m_bTop = top;
	EnumWnds();  
}  

void CMainHWnd::EnumWndsByTitle(const std::wstring& title, const std::wstring& classname, const BOOL& bVisible, const BOOL& top)
{
	m_strTitle = title;
	m_strClassName = classname;
	m_bVisible = bVisible;
	m_bTop = top;
	EnumWnds();
}

//////////////////////////////////////////////////////////////////////////  
// �ǽӿں���  
BOOL CMainHWnd::IsTargetWnd(HWND hwnd)  
{  
	// �����ҿɼ�  
	if (((m_bTop && ::GetParent(hwnd)==NULL)||!m_bTop) && ((m_bVisible && ::IsWindowVisible(hwnd)==TRUE)||(!m_bVisible && IsWindow(hwnd))))   
	{        
		if (m_pid > 0)
		{
			DWORD pidwin;  
			::GetWindowThreadProcessId(hwnd, &pidwin);  
			if (pidwin == m_pid)  
			{  
				return TRUE;  
			}       
		}
		else if (m_strTitle.length() > 0)
		{
			DWORD pidwin = 0;  
			::GetWindowThreadProcessId(hwnd, &pidwin);  
			if (GetCurrentProcessId() == pidwin)
			{
				return FALSE;
			}
			TCHAR tszTitle[128] = {0}, tszClass[128] = {0};
			//if(::SendMessage(hwnd, WM_GETTEXT, _countof(tszTitle)-1, (LPARAM)tszTitle))
			if (::GetWindowText(hwnd, tszTitle, _countof(tszTitle)-1)
				&& ::GetClassName(hwnd, tszClass, _countof(tszClass)-1))
			{

				std::wstring title(tszTitle);
				if(title.find(m_strTitle)==0 && !lstrcmp(tszClass, m_strClassName.c_str())){
					return TRUE;  
				}
			}
		}
	}  

	// ����Ŀ�괰��  
	return FALSE;  
}  