#pragma once
/*******************************************************************
*  �ļ�����:
*  ��Ҫ����:
*
*  ��������: 2016-12-27
*  ����: liwanliang
*  ˵��: �������϶���ȥ��ģ��
*
*  �޸�����:
*  ����:
*  ˵��:
******************************************************************/

#include "PiTypeDef.h"
#include <windows.h>

class CPiDataSource
{
public:
	CPiDataSource();
	~CPiDataSource();
public:
	bool PrepareDrag();
	bool BeginDrag(tcpchar szPath, RECT rt);
	void GeneralPic(RECT rtPic);
	bool Drag(tcpchar szPath);
	void SetWindow(HWND hWnd);
	bool IsFrstDrag();
	void OnFirstDrag();
	bool CanDrag();
	void CancelDrag();
	void SetClientPos(bool bClient);
private:
	HWND				m_hWnd;
	HDC					m_dc;
	HBITMAP				m_hDragBitmap;
	bool m_bDraging;
	bool m_bBtnDown;
	bool m_bClientPos;
};

