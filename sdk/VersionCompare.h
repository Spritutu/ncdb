
#pragma once

#include <string>
#include <vector>
using namespace std;

/*
***********************************************************************
* Theme:	�汾�Ƚ�
* Author:	Ming Zhi.Xue
* Data:		2014/02/28
***********************************************************************
*/

//�汾���Ͷ���
typedef		vector<unsigned char>	VersionT;

//�ַ������Ͷ���
#ifdef UNICODE
typedef		wstring					StlString;
#else
typedef		string					StlString;
#endif//UNICODE

class CVersionCompare
{
public:

	//VersionTת�����ַ�����verlen=-1ʱ��Ĭ�ϳ���
	static StlString	ConvertVersionT2String(__in VersionT& ver,int verlen = -1);

	//�ַ���ת����VersionT��verlen=-1ʱ��Ĭ�ϳ���
	static void			ConvectString2Version(__in StlString strver,__out VersionT& ver,int verlen = -1);

	//�汾�Ƚϣ�0����� 1��v1>v2 -1��v1<v2
	static int			CompareVersion(__in StlString v1,__in StlString v2);

	//�����ַ����Ͱ汾���м�λ�Ӱ汾
	static int			GetStringVersionLength(__in StlString strver);
};
