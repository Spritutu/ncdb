#pragma once
#include "PiTypeDef.h"
class CUIDataChange
{
public:
	CUIDataChange(void);
	~CUIDataChange(void);
public:
	static float GetNumAmount( StringCRef strTemp );
	//ȥ���ַ����������ߵĿո�, ���еȿ��ַ�
	static tstring TermStr(StringCRef strData);
	static double PercentSignToDecimal( StringCRef strTemp );
	static double PercentToDecimal( StringCRef strTemp );
};

