#pragma once
#include <stddef.h>
/************************************************************************
    fun:    
    author: 
    create time:   
    update time:   
    remark: Ӱ��ĺ� 
        DEBUG_INFO: ���win32������Ϣ
************************************************************************/
void DebugInfo(const char* s);

void DebugInfo(const char* s, int nValue);

void DebugInfo(const wchar_t* s);

void DebugInfo(const wchar_t* s, int nValue);
