#pragma once
#include "PiTypeDef.h"
class CPathLight
{
public:
    CPathLight();
    CPathLight(tcpchar szPath);
	CPathLight(const tstring& strPath);
    //CPathLight(const CPathLight& Path);
    ~CPathLight(void);
public:
	tstring AddSubSession(tcpchar szTitle);
	tstring AddSubSession(const tstring& szTitle);
	bool IsFileExist();

	bool SetPath(const tstring& strPath);
    const tstring& GetPath();
    bool GoParent();
    tstring GetCurPos();
    /************************************************************************
        fun:    ���û�е���GoParent, ���β�Ĳ���(�����ļ���)�ᱻ����Ŀ¼�����޸�
        remark:
    ************************************************************************/
    bool ModifyCurDirName( const tstring& strNameNew );
    bool SyncCache();
    bool ModifyFileName( const tstring& strNewName );
	tstring GetExt();
	operator tstring() const;
    operator tcpchar();

	CPathLight operator +(tcpchar szPath);
	CPathLight operator +(StringCRef szPath);
	CPathLight operator +(int nValue);
	CPathLight& operator +=(tcpchar szPath);
	CPathLight& operator +=(int nValue);
	CPathLight& operator +=(StringCRef szPath);
	CPathLight& operator =(tcpchar szPath);
	bool RenameTitle( StringCRef nameNew );
	bool RenameName( StringCRef nameNew );
	/*------------------------------------------------------------
			fun:	��ȡ�ļ���md5
			ret:	
			param: 
			remark:	�ļ���С���ܳ���200M
	------------------------------------------------------------*/
	tstring GetMD5();
	tstring GetParentPathFromPath(bool bSlash = false);
	tstring GetFileName();


	static tstring GetSelfModulePath();
	static tstring GetSelfModuleFolder();

    //�ж��ļ��Ƿ����
    static tstring AddSub(tcpchar szDir, tcpchar szFile);    
    static bool IsFileExist(tcpchar szPath);

/************************************************************************
        fun:    ȥ����β���ļ��� ��б��
        param: 
        remark: ���ֽṹ
                1. ���β����б��,��ȥ��, ��������
                2. ȥ�ļ���(�������޺�׺), ��ȥб��
                3. ֻʣ�̷�, ����β��б��
************************************************************************/
    static tstring GetParentPathFromPath( tcpchar szPath , bool bSlash = false);
    static tstring GetParentDirName(tcpchar szPath);
    //��ȡ���һ�ε��ļ���, ���β���ǿո�, ��ȥ��, �ڻ�ȡ
    static tstring GetDirName( tcpchar szPath );
    
	/************************************************************************
            fun: ��ȡ�ļ���׺, ��.���ַ�
            param: 
            remark: 
    ************************************************************************/
	static tstring GetExt(StringCRef strPath);
	/************************************************************************
            fun: ��ȡ�ļ���׺, �������ַ�
            param: 
            remark: 
    ************************************************************************/
	static tstring GetSuffixName(StringCRef strPath);
	tstring SetSuffixName(tcpchar szSuffix);

	static tstring GetFileTitleFromPath( tcpchar szPath );

    /************************************************************************
        �ļ�ö��                                                                          
    ************************************************************************/    
    typedef bool (*EnumerateFunc) (tcpchar lpFileOrPath, void* pUserData );
    /************************************************************************
            fun: 
            param: ����3:bool, true->�����ļ�, false-> ����Ŀ¼
            remark: 
    ************************************************************************/
	
	static bool FileEnumeration(tcpchar lpPath, bool bRecursion, bool bEnumFiles, bool bFindRecursionDir, EnumerateFunc pFunc, void* pUserData);
	static bool FileEnumeration(tcpchar lpPath, bool bRecursion, bool bEnumFiles, LST_STRING& lstS);
	static LST_STRING FileEnumeration(tcpchar lpPath, bool bRecursion, bool bEnumFiles);
    static bool CB_EnumerateFunc(tcpchar lpFileOrPath, void* pUserData );

    static bool IsValidPath( tcpchar szPath );
    static tstring GetExpandDir(tcpchar szVariant);
	static tstring GetFileNameFromPath( tcpchar szPath );
	static LLONG GetFileSize( tcpchar szPath );
	static tstring GetDirFromPath( tcpchar szPath );

	static bool CreateMultipleDirectory(tcpchar strFileFolder);	// �����༶Ŀ¼
	
private:
    tstring             m_strPath;
    tstring             m_strPos;   //�ڲ�������ʱλ��
};

/***************** ����Ŀ���� ***************/