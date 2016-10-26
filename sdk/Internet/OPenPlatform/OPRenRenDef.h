#pragma once
#include "PiTypeDef.h"

#define  STRING_PARAM_TOKEN         "access_token"

#define  STRING_URL_USER_GET            _T("https://api.renren.com/v2/user/get"     )
#define  STRING_URL_ALBUM_LIST          _T("https://api.renren.com/v2/album/list"   )
#define  STRING_URL_PHOTO_UPLOAD        _T("https://api.renren.com/v2/photo/upload" )


#define  STRING_JSON_RESP           _T("response")
struct tagRRAlbum
{
    tstring strAlbumID;
    tstring strClassID;         //������ID
    tstring strCreateTime;
    tstring strDesc;
    tstring strName;
    tstring strCoverUrl;        //��������Ƭ��ַ
    tstring strPicNum;      //��Ƭ��
};


typedef list<tagRRAlbum*> LST_RR_ALBUM;

struct tagRRUser
{
    string strID;
    string strName;
};