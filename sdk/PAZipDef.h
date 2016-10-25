#pragma once

struct  PATH_INFO
{
public:
    PATH_INFO(){}   /*stl ������Ҫ*/
    PATH_INFO(const tstring& szPath, const tstring& szFolder)
    {
        strPathSoft = szPath;
        strFolder = szFolder;
    }
    tstring     strPathSoft;        //�����ļ� ���յ�·����Ϣ
    tstring     strFolder;          //�����ļ� �ļ�����
};

enum ENUM_PACK_TYPE
{
    type_im = 0,        //�Ż�
    type_mm,            //����
};

enum ENUM_PATH_TYPE
{
    pt_mm_panel = 0,        //����
    pt_mm_color,      
    pt_mm_brush,      
    pt_im_panel,        //�Ż�
    pt_im_color,      
    pt_im_brush,      
};

enum ENUM_PACK_ERROR
{
    err_ok = 0,
    err_pack_no_exist,
    err_unKnown,
};