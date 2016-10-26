#pragma once
#include <windows.h>
#include "PiTypeDef.h"
/************************************************************************
/*  fun: ��ȡ�������������ĺ�����, ����ʱ�����ֻ�ܱ���20��? ,���������, ��Ҫ����,����MSDN
/************************************************************************/

class CTimeLight
{
public:
    CTimeLight(void);
    ~CTimeLight(void);
    bool    Init();
    void    Start();
    void    Stop();
    DWORD   GetPass();
    
    double  GetPassMS();
	DWORD Pass();
	DWORD PassMS();
	bool IsStart();
	static tstring GetCurrentTick();
	tstring GetPassStr();
private:
    LONGLONG       m_dwTimeBegin;
    LONGLONG       m_dwTimeEnd;
    LONGLONG      m_dwFrequencyPerSecond;
};
