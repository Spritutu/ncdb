#include "stdafx.h"
#include "ColorShade.h"
#include <GdiPlus.h>
//#include <GdiplusHeaders.h>
using namespace Gdiplus;
CColorShade::CColorShade(void)
{

    //Initial Color of show
    m_clrStart  = COLORREF(RGB(255,0,0));
    m_clrEnd    = COLORREF(RGB(0,0,255));

    m_pdcBg             = nullptr;
    m_bgOldObj          = nullptr;
    m_bInit             = false;
    m_pWnd              = NULL;
    m_nBmID         = NULL;
}


CColorShade::~CColorShade(void)
{
    UnInit();
}

bool CColorShade::Init()
{
    CDC* pdcSrc = m_pWnd->GetDC();

    if (m_pdcBg)
    {
        m_pdcBg->SelectObject(m_bgOldObj);
        //����֮ǰ�� ����֮ǰ��λͼ m_bm
        m_bm.DeleteObject();
    }
    

    m_pdcBg = new CDC;
    m_pdcBg->CreateCompatibleDC(m_pDCDist);

    if( ! m_bm.CreateCompatibleBitmap(pdcSrc, m_rectUI.right, m_rectUI.bottom) )
    {
        return FALSE;
    }

    m_bgOldObj = m_pdcBg->SelectObject(m_bm);

    m_pWnd->ReleaseDC(pdcSrc);
    return true;
}

bool CColorShade::UnInit()
{
    //m_pWnd->ReleaseDC(m_pDCUI);
    delete m_pdcBg;
    m_pdcBg = nullptr;
    return true;
}

void CColorShade::SetRect( CRect rectClient )
{
    m_rectUI = rectClient;
}

bool CColorShade::InitBg()
{
    //�������ò���, ��ʼ������ͼ��: ��ɫ��, ÿ����ɫ���
    if ( ! m_bInit )
    {
        Init();
        m_bInit = true;
    }
    if (m_nBmID)
    {
        InitBgPic();
    }
    else
    {
        InitBgShade();
    }

    return true;
}

bool CColorShade::Show( const CRect& rt )
{
    if(! m_pDCDist->BitBlt(rt.left, rt.top, rt.right, rt.bottom + 1,  m_pdcBg, 0, 0, SRCCOPY))
    {
        return true;
    }
    //ShowUI();
    return true;
}

void CColorShade::ShowUI()
{
    CDC* pdc = m_pWnd->GetDC();

    if(!pdc->BitBlt(0, 0, m_rectUI.right, m_rectUI.bottom, m_pdcBg, 0, 0, SRCCOPY))
    {
        return ;
    }
    m_pWnd->ReleaseDC(pdc);

}

void CColorShade::InitBgShade()
{
    RECT	rectFill;		//��ʾ����
    float	fStep = 0;			//ÿһ���ķ���
    CBrush	brush;			//��ʾ����ɫ��ˢ

    int		r  = 0,g  = 0,b  = 0;
    float rStep = 0;
    float gStep = 0;
    float bStep = 0;

    //�õ���ͬ��ɫ�������������ɫ֮�������ֵ
    r = ( GetRValue(m_clrEnd) - GetRValue(m_clrStart) );
    g = ( GetGValue(m_clrEnd) - GetGValue(m_clrStart) );
    b = ( GetBValue(m_clrEnd) - GetBValue(m_clrStart) );

    //ʹ��������ʾ������ ����������ɫ��ֵ, ȷ���м�����ɫ
    int nColorCount = 0;
    int nSteps = max(abs(r),max(abs(g),abs(b)));

    if (nSteps)
    {
        //����ÿһ��ɫ���Ĳ���
        rStep = r/(float)nSteps;
        gStep = g/(float)nSteps;
        bStep = b/(float)nSteps;
    }

    nColorCount = nSteps + 1;
    //ÿһ��ɫռ�ľ��ο��
    float nBlockWidth = (float)m_rectUI.right/(float)nColorCount;


    r = GetRValue(m_clrStart);
    g = GetGValue(m_clrStart);
    b = GetBValue(m_clrStart);
    //������ɫ����Ľ�����

    for(int i = 0; i < nColorCount; i++)
    {
        ::SetRect(&rectFill,
            //����Ϊ��������������Ͻ�x,y�����½�x,y
            (int)(i * nBlockWidth),
            0,
            (int)((i + 1) * nBlockWidth),
            m_rectUI.bottom + 1);

        VERIFY( brush.CreateSolidBrush( RGB( r + rStep * i, g + gStep * i, b + bStep * i)) );
        m_pdcBg->FillRect(&rectFill, &brush);

        VERIFY(brush.DeleteObject());
    }
}

bool CColorShade::InitBgPic()
{
    CDC dc;
    dc.CreateCompatibleDC(m_pdcBg);

    CBitmap bm;
    if(!bm.LoadBitmap(m_nBmID))
    {
        return false;
    }
    dc.SelectObject(bm);

    if(!m_pdcBg->BitBlt(0, 0, m_rectUI.right, m_rectUI.bottom, &dc, 0, 0, SRCCOPY))
    {
        return false;
    }
    return true;
}
