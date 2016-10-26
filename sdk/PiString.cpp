#include "StdAfx.h"
#include "PiString.h"

Pi_NameSpace_Using
using namespace std;

#define CompareNoCase(str1, str2) (_tcsicmp(str1, str2) == 0)

CPiString::~CPiString(void)
{
}

LST_STRING ns_PiPi::CPiString::SpilitStr( const tstring& strSrc, tcpchar szSpilit )
{
    LST_STRING lstStr;
    if (strSrc.empty())
    {
        return lstStr;
    }

    size_t nPosBegin = 0;
    size_t nPos = strSrc.find(szSpilit);
    size_t nCount = -1;
    while(IsValidStrPos(nPos))
    {
        lstStr.push_back(strSrc.substr(nPosBegin, nPos - nPosBegin));
        nPosBegin = NextPos(nPos);
        nPos = strSrc.find(szSpilit, nPosBegin);
    }
    lstStr.push_back(strSrc.substr(nPosBegin, nPos));
    return lstStr;
}

ARR_STRING ns_PiPi::CPiString::SpilitStrToArray( const tstring& strSrc, tcpchar szSpilit, tcpchar szPack /*= NULL*/ )
{
	ARR_STRING lstStr;
    if (strSrc.empty())
    {
        return lstStr;
    }
	//_T("a \"344 55\" s"),  _T("\"344 55\" s"), _T( "\"344 55\""), _T("\"344 55\""), _T("a \"34 4 55\" s")

	//1. �����ָ���֮��������, ���β��ʶΪ��һ�����ź���ķָ���, l1
	//2. ��һ�������ڵ�һ���ָ���֮ǰ, ��endPosΪ�ڶ����ָ���
	//3. 

    size_t nCutPosBegin = 0;
    size_t nCutPosEnd = strSrc.find(szSpilit);
    size_t nCount = -1;
	size_t nPack = 0;
    while(IsValidStrPos(nCutPosEnd))
    {
		if (szPack)
		{
			nPack = strSrc.find(szPack);
			if(nPack >= nCutPosBegin
				&& nPack < nCutPosEnd)
			{
				nPack = strSrc.find(szPack, NextPos(nPack));
				nCutPosEnd = strSrc.find(szSpilit, NextPos(nPack));
				if (!IsValidStrPos(nCutPosEnd))
				{
					break;
				}
			}
		}
		
        lstStr.push_back(strSrc.substr(nCutPosBegin, nCutPosEnd - nCutPosBegin));
        nCutPosBegin = NextPos(nCutPosEnd);
        nCutPosEnd = strSrc.find(szSpilit, nCutPosBegin);
    }
    lstStr.push_back(strSrc.substr(nCutPosBegin, nCutPosEnd));
    /*if(!IsValidStrPos(nPos))
    strSrc*/
    return lstStr;
}

MAP_STRING ns_PiPi::CPiString::SpilitStrMap( const LST_STRING& lstSrc, tcpchar szSpilit )
{
    MAP_STRING mStr;
    FOR_EACH_ITER_CONST(LST_STRING, lstSrc, it)
    {
        //���ݷָ���, �ֳ�����������
        size_t nPos = it->find(szSpilit);
        
        mStr.insert( make_pair(it->substr(0, nPos), it->substr(NextPos(nPos))) );
        //it->substr(NextPos(nPos));
    }
    return mStr;
}

ARR_PAIR_STR ns_PiPi::CPiString::SpilitStrToPairArray( const LST_STRING& lstSrc, tcpchar szSpilit )
{
	ARR_PAIR_STR mStr;
	FOR_EACH_ITER_CONST(LST_STRING, lstSrc, it)
	{
		//���ݷָ���, �ֳ�����������
		size_t nPos = it->find(szSpilit);

		mStr.push_back( make_pair(it->substr(0, nPos), it->substr(NextPos(nPos))) );
	}
	return mStr;
}




bool CPiString::IsAllNum( tcpchar szStr )
{
	int nLen = _tcslen(szStr);
	bool bNum = true;
	for (;*szStr;)
	{
		if ( !isdigit( *szStr++ ))
		{
			bNum = false;
			break;
		}
	}
	return bNum;
}

