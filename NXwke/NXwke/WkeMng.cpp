#include "WkeMng.h"
#include "WkeMng.h"


CWkeMng::CWkeMng()
{
}


CWkeMng::~CWkeMng()
{
}

bool CWkeMng::Exist(HWND hWnd)
{
	return m_pWkeData.find(hWnd) != m_pWkeData.end();
}

wkeWebView* CWkeMng::GetWebView(HWND hWnd)
{
	return m_pWkeData[hWnd].pWeb;
}

tagWKE_DATA* CWkeMng::operator[](HWND hWnd)
{
	return &m_pWkeData[hWnd];
}

tagWKE_DATA* CWkeMng::GetStruct(wkeWebView* pWeb)
{
	//TODO:����Web��ȡ����Ӧ������
	if (m_pWkeData.size())
	{
		return &m_pWkeData.begin()->second;
	}
	return NULL;
}
