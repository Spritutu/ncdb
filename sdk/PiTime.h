#pragma once
#include <Windows.h>
#include "PiTypeDef.h"

#define STR_DATATIME_FORMAT "%04d/%02d/%02d %02d:%02d:%02d"
typedef map<tstring, int> MAP_MONTH_ABBR;
class CPiTime
{

public:
	CPiTime(void);
	~CPiTime(void);
public:
	static tstring GetLocalDateTime(tcpchar szFormat = _T("%04d-%02d-%02d %02d:%02d:%02d"));

	//ʱ���ת��������ʽ�ַ�����ʱ��
	static string SwitchTimeStampToStr(const char* cTimestamp, const char* cFormat = STR_DATATIME_FORMAT);

	//��ȡ��������      
	static tstring GetLocalDate(tcpchar szFormat = _T("%04d-%02d-%02d"));

	//��ȡ����ʱ��(h,m,s) 
	static tstring GetSysTime();

	//��ȡ1970��������������,UTCʱ��
	static __time64_t GetTimestampMilliSecUTC();

	//��ȡϵͳ��ǰ�ĺ�����, 0 - 999
	static UNINT GetCurrentMillionSecond();
	static tm ST2TM(SYSTEMTIME* );
	static SYSTEMTIME TimestampToST(const char* cTimestamp);

	/*
	    fun:  ʱ����ַ���ת��1970��������������
	    note: ������ʽΪ yyyymmddhh(24)mimissMilS
	*/
	static time_t TimestampToSecond1970(const char* cTimestamp);
	//1970���������ĺ�����
	static time_t TimestampToMilSecond1970(const char* cTimestamp);

	//��ʱ��ṹ��ת���ַ���
	static string TimeToString(SYSTEMTIME* st, const char* format =  STR_DATATIME_FORMAT);
	static string TimeToString(tm* pTM, const char* format = "%04d/%02d/%02d %02d:%02d:%02d");
	//ת��1970�꾭���ĺ�����, ��ʽ˵����, ������, ʱ����, �и��ֶ��Ҳ���, �����Ķ��������
	static time_t TimeStrToIntSecond1970(tcpchar szTime, tcpchar szFormat = _T("%4d_%2d_%2d %2d:%2d:%2d"));

	static SYSTEMTIME TM2ST(tm* pTM);
	/************************************************************************/
	/*  fun: 1970�꾭���ĺ�����ת�� SYSTEMTIME �ṹ
	/************************************************************************/
	static SYSTEMTIME MillionSecond1970ToST(const time_t& timeTemp);

	static tstring MilliSecond1970ToString(const time_t& timeTemp, tcpchar format = _T("%04d-%02d-%02d %02d:%02d:%02d:%03d"));
	static tstring Second1970ToString(const time_t& timeTemp, tcpchar format = _T("%04d-%02d-%02d %02d:%02d:%02d"));

	//ָ����ʱ�����ַ���ת����ֵ��, ��ߵ�λΪʱ, �ɳ���24Сʱ

	static bool TimeStrToSecondHighHour( tcpchar szTime, time_t* pTime, tcpchar szFormat = _T("%d:%2d:%2d") );
	static tstring TimeShortToTimeStdString(const tstring& strTime);
	static tstring SecondToTimeStrHighHour(time_t nSecond, tcpchar szFormat = _T("%02d:%02d:%02d") );
	//�·ݼ�д�ַ�����Ӧ���·���
	static MAP_MONTH_ABBR GetMonthAbbrNameMap();
	static tstring VariantDTToString(double dt);
	static tstring GetTimestamp();

};
