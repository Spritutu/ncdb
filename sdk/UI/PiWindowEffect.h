#pragma once
#include "PiTypeDef.h"
#include "DataStruct/PiPoint.h"
Pi_NameSpace_Begin
class CPiWindowEffect
{
public:
	struct tagParam
	{
		tstring strPic;
	 	HWND hWnd;
	 	CPiPoint ptStart;
	 	CPiPoint ptDist;
	};
	CPiWindowEffect(void);
	~CPiWindowEffect(void);
public:
	//static bool CreateWindowMoveToPointLine( HWND hWnd, POINT& ptDist);

	static bool MoveToPointLine( HWND hWnd, POINT& ptDist);

	static DWORD _MoveToPointLine(void* paramR);
	static bool CreateWindowMoveToPointLine( tcpchar szPic, const POINT& ptStart, const POINT& ptDist );
	static DWORD _CreateWindowMoveToPointLine( void* paramR );
public:
	UNINT	m_nShowTime;	//Ч������ʱ��
};

Pi_NameSpace_End
