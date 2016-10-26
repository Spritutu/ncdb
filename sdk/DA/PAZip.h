#pragma once
#include "PiTypeDef.h"
#include <memory>
#include <map>
#include <windows.h>
#include "PAZipDef.h"
/************************************************************************
    Ŀǰֻ����������2.0 �� �Ż�1.1
************************************************************************/
class CPiZip;

using namespace std;
class CPAZip
{
public:
    CPAZip(void);
    ~CPAZip(void);
public:
    bool Init();
    bool PackConfig(PCTSTR szZipPath, ENUM_PACK_TYPE packType );
    bool UnPackonfig(PCTSTR szZipPath, ENUM_PACK_TYPE packType);
    bool CutToMM( const tstring& strPathSour );
    bool CutToIM( tstring strPathSour);
private:
    void AddDist(ENUM_PATH_TYPE nType , tstring strDistPath);
    static bool CutFileCoverFull( tstring szSour, tstring szDist );
private:
    auto_ptr<CPiZip>                m_pZip;
    map<ENUM_PATH_TYPE, PATH_INFO>                    m_lstPath;
};

