
// BinVersioner.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBinVersionerApp:
// �йش����ʵ�֣������ BinVersioner.cpp
//

class CBinVersionerApp : public CWinAppEx
{
public:
	CBinVersionerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBinVersionerApp theApp;