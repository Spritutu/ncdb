#pragma once
#include "..\PiTypeDef.h"
using std::string;
/************************************************************************/
/*	fun: ��ȡһ���Ϸ��ļ�·��, ������Ҫ֧���Ϸ�:ͨ��DragAcceptFiles����
/************************************************************************/
class CPIUITool
{
public:
	static tstring GetOneDragFilePath(const HDROP& hd);
	static tstring SelectDirectory(HWND hParent, tcpchar szBeginDir, tcpchar szTitle);
	/************************************************************************
		fun:	����ѡ��Ի���  ��ѡ���ļ���Ŀ¼
		param:	szBeginDir, ��������ʾ����ʼĿ¼�� ���Ŀ¼����������ʾ�ϴε�Ŀ¼
		memo:	
	************************************************************************/
	static tstring SelectFileOrDir(HWND hParent, tcpchar szBeginDir, tcpchar szTitle, tcpchar szBtnOkName);
};
