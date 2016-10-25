#include "StdAfx.h"
//#include <windows.h>
#include "PiZip.h"



//#include "zip.h"
#include "unzip.h"
#include "functional.h"
#include "define_gnl.h"
#include <shlobj.h>
#include "PathLight.h"
//#include "zipdef.h"

//using namespace PAZipNS;

//#pragma comment(lib, shell32.lib)
#define FOR_EACH_PATH(Cn, It) \
    FOR_EACH_ITER(LST_PATH, Cn, It)

#define IsFolder(nAttr) ((nAttr) & FILE_ATTRIBUTE_DIRECTORY)
#define ZipOK(nRet) ((nRet) == ZR_OK)
CPiZip::CPiZip(void)
{
    m_hZip       = NULL;
}


CPiZip::~CPiZip(void)
{
}

bool CPiZip::CompressFolder( tcpchar szZipPath, tcpchar szDir /*= NULL*/)
{
//     ZipAdd(hz,"znsimple.txt", "c:\\simple.txt");
    //ZipAddFolder(m_hZipCurrent, _T("test\\1_5"));      //����2, ����ѹ�����ڲ����� ָ����·��
    //ZipAdd(m_hZipCurrent,"test\\znsimple.bmp", "D:\\test\\1_5\\ch1-05.l"); //����2, ��ѹ�����ڵ�·�����ļ���
    //CloseZip(m_hZipCurrent);
    //tcpchar szDir = _T("d:\\sdk");
    ZipPath(szZipPath);

    //ѹ��ָ��Ŀ¼ ���� ʹ�ö��Ŀ¼
    if (szDir)
    {
        m_lstPath.clear();
        m_lstPath.push_back(szDir);
    }
    if (m_lstPath.size() <= 0)
    {
        return false;
    }

    return RunCompress();
}

bool CPiZip::CompressFolder( tcpchar szZipPath, const LST_PATH& lstDir )
{
    m_lstPath = lstDir;
    ZipPath(szZipPath);
    return RunCompress();

    //return true;

}

bool CPiZip::DealFileFunc( tcpchar lpFileOrPath, void* pUserData )
{
    CPiZip* pZip = static_cast<CPiZip*>(pUserData);
    pZip->_AddFile(lpFileOrPath);    //ÿһ���ļ���ӵ���ǰ
    return true;
    
}

bool CPiZip::DealDirFunc( tcpchar lpFileOrPath, void* pUserData )
{
    
    CPiZip* pZip = static_cast<CPiZip*>(pUserData); 

    tstring strPathPrev = pZip->CurrentZipLayer(); //����֮ǰ��Ŀ¼

    pZip->AppendDirLayer(lpFileOrPath); //zip��׷��Ŀ¼
    pZip->_AddFolderCB(lpFileOrPath);

    pZip->CurrentZipLayer(strPathPrev.c_str()); //��ԭ��ԭ����zipĿ¼

    return true;
}

bool CPiZip::_AddFolderCB( tcpchar szDir )
{

    FileEnumeration(szDir, false, true, CPiZip::DealFileFunc, this);

    FileEnumeration(szDir, false, false, CPiZip::DealDirFunc, this); //�ݹ���Ŀ¼
    return true;

}

bool CPiZip::_AddFile( tcpchar lpFileOrPath )
{
    //m_strCurrent;
    //tstring strFileName = GetFileNameFromPath(lpFileOrPath); /* ����·����ȡ�ļ���*/
	tstring strInnerPath = m_strCurrentZipLayer + CPathLight::GetFileNameFromPath(lpFileOrPath).c_str();
    tcpchar szInnerPath = strInnerPath.c_str();/* ���ݵ�ǰ��� ���ļ��� �����zip�ڵ�·��*/;
    

    ZipAdd(m_hZip, szInnerPath, lpFileOrPath); //����2, ��ѹ�����ڵ�·�����ļ���

    return true;
    
}

bool CPiZip::CreateZipFile( tcpchar szZip )
{
    if(!szZip)
    {
        return false;
    }
    CPathLight::CreateMultipleDirectory(CPathLight::GetDirFromPath(szZip).c_str());
    m_hZip = CreateZip(szZip, 0);
    return m_hZip > 0;

}

