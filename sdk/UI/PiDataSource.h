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
	bool BeginDrag(tcpchar szPath);

	/************************************************************************
		fun:	��λ�û�ͼƬ·����������ͼ
		param:	
		memo:	
	************************************************************************/
	void GeneralPic(RECT rtPic);
	void GeneralPic(tcpchar szPath);
	/************************************************************************
		fun:	����ͼƬ����ͼ����� ͨ���þ�������϶���ͼƬ�ĳߴ�
		param:
		memo:
	************************************************************************/
	void SetDragImage(HBITMAP hBitDrag);

	bool Drag(tcpchar szPath);
	void SetWindow(HWND hWnd);
	bool IsFrstDrag();
	void OnFirstDrag();
	bool CanDrag();
	void CancelDrag();
	void SetClientPos(bool bClient);
	/************************************************************************
		fun:	��������ͼͼƬ���ĳߴ�
		param:	
		memo:	
	************************************************************************/
	void SetDragImageSize(int cx, int cy);
	SIZE GetDragImgDistSize(const SIZE& szSrc);
	static UINT RegisterSelfFlag();
	static UINT DataDragSelfFlag() { return m_nDataDragSelfFlag; }
private:
	HWND				m_hWnd;			//ref
	HDC					m_dc;
	HBITMAP				m_hDragBitmap;
	SIZE				m_szDragImg;
	static UINT				m_nDataDragSelfFlag;
	
	bool m_bDraging;
	bool m_bBtnDown;
	bool m_bClientPos;
};

