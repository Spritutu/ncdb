#pragma once
#include "PiTypeDef.h"
#include "ThreadLight.h"
#include "PathLight.h"
/************************************************************************
	fun: ���δ��ڵĶ�����, Ҳ��֧�ֵ��ž�̬ͼƬ
	remark:	�߳����ڶ�ʱ������Ϣ��������ʵ�ֻ���, ����ͨ�����ø����ShowNextFrameʵ�ֻ���
************************************************************************/
class ImageEx;


struct tagANIMATION_FRAME
{
	tagANIMATION_FRAME(tcpchar szPath, int nRate)
	{
		strPicPath = szPath;
		nFrameRate = nRate;
	}
	tstring		strPicPath;
	int			nFrameRate;
};

typedef list<tagANIMATION_FRAME> LST_FRAME;
typedef int GroupID;
struct tagFRAME_GROUP
{
public:
	tagFRAME_GROUP()
	{
		Clear();
	}
	void Clear()
	{
		nIDGroup = 0;
		bLoop = true;
		bGif = false;
		lstFrame.clear();
	}
	GroupID		nIDGroup;
	LST_FRAME	lstFrame;
	bool		bLoop;		//����ȫ����������Ƿ�ѭ������
	bool		bGif;		//�Ƿ�ΪgifͼƬ
};
typedef list<tagFRAME_GROUP>	LST_FRAME_GROUP;


class CPiAnimation
	:public CThreadLight
{
public:
	CPiAnimation(void);
	virtual ~CPiAnimation(void);
public:
	bool Init();
	bool UnInit();
	virtual DWORD DoWork() ;

	UNINT GetFrameSleep();

public:
	bool ShowNextFrame( HDC hdcUI );

	bool DrawGif();
	bool DrawMultiPic();

	void SetImageDir( LPCTSTR param1 );
	bool SetImage( LPCTSTR param1 );
	void SetMsgID(int nMsg);
	
	//bool SetFrame(LST_FRAME lstFrame);
	int NextFrame();
	HWND GetWnd() const { return m_hWnd; }
	void SetWnd(HWND val) { m_hWnd = val; }
	bool AddGroup( const tagFRAME_GROUP& fGroup );
	void SetPlayGroup( GroupID id);
	bool SetDrawPos(const POINT& ptPos);
private:
	void SetImage( LST_STRING lstPic );
	bool SetFrameRate(LST_INT lstRate);
	bool IsNeedStopLoop();
	bool InitGif();
public:
	ImageEx*			m_pGif;
	tstring				m_strPicGif;
	vector<tstring>		m_lstPic;
	LST_INT				m_lstFrameRate;
	tagFRAME_GROUP*			m_lstFrameGroupCurrent;	//��ǰ��Ķ���, ref

	LST_FRAME_GROUP		m_lstFrameGroup;
	auto_ptr<CLock>				m_pLockGroup;
	auto_ptr<CEventLight>		m_pEventDrawIdle;
	int					m_nCurrentPic;

	bool				m_bIsGif;
	CPathLight				m_strDirPic;	

	HWND				m_hWnd;
	HDC					m_hdcUI;		//���Ƶ�dc
	int					m_nMsg;			//���ƶ�������Ϣ
	bool				m_bFrameLast;	//���鶯���ѵ����һ֡

	POINT				m_ptDraw;		//���Ƶ�λ��
};
