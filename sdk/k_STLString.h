/***********************************************************************
 Copyright (c), 2012, Unicorn Tech. Co., Ltd.

 File name   : k_STLString.h
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
      Modification : ������й��캯����֧�֣����ToAnscii��ToUnicode��

 History 3 
	  Date   : 2014/08/12
	  Author : 
	  Modification : ֧���ַ�����ѡ��

 History 4 
      Date   : 2014/08/27
      Author : 
      Modification : ��Ӵ�Сд��ת����

***********************************************************************/

#ifndef K_STLSTRING_H
#define K_STLSTRING_H

#include <tchar.h>
#include <string>
#include <vector>
using namespace std;
#include <winnls.h>

/* �ַ�����
*/
class STLString
  : public basic_string< TCHAR, char_traits<TCHAR>,allocator<TCHAR> >
{
  // [��ʽ��]
public:
  void    Format(const TCHAR* format,...);
  STLString    MakeLower(); // ת���ɴ�д
  STLString    MakeUpper(); // ת����Сд

  // [��������ת��]
public:
  int     ToInt();
  string  ToAnscii(int codepage = CP_ACP);
  wstring ToUnicode(int codepage = CP_ACP);

  // [��̬ת��]
  static string Unicode2Anscii(const wstring& wcs,int codepage);
  static wstring Anscii2Unicode(const string& str,int codepage);

  // [���������]
public:
  operator LPCTSTR() { return c_str(); }
  STLString& operator=(const STLString& str);
 
public:
	// ת���ַ�������ֵĽ����ַ���\0��
	static STLString ConvertEndCharInString(LPCTSTR inSrc,int inSize,TCHAR cReplace);

public:
  STLString() : basic_string() { }
  STLString(const _Myt& _Right) : basic_string(_Right) { }
  explicit STLString(const _Alloc& _Al) : basic_string(_Al) { }
  STLString(const _Myt& _Right, size_type _Roff,size_type _Count = npos)
    : basic_string(_Right,_Roff,_Count) { }
  STLString(const _Myt& _Right, size_type _Roff, size_type _Count,const _Alloc& _Al)
    : basic_string(_Right,_Roff,_Count,_Al) { }
  STLString(const TCHAR *_Ptr, size_type _Count) : basic_string(_Ptr,_Count) { }
  STLString(const TCHAR *_Ptr, size_type _Count, const _Alloc& _Al) : basic_string(_Ptr,_Count,_Al) { }
  STLString(const TCHAR *_Ptr) : basic_string(_Ptr) { }
  STLString(const TCHAR *_Ptr, const _Alloc& _Al) : basic_string(_Ptr,_Al) { }
  STLString(size_type _Count, TCHAR _Ch) : basic_string(_Count,_Ch) { }
  STLString(size_type _Count, TCHAR _Ch, const _Alloc& _Al) : basic_string(_Count,_Ch,_Al) { }
  template<class _It>
  STLString(_It _First, _It _Last) : basic_string(_First,_Last) { }
  template<class _It>
  STLString(_It _First, _It _Last, const _Alloc& _Al) : basic_string(_First,_Last,_Al) { }
  
  // ������չ
  STLString(int n) : basic_string() {
    Format(_T("%d"),n);
  }
  STLString(LPCTSTR cmd,int n) : basic_string() {
    if(cmd) Format(cmd,n);
  }
};

/* �����ַ������������Ͷ���
*/
typedef const STLString& ConstSTLStringRef;

/* �ַ���������
*/
class STLStringArray : public vector< STLString >
{
public:
	STLStringArray();
	STLStringArray(LPCTSTR szBuff,int nSize,TCHAR cSeparator);

public:
	void set(LPCTSTR szBuff,int nSize,TCHAR cSeparator);
};

#endif // !K_STLSTRING_H