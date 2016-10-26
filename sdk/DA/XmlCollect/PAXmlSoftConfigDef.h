#pragma once
#include "PiTypeDef.h"

/************************************************************************
#define PA_URL_TEST             //URL���԰�
************************************************************************/


#define IMP_SC_READ_WRITE(InterFaceT, FieldName) \
    IMP_READ_WRITE_COMMON(CPAXmlSoftConfig, InterFaceT, XML_PA_SOFT_CONFIG, FieldName)

struct XML_PA_SOFT_CONFIG
{
    tstring strCPUWarnPercent;
    tstring strCPUNormalBkColor;
    tstring strCPUWarnBkColor;
    tstring strMemoryWarnPercent;
    tstring strMemoryNormalBkColor;
    tstring strMemoryWarnBkColor;
    tstring strCPUTimeSpan;
    tstring strMemTimeSpan;
    tstring strPipeName ;
    tstring strWndTitle             ;
    tstring strURL_Lif		        ;
    tstring strURL_Ad			    ;
    tstring strURL_HwInfo		    ;
    tstring strURL_SoftwareList	    ;
    tstring strURL_DriverList		 ;
    tstring strURL_CloudList		 ;
    tstring strURL_CloudItem		 ;
    tstring strURL_Login		 ;
    tstring strURL_Logout		 ;
    tstring strURL_UserDetail		 ;
    tstring strURL_UserHabit		 ;
    tstring strURL_PaUpdate		 ;

    tstring strShowPromt   		 ;
    tstring strNerverNotify		 ;

};

enum ENUM_DATA_DUTY_SC 
{
    ddsc_cpu_warn_percent = 0,
    ddsc_cpu_normal_bkcolor,
    ddsc_cpu_warn_bkcolor,
    ddsc_memory_warn_percent,
    ddsc_memory_normal_bkcolor,
    ddsc_memory_warn_bkcolor,
    ddsc_cpu_time_span,
    ddsc_mem_time_span,
    ddsc_updater_pipename,
    ddsc_updater_wndtitle,
    ddsc_url_lif,           //url
    ddsc_url_ad,
    ddsc_url_hwinfo,
    ddsc_url_softwarelist,
    ddsc_url_driverlist,
    ddsc_url_cloudlist,
    ddsc_url_clouditem,
    ddsc_url_login,
    ddsc_url_logout,
    ddsc_url_userdetail,
    ddsc_url_userhabit,
    ddsc_url_paupdate,
    ddsc_show_promt   ,
    ddsc_nerver_notify,
};  




//xml�ļ��ֶζ���

static const TCHAR*        STRING_XML_SC_MONITOR                        = _T("Monitor");
static const TCHAR*        STRING_XML_SC_CPUWARNPERCENT                 = _T("CPUWarnPercent");
static const TCHAR*        STRING_XML_SC_CPUNORMALBKCOLOR               = _T("CPUNormalBkColor");
static const TCHAR*        STRING_XML_SC_CPUWARNBKCOLOR                 = _T("CPUWarnBkColor");
static const TCHAR*        STRING_XML_SC_MEMORYWARNPERCENT              = _T("MemoryWarnPercent");
static const TCHAR*        STRING_XML_SC_MEMORYNORMALBKCOLOR            = _T("MemoryNormalBkColor");
static const TCHAR*        STRING_XML_SC_MEMORYWARNBKCOLOR              = _T("MemoryWarnBkColor");
static const TCHAR*        STRING_XML_SC_CPUTimeSpan                    = _T("CPUTimeSpan");
static const TCHAR*        STRING_XML_SC_MemTimeSpan                    = _T("MemTimeSpan");

static const TCHAR*        STRING_XML_SC_UPDATEINTERFACE                = _T("UpdateInterface");
static const TCHAR*        STRING_XML_SC_UPDATE_URL                     = _T("Url");
static const TCHAR*        STRING_XML_SC_UPDATE_PIPENAME                = _T("PipeName");
static const TCHAR*        STRING_XML_SC_UPDATE_WNDTITLE                = _T("WndTitle");

static const TCHAR*        STRING_XML_SC_UDONGMAN                       = _T("udongman");
static const TCHAR*        STRING_XML_SC_URL_LIF                        = _T("URL_Lif");
static const TCHAR*        STRING_XML_SC_URL_AD                         = _T("URL_Ad");
static const TCHAR*        STRING_XML_SC_URL_HWINFO                     = _T("URL_HwInfo");
static const TCHAR*        STRING_XML_SC_URL_SOFTWARELIST               = _T("URL_SoftwareList");
static const TCHAR*        STRING_XML_SC_URL_DRIVERLIST                 = _T("URL_DriverList");
static const TCHAR*        STRING_XML_SC_URL_CLOUDLIST                  = _T("URL_CloudList");
static const TCHAR*        STRING_XML_SC_URL_CLOUDITEM                  = _T("URL_CloudItem");
static const TCHAR*        STRING_XML_SC_URL_LOGIN                      = _T("URL_Login");
static const TCHAR*        STRING_XML_SC_URL_LOGOUT                     = _T("URL_Logout");
static const TCHAR*        STRING_XML_SC_URL_USERDETAIL                 = _T("URL_UserDetail");
static const TCHAR*        STRING_XML_SC_URL_USERHABIT                  = _T("URL_UserHabit");
static const TCHAR*        STRING_XML_SC_URL_PAUPDATE                   = _T("URL_PaUpdate");

