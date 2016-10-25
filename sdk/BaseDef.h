
#pragma once

#include <tchar.h>

// XML //////////////////////////////////////////////////////////////////////////

//#include "Markup.h"

// STL //////////////////////////////////////////////////////////////////////////

//
// Include
//
#include <string>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <deque>
using namespace std;

//
// String Typedef
//
#ifdef UNICODE
	typedef std::wstring StlString;
#else
	typedef std::string StlString;
#endif //!UNICODE


// STL�������Ͷ��� ////////////////////////////////////////////////////////////////////////

//
// �ַ����б�����
//
typedef vector< StlString > StringVect;

//
// �ַ������ַ��͵�ӳ���
//
typedef map< StlString, StlString > Str_Str_Map;

//
// �ַ������ַ��͵�ӳ��������
//
typedef map< int, Str_Str_Map > Int_StrStrMap_Map;

// ���������������־ ////////////////////////////////////////////////////////////////////////

//
// ��ʾ�ᱻ�����߼�д����β�
//
#ifndef OUT
#define OUT
#endif

//
// ��ʾ���뺯�������߼�������β�
//
#ifndef IN
#define IN
#endif

// �������弰��ȡ���� ////////////////////////////////////////////////////////////////////////

//
// ���ַ���
//
#define EMPTY_STR _T("")

//
// STL �ַ��������Ķ���
//
#define ConstStlStringVar( key, value )		const StlString key = value