void CPiZip::AppendDirLayer( tcpchar lpFileOrPath )
{
    m_strCurrentZipLayer += CPathLight::GetFileNameFromPath(lpFileOrPath) + _T("\\");
    ZipAddFolder(m_hZip, m_strCurrentZipLayer.c_str());
}

bool CPiZip::AddZipFolder( tcpchar szPath )
{
    m_lstPath.push_back(szPath);
    return true;
}

bool CPiZip::_AddFolder( tcpchar szPath )
{
    m_strCurrentZipLayer.clear();
    this->AppendDirLayer(szPath); //zip��׷��Ŀ¼
    _AddFolderCB(szPath);
    return true;
}

bool CPiZip::RunCompress()
{
    if(!CreateZipFile(m_strZipPath.c_str()))
    {
        return false;
    }

    FOR_EACH_PATH(m_lstPath, it)
    {
        if(!_AddFolder((*it).c_str()))
        {
            return false;
        }
    }

    return ZR_OK == CloseZip(m_hZip);
    
}

bool CPiZip::UnZip( tcpchar szZipPath, tcpchar szDistPath , tcpchar szUnZipFile /*= NULL*/)
{
    //��ָ������Ŀ¼��, �������� zip���ļ��� Ϊ����Ŀ¼, ��ѹ����ڸ�Ŀ¼
    if(!szZipPath || ! CPathLight::IsFileExist(szZipPath))
    {
        return false;
    }
    tstring strDistDir(szDistPath);
    /*strDistDir += _T("\\");
    strDistDir += CPathLight::GetFileTitleFromPath(szZipPath);
*/

    ::SHCreateDirectoryEx(NULL, strDistDir.c_str(), NULL);

    tchar szTempPath[_MAX_FNAME] = {0};
    ::GetCurrentDirectory(MAX_PATH, szTempPath);

    ::SetCurrentDirectory(strDistDir.c_str());  //�����ú�, �ڴ�zip
    //TODO: ������ǰ����, ��ǰ·��û�л�ԭ�����

    HZIP hzPack = OpenZip(szZipPath, 0);
    if(!hzPack)
    {
        return false;
    }

	if (szUnZipFile)
	{
		//��ѹָ���ļ���ָ��Ŀ¼
		int nIndex = 0;
		ZIPENTRY ze = {0};
		if( ! ZipOK(FindZipItem(hzPack, szUnZipFile, false, &nIndex, &ze)))
		{
			return false;
		}
		if(!ZipOK(UnzipItem(hzPack, nIndex, CPathLight::GetFileNameFromPath(ze.name).c_str())))
		{
			return false;
		}
		return true;
	}
	else
	{
		ZIPENTRY ze = {0};
		if(!ZipOK(GetZipItem(hzPack, -1, &ze)))
		{
			return false;
		}
		int nCount = ze.index;
		//�ҵ�ָ���ļ�����, �ͷŵ�ָ��Ŀ¼

		for (int i = 0; i < nCount; ++i)
		{
			if(!ZipOK(GetZipItem(hzPack, i, &ze)))
			{
				return false;
			}
			if(!ZipOK(UnzipItem(hzPack, i, ze.name)))
			{
				return false;
			}

		}
	}
    CloseZip(hzPack);
    ::SetCurrentDirectory(szTempPath);  //��ԭ����ǰĿ¼
    return true;

}

bool CPiZip::UnZipPack( tcpchar szZipPath, tcpchar szDistPath, tstring& strDistRoot )
{
    if (!UnZip(szZipPath, szDistPath))
    {
        return false;
    }
    CPathLight pathConfig(szDistPath);
    pathConfig.AddSubSession(CPathLight::GetFileTitleFromPath(szZipPath));
    strDistRoot = pathConfig.GetPath();
    return true;
}

bool CPiZip::CompressFile( tcpchar szZipPath, VT_PATH& lstFile )
{
    ZipPath(szZipPath);

    if(!CreateZipFile(szZipPath))
    {
        return false;
    }

    m_strCurrentZipLayer.clear();
    FOR_EACH_ITER(VT_PATH, lstFile, it)
    {
        _AddFile(it->c_str());
    }

    return ZR_OK == CloseZip(m_hZip);

}
