
// UseNCCef.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

class CNCCef;
// CUseNCCefApp: 
// �йش����ʵ�֣������ UseNCCef.cpp
//

class CUseNCCefApp : public CWinApp
{
public:
	CUseNCCefApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
public:
	CNCCef*			m_pCef;
	virtual int ExitInstance();
};

extern CUseNCCefApp theApp;