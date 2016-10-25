// LCSort.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RFID_Data_Server.h"
#include "LCSort.h"


// CLCSort

int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

IMPLEMENT_DYNAMIC(CLCSort, CListCtrl)

CLCSort::CLCSort()
{
	m_pIsSortAsc	= NULL;
	m_bIsSortSupport = NULL;
	m_nClientColumn = 0;
	m_pfnCompare	= &CLCSort::CompareFunc;
}

CLCSort::~CLCSort()
{
	if (m_pIsSortAsc)
	{
		delete[] m_pIsSortAsc;
		m_pIsSortAsc	= NULL;
	}
}


BEGIN_MESSAGE_MAP(CLCSort, CListCtrl)
	
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, &CLCSort::OnLvnColumnclick)
END_MESSAGE_MAP()



// CLCSort ��Ϣ�������



void CLCSort::OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nClientColumn = pNMLV->iSubItem;

	this->SortAllItem();

	*pResult = 0;
}

void CLCSort::EndInsetColumn()
{
	DWORD dwColumnCount = this->GetHeaderCtrl()->GetItemCount();
	m_pIsSortAsc = new bool[dwColumnCount];
	memset(m_pIsSortAsc, 0, dwColumnCount * sizeof(bool));

}

bool CLCSort::ReverseColumnSort( UNINT nColumn )
{
	m_bSortAsc = m_pIsSortAsc[nColumn] = !m_pIsSortAsc[nColumn];
	return m_bSortAsc;
}

bool CLCSort::GetSortOrder()
{
	return m_bSortAsc;
}

bool CLCSort::SortAllItem()
{
	/************************************************************************/
	/*	ͨ������ÿ��item�� lParam����Ϊ����ǰ��������ֵ, ������ʱͨ��lParam����ʾһ��item,
		�����ڸ���32bitֵ, ����ظ��ǵ�֮ǰ���õ�lParam
	/************************************************************************/

	//�����Ĭ�ϵıȽϺ���, ����ø������ķ�ʽ����ʶÿһ��item
	if (&CLCSort::CompareFunc == m_pfnCompare )
	{
		int nCount = this->GetItemCount();
		assert(nCount >= 0 && "GetItemCount < 0");

		for (int i = 0; i < nCount; ++i)
		{
			if(!this->SetItemData(i, i))
			{
				assert(0 && "SetItemData fail");
			}
		}

	}
	/************************************************************************
		����������ȽϺ���, �������������ֱ�ʶ, ÿ���lparam����Ψһ��ʾһ����
	/************************************************************************/

	TWO_POINT tp;
	tp.pLC		= this;
	tp.nColumn	= m_nClientColumn;

	this->ReverseColumnSort(m_nClientColumn);

	this->SortItems(m_pfnCompare, (DWORD_PTR)&tp);
	return true;
}

int CALLBACK CLCSort::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	typedef CLCSort::TWO_POINT TWO_POINT;
	TWO_POINT* pTP = (TWO_POINT*)lParamSort;
	CLCSort* pLC = pTP->pLC;
	int nItemIndex = 0;
	bool bAsc	= false;

	CString str1;
	CString str2;

	nItemIndex = (int)lParam1;
	str1 = pLC->GetItemText(nItemIndex, pTP->nColumn);

	nItemIndex = (int)lParam2;
	str2 = pLC->GetItemText(nItemIndex, pTP->nColumn);

	int nRet = str1.Compare(str2);  // <0 : С��
	bAsc = pLC->GetSortOrder();
	if (!bAsc)
	{
		nRet = -nRet;
	}
	// <0 ����1��ǰ��, >0 ����1�ź���
	return nRet;
}


pfnCompare CLCSort::SetCompareFun( pfnCompare pfn )
{
	pfnCompare pOld = m_pfnCompare;
	m_pfnCompare = pfn;
	return pOld;
}
