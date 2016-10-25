#pragma once
#include "BYStatHeader.h"
Pi_M_NameSpace_Begin(ns_by_stat)
class DLL_CLASS IByStat
{
	/*typedef ns_by_stat::ENUM_PHONE_CONNECT_STATE ENUM_PHONE_CONNECT_STATE;
	typedef ns_by_stat::ENUM_UNINSTALL_REASON ENUM_UNINSTALL_REASON;
	typedef ns_by_stat::tagPARAM tagPARAM;*/
	
	
public:
	virtual ~IByStat(){};
public:
	virtual bool Init() = 0;
/************************************************************************
    fun:	����ʱ����, ��ȡϵͳ��Ϣ�����͸�������
    param:  
    ret:    true:�ռ����ͳɹ�
    remark: 
/************************************************************************/
	virtual bool CollectAppLunchyInfo() = 0;
	virtual bool CollectAppLunchyInfo_Sync() = 0;
/************************************************************************
    fun:	����ر�ʱ����, ��ȡϵͳ��Ϣ�ͽ���ʱ�䲢���͸�������
    param:  
    ret:    true:�ռ����ͳɹ�
    remark: 
/************************************************************************/
	virtual bool CollectAppExitInfo() = 0;
	virtual bool CollectAppExitInfo_Sync() = 0;

/************************************************************************
    fun:	���ͱ�����Ϣ��������
    param:  
    ret:    true:�ռ����ͳɹ�
    remark: 
/************************************************************************/
	virtual bool CollectAppExceptionInfo(tstring strExceptionDesc) = 0;
	virtual bool CollectAppExceptionInfo_Sync(tstring strExceptionDesc) = 0;

/************************************************************************
    fun:	ͳ���ֻ�����״̬
    param:  
    ret:    true:�ռ����ͳɹ�
    remark: 
/************************************************************************/
	virtual bool CollectPhoneConnectState(ENUM_PHONE_CONNECT_STATE enState) = 0;
	virtual bool CollectPhoneConnectState_Sync(ENUM_PHONE_CONNECT_STATE enState) = 0;

/************************************************************************
    fun:	ͳ�ư�װ
    param:  
    ret:    true:�ռ����ͳɹ�
    remark: 
/************************************************************************/
	virtual bool CollectInstall() = 0;
	virtual bool CollectInstall_Sync() = 0;

/************************************************************************
    fun:	ͳ��ж��
    param:  
    ret:    true:�ռ����ͳɹ�
    remark: 
/************************************************************************/
	virtual bool CollectUnInstall() = 0;
	virtual bool CollectUnInstall_Sync() = 0;

/************************************************************************
    fun:	ͳ���������
    param:  
    ret:    true:�ռ����ͳɹ�
    remark: 
/************************************************************************/
	virtual bool CollectUpdate() = 0;
	virtual bool CollectUpdate_Sync() = 0;

/************************************************************************
    fun:	ͳ��ж���еķ�����Ϣ
    param:  
    ret:    true:���ͳɹ�
    remark: 
/************************************************************************/
	virtual bool CollectUnInstallFeedback(int nReason) = 0;
	virtual bool CollectUnInstallFeedback_Sync(int nReason) = 0;
	virtual bool CollectUnInstallFeedback(tstring strReason, tstring strQQ) = 0;
	virtual bool CollectUnInstallFeedback_Sync(tstring strReason, tstring strQQ) = 0;

/************************************************************************
    fun:	ͳ��Ӧ���������
    param:  
    ret:    true:���ͳɹ�
    remark: 
/************************************************************************/
	virtual bool CollectDownloadSoft(tstring strAppName) = 0;
	virtual bool CollectDownloadSoft_Sync(tstring strAppName) = 0;

/************************************************************************
    fun:	ͳ�������������
    param:  
    ret:    true:���ͳɹ�
    remark: 
/************************************************************************/
	virtual bool CollectDownloadMusic(tstring strAppName) = 0;
	virtual bool CollectDownloadMusic_Sync(tstring strAppName) = 0;

/************************************************************************
    fun:	ͳ�Ʊ�ֽ�������
    param:  
    ret:    true:���ͳɹ�
    remark: 
/************************************************************************/
	virtual bool CollectDownloadWP(tstring strAppName) = 0;
	virtual bool CollectDownloadWP_Sync(tstring strAppName) = 0;

/************************************************************************
    fun:	�����Զ����¼�
    param:  
    ret:    true:���ͳ�
    remark: 
/************************************************************************/
	virtual bool SendEvent(tstring szLabelID,  tstring szName) = 0;
	virtual bool SendEvent(tagSTAT_CUSTOM_EVENT tagEvent) = 0;
	virtual bool SendEventList(LST_EVENT lstEvent) = 0;


	virtual bool SendEvent_Sync(tcpchar szLabelID,  tcpchar szName) = 0;
	virtual bool SendEvent_Sync(const tagSTAT_CUSTOM_EVENT& tagEvent) = 0;
	virtual bool SendEventList_Sync( const LST_EVENT& lstEvent) = 0;

	virtual tagPARAM* Param()   = 0;
	virtual void Param(const tagPARAM& val) = 0;
};

Pi_M_NameSpace_End
