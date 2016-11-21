/*******************************************************************************
*  @file      UIGroupsTreelist.cpp 2016-11-18 15:18:16
*  @author    �޹��<cuiguanghui@naycent.com>
*  @brief
******************************************************************************/

#include "stdafx.h"
#include "UIGroupsTreelist.h"
/******************************************************************************/

const int kGroupListFolderItemHeight = 32;
const int kGroupListNormalItemHeight = 60;

const TCHAR* const kLogoButtonControlName = _T("logo");
const TCHAR* const kLogoContainerControlName = _T("logo_container");
const TCHAR* const kNickNameControlName = _T("nickname");
const TCHAR* const kDescriptionControlName = _T("description");
const TCHAR* const kcreatGroupControlName = _T("creatGroup");
const TCHAR* const kOperatorPannelControlName = _T("operation");
const TCHAR* const lastContentTimeControlName = _T("lastContentTime");
const TCHAR* const kUnreadcntControlName = _T("unreadcnt");
const TCHAR* const kXMLFilePath = _T("groupListItem.xml");


CGroupsTreelistUI::CGroupsTreelistUI(CPaintManagerUI& paint_manager)
:UIIMList(paint_manager)
{
}

static bool OnButtonEvent(void* event) {
	if (((TEventUI*)event)->Type == UIEVENT_BUTTONDOWN) {
		CControlUI* pButton = ((TEventUI*)event)->pSender;
		if (pButton != NULL) {
			CListContainerElementUI* pListElement = (CListContainerElementUI*)(pButton->GetTag());
		}
	}
	else if (((TEventUI*)event)->Type == UIEVENT_TIMER){
		if (((TEventUI*)event)->wParam == FLASH_AVATAR_TIMER){
			CControlUI* pLogo = ((TEventUI*)event)->pSender;
			if (pLogo != NULL) {
				RECT rc = pLogo->GetPadding();
				CDuiString sPos = pLogo->GetUserData();
				if (rc.left == 1){
					if (sPos == _T("right")){
						rc.left = 0;
						rc.top = 1;
					}
					if (sPos == _T("left")){
						rc.left = 2;
						rc.top = 1;
					}
				}
				else if (rc.left == 2){
					rc.left = 1;
					rc.top = 0;
					pLogo->SetUserData(_T("right"));
				}
				else if (rc.left == 0){
					rc.left = 1;
					rc.top = 0;
					pLogo->SetUserData(_T("left"));
				}
				pLogo->SetPadding(rc);
			}
		}

	}
	return true;
}

