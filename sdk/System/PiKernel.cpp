#include "StdAfx.h"
#include "PiKernel.h"
#include "StrCoding.h"
#include "PiProcess.h"
#include "functional.h"
#include "TimeLight.h"
#include "PiString.h"
#include "Math\mathUnit.h"
#include "RAIILock.h"
#include "Lock.h"
#include <shlwapi.h>
#include <shellapi.h>
const int		NUM_DOS_EXECUTE_SUCCESS_CODE			= 0;
const ULONG		NUM_UN_ELAPSE_PERIOD					= 999999999;
Pi_NameSpace_Using

#pragma comment(lib, "shell32.lib")

bool CPiKernel::Init()
{
	Create_Auto_Ptr(m_pLockTimerQueue, CLock);
	Create_Auto_Ptr(m_pLockMapList,		CLock);
	Create_Auto_Ptr(m_pLockTimer,		CLock);
	m_enTimerMode = mode_queue;	
	return TRUE;
}

CPiKernel::CPiKernel(void)
{
	m_hTimerQueue = NULL;
	Init();
}

CPiKernel::~CPiKernel(void)
{
	ReleaseAllTimer();
}

bool CPiKernel::ExecuteDos( tcpchar szCmd, string& strOut, DWORD dwWaitMillSec /*= INFINITE*/)
{
	SECURITY_ATTRIBUTES sa = {0};  
	HANDLE hRead = NULL , hWrite = NULL;  
	const int NUM_RESULT_BUF = 4096;

	sa.nLength = sizeof(SECURITY_ATTRIBUTES);  
	sa.lpSecurityDescriptor = NULL;  
	sa.bInheritHandle = TRUE;  

	DWORD dwPipeBufSize = 1024 * 16;
	//DWORD dwPipeBufSize = 1024 * 2;
	if (!CreatePipe(&hRead, &hWrite, &sa, dwPipeBufSize))
	{  
		return FALSE;  
	}   

	HANDLE hCmdInputRead = NULL , hCmdInputWrite = NULL;		//TODO:��Դ�ͷ�, SEH
	if (!CreatePipe(&hCmdInputRead, &hCmdInputWrite, &sa, dwPipeBufSize))   
	{  
		return FALSE;  
	}   


	string strCmd(tp2s(szCmd));

	STARTUPINFO si = {0};  
	PROCESS_INFORMATION pi = {0};   
	si.cb = sizeof(STARTUPINFO);  
	GetStartupInfo(&si);   
	si.hStdError = hWrite;            //�Ѵ������̵ı�׼��������ض��򵽹ܵ�����  
	si.hStdOutput = hWrite;           //�Ѵ������̵ı�׼����ض��򵽹ܵ�����  
	si.hStdInput = hCmdInputRead;
	si.wShowWindow = SW_HIDE;  
	//si.wShowWindow = SW_SHOW;  
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;  

	tstring strCmdBin(_T("Cmd.exe /Q"));		//��Ϊ��Щ�ⲿ��������Ϊansi�ַ�, ����ͳһʹ��ansi�ַ���

	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[0] = 0; //ɾ���ļ�����ֻ���·��
	CPiString strCurrentDir(szFilePath);

	//OutInfo(_T("adb, ���̴�"));
	if ( !CreateProcess(NULL, &strCmdBin.at(0), NULL, NULL, TRUE, NULL, NULL, strCurrentDir.c_str(), &si, &pi) )
	{  
		CloseHandle(hWrite);
		CloseHandle(hRead);  
		return FALSE;  
	}  

	//������д��cmd����


	

	CHAR szBuf[NUM_RESULT_BUF + 1] = {0};	//��4K�Ŀռ����洢��������ݣ�ֻҪ������ʾ�ļ����ݣ�һ��������ǹ����ˡ�  
	int nCharLen = 1;
	string strBuf; 

	DWORD bytesRead;   

	//���˵�cmd�����Ȼ�����Ϣ, �ȴ���ʾ, ֱ���е�ǰ·������

	CPiString strCmdEchoHeader;
	while(1)
	{
		if (! (ReadFile(hRead, szBuf, NUM_RESULT_BUF, &bytesRead, NULL)
			&& bytesRead))
		{
			OutInfo(_T("��ȡ����ʧ��"));
			return false;
		}
		//OutInfo(_T("header��ȡ������"), ps2pwSmart(szBuf));
		strCmdEchoHeader += ps2pwSmart(szBuf);
		if(strCmdEchoHeader.Exist(strCurrentDir))
		{
			break;
		}
	}
	

	//ÿ�δ�cmd.exe����, ͨ���ܵ�������д��, ͨ������ܵ���ȡ��ִ�н��, ͨ������ & exit��ʽ, ʵ��ִ���������رճ���, 
	DWORD dwWrite = 0;
	strCmd += "& exit\r\n";
	BOOL dwRet = WriteFile(hCmdInputWrite, strCmd.c_str(), strCmd.length() * nCharLen, &dwWrite, NULL);

	if(!dwRet)
	{
		return false;
	}


	CTimeLight time;
	time.Init();
	time.Start();


	DWORD dwEmptyDuration = 0;
	DWORD dwReadTotal = 0;
	char szBufPeek[2] = {0};
	DWORD dwPeekAvail = 0;



	while(1)
	{
		if(!PeekNamedPipe(hRead, szBufPeek, sizeof(szBufPeek), NULL, &dwPeekAvail, NULL))
		{
			OutInfo(_T("ker-peek fail"));
			break;
		}
		if (dwPeekAvail <= 0)
		{
			if( WAIT_OBJECT_0 == WaitForSingleObject(pi.hProcess, 0))
			{
				//cmd.exe�������˳�
				//OutInfo(_T("ker-cmd.exe�������˳�"));
				break;
			}
			
			dwEmptyDuration = time.PassMS();
			if ( /*time.IsStart() &&*/ dwEmptyDuration > dwWaitMillSec && dwReadTotal <= 0/*û�յ��κ�����*/)
			{
				//���ݳ�ʱ, ִ��ʧ��
				//OutInfo(_T("ker-û�յ��κ�����, �ж�ִ��ʧ��"));
				return false;
			}
			//��ʼ��ʱ
			continue;
		}
		
		memset(szBuf, 0, NUM_RESULT_BUF);
		if (ReadFile(hRead, szBuf, NUM_RESULT_BUF * nCharLen, &bytesRead,NULL)
			&& bytesRead)
		{
			//OutInfo(_T("����������:"), ps2pwSmart(szBuf));
			//OutInfo(_T("����������:"), ps2pwSmart(szBuf));
			dwReadTotal += bytesRead;
			strBuf += szBuf;
			time.Start();
		}
		
	}
	//OutInfo(_T("adb, ���ݶ�ȡ����"));

	//����ص��ַ�����cmdִ�еĵ�ǰ����Ŀ¼+>֮��


	CloseHandle(hWrite);  

	CloseHandle(hRead);   
	strOut = strBuf;
	//strOut = strBuf;

	/*size_t nPos = strOut.find(strCurrentDir);
	strOut = strOut.substr(nPos + strCurrentDir.length() + 1);*/


	//TODO:�����򿪵Ľ���
	//�жϽ����Ƿ񻹴���
	DWORD dwExitCode = 0;
	if(CPiProcess::IsProcessExistHandle(pi.hProcess, &dwExitCode))
	{
		//OutInfo(_T("adb,���̻�����"));
	}
	else
	{
		//OutInfo(_T("adb, ���̽���"));
	}

	if (NUM_DOS_EXECUTE_SUCCESS_CODE != dwExitCode)
	{
		return false;
	}
	//TerminateProcess(pi.hProcess, -1);
	return TRUE;  
}


