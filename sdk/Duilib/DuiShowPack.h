#pragma once
/*------------------------------------------------------
	Fun:	��duilib���ڿؼ����ж�team-��-���Ĺ���, ÿ����ĸ��黥��,ͬһʱ��ֻ��1�����ʾ
	Authon: liwanliang
	Date:	2015/09/06
------------------------------------------------------*/
#include "PiTypeDef.h"
#include "DuiHeader.h"

struct tagSHADE_CONTROL
	
{
	tagSHADE_CONTROL(const tstring strControlR, bool bShowR)
		:bShow(bShowR)
		, strControl(strControlR)
	{
	}
	bool	bShow;
	tstring	strControl;
};
typedef list<tagSHADE_CONTROL>		LST_SHADE;
typedef map<int, LST_STRING>		MAP_CONTROL_LIST;
typedef map<int, MAP_CONTROL_LIST>	MAP_CONTROL_TEAM;
typedef map<int, LST_SHADE>			MAP_CONTROL_SHADE;

class CDuiShowPack
{
public:
	enum ENUM_ELEM{All_Elem = 999999};
	CDuiShowPack(CPaintManagerUI* pPaintManager = NULL);
	~CDuiShowPack(void);
public:
	/*------------------------------------------------------------
			fun:	��ָ�������������Ŀؼ�������, ��ʾָ����
			ret:	
			param: pCtn: �ؼ����ڵ�����,�����ֵΪ0, ��ȫ�ֽ����в��ҿؼ�
			remark:	
	------------------------------------------------------------*/
	void ChangeUI( int nTeamID, int nGroupID, CContainerUI* pCtn = NULL);
	/*------------------------------------------------------------
			fun:	����������, ��ʾָ����
			ret:	
			param: pCtn: �ؼ����ڵ�����,�����ֵΪ0, ��ȫ�ֽ����в��ҿؼ�
			remark:	
	------------------------------------------------------------*/
	void Show( int nTeamID, int nGroupID, CContainerUI* pCtn = NULL);
	/*------------------------------------------------------------
			fun:	��ʾ�ض���Ŀؼ�
			ret:	
			param: true, ʹ�����ʱָ���Ŀɼ���, false:ʹ�ø����ʱ�෴�Ŀɼ���
			remark:	
	------------------------------------------------------------*/
	void ShowShade(int nGroupID, CContainerUI* pCtn = NULL, bool bShow = true);
	//void Show(CListContainerElementUI* pListCtn, int nTeamID, int nGroupID );
	void AddShow( int nTeamID, const MAP_CONTROL_LIST& mapList );
	void ShowAll( int nGroupID );
	bool HideAll();
	bool Hide(int nTeamID);
	/*------------------------------------------------------------
			fun:	���ӿɷ�ת�Ŀؼ�����
			ret:	
			param: bShow, Ĭ�ϵ���ʾ��ʶ, ������ʾʱ���Է�ת�ñ�ʶ
			remark:	ʹ��ShowShade����ʾ��ӵĿؼ�
	------------------------------------------------------------*/
	void AddShadeShow( int nGroup, tcpchar szControl, bool bShow);
private:
	MAP_CONTROL_TEAM				m_mapConnectPrompt;//������������ʾ
	MAP_CONTROL_SHADE				m_mapShowShade;	//��ԭ������������ʾ����
	CPaintManagerUI*					m_PaintManager;
};
