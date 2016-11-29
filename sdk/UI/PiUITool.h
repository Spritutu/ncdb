#pragma once
#include "..\PiTypeDef.h"
#include <Windows.h>
using std::string;




class CPIUITool
{
public:
	struct tagSELECT_FILE_DIR
	{
		HWND			hParent;			//�������ڣ� ����Ϊ��
		const wchar_t*	szBeginDir;			//��ʼ��ʾĿ¼, ��Ϊ��
		const wchar_t*	szTitle;			//���ڱ��⣬ ��Ϊ��
		const wchar_t*	szBtnOkName;		//ok��ťҪ�滻�ɵ����֣�  ���Ϊ������ʾΪ"ȷ��"
		bool			bCenterToParent;	//true��Ը����ھ��У� ������Ļ����
		tagSELECT_FILE_DIR()
			:hParent(NULL)
			, szBeginDir(NULL)
			, szTitle(NULL)
			, szBtnOkName(NULL)
			, bCenterToParent(true)
		{

		}
	};
	/************************************************************************/
	/*	fun: ��ȡһ���Ϸ��ļ�·��, ������Ҫ֧���Ϸ�:ͨ��DragAcceptFiles����
	/************************************************************************/
	static tstring GetOneDragFilePath(const HDROP& hd);
	static tstring SelectDirectory(HWND hParent, tcpchar szBeginDir, tcpchar szTitle);
	/************************************************************************
		fun:	����ѡ��Ի���  ��ѡ���ļ���Ŀ¼
		param:	szBeginDir, ��������ʾ����ʼĿ¼�� ���Ŀ¼����������ʾ�ϴε�Ŀ¼
		memo:	
	************************************************************************/
	//static tstring SelectFileOrDir(HWND hParent, tcpchar szBeginDir, tcpchar szTitle, tcpchar szBtnOkName);
	static bool SelectFileOrDir(tagSELECT_FILE_DIR* pTag, tstring& strPath);
};
