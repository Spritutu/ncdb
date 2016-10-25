#pragma once
#include <Windows.h>
class CLock
{
public:
    CLock(void);
    ~CLock(void);

public:
    CLock*  Lock();
    void    UnLock();
    
private:
    CRITICAL_SECTION	m_cs;
};


/************************************************************************/
/*  fun:��Դ����������ͷ���Դ
/************************************************************************/
void FunUnLock(CLock*   pLock);