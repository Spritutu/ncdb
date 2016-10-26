#pragma once
#include "tTypeDef.h"
#include <tchar.h>
#include <string>
#include <list>
using namespace std;

struct ResAttribute
{
    tstring strAtbName;     //������
    tstring strAtbValue;    //����ֵ
};

struct ResNode
{
    typedef list<ResAttribute*> LST_ATTR;
    typedef list<ResNode*>      LST_NODE;

    tstring strNodeName;    //�ڵ���
    bool bChildAttribute;    /* �Ƿ��Ǹ��ڵ��������, �� 
        kImageID(reT=image) */
    LST_ATTR  lstAttribute;   //�ڵ����������
    LST_NODE   lstChildNode;//�ӽڵ�
    ResNode*        pParent;    //��ѡ, ���ڵ�ָ��
    ResNode()
    {
        pParent = NULL;
        bChildAttribute = false;
    }
    ~ResNode()
    {
        for (LST_ATTR::iterator it = lstAttribute.begin(); it != lstAttribute.end(); 
            ++it)
        {
            delete *it;
        }
        for (LST_NODE::iterator it = lstChildNode.begin(); it != lstChildNode.end(); 
            ++it)
        {
            delete *it;
        }
    }
};

class CDataAssist
{
public:
    CDataAssist(void);
    ~CDataAssist(void);
public:

    bool Init();
    /************************************************************************
		����һ���µĽڵ�, ����һ��nNew, ֮�����в���������µ�һ��nNew
	/************************************************************************/
    void AddNote(TCHAR* szName);

    /************************************************************************
		fun:��ӽڵ㱾�������
	/************************************************************************/
    void AddAttributeSelf(TCHAR* szAtbName, TCHAR* szValue);

    /************************************************************************
		function��	��ӵ�ǰ�ڵ��������,��Ƕ�����������
		remark:		���⿴�ɽڵ�, ��bChildAttribute Ϊtrue;   
                ���ո�ʽ: ����Ҳ���ɽڵ�, ���ӽڵ�����������һ��
	/************************************************************************/
    void AddAttributeChild(TCHAR* szAtbName, TCHAR* szValue);


    /************************************************************************
		fun:�����ϼ��ڵ���pParent, ֮�����в���������µ�һ��pParent
        remark: �Ӵ�����{ }���浯������һ��
	/************************************************************************/
    void PopLayer();
    /************************************************************************
		���浽���յ����ݽṹ��
	/************************************************************************/
    bool SaveToDist();
    /************************************************************************
		function��	������нڵ������, �ͷ��ڴ�
		remark:		
	/************************************************************************/
    void ClearAllData();
    void UnInit();
    ResNode*        m_pNodeRoot;
    ResNode*        m_pResNodeCur;     //������������Ľڵ�
};

