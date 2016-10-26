#include "StdAfx.h"
#include "PipeManage.h"
#include "functional.h"
#include "StrCoding.h"
#include "ResCommon.h"
//#include "RAIILock.h"
#include "define_gnl.h"
#include <assert.h>
#include "RAIILock.h"

CPipeManage::CPipeManage() : m_pReadFun(NULL)
    , m_hPipe(NULL)
    //, m_hThread(NULL)
    , m_enumPipeType(ENUM_PIPE_TYPE_CLIENT)
    , m_enumThreadState(ENUM_THREAD_STATE_STOP)
{
    m_hEvent = NULL;
    m_pBuf      = NULL;
    m_nReadSize = NULL;
    m_hEventRead = NULL;
    m_bEnd = false;
	m_bStruct = false;
	m_bConnectOk = false;
	m_bCloseActive = false;
	CThreadLight::SetThreadName(_T("PipeThread"));
}


CPipeManage::~CPipeManage()
{
    UnInit();
	
}

bool CPipeManage::Init()
{
    CThreadLight::Init();
    m_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!m_hEvent)
    {
        return false;
    }

    m_hEventRead = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (!m_hEventRead)
    {
        return false;
    }
    
    m_hEventWrite = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (!m_hEventWrite)
    {
        return false;
    }
    return true;
}

bool CPipeManage::UnInit()
{
	ClosePipe();
	CThreadLight::UnInit();
	this->WaitThreadExit();
	OutInfo(_T("�ȴ��ܵ��߳��˳�:"), m_strThreadName);

	ClearHandle(m_hEvent);
    ClearHandle(m_hEventRead);

	delete[] m_pBuf;
	m_pBuf = NULL;
	
    return true;    

}

//��ȡ��ǰ����PIPE����
ENUM_CREATE_PIPE_TYPE CPipeManage::GetCurPipeType()
{
	return m_enumPipeType;
}

//�ر�PIPE
bool CPipeManage::ClosePipe()
{
    OutInfo(_T("�رչܵ�"));
	//if (IsValidHandle())
	{
		m_bCloseActive = true;
		ClearHandle(m_hPipe);
		m_hPipe = NULL;
	}
    
    if(!ResetEvent(m_hEvent))
    {
        return false;
    }
	return true;
}

//�ж��Ƿ��Ѿ�����/����PIPE
bool CPipeManage::IsCreatePipe()
{
	if (m_hPipe)
	{
		return TRUE;
	}
	return FALSE;
}

//����/��ָ�����͵�PIPE
bool CPipeManage::CreatePipe(LPCTSTR lpPipeName/* = _T("\\\\127.0.0.1\\pipe\\mypipe")*/,
								ENUM_CREATE_PIPE_TYPE enumCreateType/* = ENUM_PIPE_TYPE_CLIENT*/,
								void(*ptr)(char * , int )/* = NULL*/
								)
{
	if (IsCreatePipe())
	{
		return false;
	}

	m_pReadFun = ptr;
	m_enumPipeType = enumCreateType;
    m_strPipeName = lpPipeName;
	switch (m_enumPipeType)
	{
	case ENUM_PIPE_TYPE_SERVER:// = 0,				//�����
		{
			return CreatePipeServer(lpPipeName);
		}
		break;
	case ENUM_PIPE_TYPE_CLIENT://,					//�ͻ���
		{
			return CreatePipeClient(lpPipeName);
		}
		break;
	default:
		{
		}
		break;
	}
	return false;
}

