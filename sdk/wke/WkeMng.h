#pragma once
#include <windows.h>
#include "wke/PiWkeDef.h"
/************************************************************************** 
        *  @Copyright (c) 2017, ChenMH, All rights reserved. 
     
        *  @file     : WkeMng.h 
        *  @version  : ver 1.0 
     
        *  @author   : liwanliang 
        *  @date     : 2017/01/16 19:02 
        *  @brief    : ���������е�wke web 
**************************************************************************/

//#include "NCWke.h"
class CPiNCWke;

class CWkeMng
{
public:
	CWkeMng();
	~CWkeMng();
public:
	typedef map<HWND, CPiNCWke*> MAP_WKE;
	HWebView GetWebView(HWND hWnd);
	/************************************************************************
			js��
	************************************************************************/
	bool AddJsBind(const wchar_t* szFunc, void* pCallBack);
	void* GetJsCallBack(const string& strName);
	void* GetJsFirstBind();
	void Erase(CPiNCWke* pWke);

	CPiNCWke*			CreateWke();
	CPiNCWke*			CreateWke(HWND hParent, tagCallBack* pTagCallBack);
	CPiNCWke*			GetObj(HWebView pWeb);
protected:

private:
	MAP_JS_BIND					m_mapJsCallBack;
	auto_ptr<CLock>				m_pLockWkeData;		//�����¶��̵߳��õĻ�����
	auto_ptr<CLock>				m_pLockJsCB;
	MAP_WKE						m_mapWke;
};
