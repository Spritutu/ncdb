#pragma once
#include "PiTypeDef.h"
#include <windows.h>
#include "zip.h"
#include <list>
#include <vector>
using namespace std;

typedef bool (*EnumerateFunc) (tcpchar lpFileOrPath, void* pUserData );
typedef list<tstring>       LST_PATH;
typedef vector<tstring>     VT_PATH;

using namespace PAZipNS;
class CPiZip
{
    
public:
    //using namespace ZIP_N;
    CPiZip(void);
    ~CPiZip(void);
public:
    /**************************************** �ӿ� ****************************************/
    bool AddZipFolder(tcpchar szPath);
    bool CompressFolder(tcpchar szZipPath, tcpchar szDir = NULL);
    bool CompressFolder( tcpchar szZipPath, const LST_PATH& lstDir);
    bool CompressFile(tcpchar szZipPath, VT_PATH& lstFile);
	/*------------------------------------------------------------
			fun:	��ѹzip�ļ���ָ��Ŀ¼
			ret:	
			param: 1. szZipPath, zip��·��; 2.szDistPath��ŵ�Ŀ¼ 3.szUnZipFile, Ҫ��ѹ���ļ���, �����ڲ���νṹ
			remark:	��ѹ����ļ�����zip�ڵ��ļ���, ���й����л���ĵ�ǰĿ¼
	------------------------------------------------------------*/
	static bool UnZip(tcpchar szZipPath, tcpchar szDistPath, tcpchar szUnZipFile = NULL);
	
    /************************************************************************
        fun: ��ѹ��ָ��Ŀ¼
        ret: strDistRoot, ���ؽ�ѹ����ļ�����Ŀ¼
    /************************************************************************/
    static bool UnZipPack(tcpchar szZipPath, tcpchar szDistPath, tstring& strDistRoot);
    
    bool RunCompress();
    tstring ZipPath() const { return m_strZipPath; }
    void ZipPath(tstring val) { m_strZipPath = val; }

    tcpchar CurrentZipLayer() const { return m_strCurrentZipLayer.c_str(); }
    void CurrentZipLayer(tcpchar val) { m_strCurrentZipLayer = val; }

protected:
    /**************************************** ���� ****************************************/
    bool CreateZipFile(tcpchar szZip);
    bool _AddFolderCB(tcpchar szDir);
    bool _AddFile( tcpchar lpFileOrPath );
    void AppendDirLayer( tcpchar lpFileOrPath );
    static bool DealFileFunc(tcpchar lpFileOrPath, void* pUserData );
    static bool DealDirFunc(tcpchar lpFileOrPath, void* pUserData );
    /************************************************************************
        fun:    ����ѹ��Ŀ¼��zip
        param: 
        remark: 
    ************************************************************************/
    bool _AddFolder( tcpchar szPath );
    
private:
    /**************************************** ���� ****************************************/
    HZIP                m_hZip;
    
    tstring                     m_strCurrentZipLayer;
    tstring                     m_strZipPath;  //�����zip�����ļ�·��
    
    LST_PATH                    m_lstPath;
};

