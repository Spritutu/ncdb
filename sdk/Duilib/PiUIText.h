#pragma once
#include "Control\UIText.h"
/*------------------------------------------------------
	Fun:	EstimateSize(CPiSize(9999,9999));
	Authon: liwanliang
	memo:	�����Ҫ��������ƽ���������С, ����EstimateSize(CPiSize(9999,9999));����ƴ�С������pos��
	Date:	2016/03/01
------------------------------------------------------*/
class CPiUIText :
	public CTextUI
{
public:
	CPiUIText(void);
	~CPiUIText(void);
public:
	virtual SIZE EstimateSize(SIZE szAvailable);
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	void PaintText(HDC hDC);
private:
	bool			m_bAutoSize;
};
