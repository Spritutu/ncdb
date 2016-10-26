/***********************************************************************
 Copyright (c), 2012, Unicorn Tech. Co., Ltd.

 File name   : k_STLString.cpp
 Description : ����STL��չΪ֧��ANSI��Unicode�����ַ������������룬
               ��֧��Format����ת����
 Other       : 
 Version     : 2.0
 Author      : 
 Date        : 2014/06/13
 -----------------------------------------------------------------------
 History 1 
      Date   : 2014/06/13
      Author : 
      Modification : ֧���ַ���������ת����ʵ����

 History 2 
      Date   : 2014/06/16
      Author : 
      Modification : ���ToAnscii��ToUnicode��
***********************************************************************/

#include "stdafx.h"
#include "k_STLString.h"
#include <stdarg.h>

// --------------------------------------------------------------------------
// Function : Format
// Thinking : ��ȡ����������Ϻ����ַ�����������Ӧ��memory�������д������ؼ����ͷ���ʱmemory
// --------------------------------------------------------------------------
void STLString::Format(const TCHAR* format,...)
{
  TCHAR *buff = (TCHAR*)0;
  va_list arglist;
  va_start(arglist, format);
  int len = _vsctprintf(format,arglist) + 1;
  buff = (TCHAR*)malloc(len * sizeof(TCHAR));
  if(buff) {
    memset(buff,0,len * sizeof(TCHAR));
    _vstprintf_s(buff,len,format,arglist);
	//_vstprintf(buff,format,arglist);
    assign(buff);
    free(buff);
  } 
  va_end(arglist);
}
// --------------------------------------------------------------------------
// Function : MakeLower
// Thinking : ת����Сд
// --------------------------------------------------------------------------
STLString STLString::MakeLower()
{
  if( 0 == this->length() ) return *this;
  DWORD len = (DWORD)size() + 1;
  TCHAR* buff = new TCHAR[ len ];
  memset(buff,0,sizeof(TCHAR) * len);
  _tcscpy(buff,c_str());
  CharLowerBuff(buff,len);
  clear();
  assign(buff);
  delete [] buff;
  return *this;
}
// --------------------------------------------------------------------------
// Function : MakeUpper
// Thinking : ת���ɴ�д
// --------------------------------------------------------------------------
STLString STLString::MakeUpper()
{
  if( 0 == this->length() ) return *this;
  DWORD len = (DWORD)size() + 1;
  TCHAR* buff = new TCHAR[ len ];
  memset(buff,0,sizeof(TCHAR) * len);
  _tcscpy(buff,c_str());
  CharUpperBuff(buff,len);
  clear();
  assign(buff);
  delete [] buff;
  return *this;
}
// --------------------------------------------------------------------------
// Function : ToInt
// Thinking : ����_ttoi�������ַ���ת����ʵ��������ַ���Ϊ�վͷ���-1
// --------------------------------------------------------------------------
int STLString::ToInt()
{
  if(!empty())
    return _ttoi(c_str());
  return -1;
}
// --------------------------------------------------------------------------
// Function : ToAnscii
// Thinking : ������ΪUnicodeʱ��ת���ɶ��ֽڣ�������Ϊ���ֽ�ʱ�����ر���
// --------------------------------------------------------------------------
string STLString::ToAnscii(int codepage /*= CP_ACP*/)
{
#if defined(UNICODE) || defined(_UNICODE)
  return Unicode2Anscii(*this,codepage);
#else
	if(CP_ACP == codepage)
		return *this;
  wstring wcs = Anscii2Unicode(*this,CP_ACP);
  return Unicode2Anscii(wcs,codepage);
#endif
}
// --------------------------------------------------------------------------
// Function : ToUnicode
// Thinking : ������Ϊ���ֽ�ʱ��ת����Unicode��������ΪUnicodeʱ�����ر���
// --------------------------------------------------------------------------
wstring STLString::ToUnicode(int codepage /*= CP_ACP*/)
{
#if defined(UNICODE) || defined(_UNICODE)
	if(CP_ACP == codepage)
		return *this;
	string str = Unicode2Anscii(*this,CP_ACP);
	return Anscii2Unicode(str,codepage);
#else
	return Anscii2Unicode(*this,codepage);
#endif
}
// --------------------------------------------------------------------------
// Function : Unicode2Anscii��Anscii2Unicode
// Thinking : 
// --------------------------------------------------------------------------
string STLString::Unicode2Anscii(const wstring& wcs,int codepage)
{
	if( wcs.empty() )
		return string();

	string _oper;
	int len = WideCharToMultiByte(codepage,0,wcs.c_str(),-1,NULL,0,NULL,NULL);
	char* buff = new char[len + 1];
	memset(buff,0,(len + 1) * sizeof(char));
	WideCharToMultiByte(codepage,0,wcs.c_str(),len,buff,len+1,NULL,NULL);
	_oper = buff;
	delete[] buff;
	return _oper;
}

