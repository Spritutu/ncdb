#pragma once
#include <WinSock2.h>
#include "PiTypeDef.h"
class SocketSelect
{
public:
    SocketSelect(void);
    ~SocketSelect(void);
};

/************************************************************************/
/*  fun: �ж�ָ����socket ��ָ��ms���Ƿ�ɶ�, 
    remark: ��λms
/************************************************************************/
int SelectRead(SOCKET s, UNLONG timeOutMillisecond = 5);
int SelectWrite(SOCKET s, UNLONG timeOutMillisecond = 5);
int GetSelectError();