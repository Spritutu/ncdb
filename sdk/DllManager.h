#pragma once
/************************************************************************
        fun:    ����dll������
        param:  
        ret:    
        remark: 
    /************************************************************************/
#include <Windows.h>
class CDllManager
{
public:
    CDllManager(void);
    ~CDllManager(void);

public:
    bool Load(const char* szFile);
    bool UnLoad();
    HMODULE GetHandle();
	void* GetProc( LPCSTR param1 );
private:
    HMODULE m_hDll;
};
