#include "StdAfx.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#include "PAZip.h"
#include "PiZip.h"
#include "functional.h"
#include "SysFilePathMgr.h"
#include "UCommon.h"
#include "PAProdictPathMng.h"
#include "PADebug.h"
#include "PathLight.h"

CPAZip::CPAZip(void)
{
}


CPAZip::~CPAZip(void)
{
}

bool CPAZip::Init()
{
    m_pZip      = auto_ptr<CPiZip>(new CPiZip);
    tstring strPathDist;
    //��ʼ�����������·��

    strPathDist = CPAProdictPathMng::GetPathMMWorkPlacement();
    AddDist(pt_mm_panel, strPathDist);

    //strPathDist = strUserDocumentPath + STRING_DIR_SUFFIX_MM_COLOR;
    strPathDist = CPAProdictPathMng::GetPathMMColor();
    AddDist(pt_mm_color, strPathDist);

    //strPathDist = strUserDocumentPath + STRING_DIR_SUFFIX_MM_BRUSH;
    strPathDist = CPAProdictPathMng::GetPathMMCtBrush();
    AddDist(pt_mm_brush, strPathDist);
    
    //strPathDist = strUserDataPath + STRING_DIR_SUFFIX_IM_PANEL;
    strPathDist = CPAProdictPathMng::GetPathIMWorkPlacement();
    AddDist(pt_im_panel, strPathDist);

    //strPathDist = strUserDocumentPath + STRING_DIR_SUFFIX_IM_COLOR;
    strPathDist = CPAProdictPathMng::GetPathIMColor();
    AddDist(pt_im_color, strPathDist);

    //strPathDist = strUserDocumentPath + STRING_DIR_SUFFIX_IM_BRUSH;
    strPathDist = CPAProdictPathMng::GetPathIMCtBrush();
    AddDist(pt_im_brush, strPathDist);

    return true;
}

bool CPAZip::PackConfig( PCTSTR szZipPath, ENUM_PACK_TYPE packType )
{
    //��ȡ·��
    switch (packType)
    {
    case type_mm:
        {
            m_pZip->AddZipFolder(m_lstPath.find(pt_mm_panel)->second.strPathSoft.c_str());
            m_pZip->AddZipFolder(m_lstPath.find(pt_mm_color)->second.strPathSoft.c_str());
            m_pZip->AddZipFolder(m_lstPath.find(pt_mm_brush)->second.strPathSoft.c_str());
        }
        break;
    case type_im:
        {
             m_pZip->AddZipFolder(m_lstPath.find(pt_im_panel)->second.strPathSoft.c_str());
             m_pZip->AddZipFolder(m_lstPath.find(pt_im_color)->second.strPathSoft.c_str());
             m_pZip->AddZipFolder(m_lstPath.find(pt_im_brush)->second.strPathSoft.c_str());
        }
        break;
    }
    
    return m_pZip->CompressFolder(szZipPath);
    

}

bool CPAZip::UnPackonfig( PCTSTR szZipPath, ENUM_PACK_TYPE packType )
{
    //��ѹ��ĳ����ʱĿ¼, �����Ӹ���ѹ�����ļ�����ͬ��Ŀ¼
    
    tstring strPathTemp(GetDirFromPath(szZipPath).c_str());
    
    if(!m_pZip->UnZip(szZipPath, strPathTemp.c_str()))
    {
        return false;
    }

    strPathTemp += '\\';
    strPathTemp += CPathLight::GetFileTitleFromPath(szZipPath);
    strPathTemp += '\\';

    //����Ŀ¼, ��Ŀ¼���е���Ӧ��Ŀ¼(��ɾ��Ŀ��Ŀ¼)
    switch(packType)
    {
    case type_mm:
        {
            CutToMM(strPathTemp);
        }
        break;
    case type_im:
        {
            CutToIM(strPathTemp);
        }
        break;

    }

    /***************** ɾ��ѹ�����ͷų�����Ŀ¼ *****************/
    CFileUtil::DeleteFile(CString(strPathTemp.c_str()));
    return true;
    
}

bool CPAZip::CutToMM( const tstring& strPathSour )
{
    /***************** �ҵ�3�������ļ���, ���и��Ǽ��в��� *****************/

    if(CutFileCoverFull(strPathSour + m_lstPath[pt_mm_panel].strFolder, m_lstPath[pt_mm_panel].strPathSoft)
        && CutFileCoverFull(strPathSour + m_lstPath[pt_mm_color].strFolder, m_lstPath[pt_mm_color].strPathSoft)
        && CutFileCoverFull(strPathSour + m_lstPath[pt_mm_brush].strFolder, m_lstPath[pt_mm_brush].strPathSoft)
    )
    {
        return true;
    }
    
    return false;
    
}

bool CPAZip::CutToIM( tstring strPathSour )
{
    /***************** �ҵ�3�������ļ���, ���и��Ǽ��в��� *****************/
    if (
        CutFileCoverFull(strPathSour + m_lstPath[pt_im_panel].strFolder, m_lstPath[pt_im_panel].strPathSoft)
        && CutFileCoverFull(strPathSour + m_lstPath[pt_im_color].strFolder, m_lstPath[pt_im_color].strPathSoft)
        && CutFileCoverFull(strPathSour + m_lstPath[pt_im_brush].strFolder, m_lstPath[pt_im_brush].strPathSoft)
        )
    {
        return true;
    }

    return false;
    
}

void CPAZip::AddDist( ENUM_PATH_TYPE nType , tstring strDistPath )
{
    //���� type, ��ȡ��ǰ׺, �м��ַ���, ���Ŀ¼

    m_lstPath.insert(pair<ENUM_PATH_TYPE, PATH_INFO>(nType, 
        PATH_INFO( strDistPath, GetFileNameFromPath(strDistPath.c_str()) ))
        );
}

bool CPAZip::CutFileCoverFull( tstring szSour, tstring szDist )
{
    if (!::PathFileExists(szSour.c_str()))
    {
        return false;
    }
    
    
    /***************** ɾ������Ŀ¼ *****************/
    CFileUtil::DeleteFile(CString(szDist.c_str()));


    /***************** Ŀ¼�ƶ���ָ��Ŀ¼ *****************/
    //�����Ŀ¼, ��ָ���ϲ�Ŀ¼
//     bool bDir = true;
//     if(bDir)
//     {
//         szDist = GetParentPathFromPath(szDist.c_str());
//     }
    //����Ŀ¼������, ���Զ�����
    if(!CFileUtil::CopyFile(CString(szSour.c_str()), CString(szDist.c_str())))
    {
        return false;
    }

    /***************** ɾ��ԴĿ¼ *****************/
    CFileUtil::DeleteFile(CString(szSour.c_str()));
    
    return true;
    
}
