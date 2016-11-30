#pragma once
#include "PiTypeDef.h"
class CTextStringCut
{
public:
	CTextStringCut(tcpchar val);
    CTextStringCut(const tstring& val);
    CTextStringCut(void);
    ~CTextStringCut(void);
public:

	bool GetInDQM(tstring& strDist);           //˫����
	bool GetInDQM(ARR_STRING& arrString);           //˫����
    bool GetInSQM(tstring strDist);           //������
	bool GetContent(tcpchar szAnchorLeft, tcpchar szAnchorRight, tstring& strDist);           //������
    bool GetContent(tcpchar szAnchorLeft, tcpchar szAnchorRight, int& Dist);           //������

    tstring Text() const { return m_strText; }
    void Text(tcpchar val) { m_strText = val; }
//protected:
    void InitVariable();
    bool GoForward( tcpchar szSignAnPostLink );
    /************************************************************************
        fun:	��ȡ��յĽ������е�ֵ, ><
        param:  
        ret:    
        remark: ��<>abc<>  , ��ȡ abc
    ************************************************************************/
	bool GetInAngleBracketsClose( tstring& strDist );
    /************************************************************************
    fun:	�����з�, \n
    param:  
    ret:    
    remark: 
/************************************************************************/
    bool GoForwardLineEnd();
	void SetText( tcpchar param1 );
private:
    tstring             m_strText;
    
    int                 m_nPosCurrent;
};