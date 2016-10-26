#pragma once
#include "PiTypeDef.h"
#include "DataStruct\PiRect.h"
#include <shellapi.h>

class CPiWindowPack
{
public:
	CPiWindowPack(void);
	~CPiWindowPack(void);
public:
	static bool _ModifyStyle(HWND hWnd, UNINT nRemove, UNINT nAdd, int nStyle);
	static bool ModifyStyleEx(HWND hWnd, UNINT nRemove, UNINT nAdd);
	static bool ModifyStyle(HWND hWnd, UNINT nRemove, UNINT nAdd );
	static bool MoveWindow(HWND hWnd, POINT ptDist );
	static bool MoveWindow(HWND hWnd, int nX, int nY);
	static 	SIZE GetWindowSize(HWND hWnd);
	static bool GetWindowPos(HWND hWnd, POINT& pt);
	static bool ChangeSize(HWND hWnd, POINT ptSize );
	/*------------------------------------------------------------
			fun:	
			ret:	
			param: nWidth��nHeightΪ-1ʱ ʹ��ԭ���Ŀ�Ȼ�߶�
			remark:	
	------------------------------------------------------------*/
	static bool ChangeSize(HWND hWnd, int nWidth, int nHeight );
	static bool SetTrackMouse(HWND hWnd);
	static bool TopMostWindow( HWND hWnd , bool bTopMost = true);
	static bool TopWindow( HWND hWnd );
	static bool SetNoTaskWindow( HWND hWnd );


	static POINT GetScreenSize();

	/************************************************************************
			fun:    ��ȡ�����С, ������������
			param: 
			remark: 
	************************************************************************/
	static POINT GetDeskTopSize();
	static RECT GetDeskTopRect();


	/************************************************************************
        fun:    ����ָ�����ڴ�С��ȡ ��ʾ���������½�ʱ������λ��
        param: 
        remark: 
	************************************************************************/
	static POINT CalcWndCloseRightBottomPos( int nCx, int nCy );
	static POINT CalcWndCloseRightTopPos( HWND hWnd,  POINT ptSpace);
	static POINT CalcWndCloseRightBottomPos( HWND hWnd,  POINT ptSpace);
	static HWND GetWindowHWND( tcpchar strTitle, tcpchar strClassName );

	/*------------------------------------------------------------
			fun:	����֧���ļ��Ϸ�
			ret:	
			param: 
			remark:	������, ���ڿɽ��ܵ�WM_DROPFILES���ļ��Ϸ���Ϣ, (WPARAM) = (HDROP) hDrop;
	------------------------------------------------------------*/
	static bool EnableDrawFile( HWND hWnd, bool bAccept = true);
	static tstring GetOneDragFilePath(const HDROP& hd, bool bDropFinish = true);
	static LST_STRING GetDragFilePathList( const HDROP& hd, bool bDropFinish = true);

	static bool IsOwnerWindow(HWND hParent, HWND hFind);
	static bool CenterWindow( HWND hWnd, HWND hWndBase );
	/*------------------------------------------------------------
			fun:	
			ret:	���ز��ֺ���Ҫ�Ŀ��
			param: 
			remark:	
	------------------------------------------------------------*/
	static int CenterPosX( ARR_RECT& lstRect, int nSpace, int nAreaWidth);
	static bool UpdateChange(HWND hWnd);
	static HWND FindWindowChild(LST_STRING& lstWndClass);
	static RECT GetClientRectToParent(HWND hWnd);
};