//��ܵ�д��
bool CPipeManage::Write(void * pBuf, int nBufSize, bool bWriteSize /*= true*/)
{
    if (!IsValidHandle())
    {
        return false;
    }
    //OutInfo(_T(" send data"));
	if ( 0 >= nBufSize)
	{
		return false;
	}

	/*if (!m_bStruct)
	{
		m_bStruct = true;
		Write(dt_single, false);
		m_bStruct = false;
	}*/

	DWORD dwWrite = 0;
    OVERLAPPED ol = {0};
    ol.hEvent = m_hEventWrite;

	try
	{

		if (bWriteSize)
		{
			WriteFile(m_hPipe, &nBufSize, sizeof(nBufSize), &dwWrite, &ol);
			if (WAIT_OBJECT_0 != WaitForSingleObject(m_hEventWrite, NUM_PIPE_WRITE_TIMEOUT))
				//if( ! WriteFile(m_hPipe, pBuf, nBufSize, &dwWrite, NULL))
			{
				throw _T("��ܵ�д����ʧ��");
				return false;
			}
			else
			{
				if(!GetOverlappedResult(m_hPipe, &ol, &dwWrite, FALSE))
				{
					OutInfo(_T("GetOverlappedResult fail"));
					throw _T("GetOverlappedResult fail");
					return false;
				}
				//д�ɹ�
			}
		}
		
		WriteFile(m_hPipe, pBuf, nBufSize, &dwWrite, &ol);
		if (WAIT_OBJECT_0 != WaitForSingleObject(m_hEventWrite, NUM_PIPE_WRITE_TIMEOUT))
		//if( ! WriteFile(m_hPipe, pBuf, nBufSize, &dwWrite, NULL))
		{
			OutInfo(_T("��ܵ�д����ʧ��"));
			throw _T("��ܵ�д����ʧ��");
			return false;
		}
		else
		{
			if(!GetOverlappedResult(m_hPipe, &ol, &dwWrite, FALSE))
			{
				OutInfo(_T("GetOverlappedResult fail"));
				throw _T("GetOverlappedResult fail");
				return false;
			}
			//д�ɹ�
		}
	}
	catch(tcpchar )
	{
		ReadFail();
		//m_bConnectOk = false;
	}
	return true;
}

bool CPipeManage::Write( int nValue , bool bWriteSize /*= true*/)
{
    return Write((void*)&nValue, sizeof(nValue), bWriteSize);
}

bool CPipeManage::Write( UNINT nValue, bool bWriteSize /*= true*/ )
{
	return Write((void*)&nValue, sizeof(nValue), bWriteSize);

}

bool CPipeManage::Write( tcpchar nValue )
{
	size_t nSize = (_tcslen(nValue) + 1) * sizeof(tchar);
	return Write((void*)nValue, nSize);
}

bool CPipeManage::Write( StringCRef nValue )
{
	return Write(nValue.c_str());
}

bool CPipeManage::Write( LLONG nValue, bool bWriteSize /*= true*/ )
{
	return Write((void*)&nValue, sizeof(nValue), bWriteSize);
}

bool CPipeManage::Write( bool nValue, bool bWriteSize /*= true*/ )
{
	return Write((void*)&nValue, sizeof(nValue), bWriteSize);

}

//��ܵ�д����
//int nData ��������
bool CPipeManage::WriteStr(int nData)
{
    char szBuf[MAX_PATH] = {0};
    sprintf_s(szBuf, "%d", nData);
    return Write(szBuf, strlen(szBuf));
}

