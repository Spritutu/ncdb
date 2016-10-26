#pragma once
#include <string>
#include <sys/stat.h>
#include "piTypeDef.h"
#include <shellapi.h>
using std::string;
using std::wstring;
class CFileStrOp
{
public:
	
	CFileStrOp(void);
	~CFileStrOp(void);
public:
	enum TIME_TYPE{TYPE_CREATE, TYPE_ACCESS, TYPE_MODIFY};
	//���ܣ���·�����ó� �� "\"��β���ַ��� e.g: "C:\23" -> "C:\23\"
	//
	static string AddDirEndingChar(const string& strPath);
	
	static wstring AddDirEndingChar(const wstring& strPath);

	//////////////////////////////////////////////////////////////////////////
	//���ܣ���ȡָ���ļ����ĺ�׺,������ .   e.g:  a.txt ->  txt
	static string GetPostFix(const string& fileName);
	static string GetDotSuffix(const string& fileName);
    
    /************************************************************************/
    /*  fun: �������Ŀ¼    eg: c:\1\2\3    , ���иú�����, �ܱ�֤��Ŀ¼����, ���ǳ���
    /************************************************************************/
	static bool CreateDeepDir(tcpchar pDir);

    //�ж�ָ���ļ�/Ŀ¼�Ƿ����
	static bool IsExist(tcpchar pFile);
    /************************************************************************/
    /*  fun: ��ȡ�ļ�������һ�����ļ����� ���ڷָ��ļ� e.g: a.txt -> a_1.txt, a_1.txt -> a_2.txt
    /************************************************************************/
    static string CFileStrOp::GetNextFileName(const char* pFile);
	//////////////////////////////////////////////////////////////////////////
	//���ܣ�����ļ�����׺����λ��(�����)
	//�������ļ���(����·��)
	//��ע���� . ��λ�ô��� ���һ��\ ��λ�ã��ļ��������к�׺   c:\34.3\Test.txt
	static string::size_type GetPostFixPos(const string& fileName);

	//////////////////////////////////////////////////////////////////////////
	//���ܣ�����ļ���Ŀ¼�ļ���
	//�������ļ���(����·��)
	static string ExtractFileDir(const string& fileName);
    /************************************************************************/
    /*  fun: Get Current execute  file 's Dir of the current process
        remark: contain the '\' end
    /************************************************************************/
    static tstring GetCurrentDir();
    
    /************************************************************************/
    /*  fun: Get Current execute  file 's Title, eg: c:\2.txt -> 2
    /************************************************************************/
    static string CFileStrOp::GetCurrentExeTitle();
	//////////////////////////////////////////////////////////////////////////
	//���ܣ�����ļ���
	//����������·���ļ���
	static string ExtractFileName(const string& fileName);

	//////////////////////////////////////////////////////////////////////////
	//���ܣ�����ļ��ı���  e.g:   c:\�ļ�.txt  ->  �ļ�
	//����������·���ļ���
	static string ExtractFileTitle(const string& fileName);

	/*------------------------------------------------------------
			fun:	�ļ���С����ת������Ӧ��λ���ַ���,�� 1024 => "1k"
			ret:	szUnit:ָ���ַ�����ʽ, ��˳��ָ��С����λ���ͺ�׺, ��"^"����ÿһ��
						. ��: "0# byte^0# KB^0# MB^0# GB"
							2# byte ��ʾ 2λС�� ��ֵ��+" byte"��׺
			param: 
			remark:	
	------------------------------------------------------------*/
	static tstring FileSizeSmartSwitch(LLONG dwSize, tcpchar szUnit = NULL);

	/************************************************************************/
	/*	fun: ����ļ�/��ͼ��                                                                     */
	/************************************************************************/
	static SHFILEINFOA GetFileIcon(const CHAR* path);



	/***********************************************************************
		�ļ���Ϣ���
	***********************************************************************/
	static struct _stat GetFileStatusInfo(const char* pFile);

	/**************
	* ��ȡ�ļ���С�����Ϊ�ļ������СΪ0
	*/
	static DWORD GetFileSize(tcpchar szFile);

	//��֧��fat32����
	static SYSTEMTIME GetFileCreateTime(const char* pFile);
	static SYSTEMTIME GetFileAccessTime(const char* pFile);
	static SYSTEMTIME GetFileModifyTime(const char* pFile);

	static string GetFileCreateTimeStr(const char* pFile);
	static tm GetFileTime(const char* pFile, TIME_TYPE type);
protected:

private:
	
};
