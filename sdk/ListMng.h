#pragma once
#include "define_gnl.h"
#include "PiTypeDef.h"
#include "ResCommon.h"
#include "Lock.h"
#include "RAIILock.h"
template<typename TypeElem, typename TypeElemCn>
class CListMng
{
public:
	CListMng(void);
	CListMng(const CListMng& lm) ;
    CListMng<TypeElem, TypeElemCn>& operator =(const CListMng<TypeElem, TypeElemCn>& lm) ;
    virtual ~CListMng(void);
public:
	bool Add(TypeElem* pElem);
    bool AddFront(TypeElem* pElem);
    bool Delete(TypeElem* pElem);
    bool Clear();
    TypeElem* First();
    /************************************************************************
        fun:    ��ȡ�б��е���һ��Ԫ��
        param: 
        remark: �����ǰλ��Ϊ��ʼλ��, ���ص�һ��Ԫ��.   ��ǰλ����ĩβ, ����NULL
    ************************************************************************/
    TypeElem* Next();
    /************************************************************************
        fun:    �����ڽӿ�Next(), �����������ǰԪ����ĩβʱ, �᷵�ص���һ��Ԫ�ض�����NULL
        param: 
        remark: 
    ************************************************************************/
    TypeElem* NextCycle();

    /************************************************************************
        fun:    �����б��е���һ��Ԫ�ص�ָ��
        param: 
        remark: �����ǰλ��Ϊ��ʼλ��, �������һ��Ԫ��. ��ͷ�� -> NULL
    ************************************************************************/
    TypeElem* Previous();

    /************************************************************************
        fun:    �����ڽӿ�Previous(), ������
        param: 
        remark: �����ǰλ��Ϊͷ���򷵻�NULL,  ��ʼλ�÷������һ��Ԫ��
    ************************************************************************/
    TypeElem* PreviousCycle();
    TypeElem* Last();
    /************************************************************************
        fun:    ���ڲ�Ԫ��λ�ûص�ͷ����ʼ��λ��
        param: 
        remark: 
    ************************************************************************/
    bool ResetPos();
    bool SetPos(TypeElem* pElem);
    UNLONG      Count();
    bool SetData(const TypeElemCn& cn);
    TypeElemCn& GetList();
protected:
    TypeElemCn        m_lstElem;
	typename TypeElemCn::iterator*      m_pitElemCur;
	CLock							m_lockLstElem;
    //typename TypeElemCn::iterator&      m_itElemCur;
};

template<typename TypeElem, typename TypeElemCn>
CListMng<TypeElem, TypeElemCn>::CListMng(void)
	:m_pitElemCur(new TypeElemCn::iterator)
{
    ResetPos();
}


template<typename TypeElem, typename TypeElemCn>
CListMng<TypeElem, TypeElemCn>::CListMng( const CListMng& lm )
	:m_lstElem(lm.m_lstElem)
	,m_pitElemCur(new TypeElemCn::iterator)
{
	ResetPos();
	
}

template<typename TypeElem, typename TypeElemCn>
CListMng<TypeElem, TypeElemCn>::~CListMng(void)
{
    Clear();
}

template<typename TypeElem, typename TypeElemCn>
CListMng<TypeElem, TypeElemCn>& CListMng<TypeElem, TypeElemCn>::operator=( const CListMng<TypeElem, TypeElemCn>& lm ) 
{
	//*thislm;
	this->m_pitElemCur = new TypeElem TypeElemCn::iterator(lm.m_pitElemCur);
	return *this;
}

template<typename TypeElem, typename TypeElemCn>
bool CListMng<TypeElem, TypeElemCn>::AddFront( TypeElem* pElem )
{
	CRAIILock raii(m_lockLstElem.Lock());
	m_lstElem.push_front(pElem);
	return true;	
}

template<typename TypeElem, typename TypeElemCn>
bool CListMng<TypeElem, TypeElemCn>::Add( TypeElem* pElem )
{
	CRAIILock raii(m_lockLstElem.Lock());
    m_lstElem.push_back(pElem);
    return true;
}

template<typename TypeElem, typename TypeElemCn>
bool CListMng<TypeElem, TypeElemCn>::SetPos( TypeElem* pElem )
{
    FOR_EACH_ITER(TypeElemCn, m_lstElem, it)
    {
        if (*it == pElem)
        {
            m_itElemCur = it;
            break;
        }
    }
    return true;
}

template<typename TypeElem, typename TypeElemCn>
TypeElem* CListMng<TypeElem, TypeElemCn>::PreviousCycle()
{
    
    TypeElem* pElem = this->Previous();
    if (! pElem && this->Count())
    {
        pElem = this->Previous();
    }

    return pElem;
}