static const TCHAR*        STRING_XML_SC_URL_PaClose                   = _T("PaClose");
static const TCHAR*        STRING_XML_SC_URL_ShowPromt                   = _T("ShowPromt");
static const TCHAR*        STRING_XML_SC_URL_NerverNotify                   = _T("NerverNotify");

//xml�ֶ�Ĭ��ֵ����
static const TCHAR*        STRING_VALUE_SC_CPUWARNPERCENT             = _T("80");
static const TCHAR*        STRING_VALUE_SC_CPUNORMALBKCOLOR           = _T("0,255,0");
static const TCHAR*        STRING_VALUE_SC_CPUWARNBKCOLOR             = _T("255,0,0");
static const TCHAR*        STRING_VALUE_SC_MEMORYWARNPERCENT          = _T("80");
static const TCHAR*        STRING_VALUE_SC_MEMORYNORMALBKCOLOR        = _T("0,255,0");
static const TCHAR*        STRING_VALUE_SC_MEMORYWARNBKCOLOR          = _T("255,0,0");
static const TCHAR*        STRING_VALUE_SC_CPUTimeSpan                  = _T("1");
static const TCHAR*        STRING_VALUE_SC_MemTimeSpan                  = _T("1");

static const TCHAR*        STRING_VALUE_SC_UPDATE_PIPENAME                = _T("PAPipeName");
static const TCHAR*        STRING_VALUE_SC_UPDATE_WNDTITLE                = _T("_PA_Updater");

#ifndef PA_URL_TEST
static const TCHAR*        STRING_VALUE_SC_URL_LIF                         = _T("http://pa.udongman.cn/index.php/inspiration/list");
static const TCHAR*        STRING_VALUE_SC_URL_AD                          = _T("http://pa.udongman.cn/index.php/ad/list");
static const TCHAR*        STRING_VALUE_SC_URL_HWINFO                      = _T("http://pa.udongman.cn/index.php/information/hardware");
static const TCHAR*        STRING_VALUE_SC_URL_SOFTWARELIST                = _T("http://pa.udongman.cn/index.php/software/list");
static const TCHAR*        STRING_VALUE_SC_URL_DRIVERLIST                  = _T("http://pa.udongman.cn/index.php/driver/list");
static const TCHAR*        STRING_VALUE_SC_URL_CLOUDLIST                   = _T("http://pa.udongman.cn/index.php/cloud/list");
static const TCHAR*        STRING_VALUE_SC_URL_CLOUDITEM                   = _T("http://pa.udongman.cn/index.php/cloud/item");
static const TCHAR*        STRING_VALUE_SC_URL_LOGIN                       = _T("http://pa.udongman.cn/index.php/member/user");
static const TCHAR*        STRING_VALUE_SC_URL_LOGOUT                      = _T("http://pa.udongman.cn/index.php/member/user");
static const TCHAR*        STRING_VALUE_SC_URL_USERDETAIL                  = _T("http://pa.udongman.cn/index.php/member/detail");
static const TCHAR*        STRING_VALUE_SC_URL_USERHABIT                   = _T("http://pa.udongman.cn/index.php/information/user_habit");
static const TCHAR*        STRING_VALUE_SC_URL_PAUPDATE                    = _T("http://pa.udongman.cn/index.php/upgrade/file");
#else
static const TCHAR*        STRING_VALUE_SC_URL_LIF                         = _T("http://pa.test.udongman.cn/index.php/inspiration/list");
static const TCHAR*        STRING_VALUE_SC_URL_AD                          = _T("http://pa.test.udongman.cn/index.php/ad/list");
static const TCHAR*        STRING_VALUE_SC_URL_HWINFO                      = _T("http://pa.test.udongman.cn/index.php/information/hardware");
static const TCHAR*        STRING_VALUE_SC_URL_SOFTWARELIST                = _T("http://pa.test.udongman.cn/index.php/software/list");
static const TCHAR*        STRING_VALUE_SC_URL_DRIVERLIST                  = _T("http://pa.test.udongman.cn/index.php/driver/list");
static const TCHAR*        STRING_VALUE_SC_URL_CLOUDLIST                   = _T("http://pa.test.udongman.cn/index.php/cloud/list");
static const TCHAR*        STRING_VALUE_SC_URL_CLOUDITEM                   = _T("http://pa.test.udongman.cn/index.php/cloud/item");
static const TCHAR*        STRING_VALUE_SC_URL_LOGIN                       = _T("http://pa.test.udongman.cn/index.php/member/user");
static const TCHAR*        STRING_VALUE_SC_URL_LOGOUT                      = _T("http://pa.test.udongman.cn/index.php/member/user");
static const TCHAR*        STRING_VALUE_SC_URL_USERDETAIL                  = _T("http://pa.test.udongman.cn/index.php/member/detail");
static const TCHAR*        STRING_VALUE_SC_URL_USERHABIT                   = _T("http://pa.test.udongman.cn/index.php/information/user_habit");
static const TCHAR*        STRING_VALUE_SC_URL_PAUPDATE                    = _T("http://pa.test.udongman.cn/index.php/upgrade/file");

#endif

static const TCHAR*        STRING_VALUE_SC_URL_ShowPromt                       = _T("1");
static const TCHAR*        STRING_VALUE_SC_URL_NerverNotify                    = _T("0");

