#pragma once
#include "InetDef.h"
using namespace ns_down_file;

//�����е�������Ϣ,ͨ���ص���������ȥ
struct DowningInfoUpdate
{
    float fPercent;     //����, �ٷֱ�, С����, 0.73
    UNINT nSpeed;           //�ٶ�, ��λʱ��������ֽ�
    UNLONG nSizeDowned;     //�����ش�С
    UNLONG nSizeTotal;      //�ܴ�С
};

struct DowningItemInfo
{
    /*ns_down_file::*/ItemID ID;
    UNLONG  dwDowned;        //�������ֽ���
    UNLONG  dwDownedCircle; //��һ�����ڵ��������ص��ֽ���
    UNLONG  dwTotal;        //�ļ����ֽ���
    CInternetHttp*        pInet;
    bool    bShow;      //�Ƿ���ʾ
    DowningItemInfo()
    {
        bShow = true;
        dwDowned        = 0;
        ID              = 0;
        dwDownedCircle  = 0;
        dwTotal         = 0;
        pInet           = NULL;
    }
};

