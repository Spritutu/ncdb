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
};
