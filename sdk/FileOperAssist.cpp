#include "StdAfx.h"
#include "FileOperAssist.h"
#include "..\..\..\..\sdk\UCommon.h"
#include <assert.h>


CFileOperAssist::CFileOperAssist(void)
{
}


CFileOperAssist::~CFileOperAssist(void)
{
}

bool CFileOperAssist::AddOperator( ENUM_OPERATOR op, const tstring& strPath )
{
    //���������б�
    return true;
}

bool CFileOperAssist::AddOperator( ENUM_OPERATOR op, const LST_STRING& strPath )
{
    return true;
}

bool CFileOperAssist::AddOperator( const LST_OPER& lstOper )
{
    m_lstOper = lstOper;
    return true;
}

bool CFileOperAssist::BeginTrans()
{
    //����б�, 
    m_lstOper.clear();
    m_lstRollBack.clear();
    return true;
}

bool CFileOperAssist::EndTransDo()
{
    bool bDoSuc = true;
    bool bRobackSuc = true;
    //����ִ�����в���
    FOR_EACH_FILE_OPER(m_lstOper, it)
    {
        //һ��������ɺ���ӵ��ع��б�, ����һ��ʧ��ʱ, ִ�лع��б�(ʧ�ܴ���), ���ж���ɺ�, ��ջع��б�
        tagFILE_OPER* pOper = *it;
        switch (pOper->oper)
        {
        case operator_rename:
            if(CFileUtil::Rename(pOper->strSrc.c_str(), pOper->strDist.c_str()))
            {
                break;
            }
            bDoSuc = false;
            if (!RoBack())
            {
                /*TODO:��ʶ ����ʧ��,�ع��ɹ� */
                bRobackSuc = false;
                return bDoSuc;
            }
        	return false;
            break;
        case operator_delete:
            if(CFileUtil::DeleteFile(CString(pOper->strSrc.c_str())))
            {
                break;
            }
            bDoSuc = false;
            if (!RoBack())
            {
                /*TODO:��ʶ ����ʧ��,�ع��ɹ� */
                bRobackSuc = false;
                return bDoSuc;
            }
            return false;
            break;
        default:
            break;
        }
        AddRobackTask(pOper);
    }
    return bDoSuc;
}

bool CFileOperAssist::RoBack()
{
    FOR_EACH_FILE_OPER(m_lstRollBack, it)
    {
        //һ��������ɺ���ӵ��ع��б�, ����һ��ʧ��ʱ, ִ�лع��б�(ʧ�ܴ���), ���ж���ɺ�, ��ջع��б�
        tagFILE_OPER* pOper = *it;
        switch (pOper->oper)
        {
        case operator_rename:
            if(!CFileUtil::Rename(pOper->strSrc.c_str(), pOper->strDist.c_str()))
            {
                return false;
            }
            break;
        case operator_delete:
            assert(0);
            break;
        default:
            break;
        }
    }
    return true;
}

bool CFileOperAssist::AddRobackTask( tagFILE_OPER* pOper )
{
    if (operator_delete == pOper->oper)
    {
        //��ʱ��֧��ɾ�������Ļع�
        return false;
    }
    tagFILE_OPER* pFile = new tagFILE_OPER;
    *pFile = *pOper;
    pFile->GetRobackOper();
    m_lstRollBack.push_front(pFile);
    return true;
}
