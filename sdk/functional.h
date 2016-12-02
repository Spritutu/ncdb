#pragma once
#include <Windows.h>
#include "PiTypeDef.h"
#include "define_gnl.h"
using namespace std;

#define _FUNCTIONAL_H_COMMON

#ifdef _FUNCTIONAL_H_COMMON 

//namespace ns_Functional
//{
//    const char* szDataFormat = "%04d/%02d/%02d %02d:%02d:%02d";
//}


//int �ֽ�ɴ�С���ĸ�����
double IntResolveToFloat(int Num, UNCHAR decimal);

string  GetLocalDateTime(const char* cFormat);



wstring GetCurrentDirIniName();



//��ȷ����ʱָ����ʱ��, MilliSecond
void Delay(UINT nMilliSecond);

/************************************************************************/
/*	fun: �ڴ�ԭ��ת����16���Ƶ��ַ���                                                                     
/************************************************************************/
string MemToHex(byte* pMem, UNLONG dwSize);

/************************************************************************/
/*  fun: �ڴ濽����string�� eg: char cChar[] = {'1','2'};  ->  string("12");
/************************************************************************/
void MemToString(string& strDist, void* pMem, UNINT nSize);
bool IsBigEndian();

//����N��������ڴ�, ����ÿ������ָ����ɵ�vector
template <class T>
vector<T*> NewPointArrar(T* tSize, UNLONG iCount);

/************************************************************************/
/*  fun:    �������������Ԫ��ת����ͨ������ʽ
    remark: Ԫ�ر�����ͬһ����
/************************************************************************/
template <class T>
typename T::value_type* ContainerToArray(T& container);

/************************************************************************/
/*  fun:    ����������ת��ָ���������͵�����
/************************************************************************/
template <class T, class Ctn>
void ArrayToContainer(const T& pArr, UNLONG dwCount, Ctn& container);

//�ж��ַ� �Ƿ��� 0-F ������
bool IsHex(char cSource);



//�ж��ַ���ÿ���ַ��Ƿ���16������
bool DecideInHex(const string strSource);

/************************************************************************
        fun:	���и�ʽ���ڴ��
        param:  
        ret:    
        remark: 
/************************************************************************/
template<class T>
void AdjustArrByLine(T* arr, UNINT nSize, UNINT nCountPerLine, ostringstream& oss);

template <class T>
vector<T*> NewPointArrar(T* tSize, UNLONG iCount)
{
	vector<T*> vt;
	for (UNLONG i = 0; i< iCount; ++i)
	{
		T* pNew= new T;
		vt.push_back(pNew);
	}
	return vt;
}

template <class T>
typename T::value_type* ContainerToArray(T& container)
{
    
    UNLONG dwMemSize = sizeof(T::value_type) * container.size();
    T::value_type* pMem = new T::value_type[container.size()];
    memset(pMem, 0, dwMemSize);
    T::value_type* pMemTemp = pMem;
    for (T::iterator it = container.begin(); it != container.end(); ++it)
    {
        *pMemTemp++ = *it;
    }
    return pMem;
}

template <class T, class Ctn>
void ArrayToContainer(T& pArr, UNLONG dwCount, Ctn& container)
{
    //vector<int> lInt;
    //typedef vector<int> CN_Type;

    for(UNLONG i = 0; i < dwCount; ++i)
    {
        container.push_back(*(pArr++));
    }
    
}


template<class T>
void AdjustArrByLine(T* arr, UNINT nSize, UNINT nCountPerLine, ostringstream& oss)
{
	UNINT nCount = 0;
	for (UNINT i = 0; i < nSize; ++i )
	{
		oss << (int)arr[i] << " ";
		
		if ((i + 1) % nCountPerLine  == 0) 
		{
			oss<<"\r\n";
		}
	}
}


/************************************************************************
    fun:	ɾ��ָ������������Ԫ�ر����ָ��
    param:  
    ret:    none
    remark: 
/************************************************************************/
template<class T>
void ClearElemPtr(T& ctn)
{
    //list ctn;
    //list::iterator it2;
    for (T::iterator it = ctn.begin(); it != ctn.end(); ++it)
    {
        ClearMem((*it));
    }
}


/************************************************************************
    fun:    ��ȡģ��exe��
    param: 
    remark: 
************************************************************************/
tstring GetSelfModuleName();
tstring GetSelfModuleTitle();

void* GetFileData( tcpchar szfilePath );
tstring GetFileDataStr( tcpchar szfilePath, bool bUtf8 = false);

/**************************************** PA���� ****************************************/







