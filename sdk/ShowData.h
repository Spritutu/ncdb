#pragma once
struct TrackShow;
#include <map>
#include "PiTypeDef.h"
#include <string>

using namespace std;

struct DeviceInfo 
{
	string	strSBDZ;
	string	strIp;
	byte	byLaneCount;
};

typedef map<string, UINT> LineMap;
typedef map<string, DeviceInfo> DeviceInfoMap;

class CShowData
{
public:
	CShowData(CWnd* );
	~CShowData(void);

public:
	bool Init();
	bool ShowData( DWORD dwLine);
	bool ShowTemplateData();
	bool ShowSubTemplateData();
	/************************************************************************/
	/*	fun: ��ȡָ���豸��ŷ���������Ҫ��ʾ�ڿؼ�����һ��                                                                     */
	/************************************************************************/
	DWORD	GetLineToShow(string strSBBH, byte laneId);
	bool	SetDeviceShowLaneMap(string strSBBH);
	bool	SetDeviceInfoMap(string strSBBH, const DeviceInfo& di);
	DWORD	GetExistTotal();
	void	SetData(TrackShow* );
	bool AdjustColumnWidth();

	UNINT	m_iColumnCount;
	CWnd* m_pWnd;

	LineMap*				m_pLineMap;
	DeviceInfoMap*		m_DeviceInfoMap;
	TrackShow*				m_pData;

	CRITICAL_SECTION		m_csDB;
};
