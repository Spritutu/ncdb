#include "StdAfx.h"
#include "PAOptDialog.h"
#include "PASetPage.h"
#include "OptionNotify.h"
#include "PAUserSetting.h"

CPAOptDialog::CPAOptDialog(void)
{
    m_nCurPageIdx = 0;
}


CPAOptDialog::~CPAOptDialog(void)
{
}

bool CPAOptDialog::Init()
{
    m_UserSetting = new CPAUserSetting;
    m_UserSetting->Init();

    
    //AddPage(pPage)
    AddPage(new CPAOptUIPageGeneral (m_pNotify, m_UserSetting));
    AddPage(new CPAOptUIPageApp     (m_pNotify, m_UserSetting));
    AddPage(new CPAOptUIPageUpdate  (m_pNotify, m_UserSetting));
    AddPage(new CPAOptUIPageFlow    (m_pNotify, m_UserSetting));

    
    return true;
}

bool CPAOptDialog::EnsureSetting()
{
    Apply();
    Cancel();
    return true;
}

bool CPAOptDialog::Cancel()
{
    //�ر����ô���
    return true;
}

bool CPAOptDialog::Apply()
{
    m_pCurPage->SaveAllSetting();
    m_pCurPage->Notify();
    return true;
}


bool CPAOptDialog::ChangePage( CPAOptUIPageBase* pPage )
{
    pPage->ShowNewest();
    m_pCurPage = pPage;

    AdjustTplBtnPos();
    ShowTplButton();
    return true;
}

bool CPAOptDialog::ShowTplButton()
{
    //TODO: ��ʾ3��ģ�尴ť
    return true;

}

bool CPAOptDialog::AdjustTplBtnPos()
{
    return true;
}

bool CPAOptDialog::ShowDefaultPage()
{
    //TODO:��ʾ��һ��ҳ��
    m_pCurPage = *(m_lstPage.begin());
    m_pCurPage->ShowNewest();

    AdjustTplBtnPos();
    ShowTplButton();
    
    return true;
    
}

bool CPAOptDialog::NextPage()
{
    ++m_nCurPageIdx;

    LST_PAGE::iterator it = m_lstPage.begin();
    advance(it, m_nCurPageIdx);
    CPAOptUIPageBase* pNext = *(it);
    
    ChangePage(pNext);
    return true;
}

bool CPAOptDialog::SetNotify( COptionNotify* pNotify )
{
    m_pNotify = pNotify;
    return true;
}

ENUM_OPTION_PAGE CPAOptDialog::GetCurrentPage()
{
    return m_pCurPage->GetPageFlag();
}

void CPAOptDialog::ModifySetting()
{
    m_pCurPage->ModifySetting();
}

void CPAOptDialog::SetUserSetting( CPAUserSetting* pUS )
{
    m_UserSetting = pUS;
}

bool CPAOptDialog::AddPage( CPAOptUIPageBase* pPage )
{
    if(!pPage->Init())
    {
        return false;
    }
    m_lstPage.push_back(pPage);
    
    return true;
}

bool CPAOptDialog::SaveAllSetting()
{
    //�ҵ�ÿ��page, ��Ӧ��ĳ���ֶ�
//     CPAOptUIPageBase* pPage = NULL;
//     pPage->SaveAllSetting()
    return true;

}
