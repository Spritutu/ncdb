#pragma once
#include "PiTypeDef.h"
class CPiDisk
{
public:
    CPiDisk(void);
    ~CPiDisk(void);
    static LST_STRING GetValidDrive();
    static MAP_STRING GetDriveMapping( LST_STRING& lstDrive );
    bool GetValidDriveMapping();
    tstring GetDosPathFromMapping( tcpchar szMapping );
    bool Init();
	/*
	* Function:GetAppVersion
	* Description:??��?��|��?3��D����?��?��?o?
	* Input:strPath ???��3��D����??��??
	* Return:?��DD3��1|����??3��D����?��?��?o?��?����??����?????��
	*/
	static tstring GetFileVersion( tcpchar path );
private:
    MAP_STRING          m_mapDrive;
};

