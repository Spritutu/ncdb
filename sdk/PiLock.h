#pragma once
#include <Windows.h>
class CPiLock
{
public:
    CPiLock(void);
    ~CPiLock(void);

public:
    CPiLock*  Lock();
    void    UnLock();
    
private:
    CRITICAL_SECTION	m_cs;
};


/************************************************************************/
/*  fun:��Դ����������ͷ���Դ
/************************************************************************/
void FunUnLock(CPiLock*   pLock);