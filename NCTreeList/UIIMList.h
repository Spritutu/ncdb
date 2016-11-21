/*******************************************************************************
*  @file      UIIMList.h 2016-11-18 15:18:16
*  @author    �޹��<cuiguanghui@naycent.com>
*  @brief
******************************************************************************/
#ifndef UIIMLIST_548A8B8B_30ED_4E85_8BB4_32FB9EC52FE6_H__
#define UIIMLIST_548A8B8B_30ED_4E85_8BB4_32FB9EC52FE6_H__

#include "UIIMListCommonDefine.h"

class IMListItemInfo
{
public:
	IMListItemInfo();
	~IMListItemInfo();

	bool folder;
	bool empty;
	int id;
	CDuiString avatarPath;
	CDuiString nickName;
	CDuiString description;
};

/******************************************************************************/

/**
 * The class <code>UIIMList</code> 
 *
 */
class UIIMList : public CListUI
{
public:
    /** @name Constructors and Destructor*/

    //@{
    /**
     * Constructor 
     */
	UIIMList(CPaintManagerUI& paint_manager);
    /**
     * Destructor
     */
    virtual ~UIIMList();
    //@}

public:
	enum { SCROLL_TIMERID = 10 };
	bool Add(CControlUI* pControl);
	bool AddAt(CControlUI* pControl, int iIndex);
	bool Remove(CControlUI* pControl);
	bool RemoveAt(int iIndex);
	void RemoveAll();
	void DoEvent(TEventUI& event);
	Node* GetRoot();
	Node* AddNode(const IMListItemInfo& item, Node* parent = NULL, int index = 0);
	bool RemoveNode(Node* node);
	void SetChildVisible(Node* node, bool visible);
	bool CanExpand(Node* node) const;
	virtual void DoInit();
	virtual void SortChildren(Node *parent, std::function<bool(Node *&x, Node *&y)> compare);
public:
	/**@name sId��item��Ӧ���*/
	//@{
	BOOL IsExistSId(IN const int sId);
	/**
	 * ��ȡ�б���������Ŀ��SID��������Ⱥʹ��
	 *
	 * @return  std::vector<std::string>
	 * @exception there is no any exception to throw.
	 */	
	std::vector<std::string> GetAllItemsSId();
	Node* GetItemBySId(IN const int sId);
	Node* GetItemBySIdRecursion(IN const int sId, IN Node *node);
	//@}

	/**
	 * ��setһ��Item·������addnod
	 *
	 * @param   CString IitemXml
	 * @return  void
	 * @exception there is no any exception to throw.
	 */	
	//void SetIitemXmlFile(CString IitemXml);
	void SetItemNormalHeight(const int nIMListItemNormalHeight);
	Node* GetParentIdForAddNode(IN CDuiString sId);
	void ExpandAll();
   // static void SetTextUICount(IN CControlUI* pCTextUI, IN UInt32 nCount);

	/**@name MKO*/
	//@{
public:
	//void MKOForUserListModuleCallback(const std::string& keyId, MKO_TUPLE_PARAM mkoParam);
	//void MKOForTcpClientModuleCallback(const std::string& keyId, MKO_TUPLE_PARAM mkoParam);
	//@}

private:
	//void _freshAvatarBySId(std::shared_ptr<void> pParam);
	//void _updateCount(IN const UInt32 nCount,OUT CString& strContent);
	int _reArrange(Node *node, int iLastIndex);
public:
	Node*			root_node_;
	LONG			delay_deltaY_;
	DWORD			delay_number_;
	DWORD			delay_left_;
	CDuiRect		text_padding_;
	int				level_text_start_pos_;
	CDuiString		level_expand_image_;
	CDuiString		level_collapse_image_;

	CPaintManagerUI& paint_manager_;
	CDialogBuilder m_dlgBuilder;

private:
	CDuiString		m_IitemXmlFilePath;
	int			m_IMListItemNormalHeight = 60;
};
/******************************************************************************/
#endif// UIIMLIST_548A8B8B_30ED_4E85_8BB4_32FB9EC52FE6_H__
