
// UseNXwke.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUseNXwkeApp: 
// �йش����ʵ�֣������ UseNXwke.cpp
//

class CUseNXwkeApp : public CWinApp
{
public:
	CUseNXwkeApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CUseNXwkeApp theApp;