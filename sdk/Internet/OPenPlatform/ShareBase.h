#pragma once

#include "explorer1.h"

// CShareBase �Ի���

class CShareBase : public CDialogEx
{
	DECLARE_DYNAMIC(CShareBase)

public:
	CShareBase(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShareBase();

// �Ի�������
	enum { IDD = IDD_SHAREBASE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    bool Start();
protected:
    CWnd* m_pWndParent;
    CExplorer1 m_webTest;
    
};
