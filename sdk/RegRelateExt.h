/*------------------------------------------------------
   	Fun:	�ļ�������
   	Authon: liwanliang
   	Date:	2015/09/30
   ------------------------------------------------------*/
   
 #if !defined(AFX_REGRELATEEXT_H__6DE7E979_9011_4639_967A_D8817DF4DE44__INCLUDED_) 
 #define AFX_REGRELATEEXT_H__6DE7E979_9011_4639_967A_D8817DF4DE44__INCLUDED_ 
 #include "ATLBASE.h" 
   
 #if _MSC_VER > 1000 
 #pragma once 
 #endif // _MSC_VER > 1000 
#include "PiString.h"
class CRegRelateExt : public CRegKey
{ 
public: 
	typedef ns_PiPi::CPiString CPiString;
	CRegRelateExt(); 
	virtual ~CRegRelateExt(); 
public:
	/*------------------------------------------------------------
			fun:	����ƶ���׺���Ƿ������ָ������
			ret:	true: �ѹ���
			param: 
			remark:	û�м�����ͼ��
	------------------------------------------------------------*/
	static bool Check(tcpchar szFileExt, tcpchar szExePath, tcpchar szParam); 
	static bool CheckSelf(tcpchar szFileExt, tcpchar szParam); 
	/*------------------------------------------------------------
			fun:	�����ļ�����
			ret:	
			param: 1. fileExe, 
			remark:	
	------------------------------------------------------------*/
	bool Set(tcpchar szFileExt, tcpchar szRelateExe, tcpchar szShellParam = NULL, tcpchar szIcon = NULL); 
	bool SetSelf(tcpchar szFileExt, tcpchar szShellParam = NULL, tcpchar szIcon = NULL); 
	void SetParam(tcpchar szRegClassName, tcpchar szArchiveDesc);
	static bool Delete(tcpchar FileExt); 
protected:
	static tstring MakeShellCmd( tcpchar szRelateExe, tcpchar szParam );
private: 
	//BOOL m_IfRelated; 

	CPiString m_RegClass; 
	//CPiString m_RelateExe; 
	CPiString m_strArchiveDesc;
	 
}; 
   
 #endif // !defined(AFX_REGRELATEEXT_H__6DE7E979_9011_4639_967A_D8817DF4DE44__INCLUDED_) 

