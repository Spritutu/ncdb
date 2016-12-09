// DllCommonMFC.h : DllCommonMFC DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include <windows.h>
#include <string>
#include "UI\PiUITool.h"
using namespace std;

#if defined(__cplusplus)
#define NCCOMMON_EXTERN_C extern "C"
#else
#define NCCOMMON_EXTERN_C
#endif

#ifdef DLLCOMMON_EXPORTS
#define NCCOMMON_SYMBOL __declspec(dllexport)
#else
#define NCCOMMON_SYMBOL __declspec(dllimport)
#endif // DLLCOMMON_EXPORTS

#define NCCOMMON_API NCCOMMON_EXTERN_C NCCOMMON_SYMBOL
#define NCCOMMON_CALL _cdecl



// CDllCommonMFCApp
// �йش���ʵ�ֵ���Ϣ������� DllCommonMFC.cpp
//

class CDllCommonMFCApp : public CWinApp
{
public:
	CDllCommonMFCApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};





typedef CPIUITool::tagSELECT_FILE_DIR	tagSELECT_FILE_DIR;

NCCOMMON_API int NCCOMMON_CALL SelectFileOrDir(tagSELECT_FILE_DIR* pTag);
NCCOMMON_API const wchar_t* NCCOMMON_CALL QuerySelectFile(int nIndex);
/************************************************************************
fun:	��������Ի���
param:	szPath: �û�ѡ����·���� ��������Ҫ���ⲿ����ã� ��СΪMAX_PATH  260;
memo:
************************************************************************/
NCCOMMON_API bool NCCOMMON_CALL PopSaveDialog(tagSELECT_FILE_DIR* pTag, wchar_t* szPath);