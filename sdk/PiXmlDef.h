#pragma once
#include "PiTypeDef.h"

#ifdef MARKUP_STL
    #define PiString tstring
#else
    #define PiString CString
#endif

//��ֵ����
#define STRING_XML_NOTE_ROOT            _T("root")

enum ENUM_DATA_MODE
{
    mode_read = 0,
    mode_write
};

enum ENUM_MODE_OPEN
{
    mode_open_create = 2<<0,
    mode_open_read = 2<<1,
};

//�궨��

//ʵ��ReadWriteConfig��һϵ�нӿ�

// bool CDAXmlUserConfig::Type( UserConfigData& ucData, tstring& strData )\
// 
// {                                       \
//     if(m_dataMode == mode_read)         \
// {                                   \
//     strData = ucData. ## FieldName;     \
// }                                   \
//     else                                \
// {                                   \
//     ucData. ## FieldName = strData;     \
// }                                   \
//     return true;                        \
// }

//�ӿڸ��ṹ���ֶΰ�
#define IMP_READ_WRITE_COMMON(Class, InterFaceT, DataStruct, FieldName) \
    bool Class::InterFaceT( DataStruct& ucData, tstring& strData )\
    {                                       \
        if(m_dataMode == mode_read)         \
    {                                   \
        strData = ucData. ## FieldName;     \
    }                                   \
    else                                \
    {                                   \
        ucData. ## FieldName = strData;     \
    }                                   \
    return true;                        \
}


//������ְ��ͽӿ�����Ӧ����
#define Imp_Duty_Cn_Interface(Duty, InterfaceFun) \
    case Duty:\
    {                                                       \
        bRet = InterfaceFun(ucData, strData); \
    }                                                       \
    break;