#endif

/************************************************************************
        fun:	�������������HANDLEת��������ʽ
        param:  
        ret:    
        remark: 
/************************************************************************/

template<class Container, typename TypeNew>
 TypeNew* HandleToArr(Container& ctn);


template<class Container, typename TypeNew>
TypeNew* HandleToArr(Container& ctn)
{
	Container::iterator it = ctn.begin();

	size_t nSize = ctn.size();
	TypeNew* pElemArr = new TypeNew[nSize];
	for (size_t i = 0; i < nSize; ++i)
	{
		pElemArr[i] = *it;
		advance(it, 1);
	}
	return pElemArr;
}

template<class Cn>
tcpchar* CtStrToArr(Cn& ctn)
{
    Cn::iterator it = ctn.begin();

    size_t nSize = ctn.size();
    tcpchar* pElemArr = new tcpchar[nSize];
    for (size_t i = 0; i < nSize; ++i)
    {
        pElemArr[i] = it->c_str();
        advance(it, 1);
    }
    return pElemArr;
}

/************************************************************************
        fun: ��ȡϵͳtemp��ʱĿ¼
        param: 
        remark: 
************************************************************************/
tstring GetSysTempFolder();



/***************************����, �߳�, �ļ���ϵͳ�ں����**********************************/

/************************************************************************
        fun:    �ж�ָ���������Ƿ����
        param: 
        remark: 
************************************************************************/
bool IsProcessExist( tcpchar szProcessName);


typedef bool (*EnumerateFunc) (tcpchar lpFileOrPath, void* pUserData );
/************************************************************************
        fun: 
        param: ����3:bool, true->�����ļ�, false-> ����Ŀ¼
        remark: 
    ************************************************************************/
bool FileEnumeration(tcpchar lpPath, bool bRecursion, bool bEnumFiles, EnumerateFunc pFunc, void* pUserData);
bool FileEnumeration(tcpchar lpPath, bool bRecursion, bool bEnumFiles, LST_STRING& lstFile);
bool CB_EnumerateFunc(tcpchar lpFileOrPath, void* pUserData );



//tstring GetFileNameFromPath(tcpchar szPath);



TimeType GetFileTimeModify(tcpchar szPath);

void OutInfo(tcpchar sz1);
void OutInfo(tcpchar sz1, tcpchar sz2);
void OutInfo(tcpchar sz1, StringCRef sz2);
void OutInfo(tcpchar sz1, __int64 nValue);

bool DecodeUrl( tstring& strTime );

tstring MakeGUID();

/*------------------------------------------------------------
		fun:	���ݷָ���, ��ȡ��ÿ���ַ��������б�
		ret:	
		param: 
		remark:	
------------------------------------------------------------*/
//ARR_STRING SpilitStrToArray(const tstring& strSrc, tcpchar szSpilit);
//LST_STRING SpilitStr(const tstring& strSrc, tcpchar szSpilit);
//PAIR_STRING SpilitStrTwoPart(const tstring& strSrc, tcpchar szSpilit);
//MAP_STRING SpilitStrMap(const tstring& strSrc, tcpchar szSpilit);

/*���ݷָ���, ���б��е�ÿ���ַ����ֳ�����������, ����map
	abc=4      =>        map["abc"]=4
	cf=5       =>		map["cf"]=5
*/
//MAP_STRING SpilitStrMap( const LST_STRING& lstSrc, tcpchar szSpilit );
//ARR_PAIR_STR SpilitStrToPairArray( const LST_STRING& lstSrc, tcpchar szSpilit );



POINT Client2Screen(HWND hwnd, long nlParam);
//POINT Client2Screen(HWND hwnd, CPoint nlParam);

template <class Container> 
bool MakeSequenceString(Container& ctn, tcpchar szFormat, int nBegin, int nEnd);

template <class Container>
bool MakeSequenceString( Container& ctn, tcpchar szFormat, int nBegin, int nEnd )
{
	if (nBegin < 0 || nEnd < 0)
	{
		return false;
	}
	ctn.clear();

	STLString strFm;
	FOR_COUNT( nEnd - nBegin + 1, i)
	{
		strFm.Format(szFormat, i + nBegin);
		ctn.push_back(strFm.c_str());
	}
	
	return true;
}

/************************************************************************
        fun:    ����������ָ���ľ���rtBig��Χ����
        param: ����3 ptSpacing, �����ⲿ���εı߿����
        remark: 
************************************************************************/
bool MoveInRect(const RECT& rtBig, RECT& rtSrc, const POINT& ptSpacing );