bool CPiKernel::ExecuteDos( tcpchar szCmd, tstring& strOut, DWORD dwWaitMillSec /*= INFINITE*/ )
{
	string sOA;
	bool bRet = ExecuteDos(szCmd, sOA, dwWaitMillSec);
	strOut = s2t(sOA);
	return bRet;
}

bool ns_PiPi::CPiKernel::BeginTimer( CB_TimerFunc cbTimer, UNINT nCircle, PVOID nData /*= NULL*/, bool oneOff /*= false*/, TimerID nTimer /*= 0*/ )
{
	if (!nTimer && !oneOff)
	{
		return false;
	}
	if(!CreateTimerQ())
	{
		return false;
	}
	
	tagPTTimer* tagTimer = NULL;
	
	CRAIILock raii(m_pLockTimer);
	if (!m_hTimerQueue)
	{
		return false;
	}

	/*-------------------- �����ʱ�����ڲ���������, ����и������� --------------------*/
	if(IsExistTimer(nTimer))
	{
		tagTimer = GetParam(nTimer);
		::ChangeTimerQueueTimer(m_hTimerQueue, tagTimer->hTimer, nCircle, NUM_UN_ELAPSE_PERIOD);
	}
	else
	{
		tagTimer = new tagPTTimer;
		tagTimer->hTimer = NULL;
		tagTimer->nTimerID = nTimer;
		DWORD dwPeriod = oneOff ? 0 : (m_enTimerMode == mode_queue ? NUM_UN_ELAPSE_PERIOD : nCircle);

		if( ! ::CreateTimerQueueTimer(&tagTimer->hTimer, m_hTimerQueue, &CPiKernel::TimerCallback, 
			tagTimer, nCircle, dwPeriod, WT_EXECUTEDEFAULT))
		{
			delete tagTimer;
			return NULL;
			/*-------------------- 
				TODO:����ʱ���رպ�, �ⲿ���û��ͬʱ����, ���ܳ����ⲿ�ľɾ��ָ���´����Ķ�ʱ�����
			--------------------*/
		}
	}
	
	tagTimer->funTimer = cbTimer;
	tagTimer->nData = nData;
	tagTimer->bOneOff = oneOff;
	tagTimer->pTimerMng = this;
	tagTimer->nCircle = nCircle;
	
	SaveParam(nTimer, tagTimer);
	
	return tagTimer->hTimer;
}

