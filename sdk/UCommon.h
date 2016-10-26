#pragma once

#include <afxtempl.h>
#include "PiTypeDef.h"

#define SAFEDELETE(ptr) if (ptr) {delete ptr; ptr = NULL;}
#define SAFEDELETEARRAY(ptr) if (ptr) {delete[] ptr; ptr = NULL;}

class CEnumFileParam
{
public:
	CEnumFileParam(){};
	virtual ~CEnumFileParam() {};

public:
	CString strName;
	CString strPath;
};

class CFileUtil
{
public:
	static BOOL IsFileExist(CString strFilePath);
	static BOOL EnumFolderFile(CString strPath, CArray<CEnumFileParam, CEnumFileParam&>& arrFileList);
	static BOOL EnumFolder(CString strPath, CArray<CEnumFileParam, CEnumFileParam&>& arrFileList);
	static bool IsFileNameValid(const TCHAR* FileName);			// ???????

	static BOOL CopyFile(CString& szSrcPath, CString& szDistPath);		// ���ļ���Src���Ƶ�Dist
	static BOOL DeleteFile(CString& szSrcPath);				// ɾ���ļ�
    static BOOL Rename(CString szSrcPath, CString szDistPath );
};

class CFolderUtil
{
public:
	static CString GetExePath();						// ??EXE????
	static CString GetExeFoloder();						// ??EXE????
	static CString GetPaUserMainFolder();				// ?????????(%TEMP%/../Unicorn/PaintAid)
	static CString GetPaTempFolder();					// ??????TEMP??(%TEMP%/Unicorn/PaintAid)

public:
	static CString BrowseFolder();							// ????
	static CString BrowseFolder(HWND hOwner, CString strSetStartPath);	// ????
};

class CWebMgr
{
public:
	static void OpenURL(CString strURL);						// ??URL
	static CString GetHtmlFilePath(LPCTSTR pszURL);				// ??HTML??????
};

// ?????
class CDirectoryUtil
{
public:
    static bool CreateMultipleDirectory(tcpchar strFileFolder);	// �����༶Ŀ¼
};

// ��������
class CPowerBootMgr
{
public:
	static BOOL PowerBoot(BOOL bPower, CString strExePath);
};