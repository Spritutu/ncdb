#ifndef GifAnimUIEx_h__
#define GifAnimUIEx_h__

#pragma once
class CControl;

#define ENTER_TIMER              UIMSG_USER+1
#define EVENT_TIEM_ID	100
#define NORMAL_BORDER_COLOR      0xFFCCCCCC              //��ͨ״̬�߿���ɫ
#define HOT_BORDER_COLOR         0xFF00B3F3              //����״̬�߿���ɫ
#define TOP_DISTANCE_GIF         4                       //�����������붥������
#define BOTTOM_DISTANCE_GIF      40                      //������������ײ�����
#define HEIGHT_RECT              60                      //��������߶�
#define WIDTH_RECT               60                      //����������
#define DUI_MSGTYPE_GIF_CLICK                  (_T("gifclick"))
#define DUI_MSGTYPE_GIF_MENU                   (_T("gifmenu"))
class CGifAnimUIEx : public CControlUI
{
	DECLARE_DUICONTROL(CGifAnimUIEx)
public:
	CGifAnimUIEx(void);
	~CGifAnimUIEx(void);

	void	DoEvent(TEventUI& event) override;
	void	SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue) override;
	void	DoPaint(HDC hDC, const RECT& rcPaint) override;
	void	DoInit() override;
	void	SetVisible(bool bVisible = true) override;

	void	SetBkImage(LPCTSTR pStrImage);
	LPCTSTR GetBkImage();

	void	SetAutoPlay(bool bIsAuto = true);
	bool	IsAutoPlay() const;
	void	SetAutoSize(bool bIsAuto = true);
	bool	IsAutoSize() const;
	void	PlayGif();
	void	PauseGif();
	void	StopGif();
	
private:
	void	InitGifImage();
	void	DrawFrame(HDC hDC);		// ����GIFÿ֡
	void    OnMouseInTimer(UINT_PTR idEvent);
	Gdiplus::Image*	LoadGifFromFile(LPCTSTR pstrGifPath);
	Gdiplus::Image* LoadGifFromMemory(LPVOID pBuf, size_t dwSize);
	void	DeleteGif();
	void    OnTimer(UINT_PTR idEvent);
	//Gdiplus::Image	*m_pGifImage;

	bool smallGif;
public:
	int gifHeight;
	int gifWidth;

	Gdiplus::Image	*m_pGifImage;
	UINT			m_nFrameCount;				// gifͼƬ��֡��
	UINT			m_nFramePosition;			// ��ǰ�ŵ��ڼ�֡
	Gdiplus::PropertyItem*	m_pPropertyItem;	// ֡��֮֡����ʱ��

	CDuiString		m_sBkImage;
	bool			m_bIsAutoPlay;				// �Ƿ��Զ�����gif
	bool			m_bIsAutoSize;				// �Ƿ��Զ�����ͼƬ���ô�С
	bool			m_bIsPlaying;
	HGLOBAL hMem;
	IStream* pStm;
};

#endif // GifAnimUI_h__