VOID CALLBACK ns_PiPi::CPiKernel::TimerCallback( PVOID lpParameter,BOOLEAN TimerOrWaitFired )
{
	//OutInfo(_T("call timerCB begin"));
	tagPTTimer* pTag = (tagPTTimer*)lpParameter;
	pTag->pTimerMng->DealTimerCallback(lpParameter, TimerOrWaitFired);

	
	//OutInfo(_T("call timerCB end"));
}

bool ns_PiPi::CPiKernel::ReleaseAllTimer( bool bWait /*= true*/ )
{
	CRAIILock raii(m_pLockTimer);

	if (!m_hTimerQueue)
	{
		return true;
	}

	//OutInfo(_T("�ͷ����ж�ʱ��,begin"));
	FOR_EACH_ITER_NO_ADD(MAP_TIMER_PARAM, m_mapTimerParam, it)
	{
		ReleaseTimer(it, false);
		
	}
	
	bool bRet = DeleteTimerQueueEx(m_hTimerQueue, bWait ? INVALID_HANDLE_VALUE : NULL) == TRUE;
	m_hTimerQueue = NULL;
	//OutInfo(_T("�ͷ����ж�ʱ��,end"));
	return bRet;

}

bool ns_PiPi::CPiKernel::ReleaseTimer( TimerID nTimer, bool bClearMem /*= true*/ )
{
	CRAIILock raii(m_pLockTimer);

	if (!nTimer || !m_hTimerQueue)
	{
		return false;
	}

	/*-------------------- 
		�ṹ�������ͷ�, �ȴ��ص���ɺ���ͷ��ڴ�, ���ȴ��ص����, �����ͷŶ�ʱ��, ������ͷ���ؽṹ��
		ע�ⶨʱ���ͽṹ�岻Ҫ�ظ��ͷ�
	--------------------*/
	MAP_TIMER_PARAM::iterator itTimer = m_mapTimerParam.find(nTimer) ;
	if (itTimer == m_mapTimerParam.end())
	{
		return false;
	}
	return ReleaseTimer(itTimer, bClearMem);

}

bool ns_PiPi::CPiKernel::ReleaseTimer( MAP_TIMER_PARAM::iterator& itTimer, bool bClearMem /*= true*/ )
{
	//OutInfo(_T("kill timer"));
	CRAIILock raii(m_pLockTimer);

	bool bWait = false;
	if(!m_hTimerQueue)
	{
		return false;
	}
	tagPTTimer* pPTTimer = itTimer->second;
	/*if (!pPTTimer)
	{//��ʱ���ͽṹ�嶼���ͷ�
		return false;
	}*/
	if (pPTTimer->hTimer)		//���ȴ������ֻ�ͷŶ�ʱ��, û���ͷ��ڴ�
	{
		//TODO:���ǵȴ�ɾ����ʱ�������, ����Ļص���ʱ���Ѿ�������Ҫ����t1ռ�õ���, t1���ڵȴ�t2�������
		DeleteTimerQueueTimer(m_hTimerQueue, pPTTimer->hTimer, bWait ? INVALID_HANDLE_VALUE : NULL);
		pPTTimer->hTimer = NULL;
	}

	//�����һ���Ե�, ���治�ᱻ���õ�, ����ֱ���ͷ��ڴ�
	if (pPTTimer->bOneOff || bClearMem)	//TODO:��û�к����Ķ�ʱ����������ʱ��Ҫ��ʱɾ��
	{
		//��ɾ��ָ���Ľṹ��
		//m_mapTimerParam[nTimer] = NULL;
		CRAIILock raii(m_pLockMapList);
		m_mapTimerParam.erase(itTimer++);
		delete pPTTimer;
		//itTimer++;
	}
	else
	{
		++itTimer;
	}
	return true;
}