//��ȡPIPE����
bool CPipeManage::ReadPipe(void)
{
	m_nReadSize = 0;
	if (!IsValidHandle())
	{
		return false;
	}
	char szReadBuf[MAX_PATH] ={0};
	DWORD dwRead = 0;
    OVERLAPPED ol = {0};
    ol.hEvent = m_hEventRead;
    
    BOOL bRet = ReadFile(m_hPipe, szReadBuf, sizeof(int), &dwRead, &ol);
	if( !bRet && IsReadErr())
	{
		throw _T("ʧ��");
	}

    DWORD dwWait = WaitForSingleObject(m_hEventRead, INFINITE);
    if (WAIT_FAILED == dwWait)
        //if (! ReadFile(m_hPipe, szReadBuf, g_nReadDataMaxSize, &dwRead, NULL))
    {
        OutInfo(_T("��ȡ�ܵ�����ʧ��"));
		throw _T("WaitForSingleObjectʧ��");
        return false;
    }

    if(!GetOverlappedResult(m_hPipe, &ol, &dwRead, FALSE))
    {
		throw _T("��ȡ�ܵ�����ʧ��");
		return false;
    }

	DataSize nDataLen = *(DataSize*)szReadBuf;

	delete [] m_pBuf;
	m_pBuf = NULL;

	m_pBuf = new char[nDataLen + 1];
	memset(m_pBuf, 0, nDataLen + 1);

    bRet = ReadFile(m_hPipe, m_pBuf, nDataLen, &dwRead, &ol);
	if( !bRet && IsReadErr())
	{
		throw _T("��ȡ�ܵ�����ʧ��");
	}

    dwWait = WaitForSingleObject(m_hEventRead, INFINITE);

	if (WAIT_FAILED == dwWait)
	{
		OutInfo(_T("��ȡ�ܵ�����ʧ��"));
		throw _T("��ȡ�ܵ�����ʧ��");
		return false;
	}
	else 
	{
        if(!GetOverlappedResult(m_hPipe, &ol, &dwRead, FALSE))
        {
			throw _T("��ȡ�ܵ�����ʧ��");
			return false;
        }
        //OutInfo(_T("pipe read size:"), dwRead);
		//�����Ҫ�Ļ�,��������Ҫ���ӽ������յ�������,��Ϊ�������п��ܴ��ڶ��һ�𱻽��յ����,Ŀǰ��ʱ�������������
		if (/*szReadBuf[0] != '\0'*/ !dwRead)
        {
            OutInfo(_T("�ܵ�����"));
			throw _T("��ȡ�ܵ�����ʧ��");
			return true;
        }
        //OutInfo(_T("�ܵ���������"));
		
        m_nReadSize = dwRead;

        
        /*if (m_pReadFun)
        {
            m_pReadFun(szReadBuf, dwRead);
        }
        else
        {
            OutInfo(ps2pwSmart(szReadBuf));
        }*/
	
        
	}
	
	return true;
}

bool CPipeManage::ReadPipe( bool& nValue )
{
	if(!ReadPipeCatch())
	{
		return false;
	}
	nValue = *(bool*)m_pBuf;
	return true;
}

bool CPipeManage::ReadPipe( int& nValue )
{
	if(!ReadPipeCatch())
	{
		return false;
	}
	nValue = *(int*)m_pBuf;
	return true;
}

bool CPipeManage::ReadPipe( UNINT& nValue )
{
	if(!ReadPipeCatch())
	{
		return false;
	}
	nValue = *(UNINT*)m_pBuf;
	return true;
}

bool CPipeManage::ReadPipe( LLONG& nValue )
{
	if(!ReadPipeCatch())
	{
		return false;
	}
	nValue = *(int*)m_pBuf;
	return true;
}

bool CPipeManage::ReadPipe( tstring& nValue )
{
	if(!ReadPipeCatch())
	{
		return false;
	}
	nValue = (tcpchar)m_pBuf;
	return true;
}	

bool CPipeManage::ReadPipeCatch( void )
{
	bool bRet = false;
	try
	{	
		bRet = ReadPipe();
	}
	catch(tcpchar )
	{
		ReadFail();
		bRet = false;
	}
	return bRet;
}

bool CPipeManage::ReadDataType( ENUM_PIPE_DATA_TYPE& dType )
{
	if (!IsValidHandle())
	{
		return false;
	}
	char szReadBuf[10] ={0};
	DWORD dwRead = 0;
	OVERLAPPED ol = {0};
	ol.hEvent = m_hEventRead;
	try
	{

		BOOL bRet = ReadFile(m_hPipe, szReadBuf, sizeof(ENUM_PIPE_DATA_TYPE), &dwRead, &ol);
		if( !bRet && IsReadErr())
		{
			throw _T("��ȡʧ��");
		}

		DWORD dwWait = WaitForSingleObject(m_hEventRead, INFINITE);
		if (WAIT_FAILED == dwWait)
		{
			OutInfo(_T("��ȡ�ܵ�����ʧ��"));
			throw _T("��ȡ�ܵ�����ʧ��");
			return false;
		}

		if(!GetOverlappedResult(m_hPipe, &ol, &dwRead, FALSE))
		{
			throw _T("��ȡ�ܵ�����ʧ��");
			return false;
		}
	}
	catch( tcpchar )
	{
		ReadFail();
		return false;
	}
	dType = (ENUM_PIPE_DATA_TYPE)*(DataSize*)szReadBuf;
	assert(dType >= 0 && dType <= 2);
	return true;
}