wstring STLString::Anscii2Unicode(const string& str,int codepage)
{
	if( str.empty() )
		return wstring();

	wstring _oper;
	int len = MultiByteToWideChar(codepage,0,str.c_str(),-1,NULL,0);
	wchar_t* buff = new wchar_t[len + 1];
	memset(buff,0,(len + 1) * sizeof(char));
	MultiByteToWideChar(codepage,0,str.c_str(),len,buff,len+1);
	_oper = buff;
	delete[] buff;
	return _oper;
}
// --------------------------------------------------------------------------
// Function : ConvertEndCharInString
// Thinking : ѭ���Ƚ��ַ���ÿ���ַ�������'\0'ʱ���滻ΪcReplace
// --------------------------------------------------------------------------
STLString STLString::ConvertEndCharInString(LPCTSTR inSrc,int inSize,TCHAR cReplace)
{
	if(NULL == inSrc) return STLString();
	STLString result;
	bool isEnd = false;
	TCHAR* dist = new TCHAR[inSize];
	memset(dist,0,inSize * sizeof(TCHAR));
	for(int i = 0; i < inSize; ++i)
	{
		TCHAR c = inSrc[i];
		if(_T('\0') == c) {
			if(isEnd)
				break;
			c = cReplace;
			isEnd = true;
		}
		else {
			isEnd = false;
		}
		dist[i] = c;
	}
	result = dist;
	delete[] dist;
	return result;
}

// --------------------------------------------------------------------------
// Function : operator=
// Thinking : ���������
// --------------------------------------------------------------------------
STLString& STLString::operator=(const STLString& str)
{
	assign(str);
	return *this;
}

/******************************* STLStringArray *******************************************/

// --------------------------------------------------------------------------
// Function : STLStringArray�๹�캯��
// Thinking : ��һ�ɷָ����ָ����ַ���������飻
// --------------------------------------------------------------------------
STLStringArray::STLStringArray()
{

}

STLStringArray::STLStringArray(LPCTSTR szBuff,int nSize,TCHAR cSeparator)
{
	set(szBuff,nSize,cSeparator);
}
// --------------------------------------------------------------------------
// Function : STLStringArray�๹�캯��
// Thinking : ��һ�ɷָ����ָ����ַ���������飻
// --------------------------------------------------------------------------
void STLStringArray::set(LPCTSTR szBuff,int nSize,TCHAR cSeparator)
{
	bool isEnd = false;
	STLString save;
	for(int i = 0; i < nSize; ++i) 
	{
		TCHAR c = szBuff[i];
		if(c != cSeparator) {
			save += c;
			isEnd = false;
		}
		else {
			// ����һ���ļ����ʱ�����Ϊ1��Ĭ��Ϊ��������
			if(isEnd) {
				break;
			}
			this->push_back(save);
			save.clear();
			isEnd = true;
		}
	}

	// �ݴ���δ�Էָ��Ž�βҲ���ںϷ���Χ��
	if(!save.empty()) {
		this->push_back(save);
	}
}
