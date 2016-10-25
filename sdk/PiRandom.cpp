#include "StdAfx.h"
#include "PiRandom.h"
#include "PiTypeDef.h"
#include "AutoType.h"
CPiRandom::CPiRandom(void)
{

}


CPiRandom::~CPiRandom(void)
{
}

bool CPiRandom::Init()
{
    //��ʼ�����������
    ::srand((UNINT)::time(NULL));
    return true;
}

int CPiRandom::GetRandomNum( int nMax )
{
    //const int nRandomMax = 32767;
    CPiRandom rd;
    rd.Init();
    nMax = min(nMax, RAND_MAX );

    int nRandom = ::rand();
    TRACE(_T("randomNum: "));
    CAutoType at(nRandom);
    TRACE((tcpchar)at);
    TRACE(_T("\n"));

    //0 to RAND_MAX (32767). 
    //TODO: x Ϊ 0 - 100 �������, +n ��Ϊ n - 100+n �������?

    nRandom = nRandom % (nMax + 1);
    return nRandom;
}
