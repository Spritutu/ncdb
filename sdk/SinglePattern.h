#pragma once
#include <Windows.h>
template <class T>
class CSinglePattern
{
public:
	virtual ~CSinglePattern(void);
private:
	CSinglePattern(void);
	
public:
	//�����µĶ���,����֮ǰ�Ķ���
	
	//T* SetObj(T* pNewObj);
	static T*       GetObj();
    static  void    DeleteObj();

	void    Init();
	void    UnInit();
    
public:
	
	
private:
    CRITICAL_SECTION	m_cs; //�������ṩ�̱߳���
    static T*	m_UniqueObj;
};

template<class T>
T* CSinglePattern<T>::m_UniqueObj = 0;




template <class T>
CSinglePattern<T>::CSinglePattern(void)
{
	m_UniqueObj = NULL;

	memset(&m_cs, 0, sizeof(CRITICAL_SECTION));
}

template <class T>
CSinglePattern<T>::~CSinglePattern(void)
{
	if (m_UniqueObj)
	{
		delete m_UniqueObj;
		m_UniqueObj = NULL;
	}
}


template <class T>
T* CSinglePattern<T>::GetObj()
{
	
	//���߳��е�������ʼ��, �����߳̾Ͳ���new����, ��Ϊû���̱߳���
	//�̼߳���
	//....
	if(!m_UniqueObj)
	{
		m_UniqueObj = new T;
		m_UniqueObj->Init();
	}
	//����
	return m_UniqueObj;
}

template <class T>
void CSinglePattern<T>::DeleteObj()
{
    if(m_UniqueObj)
    {
        delete m_UniqueObj;
    }
}

template <class T>
void CSinglePattern<T>::Init()
{

}
