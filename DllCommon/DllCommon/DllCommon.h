////////////////////////////  ����ͷ�ļ� ///////////////////////////////////////
#include <windows.h>
#include <string>
#include "UI\PiUITool.h"
using namespace std;

#if defined(__cplusplus)
#define NCCOMMON_EXTERN_C extern "C"
#else
#define NCCOMMON_EXTERN_C
#endif

#ifdef DLLCOMMON_EXPORTS
#define NCCOMMON_SYMBOL __declspec(dllexport)
#else
#define NCCOMMON_SYMBOL __declspec(dllimport)
#endif // DLLCOMMON_EXPORTS

#define NCCOMMON_API NCCOMMON_EXTERN_C NCCOMMON_SYMBOL
#define NCCOMMON_CALL _cdecl


typedef CPIUITool::tagSELECT_FILE_DIR tagSELECT_FILE_DIR;

/*
struct tagSELECT_FILE_DIR
{
	HWND			hParent;			//�������ڣ� ����Ϊ��
	const wchar_t*	szBeginDir;			//��ʼ��ʾĿ¼, ��Ϊ��
	const wchar_t*	szTitle;			//���ڱ��⣬ ��Ϊ��
	const wchar_t*	szBtnOkName;		//ok��ťҪ�滻�ɵ����֣�  ���Ϊ������ʾΪ"ȷ��"
	const wchar_t*	szFilter;			//�����ַ���
	bool			bCenterToParent;	//true��Ը����ھ��У� ������Ļ����
	bool			bSelectMulti;		//trueΪ����ѡ�����ļ�

	//���³�Ա�����ڲ�ʹ��
	//int				nSelectCount;		
	//int				pFileLst;			

	tagSELECT_FILE_DIR()
		:hParent(NULL)
		, szBeginDir(NULL)
		, szTitle(NULL)
		, szBtnOkName(NULL)
		, bCenterToParent(true)
		, bSelectMulti(false)
	{

	}
};*/
/************************************************************************
	fun:	����ѡ��Ի���  ��ѡ���ļ���Ŀ¼
	param:	
	memo:	
************************************************************************/
NCCOMMON_API int NCCOMMON_CALL SelectFileOrDir(tagSELECT_FILE_DIR* pTag);
NCCOMMON_API const wchar_t* QuerySelectFile(int nIndex);
