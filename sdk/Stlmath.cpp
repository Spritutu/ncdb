#pragma once
#include "stdafx.h"
#include "Stlmath.h"
/************************************************************************/
/*  ����: �ṩһЩ��ѧ��صĺ����ӿ�, ��stlʵ��, �������,
/************************************************************************/

UNLONG SecondToMillSecond(UNLONG nSecond)
{
    return nSecond * 1000;
}

UNLONG MillSecondToSecond(UNLONG nMillSecond)
{
    return nMillSecond / 1000;
}