template<typename TypeElem, typename TypeElemCn>
TypeElem* CListMng<TypeElem, TypeElemCn>::NextCycle()
{
    TypeElem* pElem = this->Next();
    if (! pElem && this->Count())
    {
        pElem = this->Next();
    }

    return pElem;
}

template<typename TypeElem, typename TypeElemCn>
bool CListMng<TypeElem, TypeElemCn>::ResetPos()
{
	TypeElemCn::iterator&      m_itElemCur = *m_pitElemCur;
    m_itElemCur = m_lstElem.end();
    return true;
}

template<typename TypeElem, typename TypeElemCn>
bool CListMng<TypeElem, TypeElemCn>::Clear()
{
	CRAIILock raii(m_lockLstElem.Lock());
    FOR_EACH_ITER(TypeElemCn, m_lstElem, it)
    {
        delete *it;
    }
	ClearMem(m_pitElemCur);
    m_lstElem.clear();
    return true;
}

template<typename TypeElem, typename TypeElemCn>
UNLONG CListMng<TypeElem, TypeElemCn>::Count()
{
	CRAIILock raii(m_lockLstElem.Lock());
    return m_lstElem.size();
}

template<typename TypeElem, typename TypeElemCn>
bool CListMng<TypeElem, TypeElemCn>::SetData( const TypeElemCn& cn )
{
    m_lstElem = cn;
    return true;
}

template<typename TypeElem, typename TypeElemCn>
TypeElem* CListMng<TypeElem, TypeElemCn>::Last()
{
	CRAIILock raii(m_lockLstElem.Lock());
	TypeElemCn::iterator&      m_itElemCur = *m_pitElemCur;
    TypeElem* pElem = NULL; //TODO:�����ָ��Ĭ�Ϲ������ֵΪ0
    m_itElemCur = m_lstElem.end();
    if (m_lstElem.size())
    {
        --m_itElemCur;//����ǿ�����, ���ܽ��иò���
    }
    
    if(IsValidIter(m_itElemCur, m_lstElem))
    {
        pElem = *m_itElemCur;
    }

    return pElem;
}

template<typename TypeElem, typename TypeElemCn>
bool CListMng<TypeElem, TypeElemCn>::Delete( TypeElem* pElem )
{
	CRAIILock raii(m_lockLstElem.Lock());
	TypeElemCn::iterator&      m_itElemCur = *m_pitElemCur;
    FOR_EACH_ITER(TypeElemCn, m_lstElem, it)
    {
        if (*it == pElem)
        {
            it = m_itElemCur = m_lstElem.erase(it);
			ClearMem(pElem);
            break;
        }
    }
    return true;
}

template<typename TypeElem, typename TypeElemCn>
TypeElemCn& CListMng<TypeElem, TypeElemCn>::GetList()
{
    return m_lstElem;
}

template<typename TypeElem, typename TypeElemCn>
TypeElem* CListMng<TypeElem, TypeElemCn>::Previous()
{
	CRAIILock raii(m_lockLstElem.Lock());
	TypeElemCn::iterator&      m_itElemCur = *m_pitElemCur;
    TypeElem* pElem = NULL; //TODO:�����ָ��Ĭ�Ϲ������ֵΪ0
    if (!IsValidIter(m_itElemCur, m_lstElem) 
        )
    {
        Last();
    }
    else if (m_itElemCur == m_lstElem.begin())
    {
        ResetPos();
    }
    else
    {
        --m_itElemCur;
    }
    if(IsValidIter(m_itElemCur, m_lstElem))
    {
        pElem = *m_itElemCur;
    }
    return pElem;
}

template<typename TypeElem, typename TypeElemCn>
TypeElem* CListMng<TypeElem, TypeElemCn>::Next()
{
	CRAIILock raii(m_lockLstElem.Lock());
	TypeElemCn::iterator&      m_itElemCur = *m_pitElemCur;
    TypeElem* pElem = NULL; //TODO:�����ָ��Ĭ�Ϲ������ֵΪ0
    if (!IsValidIter(m_itElemCur, m_lstElem))
    {
        m_itElemCur = m_lstElem.begin();
    }
    else
    {
        ++m_itElemCur;
    }

    if(IsValidIter(m_itElemCur, m_lstElem))
    {
        pElem = *m_itElemCur;
    }
    
    return pElem;

}

template<typename TypeElem, typename TypeElemCn>
TypeElem* CListMng<TypeElem, TypeElemCn>::First()
{
	CRAIILock raii(m_lockLstElem.Lock());
	TypeElemCn::iterator&      m_itElemCur = *m_pitElemCur;
    TypeElem* pElem = NULL; //TODO:�����ָ��Ĭ�Ϲ������ֵΪ0
    m_itElemCur = m_lstElem.begin();
    if(IsValidIter(m_itElemCur, m_lstElem))
    {
        pElem = *m_itElemCur;
    }

    return pElem;
}