bool ns_PiPi::CPiKernel::CreateTimerQ()
{
	CRAIILock raii(m_pLockTimer);
	if (m_hTimerQueue)
	{
		return true;
	}
	m_hTimerQueue = ::CreateTimerQueue();
	if (!m_hTimerQueue)
	{
		return false;
	}
	return true;
}

bool ns_PiPi::CPiKernel::SaveParam(TimerID nTimer, tagPTTimer* tagTimer )
{
	if (!nTimer)
	{
		return false;
	}
	CRAIILock raii(m_pLockTimer);
	m_mapTimerParam[nTimer] = tagTimer;
	return true;
}

bool ns_PiPi::CPiKernel::DealTimerCallback( PVOID lpParameter, BOOLEAN TimerOrWaitFired )
{
	tagPTTimer* pTag = (tagPTTimer*)lpParameter;
	
	bool bRet = pTag->funTimer(pTag->hTimer, pTag->nData);	//�ص�����������ͷŶ�ʱ������ڴ�, �ⲿע�����
	
	if(pTag->bOneOff || bRet)
	{
		if (pTag->nTimerID)
		{
			ReleaseTimer(pTag->nTimerID);
		}
		/*else
		{
			OutInfo(_T("һ����, û���, �ͷŶ�ʱ��"));
			delete pTag;
		}*/
	}
	else if(mode_queue == m_enTimerMode)
	{
		
		if(!::ChangeTimerQueueTimer(m_hTimerQueue, pTag->hTimer, pTag->nCircle, NUM_UN_ELAPSE_PERIOD))
		{
			OutInfo(_T("err, ChangeTimerQueueTimer fail!"));
		}
	}
	return true;
}

bool ns_PiPi::CPiKernel::IsExistTimer( TimerID pHTimer )
{
	if (!pHTimer)
	{
		return false;
	}
	CRAIILock raii(m_pLockMapList);
	MAP_TIMER_PARAM::iterator itP = m_mapTimerParam.find(pHTimer);
	bool bValid = itP != m_mapTimerParam.end()
		&& itP->second->hTimer;
	return bValid;
}

bool ns_PiPi::CPiKernel::ExplorePath( tcpchar szPath, tcpchar szFocusFile /*= NULL*/)
{
	tstring strParam(szPath);
	tstring strPath(szPath);
	if (szFocusFile)
	{
		if(*strPath.rbegin() != '\\')
		{
			strPath += _T("\\");
		}
		strPath += szFocusFile;

		if (PathFileExists(strPath.c_str()))
		{
			strParam = _T("/select, ") + strPath;
		}
	}
	
	ShellExecute(NULL, _T("open"), _T("explorer.exe"), strParam.c_str(), NULL, SW_SHOWNORMAL);
	return true;
}


bool ns_PiPi::CPiKernel::StartItem( LPTHREAD_START_ROUTINE cbFun, void* pData )
{
	return QueueUserWorkItem(cbFun, pData, WT_EXECUTEDEFAULT) == TRUE;
}

bool ns_PiPi::CPiKernel::WriteMemMap( LPCTSTR szData, LPCTSTR szName )
{
	const DWORD dwBufMemMapSize = 1024;	
	DWORD dwDataSize = (_tcslen(szData) + 1) * sizeof(TCHAR);		//���Ͻ�β�ַ�
	if (dwDataSize > dwBufMemMapSize)
	{
		return false;
	}
	HANDLE hMO = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, HIWORD(dwBufMemMapSize), LOWORD(dwBufMemMapSize), szName);
	if (!hMO)
	{
		return false;
	}
	LPVOID pMemData = MapViewOfFile(hMO, FILE_MAP_WRITE, 0, 0, dwBufMemMapSize);
	if (!pMemData)
	{
		return false;
	}

	::memcpy(pMemData, szData, dwDataSize);
	UnmapViewOfFile(pMemData);
	//::CloseHandle(hMO);
	return true;
}

