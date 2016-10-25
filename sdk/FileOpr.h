#pragma once
#include <Windows.h>
#include <stdio.h>
#include <string>
#include "PiTypeDef.h"
using std::string;
const UNLONG MAX_READ_SIZE = 1024 * 1024 * (UNLONG)5;//1M

enum ENUM_FILE_POS
{
    pos_begin = 0,
    pos_end,
};
class CFileOpr
{
public:
	CFileOpr(void);
	virtual ~CFileOpr(void);

public:
	bool	Init();
	bool	UnInit();

	/************************************************************************
        fun:	��ָ��ģʽ��ָ���ļ�,ԭ�ȴ򿪵Ļᱻ�رյ���	
		param:  mode:"r"- ֻ�� , "w"-д�� �����ļ��ᱻ��գ�"wb"- ������д

        ret:    
        remark: �����ʧ��,ԭ�ȵ��ļ����ܼ��������� �����ܵ�Ӱ��
	/************************************************************************/
	//bool	Open(PCSTR filePath, PCSTR cMode = "rb", int shflag = _SH_DENYWR);
    bool    Open(tstring& strFile, tcpchar cMode = _T("rb"), int shflag = _SH_DENYWR);
    bool    Open(tcpchar filePath, tcpchar cMode = _T("rb"), int shflag = _SH_DENYWR);
	bool Read( void*& pBuf, UNLONG MaxSize, UNLONG* nReadReal = NULL);
	bool ReadBuf( void* pBuf, UNLONG MaxSize, UNLONG* nReadReal = NULL);
    bool    Write(const void* data, UNLONG dwSize);
	bool	Flush();
	bool	Close();
	char*	GetFileData();
    UNLONG	GetFileSize();
	static UNLONG	GetFileSize(tcpchar szPath);
    tstring GetFilePath();

    //��������
    void SetErrDesc(tcpchar szDesc );
    tstring GetErrDesc();
    static bool RemoveData( tcpchar szFile, DWORD nEraseSize, int nStartPos);
    static bool RemoveData( tcpchar szFile, DWORD nEraseSize, ENUM_FILE_POS nPos);
    /*����ƫ��, 
        nOrigin:
            SEEK_SET:��ʼλ��
            SEEK_END: �ļ���β
            SEEK_CUR: ��ǰλ��
    */
    bool SetPos( UNLONG nRightStart, int nOrigin  = SEEK_SET);
    bool DeleteFile();
    static bool DeleteFile(tcpchar szPath);
    //������, Ŀ�����ֲ��ɴ���
    //���ƶ��ļ�, �������ƶ�Ŀ¼
    bool Rename(tcpchar szNewName);
    static bool Rename(tcpchar szOldName, tcpchar szNewName);

	static bool IsModuleBit64(tcpchar szPath);
	static bool Save( void* pData, int nSize, tcpchar szFile );
	bool OpenWrite( tcpchar szFile);
	bool IsOpen();
private:
	FILE* m_pFile;
	char* m_pFileData;
    tstring m_strFilePath;//��ǰ�����ļ��ľ���·��

	UNLONG m_dwFileSize;
    CRITICAL_SECTION	m_cs;
	tstring              m_strErrDesc;//��������
};
