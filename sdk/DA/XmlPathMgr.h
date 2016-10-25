#pragma once

class CXmlPathMgr
{
public:
	static CString GetUserSettingFolder(BOOL bCreate = TRUE);				// �û�����Ŀ¼
	static CString GetUserSettingXmlPath();				// �û�����XML

	static CString GetUserCollectXmlFolder(BOOL bCreate = TRUE);			// �û��ռ�Ŀ¼

	static CString GetUpdateFolder(BOOL bCreate = TRUE);	// �����������Ŀ¼
	static CString GetUpdateXmlPath();					// �����������XML

    static CString GetSoftSettingFolder(BOOL bCreate = TRUE);	// �������Ŀ¼
    static CString GetSoftSettingXmlPath();					// �������XML

    static CString GetVideoXmlFolder(BOOL bCreate = TRUE);					// ¼������Ŀ¼
    static CString GetVideoXmlPath();										// ¼������XML

	static CString GetUserDataFolder(BOOL bCreate = TRUE);					// ��ȡ�û��������Ŀ¼
	static CString GetUserHeadPath();										// ��ȡ�û�ͷ��·��

	static CString GetDriverFolder(LPCTSTR vid,LPCTSTR pid,BOOL bCreate = FALSE);// ��ȡ����Ŀ¼

	static CString GetDownloadTempFolder(BOOL bCreate = TRUE);				// %TEMP%/Unicorn/PaintAid/Download
	static CString GetUploadTempFolder(BOOL bCreate = TRUE);				// %TEMP%/Unicorn/PaintAid/Upload
};