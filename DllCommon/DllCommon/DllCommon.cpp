#include "DllCommon.h"
#include <tchar.h>
#include "UI\PiUITool.h"
//ARR_STRING* g_pFileLst = NULL;	//ѡ�����ļ����б� ��һ��ΪĿ¼�� �ڶ�����ʼΪ�ļ�

NCCOMMON_API int NCCOMMON_CALL SelectFileOrDir(tagSELECT_FILE_DIR* pTag)
{
	tstring  strSelectPath;
	int nSelect = CPIUITool::SelectFileOrDir(pTag, strSelectPath);
	//g_pFileLst = pTag->pFileLst;
	return nSelect;
}

NCCOMMON_API const wchar_t* QuerySelectFile(int nIndex)
{
	return CPIUITool::QuerySelectFile((UINT)nIndex);
	
}

NCCOMMON_API bool NCCOMMON_CALL PopSaveDialog(tagSAVE_FILE* pTag, wchar_t* szPath)
{
	if (!szPath)
	{
		return false;
	}
	tstring strPath = CPIUITool::PopSaveDialog(pTag).c_str();
	if (strPath.length() >= MAX_PATH)
	{
		_tcscpy_s(szPath, MAX_PATH, _T("buf too small"));
		return false;
	}
	_tcscpy_s(szPath, MAX_PATH, strPath.c_str());
	return strPath.length() > 0;
}