//���������
bool CPipeManage::CreatePipeServer(LPCTSTR lpPipeName)
{
	SECURITY_ATTRIBUTES     sa;
	PSECURITY_DESCRIPTOR    pSD;
	pSD = (PSECURITY_DESCRIPTOR) LocalAlloc(LPTR,
		SECURITY_DESCRIPTOR_MIN_LENGTH);
	if (!InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION))
	{
		LocalFree((HLOCAL)pSD);
		return false;
	}
	if (!SetSecurityDescriptorDacl(pSD, TRUE, (PACL) NULL, FALSE))
	{
		LocalFree((HLOCAL)pSD);
		return false;
	}
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = pSD;
	sa.bInheritHandle = TRUE;
	m_hPipe = CreateNamedPipe(	lpPipeName,	//�ܵ���
								PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,//��ģʽ ˫�� �������ص�
								0,	//ָ���ܵ����ֽڷ�ʽ�� д�Լ��ȴ�
								1,	//�ܵ������Ŀ
								1024,//�����������С
								1024,//���뻺������С
								0,	//��ʱֵ
								&sa// ��ȫ����
								);
	if (INVALID_HANDLE_VALUE == m_hPipe)
	{
		m_hPipe = INVALID_HANDLE_VALUE;
		return false;
	}
	return CreateWorkThread();
}

//�����ͻ���
bool CPipeManage::CreatePipeClient(LPCTSTR lpPipeName)
{
    if( ! ConnectPipe(lpPipeName))
    {
        return false;
    }

	return CreateWorkThread();
}

bool CPipeManage::CreateWorkThread( void )
{
		//return S_OK;
	DWORD dwThreadID = 0;
	m_enumThreadState = ENUM_THREAD_STATE_WAIT;
    Run();

	/*m_hThread = CreateThread(NULL, 0, RunProc, this, 0, &dwThreadID);
	if (NULL != m_hThread)
	{
		//CloseHandle(m_hThread);
		//m_hThread = NULL;
		return true;
	}*/
	return true;
}

/*
DWORD WINAPI CPipeManage::RunProc(LPVOID lpParam)
{
	CPipeManage * pPipeManage = (CPipeManage*)lpParam;
	if (NULL != pPipeManage)
	{
		pPipeManage->Porc();
	}
	return 0;
}*/

/*
void CPipeManage::Porc(void)
{
	//int nReadCount = 0;
    int nSleepCount = 0;
	bool bReadRet = false;
    bool bNeedEndLoop = false;
	while (!bNeedEndLoop)
	{
        if (IsClose())
        {
            m_enumThreadState = ENUM_THREAD_STATE_STOP;
            continue;
        }
		switch (m_enumThreadState)
		{
		case ENUM_THREAD_STATE_START:// = 0,			//��ʼ
			{
                / *if (m_enumPipeType == ENUM_PIPE_TYPE_SERVER)
                {
                    break;
                }* /
				bReadRet = ReadPipe();
				if (!bReadRet)
				{
                    DealReadFail();
					/ *nReadCount++;
					if (g_nReadErrorCount <= nReadCount)
					{
						
					}* /
				}
				else
				{
                    if (!m_nReadSize)
                    {
                        if (m_bEnd)
                        {
                            OutInfo(_T("�˳�������ȡ�߳�"));
                            m_enumThreadState = ENUM_THREAD_STATE_STOP;
                            break;
                        }
                        DealPipeEnd();
                    }
					//nReadCount = 0;
                    if ((nSleepCount = nSleepCount % 10) == 0)
                    {
                        Sleep(100);
                    }
				}
			}
			break;
		case ENUM_THREAD_STATE_WAIT://,					//��ͣ
			{
				if (ENUM_PIPE_TYPE_SERVER == m_enumPipeType)
				{
					//�����
                    ReWaitConnect();

                    / *m_lockEvent.Lock();
                    if (!m_hEvent)
                    {
                        OutInfo(_T("�¼����Ϊ��, �˳��߳�"));
                        m_lockEvent.UnLock();
                        break;
                    }

                    ResetEvent(m_hEvent);
					/ *OVERLAPPED overlap;
					ZeroMemory(&overlap, sizeof(OVERLAPPED));
					overlap.hEvent = m_hEvent;* /
                    m_lockEvent.UnLock();

					ConnectNamedPipe(m_hPipe, NULL);
                    OutInfo(_T("�߳��еȴ��ͻ�����"));
					//if (WAIT_FAILED == WaitForSingleObject(overlap.hEvent, INFINITE))
					{
						TRACE(_T("�ȴ�����ʧ��"));
						CloseHandle(overlap.hEvent);
						m_enumThreadState = ENUM_THREAD_STATE_STOP;
						break;
					}* /
                    OutInfo(_T("�ͻ������ӳɹ�"));
				}
				else
				{
					//�ͻ���,������
					//return;
				}
				m_enumThreadState = ENUM_THREAD_STATE_START;
			}
			break;
		case ENUM_THREAD_STATE_STOP://,					//ֹͣ
			{
                bNeedEndLoop = true;
			}
			break;
		default:
			{
				if (INVALID_HANDLE_VALUE != m_hPipe)
				{
					CloseHandle(m_hPipe);
					m_hPipe = NULL;
				}
				//�����߳�
				if (NULL != m_hThread)
				{
					CloseHandle(m_hThread);
					m_hThread = NULL;
				}
				return;
			}
			break;
		}
	}
}*/

bool CPipeManage::WaitConnect()
{
    HANDLE  hEvent = m_hEvent;
    if (WAIT_FAILED == WaitForSingleObject(hEvent, INFINITE))
    {
        CloseHandle(hEvent);
        return false;
    }
    OutInfo(_T("�ȴ����ӳɹ�"));
    return true;
}

bool CPipeManage::DealReadData()
{
    OutInfo(ps2pwSmart((char*)m_pBuf));
    return true;
}

bool CPipeManage::DealReadFail()
{
    DealPipeEnd();
    /*if (ENUM_PIPE_TYPE_SERVER == m_enumPipeType)
    {
        ReWaitConnect();
        
    }
    else
    {
        m_enumThreadState = ENUM_THREAD_STATE_STOP;
    }*/
    return true;
}

bool CPipeManage::ConnectPipe( LPCTSTR lpPipeName )
{
    WaitNamedPipe(lpPipeName, NUM_PIPE_TIMEOUT_CONNECT);
    m_hPipe = CreateFile(	lpPipeName,					//ָ���ļ�����ָ��
        GENERIC_READ | GENERIC_WRITE,	//����ģʽ(��/д)
        0,								//����ģʽ
        NULL,							//ָ��ȫ���Ե�ָ��
        OPEN_EXISTING,					//��δ���
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,//�ļ�����
        NULL							//���ڸ����ļ����
        );
    if (m_hPipe == INVALID_HANDLE_VALUE)
    {
		OutInfo(_T("�������ܵ�ʧ��, err:"), GetLastError());
        m_hPipe = INVALID_HANDLE_VALUE;
        return false;
    }
	m_bCloseActive = false;
	m_bConnectOk = true;
    return true;
}

bool CPipeManage::DealPipeEnd()
{
    if (ENUM_PIPE_TYPE_SERVER == m_enumPipeType)
    {
        ReWaitConnect();
    }
    else
    {
		OutInfo(_T("�ܵ�����, �ͻ��˹رձ��˹ܵ�"));
		ClosePipe();
        m_enumThreadState = ENUM_THREAD_STATE_STOP;
    }
    
    return true;
}

bool CPipeManage::ReWaitConnect()
{
    DisconnectNamedPipe(m_hPipe);
    ResetEvent(m_hEvent);
    /*OVERLAPPED overlap;
    ZeroMemory(&overlap, sizeof(OVERLAPPED));
    overlap.hEvent = m_hEvent;*/

    ConnectNamedPipe(m_hPipe, NULL);
    SetEvent(m_hEvent);
	m_bCloseActive = false;
	m_bConnectOk = true;
    //WaitConnect();
    return true;
}

