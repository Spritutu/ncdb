#pragma once
#include "PiTypeDef.h"
/************************************************************************/
/*  ����: �ṩһЩ��ѧ��صĺ����ӿ�, ��stlʵ��, �������,
/************************************************************************/

template <class InputIterator>
__int64 Sum(InputIterator first, InputIterator last);

template <class InputIterator>
__int64 Average(InputIterator first, InputIterator last);

/************************************************************************
        fun:	�ж�һ�����Ƿ���2�ĳ˷�
        param:  
        ret:    ������򷵻�true, ���򷵻�false
        remark: 
/************************************************************************/
template<class T>
bool Is2Power(T nNum);



template <class InputIterator>
__int64 Sum(InputIterator first, InputIterator last)
{
    __int64 iTotal = 0;
    for (;first != last; ++first)
    {
        iTotal += (*first);
    }
    return iTotal;
}






template <class InputIterator>
__int64 Average(InputIterator first, InputIterator last)
{
    __int64 iTotal = Sum(first, last);

    return iTotal/ (last - first);
}



UNLONG SecondToMillSecond(UNLONG nSecond);
UNLONG MillSecondToSecond(UNLONG nMillSecond);

template<class T>
bool Is2Power(T nNum)
{
	/************************************************************************
		һ������2�ĳ˷�, ��������������λΪ1, ����Ϊ0,  (n-1)& n == 0
	/************************************************************************/
	return (nNum & nNum - 1) == 0;
}
