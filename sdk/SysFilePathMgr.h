#pragma once
#include "PiTypeDef.h"
class CSysFilePathMgr
{
public:
	static tstring GetProfileDocumentPath();			// ��á��ҵ��ĵ���·��
 	static tstring GetSysTempFolder();					// ���ϵͳTEMPĿ¼·��
//	static tstring GetSysTempFolder();					// ���ϵͳTEMPĿ¼·��
	static tstring GetSysFontFolder();					// ���ϵͳFontĿ¼·��
	static tstring GetUserAppData();					//��ȡAPPDATAĿ¼
	static tstring GetDesktop();					//��ȡAPPDATAĿ¼
protected:
	static tstring ExpandString(tstring strOriginal, HMODULE hModule = NULL);

	static tstring GetSysSpecialFolder(int csidl);				// ��ȡϵͳ�����ļ��е�·���磺ϵͳĿ¼�������
};