Node* CGroupsTreelistUI::AddNode(const GroupsListItemInfo& item, Node* parent)
{
	if (!parent)
		parent = root_node_;

	TCHAR szBuf[MAX_PATH] = {0};

    CListContainerElementUI* pListElement = NULL;
	if (!UIIMList::m_dlgBuilder.GetMarkup()->IsValid()) {
		pListElement = static_cast<CListContainerElementUI*>(UIIMList::m_dlgBuilder.Create(kXMLFilePath, (UINT)0, NULL, &paint_manager_));
    }
    else {
		pListElement = static_cast<CListContainerElementUI*>(UIIMList::m_dlgBuilder.Create((UINT)0, &paint_manager_));
    }
    if (pListElement == NULL)
        return NULL;

	Node* node = new Node;
	node->data().level_ = parent->data().level_ + 1;
	if (item.folder)
		node->data().has_child_ = !item.empty;
	else
		node->data().has_child_ = false;

	node->data().folder_ = item.folder;

	node->data().child_visible_ = (node->data().level_ == 0);
	node->data().child_visible_ = false;
	node->data().sId = item.id;
	node->data().text_ = item.nickName;
	node->data().list_elment_ = pListElement;

	if (!parent->data().child_visible_)
		pListElement->SetVisible(false);

	if (parent != UIIMList::root_node_ && !parent->data().list_elment_->IsVisible())
		pListElement->SetVisible(false);

	CDuiRect rcPadding = UIIMList::text_padding_;
	for (int i = 0; i < node->data().level_; ++i)
	{
		rcPadding.left += UIIMList::level_text_start_pos_;
	}
	pListElement->SetPadding(rcPadding);

	CControlUI* log_button = static_cast<CControlUI*>(UIIMList::paint_manager_.FindSubControlByName(pListElement, kLogoButtonControlName));
	if (log_button != NULL)
	{
		if (!item.folder && !item.avatarPath.IsEmpty())
		{
			_stprintf_s(szBuf, MAX_PATH - 1, _T("%s"), item.avatarPath);
			log_button->SetBkImage(szBuf);
		}
		else
		{
			CContainerUI* logo_container = static_cast<CContainerUI*>(paint_manager_.FindSubControlByName(pListElement, kLogoContainerControlName));
			if (logo_container != NULL)
				logo_container->SetVisible(false);
		}
        log_button->SetTag((UINT_PTR)pListElement);
        log_button->OnEvent += MakeDelegate(&OnButtonEvent);
	}

	CDuiString html_text;
	if (node->data().has_child_)
	{
		if (node->data().child_visible_)
			html_text += UIIMList::level_expand_image_;
		else
			html_text += UIIMList::level_collapse_image_;

		_stprintf_s(szBuf, MAX_PATH - 1, _T("<x %d>"), level_text_start_pos_);

		html_text += szBuf;
	}

	if (item.folder)
	{
		html_text += node->data().text_;
	}
	else
	{
		_stprintf_s(szBuf, MAX_PATH - 1, _T("%s"), item.nickName);

		html_text += szBuf;
	}

	CLabelUI* nick_name = static_cast<CLabelUI*>(UIIMList::paint_manager_.FindSubControlByName(pListElement, kNickNameControlName));
	if (nick_name != NULL)
	{
		if (item.folder)
			nick_name->SetFixedWidth(0);

		nick_name->SetShowHtml(true);
		nick_name->SetText(html_text);
	}

	if (!item.folder && !item.description.IsEmpty())
	{
		CLabelUI* description = static_cast<CLabelUI*>(UIIMList::paint_manager_.FindSubControlByName(pListElement, kDescriptionControlName));
		if (description != NULL)
		{
			_stprintf_s(szBuf, MAX_PATH - 1, _T("<x 10><c #808080>%s</c>"), item.description);

			description->SetShowHtml(true);
			description->SetText(szBuf);
		}
	}

	if (item.folder)
	{
		pListElement->SetFixedHeight(kGroupListFolderItemHeight);
	}
	else
	{
		pListElement->SetFixedHeight(kGroupListNormalItemHeight);
		//pListElement->SetUserData(item.id);
	}
	pListElement->SetTag((UINT_PTR)node);
	int index = 0;
	if (parent->has_children())
	{
		Node* prev = parent->get_last_child();
		index = prev->data().list_elment_->GetIndex() + 1;
	}
	else 
	{
		if (parent == UIIMList::root_node_)
			index = 0;
		else
			index = parent->data().list_elment_->GetIndex() + 1;
	}
	if (!CListUI::AddAt(pListElement, index))
	{
		delete pListElement;
		delete node;
		node = NULL;
	}

	parent->add_child(node);

	return node;
}

Node* CGroupsTreelistUI::UpdateNode(const GroupsListItemInfo& item)
{
	return nullptr;
}
BOOL CGroupsTreelistUI::UpdateItemBySId(const std::string& sId)
{
	return TRUE;
}

void CGroupsTreelistUI::FlashAvatar(IN const int sId)
{
	Node* node = GetItemBySId(sId);
	if (node){
		CListContainerElementUI* plistElmen = node->data().list_elment_;
		CControlUI* logoBtn = static_cast<CControlUI*>(UIIMList::paint_manager_.FindSubControlByName(plistElmen, kLogoButtonControlName));
		logoBtn->SetTimer(FLASH_AVATAR_TIMER, 260);
	}
}

void CGroupsTreelistUI::StopFlashAvatar(IN const int sId)
{
	Node* node = GetItemBySId(sId);
	if (node){
		CListContainerElementUI* plistElmen = node->data().list_elment_;
		CControlUI* logoBtn = static_cast<CControlUI*>(UIIMList::paint_manager_.FindSubControlByName(plistElmen, kLogoButtonControlName));
		logoBtn->KillTimer(FLASH_AVATAR_TIMER);
		logoBtn->SetPadding({0,0,0,0});
	}
}
/******************************************************************************/