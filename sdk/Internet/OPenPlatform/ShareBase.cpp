// ShareBase.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PA_test.h"
#include "ShareBase.h"
#include "afxdialogex.h"


// CShareBase �Ի���

IMPLEMENT_DYNAMIC(CShareBase, CDialogEx)

CShareBase::CShareBase(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShareBase::IDD, pParent)
{

}

CShareBase::~CShareBase()
{
}

void CShareBase::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CShareBase, CDialogEx)
END_MESSAGE_MAP()

bool CShareBase::Start()
{
    return true;
}


// CShareBase ��Ϣ�������
