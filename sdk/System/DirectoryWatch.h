// DirectoryWatch.h
#pragma once
#include <windows.h>
#include <list>

// ͨ�õ�֪ͨ������
typedef void(*funNotifyAction)(LPWSTR wzSrcFile);

// Ҫ��ص�Ŀ¼����Ϣ
typedef struct _WATCH_PARAM
{
	_WATCH_PARAM()
	{
		hFile = INVALID_HANDLE_VALUE;
		hEvent = NULL;
		hWatch = NULL;
		pBuffer = NULL;
		bIsExit = FALSE;
		dwBufferSize = 0;
		NotifyAction = NULL;
		ZeroMemory(&wzPath, sizeof(WCHAR)*MAX_PATH);
		ZeroMemory(&ol, sizeof(OVERLAPPED));
	}
	WCHAR  wzPath[MAX_PATH]; // ·��
	HANDLE hFile;            // �ļ����
	HANDLE hEvent;           // �¼����
	BYTE  *pBuffer;          // ������
	DWORD  dwBufferSize;     // ��������С
	OVERLAPPED ol;           // �첽�ṹ

	HANDLE hWatch;           // ����߳̾��
	BOOL   bIsExit;          // ����߳��Ƿ��˳�

	funNotifyAction NotifyAction;

}WATCH_PARAM, *PWATCH_PARAM;

// �����
class CDirectoryWatch
{
public:
	CDirectoryWatch();
	virtual ~CDirectoryWatch();

public:
	BOOL StartWatch(LPWSTR wzPath, funNotifyAction lpfunNotifyAction);
	BOOL StopWatch(LPWSTR wzPath);

private:
	static unsigned __stdcall MSGThred(LPVOID lpParam);   // ��Ϣ�߳�
	static unsigned __stdcall WatchThred(LPVOID lpParam); // ����߳�

	void Lock();
	void UnLock();

private:
	std::list<WATCH_PARAM*> m_vWatchList; // ��ص��б�
	HANDLE m_hMSG;                        // ��Ϣ�߳̾��
	DWORD  m_dwMSGTID;                    // ��Ϣ�߳�ID
	HANDLE m_hMutex;                      // ������(list����)
};