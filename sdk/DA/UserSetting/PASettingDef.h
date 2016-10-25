#pragma once
#include "PiTypeDef.h"
//����ѡ���ʶ

#define IMP_UC_READ_WRITE(InterFaceT, FieldName) \
    IMP_READ_WRITE_COMMON(CPAXmlUserConfig, InterFaceT, UserConfigData, FieldName)

enum ENUM_DATA_DUTY
{
    dn_unKnown = 0,
    dn_launch_as_boot, //�����ϵͳ����
    dn_close_app,
    dn_task,        //�����Ƿ���滭�������
    dn_app_save_setting,    //Ӧ�ñ�������
    dn_app_save_dir,        //Ӧ�ñ���Ŀ¼
    dn_driver_save_setting,    //������������
    dn_driver_save_dir,        //��������Ŀ¼
    dn_desktop_record_path,
    dn_works_save_path,
    dn_fontLib_save_path,
    dn_update_type,
    dn_flow_auto_open,
    dn_flow_top_wnd,
};

 enum ENUM_DATA_TYPE
 {
     dt_enum = 0,   //ö����������
     dt_path,       //�ַ���
 };

enum ENUM_OPTION_PAGE
{
    op_general = 0,
    op_app,
    op_update,
    op_flow
};






static const TCHAR*        STRING_XML_UC_ELEM_COMMON       = _T("Common");
static const TCHAR*        STRING_XML_UC_ELEM_AUTO_OPEN    = _T("AutoOpen");
static const TCHAR*        STRING_XML_UC_ELEM_EXIT_TYPE    = _T("ExitType");
static const TCHAR*        STRING_XML_UC_ELEM_TASK         = _T("Task");

static const TCHAR*        STRING_XML_UC_ELEM_APP          = _T("Application");

static const TCHAR*        STRING_XML_UC_ELEM_SOFT         = _T("Soft");
static const TCHAR*        STRING_XML_UC_ELEM_SOFT_PACKAGESAVE  = _T("PackageSave");
static const TCHAR*        STRING_XML_UC_ELEM_SOFT_PACKAGEPATH  = _T("PackagePath");

static const TCHAR*        STRING_XML_UC_ELEM_DRIVER         = _T("Driver");
static const TCHAR*        STRING_XML_UC_ELEM_DRIVER_PACKAGESAVE    = _T("PackageSave");
static const TCHAR*        STRING_XML_UC_ELEM_DRIVER_PACKAGEPATH         = _T("PackagePath");

static const TCHAR*        STRING_XML_UC_ELEM_VIDEO            = _T("video");
static const TCHAR*        STRING_XML_UC_ELEM_VIDEO_PATH           = _T("Path");
static const TCHAR*        STRING_XML_UC_ELEM_WORKSSAVE        = _T("WorksSave");
static const TCHAR*        STRING_XML_UC_ELEM_WORKS_PATH           = _T("Path");
static const TCHAR*        STRING_XML_UC_ELEM_FONTLIB          = _T("Fontlib");
static const TCHAR*        STRING_XML_UC_ELEM_FONT_PATH           = _T("Path");

static const TCHAR*        STRING_XML_UC_ELEM_UPDATE           = _T("Update");
static const TCHAR*        STRING_XML_UC_ELEM_UPATETYPE           = _T("UpateType");

static const TCHAR*        STRING_XML_UC_ELEM_FLOWWND           = _T("FlowWnd");
static const TCHAR*        STRING_XML_UC_ELEM_FLOW_SHOW           = _T("Show");
static const TCHAR*        STRING_XML_UC_ELEM_FLOW_AUTOOPEN           = _T("AutoOpen");
static const TCHAR*        STRING_XML_UC_ELEM_FLOW_TOPMOST           = _T("Topmost");



//Ĭ��ֵ

static const TCHAR*        STRING_UC_VALUE_SOFT_AUTO_OPEN_ENABLE          = _T("1");
static const TCHAR*        STRING_UC_VALUE_SOFT_AUTO_OPEN_DISABLE          = _T("0");

static const TCHAR*        STRING_UC_VALUE_EXIT_TYPE_EXIT       = _T("1");
static const TCHAR*        STRING_UC_VALUE_EXIT_TYPE_OTHER      = _T("0");

static const TCHAR*        STRING_UC_VALUE_TASK_Manual      = _T("1");
static const TCHAR*        STRING_UC_VALUE_TASK_AS_DRAWER   = _T("0");

static const TCHAR*        STRING_UC_VALUE_PACKAGESAVE_DELETE   = _T("0");
static const TCHAR*        STRING_UC_VALUE_PACKAGESAVE_SAVE     = _T("1");

static const TCHAR*        STRING_UC_VALUE_PACKAGEPATH     = _T("C:\\temp");

static const TCHAR*        STRING_UC_VALUE_DRIVER_PACKAGESAVE_SAVE       = _T("1");
static const TCHAR*        STRING_UC_VALUE_DRIVER_PACKAGESAVE_DELETE       = _T("0");

static const TCHAR*        STRING_UC_VALUE_D_PACKAGEPATH       = _T("C:\\temp");

static const TCHAR*        STRING_UC_VALUE_VIDEO_PATH               = _T("C:\\temp");
static const TCHAR*        STRING_UC_VALUE_W_PATH                   = _T("C:\\temp");
static const TCHAR*        STRING_UC_VALUE_F_PATH                   = _T("C:\\temp");

static const TCHAR*        STRING_UC_VALUE_UPATETYPE_AUTO          = _T("0");
static const TCHAR*        STRING_UC_VALUE_UPATETYPE_NOAUTO          = _T("1");

static const TCHAR*        STRING_UC_VALUE_FLOW_AUTOOPEN_YES          = _T("1");
static const TCHAR*        STRING_UC_VALUE_FLOW_AUTOOPEN_NO          = _T("0");

static const TCHAR*        STRING_UC_VALUE_FLOW_TOPMOST_YES             = _T("1");
static const TCHAR*        STRING_UC_VALUE_FLOW_TOPMOST_NO              = _T("0");

struct UserConfigData
{
    //ͨ������       
    tstring appAutoLaunch;
    tstring exitType;   //�ر�Ӧ�ó���Ĳ���
    tstring task;


    //Ӧ������
    tstring softPackageSave;
    tstring softPackagePath;

    //��������
    tstring dPackageSave;
    tstring dPackagePath;

    tstring videoPATH;
    tstring worksPath;
    tstring fontPath;

    tstring updateType;
    tstring flowAutoOpen;
    tstring flowTopMost;
};