tstring ns_PiPi::CPiKernel::ReadMemMap( LPCTSTR szName )
{
	const DWORD dwMemSize = 1024;
	tstring strData;
	HANDLE hMO = OpenFileMapping(FILE_MAP_READ, FALSE, szName);
	if (!hMO)
	{
		return strData;
	}
	LPVOID pMemData = MapViewOfFile(hMO, FILE_MAP_READ, 0, 0, dwMemSize);
	if (!pMemData)
	{
		return strData;
	}
	strData = (tcpchar)pMemData;

	UnmapViewOfFile(pMemData);
	::CloseHandle(hMO);
	return strData;
	
	
}

DWORD ns_PiPi::CPiKernel::RunBinExitCode( tcpchar szCmd )
{
	STARTUPINFO si = {0};  
	PROCESS_INFORMATION pi = {0};   
	si.cb = sizeof(STARTUPINFO);  
	GetStartupInfo(&si);   
	si.wShowWindow = SW_HIDE;  
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;  

	tstring strCmdBin(szCmd);		

	if ( !CreateProcess(NULL, &strCmdBin.at(0), NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi) )
	{  
		return FALSE;  
	}  

	::WaitForSingleObject(pi.hProcess, INFINITE);
	DWORD nResult = 0;
	if(!GetExitCodeProcess(pi.hProcess, &nResult))
	{
		OutInfo(_T("get exit code err"));
	}
	return nResult;
}

bool ns_PiPi::CPiKernel::RunBin( tcpchar szCmd )
{
	STARTUPINFO si = {0};  
	PROCESS_INFORMATION pi = {0};   
	si.cb = sizeof(STARTUPINFO);  
	GetStartupInfo(&si);   
	si.wShowWindow = SW_HIDE;  
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;  

	tstring strCmdBin(szCmd);		

	if ( !CreateProcess(NULL, &strCmdBin.at(0), NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi) )
	{  
		return false;  
	}  
	return true;
}

CPiKernel::tagPTTimer* CPiKernel::GetParam( TimerID pHTimer )
{
	CRAIILock raii(m_pLockTimer);
	return m_mapTimerParam[pHTimer];
}



/*------------------------------------------------------------
		xp��

		PTP_TIMER ns_PiPi::CPiKernel::BeginTimer( CB_TimerFunc cbTimer, UNINT nCircle, PVOID nData, bool oneOff  )
{

	tagPTTimer* tagTimer = new tagPTTimer;
	tagTimer->funTimer = cbTimer;
	tagTimer->nData = nData;
	tagTimer->bOneOff = oneOff;
	tagTimer->pTimerMng = this;

	//TODO:��α�֤û���ڴ�й¶

	PTP_TIMER tId = CreateThreadpoolTimer(&CPiKernel::TimerCallback, tagTimer, NULL);
	if(!tId)
	{
		return NULL;
	}
	m_lstTimerID.push_back(tId);
	//������ʱ��

	//��ʼ���ж�ʱ��

	LARGE_INTEGER nTime;
	nTime.QuadPart = - LONGLONG(MILLISECOND_TO_NANOSECOND100(nCircle));
	FILETIME fStart = {0};
	fStart.dwHighDateTime = nTime.HighPart;
	fStart.dwLowDateTime = nTime.LowPart;

	SetThreadpoolTimer(tId, &fStart, (oneOff ? 0 : nCircle), 0);
	return tId;
#endif
}


VOID CALLBACK ns_PiPi::CPiKernel::TimerCallback( PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_TIMER Timer )
{
	tagPTTimer* pTag = (tagPTTimer*)Context;
	//CB_TimerFunc pFun = (CB_TimerFunc)Context;
	pTag->funTimer(Timer, pTag->nData);
	if (pTag->bOneOff)
	{
		pTag->pTimerMng->ReleaseTimer(Timer, false);
	}
}

bool ns_PiPi::CPiKernel::ReleaseAllTimer()
{
	FOR_EACH_ITER(LST_TIMERID, m_lstTimerID, it)
	{
		//�ͷŶ�ʱ��WaitForThreadpoolTimerCallbacks , CloseThreadpoolTimer 
		ReleaseTimer(*it, true);
	}
	return true;
}

bool ns_PiPi::CPiKernel::ReleaseTimer( PTP_TIMER nTimer, bool bWait  )
{
	if (!nTimer)
	{
		return true;
	}

	//Sleep(4000);
	if (bWait)
	{
		SetThreadpoolTimer(nTimer, NULL, 0, 0);
		WaitForThreadpoolTimerCallbacks(nTimer, TRUE);
	}

	CloseThreadpoolTimer(nTimer);
	m_lstTimerID.remove(nTimer);
	return true;
}
------------------------------------------------------------*/