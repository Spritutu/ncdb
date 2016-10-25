#pragma once
#include <windows.h>
#include <memory>

// CLCSort

typedef int  (CALLBACK* pfnCompare)(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
class CLCSort : public CListCtrl
{
	DECLARE_DYNAMIC(CLCSort)

public:
	struct TWO_POINT
	{	
		int			nColumn;		//��ǰ���������һ��
		CLCSort*	pLC;			//CListCtrlָ��
	};
	CLCSort();
	virtual ~CLCSort();

protected:
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult);

public:
	/************************************************************************/
	/*	fun: item����ӿ�
	/************************************************************************/
	bool SortAllItem();
	/************************************************************************/
	/*	fun: ����ָʾ��������
	/************************************************************************/
	void EndInsetColumn();	

	/************************************************************************/
	/*	fun: ָ���е�ǰ�Ƿ�Ϊ��������
	/************************************************************************/
	bool ReverseColumnSort(UNINT nColumn);
	/************************************************************************/
	/*	fun: ��ȡ��ǰӦ�ý��е�����״̬
		ret: ��ǰ�Ƿ�Ӧ������, true -> ����,   false -> ����
	/************************************************************************/
	bool GetSortOrder();
	pfnCompare SetCompareFun(pfnCompare pfn);
private:
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
private:
	bool*		m_pIsSortAsc;		//ÿһ�е�ǰ������״̬�Ƿ�Ϊ����,
	bool		m_bSortAsc;		//��ǰ�Ƿ�Ӧ������, true -> ����,   false -> ����
	bool		m_bIsSortSupport;
	int			m_nClientColumn;	//��ǰ�������
	pfnCompare	m_pfnCompare;		//
};