bool CPipeManage::EndPipe( void )
{
    m_bEnd = true;
    ClosePipe();
    if (NULL != m_hThread)
    {
        m_enumThreadState = ENUM_THREAD_STATE_STOP;
        WaitForSingleObject(m_hThread, 1000);
        TerminateThread (m_hThread, 0);
        CloseHandle(m_hThread);
        m_hThread = NULL;
    }
    return true;
}

bool CPipeManage::IsClose()
{
    return m_hPipe == NULL;
}

DWORD CPipeManage::DoWork()
{
	//OutInfo(_T("����ܵ��߳�"));
    int nSleepCount = 0;
	bool bReadRet = false;
    bool bNeedEndLoop = false;
	while (!bNeedEndLoop && ! CThreadLight::IsWillStopThread())
	{
        if (IsClose())
        {
            break;
        }
		switch (m_enumThreadState)
		{
		case ENUM_THREAD_STATE_START:// = 0,			//��ʼ
			{
				ENUM_PIPE_DATA_TYPE dt;
				if(!ReadDataType(dt))
				{
					//ReadFail();
					break;
				}
				switch(dt)	//�ṹ��������
				{
				case dt_struct:
					DealReadStruct();
					break;
				case dt_single:
					bReadRet = ReadPipeCatch();	//��������
					if (!bReadRet)
					{
						//ReadFail();
						break;
					}
					this->DealReadData();
					break;
				default:
					assert(0 && "unknown pipe data type");
				}
			}
			break;
		case ENUM_THREAD_STATE_WAIT://,					//��ͣ
			{
				if (ENUM_PIPE_TYPE_SERVER == m_enumPipeType)
				{
					//�����
                    ReWaitConnect();
					m_bConnectOk  = true;
                    /*m_lockEvent.Lock();
                    if (!m_hEvent)
                    {
                        OutInfo(_T("�¼����Ϊ��, �˳��߳�"));
                        m_lockEvent.UnLock();
                        break;
                    }

                    ResetEvent(m_hEvent);
					/ *OVERLAPPED overlap;
					ZeroMemory(&overlap, sizeof(OVERLAPPED));
					overlap.hEvent = m_hEvent;* /
                    m_lockEvent.UnLock();

					ConnectNamedPipe(m_hPipe, NULL);
                    OutInfo(_T("�߳��еȴ��ͻ�����"));
					//if (WAIT_FAILED == WaitForSingleObject(overlap.hEvent, INFINITE))
					{
						//AfxMessageBox(_T("�ȴ�����ʧ��"));
						TRACE(_T("�ȴ�����ʧ��"));
						CloseHandle(overlap.hEvent);
						m_enumThreadState = ENUM_THREAD_STATE_STOP;
						break;
					}*/
                    OutInfo(_T("�ͻ������ӳɹ�"));
					DoClientConnectOk();
				}
				else
				{
					//�ͻ���,������
					//return;
				}
				m_enumThreadState = ENUM_THREAD_STATE_START;
			}
			break;
		case ENUM_THREAD_STATE_STOP://,					//ֹͣ
			{
                bNeedEndLoop = true;
			}
			break;
		default:
			{
				if (INVALID_HANDLE_VALUE != m_hPipe)
				{
					CloseHandle(m_hPipe);
					m_hPipe = NULL;
				}
				//�����߳�
				if (NULL != m_hThread)
				{
					CloseHandle(m_hThread);
					m_hThread = NULL;
				}
				return 1;
			}
			break;
		}
	}
    return 1;
}

bool CPipeManage::IsValidHandle()
{
    return m_hPipe != NULL && m_hPipe != INVALID_HANDLE_VALUE
		&& m_bConnectOk;
}