void CPiString::TermStrRight( tstring& strSrc , tcpchar szFind /*= _T(" ")*/)
{
	tstring strTemp(strSrc);
	reverse(strTemp.begin(), strTemp.end());
	TermStrLeft(strTemp, szFind);
	reverse(strTemp.begin(), strTemp.end());
    /*size_t nPosBegin = strTemp.find_first_not_of(szFind);	//���һ���ո��λ��
	if (! IsValidStrPos(nPosBegin))
	{
		return ;
	}*/
    //strSrc = strSrc.substr(0, strSrc.length() - nPosBegin);
	strSrc = strTemp;

}

void CPiString::TermStrLeft( tstring& strSrc , tcpchar szFind /*= _T(" ")*/)
{
	//src����ҵ�һ������szFind����ַ���λ��, pos, pos��ߵ��е�
	tstring strFind(szFind);
	size_t nPosBegin = 0;
	FOR_COUNT(strSrc.size(), i)
	{
		if(!IsValidStrPos(strFind.find(strSrc.at(i))))
		{
			nPosBegin = i;
			break;
		}
	}
	if (! IsValidStrPos(nPosBegin))
	{
		return ;
	}
	strSrc = strSrc.substr(nPosBegin);
}

void CPiString::TermStr( tstring& strSrc , tcpchar szFind /*= _T(" ")*/)
{
	TermStrLeft(strSrc, szFind);
	TermStrRight(strSrc, szFind);
}
tstring CPiString::GetStrRight(UNINT nCount )
{

	size_t nLength = size();
	return substr(nLength - nCount);
}

tstring ns_PiPi::CPiString::Left( UNINT nCount )
{
	return substr(0, nCount);
}

tstring ns_PiPi::CPiString::Left( tcpchar szChar )
{
	return substr(0, find(szChar));
}

bool ns_PiPi::CPiString::Exist( LPCTSTR szFind )
{
	return find(szFind) != tstring::npos;
}

ns_PiPi::CPiString::operator tcpchar()
{
	return c_str();
}

ns_PiPi::CPiString::CPiString( tcpchar szData )
:PiStringClassType(szData)
{

}

ns_PiPi::CPiString::CPiString()
{

}

ns_PiPi::CPiString::CPiString( const tstring& szData )
:PiStringClassType(szData)
{

}

CPiString& ns_PiPi::CPiString::ToLower()
{
	if(empty())
	{
		return *this;
	}
	DWORD dwRet = CharLowerBuff(const_cast<tpchar>(c_str()), length());
	return *this;
}

bool ns_PiPi::CPiString::EqualNoCase( tcpchar szStr )
{
	return CompareNoCase(c_str(), szStr);
}

CPiString& ns_PiPi::CPiString::ToUpper()
{
	if(empty())
	{
		return *this;
	}
	DWORD dwRet = CharUpperBuff(const_cast<tpchar>(c_str()), length());
	return *this;
}

CPiString ns_PiPi::CPiString::operator+(tcpchar szData)
{
	return CPiString(::operator +(*this, szData));
}

PAIR_STRING ns_PiPi::CPiString::SpilitStrTwoPart( const tstring& strSrc, tcpchar szSpilit )
{
	PAIR_STRING pairS;
	if (strSrc.empty())
	{
		return pairS;
	}

	size_t nPosBegin = 0;
	size_t nPos = strSrc.find(szSpilit);
	size_t nCount = -1;
	if(IsValidStrPos(nPos))
	{
		pairS.first = strSrc.substr(nPosBegin, nPos - nPosBegin);
		nPosBegin = NextPos(nPos);
	}
	pairS.second = strSrc.substr(nPosBegin);
	return pairS;
}

void CPiString::Format(const TCHAR* format,...)
{
	TCHAR *buff = (TCHAR*)0;
	va_list arglist;
	va_start(arglist, format);
	int len = _vsctprintf(format,arglist) + 1;
	buff = (TCHAR*)malloc(len * sizeof(TCHAR));
	if(buff) {
		memset(buff,0,len * sizeof(TCHAR));
		_vstprintf_s(buff,len,format,arglist);
		assign(buff);
		free(buff);
	} 
	va_end(arglist);
}


int CPiString::ToInt()
{
	return (int)_ttoi64(c_str());

}
