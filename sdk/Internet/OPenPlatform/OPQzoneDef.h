#pragma once
#include "PiTypeDef.h"

struct tagAlbumQzone
{
    tstring strAlbumID;
    tstring strClassID;         //������ID
    tstring strCreateTime;
    tstring strDesc;
    tstring strName;
    tstring strCoverUrl;        //��������Ƭ��ַ
    tstring strPicNum;      //��Ƭ��
};

struct tagCreateAlbumQzone
{
    tstring strLocation;
    tstring strDesc;
    tstring strName;

};

typedef list<tagAlbumQzone*> LST_ALBUM_QZONE;