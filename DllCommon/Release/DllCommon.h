////////////////////////////  ����ͷ�ļ� ///////////////////////////////////////
#include <windows.h>
#include <string>
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
#endif // NC_DLL_COMMON_BUILDING

#define NCCOMMON_API NCCOMMON_EXTERN_C NCCOMMON_SYMBOL
#define NCCOMMON_CALL _cdecl


struct tagSELECT_FILE_DIR
{
	HWND			hParent;		//��ʾʱ��Ը����ھ���;  ���Ϊ��, ����ʾ����ʱ�����Ļ����
	const wchar_t*	szBeginDir;		//��ʼ��ʾĿ¼, ��Ϊ��
	const wchar_t*	szTitle;		//���ڱ��⣬ ��Ϊ��
	const wchar_t*	szBtnOkName;	//ok��ťҪ�滻�ɵ����֣�  ���Ϊ������ʾΪ"ȷ��"

	tagSELECT_FILE_DIR()
		:hParent(NULL)
		, szBeginDir(NULL)
		, szTitle(NULL)
		, szBtnOkName(NULL)
	{

	}
};

/************************************************************************
	fun:	����ѡ��Ի���  ��ѡ���ļ���Ŀ¼
	param:	szBeginDir, ��������ʾ����ʼĿ¼�� ���Ŀ¼����������ʾ�ϴε�Ŀ¼
	memo:	szSelectPath����ѡ���·���� ���1024�ֽ�, ��Ҫ�ⲿ����
************************************************************************/
NCCOMMON_API void NCCOMMON_CALL SelectFileOrDir(tagSELECT_FILE_DIR* pTag, OUT wchar_t* szSelectPath);

