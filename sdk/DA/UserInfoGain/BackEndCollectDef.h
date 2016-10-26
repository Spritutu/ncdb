#pragma once
#include <map>
#include "PiTypeDef.h"
using namespace std;
typedef time_t     TimeType;

//�û���Ϣ����ְ��
 enum ENUM_UD_DATA_DUTY
 {
     unKnown = 0,
     da_btn_use_my_assist,               
     da_btn_use_my_assist_protect_works, //��Ʒ������ť
     ps_use_times,
     ps_use_time_duration,
     sai_use_times,
     sai_use_time_duration
 };
// 
// enum ENUM_UD_TIMES_TYPE
// {
//     tt_ps = 0,
//     tt_csa,
//     tt_DA,
//     tt_da_btn_record,
//     tt_sai,
// };
// 
// enum ENUM_UD_TIME_DURATION_TYPE
// {
//     td_ps = 0,
//     td_csa,
//     td_DA
// };

struct TimeDuration
{
    bool        bExistPre;  //�ϴ��Ƿ����
    TimeType timeTotal;     //�ܴ���ʱ��
    TimeType timeLast;      //��һ�ε�ʱ��, 
    
};



typedef map<ENUM_UD_DATA_DUTY, UNINT> LST_USE_COUNT;
typedef map<ENUM_UD_DATA_DUTY, TimeDuration> LST_TIME_DURATION;
