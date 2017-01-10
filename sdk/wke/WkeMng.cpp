#include "stdAfx.h"
#include "WkeMng.h"
#include "StrCoding.h"
#include "RAIILock.h"
#include "PiNCWke.h"
#include "System\LogSystemDll.h"

CWkeMng::CWkeMng()
{
	Create_Auto_Ptr(m_pLockWkeData, CLock);
	Create_Auto_Ptr(m_pLockJsCB,	CLock);
}


CWkeMng::~CWkeMng()
{
}

/*
bool CWkeMng::Exist(HWND hWnd)
{
	CRAIILock raii(m_pLockWkeData.get());
	return m_pWkeData.find(hWnd) != m_pWkeData.end();
}*/

HWebView CWkeMng::GetWebView(HWND hWnd)
{
	CRAIILock raii(m_pLockWkeData.get());
	if (m_mapWke.find(hWnd) == m_mapWke.end())
	{
		return NULL;
	}
	return m_mapWke[hWnd]->GetWeb();
}
/*

tagWKE_DATA* CWkeMng::operator[](HWND hWnd)
{
	//CRAIILock raii(m_pLockWkeData.get());
	return &m_mapWke[hWnd];
}*/

/*
tagWKE_DATA* CWkeMng::operator[](HWebView pWeb)
{
	return GetStruct(pWeb);
}
*/

/*
tagWKE_DATA* CWkeMng::GetStruct(HWebView pWeb)
{
	MAP_WKE_DATA::iterator it = GetStructIter(pWeb);
	if (it != m_pWkeData.end())
	{
		return &it->second;
	}
	return NULL;
}*/

/*
MAP_WKE_DATA::iterator CWkeMng::GetStructIter(HWebView pWeb)
{
	//����Web��ȡ����Ӧ������
	if (!pWeb)
	{
		return m_pWkeData.end();
	}
	CRAIILock raii(m_pLockWkeData.get());
	if (!m_pWkeData.size())
	{
		return m_pWkeData.end();
	}

	FOR_EACH_ITER_C11(m_pWkeData, it)
	{
		if (it->second.pWeb == pWeb)
		{
			return it;
		}
	}
	return m_pWkeData.end();
}
*/

/*
CRender* CWkeMng::GetRender(HWebView pWeb)
{
	tagWKE_DATA* pWD = GetStruct(pWeb);
	if (pWD)
	{
		return pWD->pRender;
	}
	return NULL;
}*/

/*
bool CWkeMng::Release(HWebView pWeb)
{
	CRAIILock raii(m_pLockWkeData.get());
	MAP_WKE_DATA::iterator it = GetStructIter(pWeb);
	tagWKE_DATA* pWD = &it->second;
	CRAIILock raii2(pWD->pLock);		//��ִֹ�нű����ͷŽӿڶ��̵߳���

	if (!pWD)
	{
		return false;
	}

	if (pWD->pRender)
	{
		pWD->pRender->destroy();
		pWD->pRender = nullptr;
	}
	wkeDestroyWebView((HNCwkeWebView)pWeb);
	::DestroyWindow(pWD->hParent);
	Erase(it);
	return true;
}*/

/*
void CWkeMng::Erase(MAP_WKE_DATA::iterator it)
{
	CRAIILock raii(m_pLockWkeData.get());
	m_pWkeData.erase(it);
}*/

void CWkeMng::Erase(CPiNCWke* pWke)
{
	CRAIILock raii(m_pLockWkeData.get());
	for (auto iter = m_mapWke.begin(); iter != m_mapWke.end(); ++iter)
	{
		if (iter->second == pWke)
		{
			m_mapWke.erase(iter);
			pWke->ClearData();
			delete pWke;
			break;
		}
	}

}

/*
tagWKE_DATA* CWkeMng::GetFirst()
{
	CRAIILock raii(m_pLockWkeData.get());
	if (!m_pWkeData.size())
	{
		return NULL;
	}
	return &m_pWkeData.begin()->second;
}*/


void* CWkeMng::GetJsCallBack(const string& strName)
{
	CRAIILock raii(m_pLockJsCB.get());
	if (!m_mapJsCallBack.size())
	{
		return NULL;
	}
	return m_mapJsCallBack[strName];
}

void* CWkeMng::GetJsFirstBind()
{
	CRAIILock raii(m_pLockJsCB.get());
	if (!m_mapJsCallBack.size())
	{
		return NULL;
	}
	return m_mapJsCallBack.begin()->second;
}


bool CWkeMng::AddJsBind(const wchar_t* szFunc, void* pCallBack)
{	
	CRAIILock raii(m_pLockJsCB.get());
	m_mapJsCallBack[pw2psSmart(szFunc)] = pCallBack;
	return true;
}

/*
bool CWkeMng::IsValidWeb(HWebView pWeb)
{
	if (!pWeb)
	{
		return false;
	}
	CRAIILock raii(m_pLockWkeData.get());
	if (!m_pWkeData.size())
	{
		return false;
	}

	FOR_EACH_ITER_C11(m_pWkeData, it)
	{
		if (it->second.pWeb == pWeb)
		{
			return true;
		}
	}
	return false;
}*/

CPiNCWke* CWkeMng::CreateWke()
{
	CPiNCWke* pNew = new CPiNCWke;
	//m_lstWke.push_back(pNew);
	return pNew;
}

CPiNCWke* CWkeMng::CreateWke(HWND hParent, tagCallBack* pTagCallBack)
{
	CPiNCWke* pWke = CreateWke();
	if (!pWke)
	{
		LogSystem::WriteLogToFileErrorFormat(_T("create wke on parent %d faild: new Null"), hParent);
		return nullptr;
	}
	if (!pWke->Create(hParent, pTagCallBack))
	{
		return nullptr;
	}
	
	CRAIILock raii(m_pLockWkeData.get());
	m_mapWke[pWke->GetParent()] = pWke;
	return pWke;
}

CPiNCWke* CWkeMng::GetObj(HWebView pWeb)
{
	CRAIILock raii(m_pLockWkeData.get());
	for (auto it : m_mapWke)
	{
		if ((it.second)->GetWeb() == pWeb)
		{
			return it.second;
		}
	}
	return nullptr;
}
