#include "StdAfx.h"
#include "PiThread.h"

CPiThread::CPiThread( ProcThreadFun pFun /*= NULL*/, void* pAdd /*= NULL*/ )
:CThreadLight(pFun, pAdd)
{
	//TODO:�����߳�
	CThreadLight::DieKillThread(false);
	CThreadLight::Init();
	CThreadLight::Run();
	CThreadLight::WaitInitDone();
	//��ȡ���߳�id���ٷ���
}

CPiThread::~CPiThread(void)
{
}
/*

DWORD CPiThread::ProcObjCall( void* paramR )
{
	(CPiThread*)paramR;
	return 1;
}

bool CPiThread::DoRunEnd(DWORD dwRet)
{
	::SendMessage(m_hWnd, m_nMsgID, dwRet, NULL);
	return true;
}

unsigned CPiThread::ThreadRun()
{
	m_pObj->*(m_procThreadFun)(NULL);
	return 1;

}
*/
