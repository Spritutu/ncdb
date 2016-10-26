/***********************************************************************
 Copyright (c), 2012, Unicorn Tech. Co., Ltd.

 File name   : k_filepath.h
 Description : �ļ�·����
 Other       : 
 Version     : 1.0
 Author      : xuemingzhi
 Date        : 2014/06/23
 -----------------------------------------------------------------------
 History 1 
      Date   : 
      Author : 
      Modification : 
***********************************************************************/

#ifndef KERNEL_FILEPATH_H
#define KERNEL_FILEPATH_H

#include "k_STLString.h"
#include <WinBase.h>

/* �ļ�·����
*/
class KFilePath
{
public:
	KFilePath(LPCTSTR inSzPath = NULL);
	KFilePath(ConstSTLStringRef inStrPath);
	~KFilePath();

public:
	// ��̬-��ȡ�ļ�Ŀ¼�����ơ���׺��
	static STLString GetFileDirectory(ConstSTLStringRef inPath);
	static STLString GetFileName(ConstSTLStringRef inPath,bool inHasExtend);
	static STLString GetFileExtend(ConstSTLStringRef inPath);
	static bool      IsValidFileName(ConstSTLStringRef inFileName);
	// ��̬-�Ƿ�������Ч
	static bool      IsExist(ConstSTLStringRef inPath);
	static bool      IsDirectory(ConstSTLStringRef inPath);
	
public:
    LPCTSTR    cdat() { return path_.c_str(); }
	STLString& GetPath() { return path_; }
	STLString  GetFileDirectory();
	STLString  GetFileName(bool inHasExtend);
	STLString  GetFileExtend();
	bool       IsExist();
	bool       IsDirectory();
	STLString  GetMD5();

public:
	KFilePath& operator=(ConstSTLStringRef inPath);
	KFilePath  operator+(ConstSTLStringRef inPath);
	KFilePath& operator+=(ConstSTLStringRef inPath);
	operator STLString() { return GetPath(); }
    operator LPCTSTR() { return GetPath().c_str(); }

	// ���·��
public:
	static STLString GetCurrentDir(); // ��ȡ��ǰģ��Ŀ¼
	static STLString GetTempDir(); // ��ȡtempĿ¼

protected:
	static void _unified_format(STLString& inPath);
protected:
	STLString path_;
};

#endif // !KERNEL_FILEPATH_H