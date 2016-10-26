#pragma once
#include "PiTypeDef.h"
#include <string>
#include <list>
#include "define_gnl.h"

/*******************************
    ����ģ�������Ϣ��
*******************************/
#define MACRO_PI_INET_DEBUG_INFO

using std::string;
using std::list;

class CInternetHttp;
class CTrDownFile;

namespace ns_down_file
{
    typedef void (*CBDowningInfo)(void*, void*);
    typedef int ItemID;
    typedef CInternetHttp CDownItem;
}

enum TaskState
{
    ts_new_add = 0          ,
    ts_downing              ,
    ts_retry                ,
    ts_done                 ,
};

enum DownState
{
	ok_completion = 0,
    ok_downing,
	err_net,				//������������Ĵ���
	err_local_file,			//�����ļ�����
    err_file_create,        //�����ļ�
    err_file_write,         //д�ļ�
    err_server_404,         //�������ҳ404 ����
	err_server_403,         //�������ҳ405 ����, ���������ܾ�������
    err_proxy,              //��������Ĵ���
    err_user_cancel,        //�û�ȡ������
    err_user_stop,          //�û���ͣ����
    err_get_file_size,      //��ȡ�ļ���Сʧ��
	err_server,
	err_too_big,	
	err_unKnown,
};


struct DownFileInfo
{
public:
    //using ns_down_file::ItemID;

	tstring strUrl;
	tstring strSavePath;
	DownState	dState;	//����״̬
    TaskState   taskState;  //����״̬
    UNINT       nServerCode;
    UNINT       nErrCode;   //�������
    bool        bUseServerName; //�Ƿ�ʹ�÷������ϵ�������Ϊ���ر����ļ���
    UNINT       nAddi;  //��������
    bool        bNeedBPDown;    //�������Ƿ���öϵ�����
    ns_down_file::ItemID      itemID;     //ÿ�������Ψһ��ʶ

    DownFileInfo()
    {
        dState          = err_unKnown;
        taskState       = ts_new_add;
        bUseServerName  = false;
        itemID          = 0;
        nAddi           = NULL;
        nServerCode     = 0;
    	nErrCode		= 0;   //�������
        bNeedBPDown     = false;
    }
    
};

typedef list<DownFileInfo>	DownList;
typedef list<CTrDownFile*>	DownObjList;


//����������ÿ��Ԫ��
#define FOR_EACH_DOWN_TASK(Cn, Iter)\
    FOR_EACH_ITER(DownList, Cn, Iter)
