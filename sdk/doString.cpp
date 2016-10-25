#include "stdafx.h"

/*************
*
*���� Abel(������)
*���� һЩ�ַ����Ĳ����� ���ң��滻������
*************/
#include <Windows.h>
#include "doString.h"
#include <comutil.h>
#include "PiTypeDef.h"
#include "define_gnl.h"
#include <algorithm>
using std::string;
#pragma comment(lib, "comsuppw.lib") //_bstr_t ��Ҫ�Ŀ��ļ�
int GetContentBetweenChar(const tstring& strSource,
                          tstring & strDest, 
                          tcpchar c,
						  const UINT cTimes /*= 1*/,
                          UINT pos /*= 0*/ )
{
	//int pos(0);
	size_t charLen = _tcslen(c);
	size_t end(0);
	//string strPHtype;
	string     strTemp;
	const int nNPos = cTimes ;//�ڼ���������������
    byte bySymbleHoldLen = cTimes > 0 ? charLen : 0;
    if (cTimes > 0)
    {
        pos = strSource.find(c ,pos);
        if(pos == string::npos)
        {
            return pos ;
        }
        for (int i = 2;i <= nNPos;i++)
        {
            pos = strSource.find(c ,NextPos(pos));
            if(pos == string::npos)
            {
                return pos ;
            }

        }
    }
	
	end = strSource.find(c ,NextPos(pos + charLen));

	//wstring wTemp;
	//û�ҵ��ұߵ� �����ַ���˵��ʣ���ұߵľ�������
	if(end ==  string::npos)
	{
		if(pos == strSource.length() - 1)//Ҫ���ҵ��ַ��������ַ�,˵���ұ�û��������
		{
			strDest = _T("");
		}
		else
		{
			strDest = strSource.substr(pos + bySymbleHoldLen,string::npos);
		}
	}
	else
	{
		strDest = strSource.substr(pos + bySymbleHoldLen,end - pos - bySymbleHoldLen);
	}
	
    if (0 == cTimes)
    {
        return end;
    }
	return end;
}

//��ȡ���� ��ͬ�ַ� �м���ַ���
int GetContentBetweenTwoChar(const tstring& strSource, 
                             tstring & strDest, 
                             tcpchar c1,
                             tcpchar c2 /*= 1*/,
                             const UINT cTimes1,
                             UINT pos /*= 0*/)
{
	int c1Len = _tcslen(c1);//�ü��ַ���ʱ�������ϲ����ַ��ĳ���
	int c2Len = _tcslen(c2);
	
	int end(-1);
	//string strPHtype;
	string     strTemp;
	const int nNPos = cTimes1 ;//�ڼ���������������

	pos = strSource.find(c1 ,pos);
	if (pos ==  string::npos )
	{
		return end;
	}

	for (int i = 2;i <= cTimes1;i++)
	{
		pos = strSource.find(c1 ,pos + 1);

	}
	
	end = strSource.find(c2, NextPos(pos + c1Len));
	

	//wstring wTemp;
	//û�ҵ��ұߵ� c2�ַ�������һ����ַ�
	if(end ==  string::npos )
	{
        end = strSource.find(_T("\r\n"),pos+1);
		if (end == string::npos)
		{
		
			if(pos == strSource.length() - 1)//Ҫ���ҵ��ַ��������ַ�,˵���ұ�û��������
			{
				strDest = _T("");
			}
			else//�������һ���ַ�,���ʣ�µĶ��ó���
			{
				strDest = strSource.substr(pos + c1Len,string::npos);
				
			}
		}
	}
	else //���ҵ��ұߵ�c2�ַ�
	{
		strDest = strSource.substr(pos + c1Len,end - pos - c1Len);
	}
	return end; //���ط���������c2��λ��
}


bool StrReplace(tstring& strSource,tcpchar c,tcpchar c2  /*= ""*/, int nCount/* = -1*/)
{
    //-1,����, 0, ����, >0 , ָ������
	bool bReplase = false;
    if (nCount == 0)
    {
        return bReplase;
    }
	int pos = -1;
	bool bCount = nCount >0;
	while(1)
	{
        if (nCount > 0)
        {
            --nCount;
        }
        else if(bCount)
        {
            break;
        }

		pos = strSource.find(c, pos + _tcslen(c2));
		if (pos == string::npos)
		{
			break;
		}
		strSource.replace(pos, _tcslen(c), c2, _tcslen(c2));
        ++bReplase;
	}
	return bReplase;
}

