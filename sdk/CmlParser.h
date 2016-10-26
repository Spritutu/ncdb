#pragma once
#include "PiTypeDef.h"
/*------------------------------------------------------
	Fun:	����������
	remark:	������Ҫÿ��������������ֵ -r [value] -d [value].  ��������û�����ֶ��˿���û�в���ֵ, ��: "-r"  ���� "-r 1 -d"
	Authon: liwanliang
	Date:	2016/03/17
------------------------------------------------------*/
class CCmlParser
{
public:
	CCmlParser(void);
	~CCmlParser(void);
public:
	bool Parse();
	bool IsHasParam( tcpchar szP );
	tstring GetParamValue(tcpchar szP);
	tstring operator[](tcpchar szP);
	tstring GetCml();
	bool Parse( StringCRef strCmd );
	void SetParamFlag(tcpchar szFlag) { m_strSpilit = szFlag;}

public:
	map<tstring, tstring>			m_mapParam;
	tstring							m_strSpilit;
	tstring							m_strCml;
};
