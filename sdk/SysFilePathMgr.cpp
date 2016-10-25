#include "StdAfx.h"
#include "SysFilePathMgr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/************************************************************************/
/* 
VC ��ȡϵͳ�����ļ��е�·���磺ϵͳĿ¼�������

qtom:
TCHAR MyDir[_MAX_PATH];  
SHGetSpecialFolderPath(this->GetSafeHwnd(),MyDir,CSIDL_APPDATA,0);
AfxMessageBox(MyDir);
���е���������CSIDL_APPDATA����Ϊ���µ�ֵ��

CSIDL_BITBUCKET ����վ
CSIDL_CONTROLS �������
CSIDL_DESKTOP Windows ����Desktop
CSIDL_DESKTOPDIRECTORY Desktop��Ŀ¼
CSIDL_DRIVES �ҵĵ���
CSIDL_FONTS ����Ŀ¼
CSIDL_NETHOOD �����ھ�
CSIDL_NETWORK �����ھ�����Ŀ¼
CSIDL_PERSONAL �ҵ��ĵ�
CSIDL_PRINTERS ��ӡ��
CSIDL_PROGRAMS ������
CSIDL_RECENT ����򿪵��ĵ�
CSIDL_SENDTO �����͵����˵���
CSIDL_STARTMENU �����������˵���
CSIDL_STARTUP ����Ŀ¼
CSIDL_TEMPLATES �ĵ�ģ��
*/
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
//

tstring CSysFilePathMgr::GetProfileDocumentPath()
{
// 	tstring strProfileDocumentPath;
// 
// 	TCHAR szDocument[MAX_PATH] = {0};
// 	memset(szDocument, 0, sizeof(szDocument));
// 
// 	LPITEMIDLIST pidl = NULL;
// 	SHGetSpecialFolderLocation(NULL, CSIDL_PERSONAL, &pidl);
// 	if (pidl && SHGetPathFromIDList(pidl, szDocument))
// 	{
// 		strProfileDocumentPath = szDocument;
// 	}
// 
// 	return strProfileDocumentPath;
	return GetSysSpecialFolder(CSIDL_PERSONAL);
}

tstring CSysFilePathMgr::GetSysFontFolder()
{
	return GetSysSpecialFolder(CSIDL_FONTS);
}

tstring CSysFilePathMgr::GetSysSpecialFolder(int csidl)
{
	tstring strProfileDocumentPath;

	TCHAR szDocument[MAX_PATH] = {0};
	memset(szDocument, 0, sizeof(szDocument));

	LPITEMIDLIST pidl = NULL;
	SHGetSpecialFolderLocation(NULL, csidl, &pidl);
	if (pidl && SHGetPathFromIDList(pidl, szDocument))
	{
		strProfileDocumentPath = szDocument;
	}

	return strProfileDocumentPath;
}

tstring CSysFilePathMgr::GetSysTempFolder()
{
// 	tstring strExpand = _T("%TEMP%");
// 
// 	tstring strTempFld;
// 	ExpandEnvironmentStrings(strExpand, strTempFld.GetBuffer(MAX_PATH), MAX_PATH);
// 
//	return strTempFld;

	tstring strTempFld;

	tstring strExpand(_T("%TEMP%"));
	TCHAR szBuffer[MAX_PATH];
	ExpandEnvironmentStrings(strExpand.c_str(), szBuffer, MAX_PATH);
	strTempFld = szBuffer;

	return strTempFld;
}

tstring CSysFilePathMgr::ExpandString(tstring strOriginal, HMODULE hModule)
{
	const int macro_prefix_length = 2;
	const int macro_subfix_length = 1;

	tstring expanded;
	for (;;)
	{
		int start_pos(strOriginal.find(_T("$(")));
		if (-1 == start_pos)
		{
			expanded = strOriginal;
			break;
		}

		int end_pos(strOriginal.find(_T(")"), start_pos));
		if (-1 == end_pos)
		{
			expanded = strOriginal;
			break;;
		}

		tstring macro(strOriginal.substr(start_pos+macro_prefix_length, end_pos-start_pos-macro_prefix_length));
		expanded = strOriginal.substr(0, start_pos);

		/*if (0 == macro.Compare(_T("ProgramDir")))
		{
		}*/
	}

	return _T("");
}

tstring CSysFilePathMgr::GetUserAppData()
{
	return GetSysSpecialFolder(CSIDL_APPDATA);
}

tstring CSysFilePathMgr::GetDesktop()
{
	return GetSysSpecialFolder(CSIDL_DESKTOP);
}
