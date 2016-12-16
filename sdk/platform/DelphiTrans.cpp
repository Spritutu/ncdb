#include "stdafx.h"
#include "DelphiTrans.h"
#include "PiString.h"
Pi_NameSpace_Using

CDelphiTrans::CDelphiTrans()
{
}


CDelphiTrans::~CDelphiTrans()
{
}

tcpchar CDelphiTrans::FilterToMFC(tcpchar szFilter)
{
	static tchar szFilterCommon[] = _T("All Files (*.*)|*.*||");
	static tcpchar pFilter = nullptr;
	if (pFilter)
	{
		delete[] pFilter;
	}
	/************************************************************************
	win32 ��ʽ:	All\0*.*\0ͼƬ\0*.jpg;*.png\0\0\0
	\0�ָ���ʾ�����ͣ� 2��һ�飬 �ֺŷָ����������ͣ� ��β3��\0

	delphi��ʽ: �����ļ�|*.*;ͼƬ|*.jpg,*.png;�ĵ�|*.doc,*.ppt
	���߷ָ���ʾ�����ͣ� �ֺŷָ�ÿ�飬���ŷֿ������������


	************************************************************************/
	//���� -> \0,   �ֺ�  -> \0,  ����->�ֺ�,  ��β��������\0
	if (!szFilter || !*szFilter)
	{
		return szFilterCommon;
	}
	CPiString str;
	if (szFilter && *szFilter)
	{
		//delphi��ʽת��MFC
		str = szFilter;
		str.append(_T("||"));

		void* p = new TCHAR[str.size() + 1];
		memcpy_s(p, str.size() * sizeof(TCHAR), str.c_str(), str.size() * sizeof(TCHAR));
		pFilter = (tcpchar)p;
	}
	return pFilter;
}

tcpchar CDelphiTrans::FilterToWin32(tcpchar szFilter)
{
	static tchar szFilterCommon[] = _T("All\0*.*\0ͼƬ\0*.jpg;*.png\0\0\0");
	static tcpchar pFilter = nullptr;
	if (pFilter)
	{
		delete[] pFilter;
	}
	/************************************************************************
			win32 ��ʽ:	All\0*.*\0ͼƬ\0*.jpg;*.png\0\0\0
						\0�ָ���ʾ�����ͣ� 2��һ�飬 �ֺŷָ����������ͣ� ��β3��\0

			delphi��ʽ: �����ļ�|*.*;ͼƬ|*.jpg,*.png;�ĵ�|*.doc,*.ppt
						���߷ָ���ʾ�����ͣ� �ֺŷָ�ÿ�飬���ŷֿ������������


	************************************************************************/
	//���� -> \0,   �ֺ�  -> \0,  ����->�ֺ�,  ��β��������\0
	if (!szFilter || !*szFilter)
	{
		return szFilterCommon;
	}
	CPiString str;
	if (szFilter && *szFilter)
	{
		//delphi��ʽת��MFC
		str = szFilter;
		str.ReplaceZero(_T("|"));
		str.ReplaceZero(_T(";"));
		str.Replace(_T(","), _T(";"));
		str.AppendZero(2);
		
		void* p = new TCHAR[str.size() + 1];
		memcpy_s(p, str.size() * sizeof(TCHAR), str.c_str(), str.size() * sizeof(TCHAR));
		pFilter = (tcpchar)p;
	}
	return pFilter;
}
