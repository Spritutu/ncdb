#pragma once
#include "PiTypeDef.h"
#include "ResCommon.h"
Pi_NameSpace_Begin

//#define M_TP_XP_OK	//֧��XP

typedef VOID (*CB_TimerCallback)(PVOID lpParameter,BOOLEAN TimerOrWaitFired);


typedef bool (*CB_TimerFunc)(HANDLE nTimerID, PVOID pAddi);


class CPiKernel
{
	typedef list<PTP_TIMER>	LST_TIMERID;
	typedef int TimerID;
	struct tagPTTimer
	{
		CB_TimerFunc funTimer;
		PVOID nData;
		CPiKernel* pTimerMng;
		bool bOneOff;	//�Ƿ���һ���Ե�
		HANDLE hTimer;
		ULONG	nCircle;	//��ʱ������, ��λ����
		TimerID nTimerID;	//�û�ָ����ʾ
	};
	typedef map<TimerID,tagPTTimer*>	MAP_TIMER_PARAM;
	enum ENUM_TIMER_MODE{ 
		mode_callback,	//��ʱ�����ڵ���������
		mode_queue		//��ʱ������һ������������ɺ���������һ������
	};
public:
	CPiKernel(void);
	~CPiKernel(void);
public:
	bool Init();
	/*------------------------------------------------------------
			fun:	��ָ����Ƶ�ʶ�ʱִ��ָ���ĺ���
			ret:	���ض�ʱ��id
			param: cbTimer:�ص�����,  nCircle, ������ú�����ʱ��, ��λ����. nData:��������, ��Ϊ�ص������ĵڶ�������. oneOff:true, �ص�����ֻ����һ�κ�ʱ��������, false:��ʱִ��
			remark:	��ʱ��ʱ����ûص�����ʱ��һ������Ϊ��ʱ����id, ������Ҫ����Ϊ��������ReleaseTimer������ȡ����ʱ��
	------------------------------------------------------------*/
	bool BeginTimer(CB_TimerFunc cbTimer, UNINT nCircle, PVOID nData = NULL, bool oneOff = false, TimerID nTimer = 0);

	bool CreateTimerQ();

	/*------------------------------------------------------------
			fun:	ȡ����ʱ��
			ret:	
			param: nTimer:Ҫȡ���Ķ�ʱ��id, bWait: true->�ȴ����ж�ʱ���ص�����ִ������ȡ��, false->ֱ��ȡ��, ���ȴ�
			remark:	
	------------------------------------------------------------*/
	bool ReleaseTimer(TimerID nTimer, bool bClearMem = true);
	/*------------------------------------------------------------
			fun:	�ر����еĶ�ʱ��
			ret:	
			param: 
			remark:	
	------------------------------------------------------------*/
	bool ReleaseAllTimer(bool bWait = true);

	
/*------------------------------------------------------------
		xp��

		typedef VOID (*CB_TimerCallback)(PTP_CALLBACK_INSTANCE Instance,  PVOID Context, PTP_TIMER Timer);
		typedef bool (*CB_TimerFunc)(PTP_TIMER nTimerID, PVOID pAddr);


	typedef list<PTP_TIMER>	LST_TIMERID;
	struct tagPTTimer
	{
	CB_TimerFunc funTimer;
	PVOID nData;
	CPiKernel* pTimerMng;
	bool bOneOff;	//�Ƿ���һ���Ե�
	};

	PTP_TIMER BeginTimer(CB_TimerFunc cbTimer, UNINT nCircle, PVOID nData, bool oneOff = false);
	static VOID CALLBACK TimerCallback(PTP_CALLBACK_INSTANCE Instance,  PVOID Context, PTP_TIMER Timer);
	bool ReleaseTimer(PTP_TIMER nTimer, bool bWait = false);
	bool ReleaseAllTimer();
	LST_TIMERID		m_lstTimerID;

	------------------------------------------------------------*/

//#endif
	/*------------------------------------------------------------
		fun:	ִ��dos����
		ret:	true: ִ�гɹ�,				
		param: 
			strOut: ִ�з�������,	dwWaitMillSec: �ȴ�ʱ��, ����
		remark:	����ص����ݳ��Ȳ��ܳ���16k
				�����ʱʱ�䵽, ����û�յ�����ص��κ�����, �򷵻�false
	------------------------------------------------------------*/

	bool StartItem(LPTHREAD_START_ROUTINE cbFun, void* pData);

	static bool ExecuteDos(tcpchar szCmd, string& strOut, DWORD dwWaitMillSec = INFINITE);
	static bool ExecuteDos(tcpchar szCmd, tstring& strOut, DWORD dwWaitMillSec = INFINITE);
	static bool ExplorePath( tcpchar szPath, tcpchar szFocusFile = NULL);
	static DWORD RunBinExitCode(tcpchar szCmd);
	static bool RunBin(tcpchar szCmd);
	/*------------------------------------------------------------
			fun:	ͨ���ڴ�ӳ��д����
			ret:	
			param: 
			remark:	ע���С���ܳ����ڲ����ƵĴ�С, 1024
	------------------------------------------------------------*/
	static bool WriteMemMap( LPCTSTR szData, LPCTSTR szName );

	/*------------------------------------------------------------
			fun:	ͨ���ڴ�ӳ���ȡ����
			ret:	
			param: 
			remark:	ע���С���ܳ����ڲ����ƵĴ�С, 1024
	------------------------------------------------------------*/
	static tstring ReadMemMap( LPCTSTR szName );
protected:
	bool ReleaseTimer(MAP_TIMER_PARAM::iterator& itTimer, bool bClearMem = true);
	static VOID CALLBACK TimerCallback(PVOID lpParameter,BOOLEAN TimerOrWaitFired);
	bool SaveParam(TimerID nTimer, tagPTTimer* tagTimer );
	bool DealTimerCallback( PVOID lpParameter, BOOLEAN TimerOrWaitFired );
	bool IsExistTimer( TimerID pHTimer );
	tagPTTimer* GetParam( TimerID pHTimer );
	
private:
	MAP_TIMER_PARAM		m_mapTimerParam;	//��ʹ��map, keyֵ���ܸı�
	HANDLE			m_hTimerQueue;
	auto_ptr<CLock>				m_pLockTimerQueue;
	auto_ptr<CLock>				m_pLockMapList;
	auto_ptr<CLock>				m_pLockTimer;
	ENUM_TIMER_MODE				m_enTimerMode;
};

Pi_NameSpace_End
Pi_NameSpace_Using 