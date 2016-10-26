#pragma once
/************************************************************************
    fun:    �¼��źŶ���
    remark:
************************************************************************/
#include "PiTypeDef.h"
#include <Windows.h>
class CEventLight
{
public:
	CEventLight(void);
	~CEventLight(void);

public:
	bool Init(tcpchar cName = NULL);
	bool UnInit();
	bool SetEventSign(bool bRet = true);
    
    /************************************************************************
        fun:    ��ȡ��, ֱ���ȴ�ʱ�䳬ʱ�򷵻�
        param: 
        remark: true:������ʱ; false://���ⲿӰ���¼�
    ************************************************************************/
	bool GetLock(UNINT nWaitMax = INFINITE);
	bool Open(const char* cName);
	/************************************************************************
        fun:    ���õȴ��¼���ʱ, ��λ����
        param: 
        remark: 
    ************************************************************************/
	bool SetWaitTimeout( UNINT nWaitMaxMS = INFINITE);
    static bool IsExist( tcpchar cName );
private:
	HANDLE			m_hEventSync;
    UNINT           m_nWaitMax; //���ȴ�ʱ��, ��λms
    DWORD           m_dwErr;
    bool            m_bWaitRet; //�ȴ����, ����֪ͨ�ⲿ�ȴ��ɹ���ʧ��
};
