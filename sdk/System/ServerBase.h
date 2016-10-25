#pragma once
/*------------------------------------------------------
	Fun:	���������ģ��, �򻯷���Ĵ���
	remark:	����:
				1. �ӱ�������һ������, ʵ�ֽӿ�DoTaskִ�з�������� �ڳ�����ڴ�(win32Ϊmain) ����Start�ӿ�
				2. ��������m_nPeriodMils��ֵ�ı�ִ������, ��λ����
	Authon: liwanliang, QQ:396257680
	Date:	2016/04/01
------------------------------------------------------*/
#include "PiTypeDef.h"
#include "SingleLog.h"
#include <Windows.h>
class CServerBase
{
public:
	CServerBase(void);
	virtual ~CServerBase(void);
protected:
	/*------------------------------------------------------------
			fun:	��һЩ��ʱ���õĳ�ʼ������
			ret:	
			param: 
			remark:	
	------------------------------------------------------------*/
	virtual bool InitThread();
	/*------------------------------------------------------------
			fun:	ִ�з�������, ����ִ�иýӿ�
			ret:	
			param: 
			remark:	
	------------------------------------------------------------*/
	virtual bool DoTask();
	/*------------------------------------------------------------
			fun:	���񼴽��˳�ʱ����, �������˳�����ʼ������
			ret:	
			param: 
			remark:	
	------------------------------------------------------------*/
	virtual void OnExit();

public:
	/*------------------------------------------------------------
			fun:	��ʼִ�з���
			ret:	
			param: 
			remark:	�����̻߳�һֱ�ȴ�, ֱ�������������з����˳���ŷ���
	------------------------------------------------------------*/
	bool Start();
	
protected:
	bool Init();
	static VOID WINAPI ServiceMain(DWORD dwArgc,LPTSTR* lpszArgv);
	static VOID WINAPI ServerHandler(DWORD fdwControl);
protected:
	tstring				m_strServiceName;	//���������ֻ��1������, ����ָ��, ���ⲿ��������ʱָ��
	bool				m_bWriteLog;
	UNINT				m_nPeriodMils;		//��ʱִ�����������, ��λ����
};
