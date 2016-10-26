
#ifndef CARLTON_VERSION_H__
#define CARLTON_VERSION_H__

#include "BaseDef.h"

/* .Declaration Header
****************************************************************************************
* Theme:	�汾����
* Author:	Ming Zhi.Xue ( Carlton )
* Data:		2014.1.21
* Brief:	
****************************************************************************************
*/

//�Ӱ汾������������
typedef std::vector<unsigned int>	SubVersionSet;

class CCarltonVersion
{
public:
	CCarltonVersion();
	~CCarltonVersion();

public:

	//�����汾�ַ���
	static BOOL			ParseVersion(IN LPCTSTR lpszVer,OUT SubVersionSet& set);
    static StlString    VerToString(const SubVersionSet& sVer);
	//�Ƚ��ַ���ʽ�汾
	static enum CmpVerRetT { paramer_error=-2,ver1_gt_ver2=1,ver1_equal_ver2=0,ver1_lt_ver2=-1 };
	static CmpVerRetT	CompareVersion(IN LPCTSTR lpszVer1,IN LPCTSTR lpszVer2);

    static CmpVerRetT CompareVersion( SubVersionSet &vs1, SubVersionSet &vs2 );

};

//////////////////////////////////////////////////////////////////////////
#endif