bool CPipeManage::IsReadErr()
{
    DWORD dwErr = GetLastError();
    //OutInfo(_T("lastErr:"), dwErr);
    if (dwErr != ERROR_IO_PENDING) //��һ���Ѿ�����
    {
        return true;
    }
    return false;
}

bool CPipeManage::DoReadFail()
{
	return true;
}

bool CPipeManage::DealReadStruct()
{
	return true;
}

void CPipeManage::ReadFail()
{
	OutInfo(_T("�ܵ��ж�"));
	m_bConnectOk = false;
	DoReadFail();
	DealReadFail();
}

bool CPipeManage::WriteStructBegin()
{
	m_lockWrite.Lock();
	m_bStruct = true;
	Write(dt_struct, false);
	return true;
}

bool CPipeManage::WriteStructBegin( ENUM_TRANSFER_TYPE enMode )
{
	if (enMode != type_write)
	{
		return true;
	}
	return WriteStructBegin();
}

bool CPipeManage::WriteStructEnd()
{
	m_bStruct = false;
	m_lockWrite.UnLock();
	return true;
}

bool CPipeManage::WriteStructEnd( ENUM_TRANSFER_TYPE enMode )
{
	if (enMode != type_write)
	{
		return true;
	}
	return WriteStructEnd();
}

bool CPipeManage::WriteSingleBegin()
{
	m_lockWrite.Lock();

	return Write(dt_single, false);
}

bool CPipeManage::DoClientConnectOk()
{

	return true;
}

bool CPipeManage::WriteSingleData( int nValue )
{
	WriteSingleBegin();
	Write(nValue);
	WriteSingleEnd();
	return true;
}

bool CPipeManage::WriteSingleEnd()
{
	m_lockWrite.UnLock();
	return true;
}


bool CPipeManage::IsCloseBySelf()
{
	return m_bCloseActive;
}

bool CPipeManage::Transfer( int& nValue, ENUM_TRANSFER_TYPE enType )
{
	bool bRet = false;
	if (enType == type_write)
	{
		bRet = Write(nValue);
	}
	else
	{
		bRet = ReadPipe(nValue);
	}
	return bRet;
}

bool CPipeManage::Transfer( tstring& nValue, ENUM_TRANSFER_TYPE enType )
{
	bool bRet = false;
	if (enType == type_write)
	{
		bRet = Write(nValue);
	}
	else
	{
		bRet = ReadPipe(nValue);
	}
	return bRet;
}

bool CPipeManage::Transfer( LLONG& nValue, ENUM_TRANSFER_TYPE enType )
{
	bool bRet = false;
	if (enType == type_write)
	{
		bRet = Write(nValue);
	}
	else
	{
		bRet = ReadPipe(nValue);
	}
	return bRet;
}

bool CPipeManage::Transfer( UNINT& nValue, ENUM_TRANSFER_TYPE enType )
{
	bool bRet = false;
	if (enType == type_write)
	{
		bRet = Write(nValue);
	}
	else
	{
		bRet = ReadPipe(nValue);
	}
	return bRet;
}

bool CPipeManage::Transfer( bool& nValue, ENUM_TRANSFER_TYPE enType )
{
	bool bRet = false;
	if (enType == type_write)
	{
		bRet = Write(nValue);
	}
	else
	{
		bRet = ReadPipe(nValue);
	}
	return bRet;
}

bool CPipeManage::TransferSP( POINT * param1, ENUM_TRANSFER_TYPE enType)
{
	/*

	CPipeManage::WriteStructBegin(enType);
	TransferProtocal(pd_hz_send_file, enType);
	Transfer(param1->nID, enType);
	Transfer(param1->bIsApk, enType);
	Transfer(param1->strFileName, enType);
	Transfer(param1->nFileSize, enType);
	Transfer(param1->strPackageName, enType);
	Transfer(param1->strThumbPath, enType);
	Transfer(param1->strFilePath, enType);
	Transfer(param1->bIsTrueID, enType);
	Transfer((int&)param1->enStatus, enType);
	Transfer((int&)param1->enFileType, enType);
	Transfer(param1->bIsDemonSend, enType);
	CPipeManage::WriteStructEnd(enType);

	*/
	return true;
}
