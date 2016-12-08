#pragma once
#include "..\PiTypeDef.h"
#include <Windows.h>
#include <shlwapi.h>
#include <shellapi.h>
using std::string;




class CPIUITool
{
public:
	struct tagSELECT_FILE_DIR
	{
		HWND			hParent;			//�������ڣ� ����Ϊ��
		const wchar_t*	szBeginDir;			//��ʼ��ʾĿ¼, ��Ϊ��
		const wchar_t*	szBeginFileName;	//��ʼ��ʾ�ļ���
		const wchar_t*	szTitle;			//���ڱ��⣬ ��Ϊ��
		const wchar_t*	szBtnOkName;		//ok��ťҪ�滻�ɵ����֣�  ���Ϊ������ʾΪ"ȷ��"
		const wchar_t*	szFilter;			//�����ַ���
		bool			bCenterToParent;	//true��Ը����ھ��У� ������Ļ����
		bool			bSelectMulti;		//trueΪ����ѡ�����ļ�
		
		//���³�Ա�����ڲ�ʹ��
		//int				nSelectCount;		
		//int				pFileLst;			

		tagSELECT_FILE_DIR()
			:hParent(nullptr)
			, szBeginDir(nullptr)
			, szBeginFileName(nullptr)
			, szTitle(nullptr)
			, szBtnOkName(nullptr)
            , szFilter(nullptr)
			, bCenterToParent(true)
			, bSelectMulti(false)
		{

		}
	};
	struct tagSAVE_FILE
	{
		HWND			hParent;			//�������ڣ� ����Ϊ��
		const wchar_t*	szBeginDir;			//��ʼ��ʾĿ¼, ��Ϊ��
		const wchar_t*	szTitle;			//���ڱ��⣬ ��Ϊ��
		const wchar_t*	szFilter;			//�����ַ���
		const wchar_t*	szBeginFileName;	//Ĭ���ļ���
		bool			bCenterToParent;	//true��Ը����ھ��У� ������Ļ����
		bool			bTypeSmall;			//trueʹ��С������ʽ�� ���򿪶Ի���һ���Ĵ�С

		tagSAVE_FILE()
			:hParent(nullptr)
			, szBeginDir(nullptr)
			, szTitle(nullptr)
			, szFilter(nullptr)
			, szBeginFileName(nullptr)
			, bCenterToParent(true)
			, bTypeSmall(false)
		{}
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
	static int SelectFileOrDir(tagSELECT_FILE_DIR* pTag);
	static ARR_STRING& GetFileList();
	static void AlterPath();
	static tcpchar QuerySelectFile(UNINT nIndex);

	/************************************************************************
		fun:	����Ի���
		param:	
		memo:	
	************************************************************************/
	static tstring PopSaveDialog(tagSELECT_FILE_DIR* pTag);
private:
	static		ARR_STRING		m_FileList;
};