/*
bool StrReplace( wstring& strSource,PCSTR c,PCSTR c2 / *= ""* / )
{
    string strTemp(ws2s(strSource.c_str()));
    bool bRet = StrReplace(strTemp, c, c2);
    strSource = s2ws(strTemp.c_str());
    return bRet;
}
*/

bool StrReplaceFirst( tstring& strSource, tcpchar cFind, tcpchar cDist /*= _T("")*/ )
{
    int pos=0;

    pos = strSource.find(cFind,0);
    if (pos == string::npos)
    {
        return false;
    }
    strSource.replace(pos,_tcslen(cFind),cDist,_tcslen(cDist));
    return true;
}

int GetCharPos(const tstring strSource,tcpchar c,const UINT cTimes /*= 1*/, int nOffset /*= 0*/)
{
	int end(0);
	int pos = nOffset;
	//int strLen = strlen(c); //�ַ�����

	const int nNPos = cTimes ;//�ڼ���������������

	pos = strSource.find(c ,pos);
	for (int i = 2;i <= nNPos && pos != string::npos;i++)
	{
		pos = strSource.find(c ,pos + 1);

	}

	//end = strSource.find(c ,pos + 1);
	return pos;
}

DWORD GetCharHaveCount( const tstring &strSource, tcpchar pCh )
{
	DWORD nCount = 0;
	DWORD pos = 0;
	pos = strSource.find(pCh,pos);
	while(pos != string::npos)
	{
		pos = strSource.find(pCh,pos+1);
		++nCount;

	}
	return nCount;
}


string ws2s(const wstring& ws)
{
	_bstr_t t = ws.c_str();
	char* pchar = (char*)t;
	string result = pchar;
	return result;
}

string ws2s(const wchar_t* ws)
{
	_bstr_t t = ws;
	string result = (char*)t;
	return result;
}

wstring s2ws(const string& s)
{
	_bstr_t t = s.c_str();
	wchar_t* pwchar = (wchar_t*)t;
	wstring result = pwchar;
	return result;
}

wstring s2ws(const char* s)
{
	_bstr_t t = s;
	wstring result  = (wchar_t*)t;
	return result;
}

bool StrReplaceRange( tstring& strSource,tcpchar nFlagLeft, tcpchar nFlagRight,tcpchar cDist /*= _T("")*/, int nCount /*= -1*/ )
{
	if (strSource.empty() || nCount == 0)
	{
		return false;
	}

	//�������λ��
	int nPosLeft = 0;
	int nPosRight = 0;
	//�����ұ�λ��
	int nCountLeft = nCount;
	bool bCount = !(nCountLeft == -1);
	while(1)
	{
		nPosLeft = strSource.find(nFlagLeft, nPosLeft);
		if (!IsValidStrPos(nPosLeft))
		{
			break;
		}
		nPosRight = strSource.find(nFlagRight, NextPos(nPosLeft));
		if (!IsValidStrPos(nPosRight))
		{
			break;
		}

		strSource.replace(nPosLeft, nPosRight - nPosLeft + 1/*�ұ߱�ʶҲ��Ϊ�滻ԭ*/, cDist);
		nPosLeft = NextPos(nPosRight);
		if (bCount && --nCountLeft <= 0)
		{
			break;
		}
	}
	return true;
}

#define IsDigit(num) ((num) >= '0' && (num) <= '9' )
bool Pred_Not_Digit(tchar cChar)
{
	return !(IsDigit(cChar) 
		|| cChar == '.'
		);
}
bool EraseNoDigit( tstring& szStrR )
{
	szStrR.assign(szStrR.begin(), remove_if(szStrR.begin(), szStrR.end(), Pred_Not_Digit));
	return true;
}

bool IsStrExist( const tstring str1, tstring& str2 )
{
	return str1.find(str2) != tstring::npos;
}

bool IsStrExist( const tstring str1, tcpchar str2 )
{
	return str1.find(str2) != tstring::npos;
}
