#include "StdAfx.h"
#include "UIUtil.h"

CUIUtil::CUIUtil(void)
{
}

CUIUtil::~CUIUtil(void)
{
}

tstring CUIUtil::GetOpenDialog()
{
	tstring strPath;

	TCHAR szBuffer[MAX_PATH + 1] = {0};  
	OPENFILENAME ofn = {0};
	ofn.lStructSize = sizeof(OPENFILENAME);   
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = _T("apk�ļ�(*.apk)\0*.apk\0�����ļ�(*.*)\0*.*\0\0");//Ҫѡ����ļ���׺   
	//ofn.lpstrInitialDir = _T("D:\\Program Files");//Ĭ�ϵ��ļ�·��   
	ofn.lpstrFile = szBuffer;//����ļ��Ļ�����   
	ofn.nMaxFile = MAX_PATH;   
	ofn.nFilterIndex = 0;   

	if(!GetOpenFileName(&ofn))
	{
		return strPath;
	}
	strPath = ofn.lpstrFile;
	return strPath;
}
