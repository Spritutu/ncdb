#include "StdAfx.h"
#include "StrTrans.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//

#if 0
//��wchar_t* ת��char*��ʵ�ֺ������£�

char *w2c(char *pcstr,const wchar_t *pwstr, size_t len)
{
	int nlength=wcslen(pwstr);
	//��ȡת����ĳ���

	int nbytes = WideCharToMultiByte( 0, // specify the code page used to perform the conversion

		0,         // no special flags to handle unmapped characters

		pwstr,     // wide character string to convert

		nlength,   // the number of wide characters in that string

		NULL,      // no output buffer given, we just want to know how long it needs to be

		0,

		NULL,      // no replacement character given

		NULL );    // we don't want to know if a character didn't make it through the translation

	// make sure the buffer is big enough for this, making it larger if necessary

	if(nbytes>len)   nbytes=len;

	// ͨ�����ϵõ��Ľ����ת��unicode �ַ�Ϊascii �ַ�

	WideCharToMultiByte( 0, // specify the code page used to perform the conversion

		0,         // no special flags to handle unmapped characters

		pwstr,   // wide character string to convert

		nlength,   // the number of wide characters in that string

		pcstr, // put the output ascii characters at the end of the buffer

		nbytes,                           // there is at least this much space there

		NULL,      // no replacement character given

		NULL );

	return pcstr ;

}

//��char* ת��wchar_t*��ʵ�ֺ������£�

//���ǰ�asii�ַ�ת��Ϊunicode�ַ�

void c2w(wchar_t *pwstr,size_t len,const char *str)
{

	if(str)

	{

		size_t nu = strlen(str);

		size_t n =(size_t)MultiByteToWideChar(CP_ACP,0,(const char *)str,(int)nu,NULL,0);

		if(n>=len)n=len-1;

		MultiByteToWideChar(CP_ACP,0,(const char *)str,(int)nu,pwstr,(int)n);

		pwstr[n]=0;

	}

}
#endif


int ustr_astr(WCHAR * unicodestr, char *ansistr )
{
	int result = 0;
	try
	{
		int needlen = WideCharToMultiByte( CP_ACP, 0, unicodestr, -1, NULL, 0, NULL, NULL );
		if( needlen < 0 )
		{
			return needlen;
		}
		result = WideCharToMultiByte( CP_ACP, 0, unicodestr, -1, ansistr, needlen + 1, NULL, NULL );
		if( result < 0 )
		{
			return result;
		}
		return strlen( ansistr );
	}
	catch( ... )
	{
	}
	return result;
}

WCHAR* CStrTrans::FontFile_AnsiToUnicode(char* pUnicoDestr, int nLen)
{
	WCHAR* pWUnicodeBuf = new WCHAR[nLen + sizeof(WCHAR)];

	int i = 0;
	for (i = 0; i < (nLen/2); ++i)
	{
		WCHAR wcHigh = (pUnicoDestr[i*2]<<8) & 0xFF00;
		WCHAR wcLow = (pUnicoDestr[i*2+1]) & 0X00FF;
		pWUnicodeBuf[i] = wcHigh | wcLow;
	}
	
	pWUnicodeBuf[nLen/sizeof(WCHAR)] = 0;
	return pWUnicodeBuf;

// 	char* szAnsi = NULL;
// 
// 	int result = 0;
// 	try
// 	{
// 		int needlen = WideCharToMultiByte( CP_ACP, 0, unicodestr, -1, NULL, 0, NULL, NULL );
// 		if( needlen < 0 )
// 		{
// 			return NULL;
// 		}
// 		char* szAnsi = new char[ansiLen + 1];
// 		result = WideCharToMultiByte( CP_ACP, 0, unicodestr, -1, ansistr, needlen + 1, NULL, NULL );
// 		if( result < 0 )
// 		{
// 			return NULL;
// 		}
// 		return strlen( ansistr );
// 	}
// 	catch( ... )
// 	{
// 	}
// 
// 	return szAnsi;
}

string CStrTrans::UnicodeToAnsi( const wchar_t* wszString )
{
	int ansiLen = ::WideCharToMultiByte(CP_ACP, NULL, wszString, wcslen(wszString), NULL, 0, NULL, NULL);
	char* szAnsi = new char[ansiLen + 1];
	::WideCharToMultiByte(CP_ACP, NULL, wszString, wcslen(wszString), szAnsi, ansiLen, NULL, NULL);
	szAnsi[ansiLen] = 0;
	return szAnsi;
}

wstring CStrTrans::AnsiToUnicode( const char* szStr )
{
	int nLen = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szStr, -1, NULL, 0 );
	if (nLen == 0)
	{
		return NULL;
	}
	wchar_t* pResult = new wchar_t[nLen];
	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szStr, -1, pResult, nLen );
	return pResult;
}

CString CStrTrans::AnsiToUnicode_Str( const char* szStr )
{
	int nLen = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szStr, -1, NULL, 0 );
	if (nLen == 0)
	{
		return NULL;
	}
	wchar_t* pResult = new wchar_t[nLen];
	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szStr, -1, pResult, nLen );

	CString strRet = pResult;
	delete[] pResult;
	pResult = NULL;

	return strRet;
}

CString CStrTrans::UTF8ToUnicode( const char* UTF8 )
{
	DWORD dwUnicodeLen;        //ת����Unicode�ĳ���
	TCHAR *pwText;            //����Unicode��ָ��
	CString strUnicode;        //����ֵ

	//���ת����ĳ��ȣ��������ڴ�
	dwUnicodeLen = MultiByteToWideChar(CP_UTF8,0,UTF8,-1,NULL,0);
	pwText = new TCHAR[dwUnicodeLen];
	if (!pwText)
	{
		return strUnicode;
	}

	//תΪUnicode
	MultiByteToWideChar(CP_UTF8,0,UTF8,-1,pwText,dwUnicodeLen);

	//תΪCString
	strUnicode.Format(_T("%s"),pwText);

	//����ڴ�
	delete []pwText;

	//����ת���õ�Unicode�ִ�
	return strUnicode;

}

char* CStrTrans::UnicodeToUTF8(CString strUnicode)
{
//	AtlUnicodeToUTF8(strUnicode, strUnicode.GetLength(), )

	//Ԥת�����õ�����ռ�Ĵ�С������õĺ��������������෴
	int u8Len = ::WideCharToMultiByte(CP_UTF8, NULL, strUnicode, strUnicode.GetLength(), NULL, 0, NULL, NULL);

	//ͬ�ϣ�����ռ�Ҫ��'\0'�����ռ�
	//UTF8��Ȼ��Unicode��ѹ����ʽ����Ҳ�Ƕ��ֽ��ַ��������Կ�����char����ʽ����
	char* szU8 = new char[u8Len + 1];

	//ת��
	//unicode���Ӧ��strlen��wcslen
	::WideCharToMultiByte(CP_UTF8, NULL, strUnicode, strUnicode.GetLength(), szU8, u8Len, NULL, NULL);
	//������'\0'
	szU8[u8Len] = '\0';

	return szU8;
}