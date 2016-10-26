#pragma once
#include "PiTypeDef.h"
Pi_M_NameSpace_Begin(ns_by_stat)

#define STRING_LABELID_INSTALL		_T("install")
#define STRING_LABELID_UNINSTALL	_T("uninst")
#define STRING_LABELID_UPDATE		_T("update")
#define STRING_LABELID_DOWNLOAD_SOFT	_T("PCdownload")
#define STRING_LABELID_DOWNLOAD_MUSIC	_T("MusicDownload")
#define STRING_LABELID_DOWNLOAD_WP		_T("WPdownload")

enum ENUM_PHONE_CONNECT_STATE
{
	connect_usb_success					= 0,	//USB���ӳɹ�
	connect_usb_start					,		//USB��ʼ����
	connect_usb_start_no_check_port		,		//USB��ʼ����(������豸����)
	connect_wifi_success				,		//WIFI���ӳɹ�
	connect_wifi_start					,		//WIFI��ʼ����
};

enum ENUM_UNINSTALL_REASON
{
	reason_cannot_connect		= 1,		//�ֻ��������Ӳ���
	reason_no_androw			= 2 << 1	,	//��ʹ�õĲ��ǰ�׿�ֻ�
	reason_download_app			= 2 << 2	,	//���ص�Ӧ��������
	reason_bad_download_speed	= 2 << 3	,	//��Դ�����ٶ���
	reason_res_lack				= 2 << 4	,	//�Ҳ�����Ҫ����Դ
	reason_use_other			= 2 << 5	,	//���������ֻ��������
	reason_other				= 2 << 6	,	//����ԭ��+QQ����
};

//�Զ����¼�
struct tagSTAT_CUSTOM_EVENT
{
	tstring strLabelID;	
	tstring strName;	
public:
	tagSTAT_CUSTOM_EVENT(tcpchar szLabelId =_T(""), tcpchar szName =_T(""))
		:strLabelID(szLabelId)
		,strName(szName){}
};


struct tagEXCEPTION
{
	tstring strExceptionDesc;
};

//�ⲿ�����޸ĵĲ����ṹ
struct tagPARAM
{
	tstring	strServer;		//ͳ�Ʒ�����, ��http://tj1.3310.com
	tstring	strAESKey;
	tstring	strAESIV;		//�ڲ�д��, �ⲿ��������
	tstring	strProductID;	//��ƷID

	tstring	strChannel;			// ����
	tstring strSoftVersion;		//����汾
	tagPARAM()
		:strChannel(_T("0000"))
	{

	}
};

typedef list<tagSTAT_CUSTOM_EVENT>	LST_EVENT;
typedef map<ENUM_UNINSTALL_REASON, tstring>	MAP_REASON;
Pi_M_NameSpace_End
