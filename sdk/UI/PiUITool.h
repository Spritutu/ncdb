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
	static int SelectFileOrDir(tagSELECT_FILE_DIR* pTag, tstring& strPath);
	static ARR_STRING& GetFileList();
	static void AlterPath();
	static const wchar_t* QuerySelectFile(UNINT nIndex);
private:
	static		ARR_STRING		m_FileList;
};
