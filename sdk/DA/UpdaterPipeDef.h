#pragma once

#define STRING_PIPE_PREFIX          _T("\\\\.\\pipe\\")
//��Ϣ����
enum ENUM_PIPE_DATA_TYPE
{
    dt_update_progress = 0, //���½���
    dt_state_notify,        
    dt_error,        

    //����
    dt_notify_exit,            //���������˳�
    dt_notify_down_complete,    //֪ͨ�����������, �Ƿ����
    dt_notify_upgrade,           //�Ƿ�Ҫ����
    dt_notify_version_newest,   //�汾�����������

    //����
    dt_update_now,          //��������
    dt_update_after,        //�´θ���

    dt_upgrade_now,         //����
    dt_upgrade_after,       //�´�����
};

enum ENUM_UPDATER_ERROR_TYPE
{
    u_error_internet = 0,
    u_error_update,

};

struct tagUPDATE_ERROR
{
    const ENUM_PIPE_DATA_TYPE dType;
    ENUM_UPDATER_ERROR_TYPE nErrType;
    tagUPDATE_ERROR()
        :dType(dt_error)
    {
    }
};

struct tagUPDATE_PERCENT
{
    const ENUM_PIPE_DATA_TYPE dType;
    float nPercent;
    int nSpeed;     // 1kb/s
    tagUPDATE_PERCENT()
        :dType(dt_update_progress)
    {
    }
};

//����, ����״̬֪ͨ
struct tagSTATE_NOTIFY
{
    const ENUM_PIPE_DATA_TYPE dType ;
    int nState;
    tagSTATE_NOTIFY()
        :dType(dt_state_notify)
    {

    }
};