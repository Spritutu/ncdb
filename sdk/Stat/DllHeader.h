#pragma once
/************************************************************************
	Ĭ��Ϊ��̬��, ��̬����Ҫ����STAT_DLL_DYNAMIC ��
************************************************************************/
#ifdef DLL_SELF
	#define DLL_CLASS _declspec(dllexport)
#else 
#ifdef STAT_DLL_DYNAMIC
	#define DLL_CLASS _declspec(dllimport)
#else
	#define DLL_CLASS 
#endif

#ifdef _DEBUG
	// _DEBUG
	#ifdef _UNICODE
	#pragma comment(lib, "BYStat_d.lib")
	#else 
	#pragma comment(lib, "BYStat_da.lib")
	#endif
#else
	//release
	#ifdef _UNICODE
	#pragma comment(lib, "BYStat.lib")
	#else 
	#pragma comment(lib, "BYStat_a.lib")
	#endif
#endif 

#endif