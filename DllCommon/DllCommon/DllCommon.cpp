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

