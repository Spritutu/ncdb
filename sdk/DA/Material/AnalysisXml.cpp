#include "stdafx.h"
#include "AnalysisXml.h"
#include "Markup.h"
#include "k_STLString.h"
#include "DBOperation.h"

CAnalysisXml::CAnalysisXml()
{

}

CAnalysisXml::~CAnalysisXml()
{

}
/*************************************************************************/
/* ���ܣ����زĵĸ���xml���н�����д�뵽���ݿ���                         */
/* ������dbPath ���ݿ��·����Documents\Unicorn\UDMCommon\MaterialDB��   */
/*       materialPath �ز�·����\Unicorn\UDMCommon\Material\PaintAidSetup*/
/*                              \62fb940046-084d-97b4-550a-e1bff5bf00��  */ 
/*************************************************************************/
BOOL CAnalysisXml::AnalysisAndInstall(const CString dbPath, const CString materialPath)
{
	STLString pathStr(dbPath);
	CDBOperation dbOp(pathStr.ToAnscii());
	if (!dbOp.InitCatalogMaterialDB())
	{
		return FALSE;
	}
	MaterialModifierInfo mtInfo;
	CatalogMetaDataInfo  cmInfo;
	std::vector <string> vectorTag;
	std::vector <string> vectorSystemTag;
	std:string folderTag = "";
    AnalysisCatalog(mtInfo, cmInfo, materialPath);
	AnalysisInfo(vectorTag, materialPath);
	AnalysisLayerData(vectorSystemTag, folderTag, materialPath);
	CString pathTemp(_T(".:PaintAidSetup:"));
	STLString tempPathStr = pathTemp.GetString();
	std::string installPath = tempPathStr.ToAnscii(CP_UTF8) + mtInfo.catalogUuid;
 	mtInfo.path = installPath;
	if(!dbOp.InsertDataIntoMTModifier(mtInfo))
	{
		return FALSE;
	}
	if(!dbOp.InsertDataIntoCAMMetaData(cmInfo))
	{
		return FALSE;
	}
	std::string freeWord = mtInfo.materialName;
	for (int i = 0; i < vectorTag.size(); i++)
	{
		freeWord += "\t";
		freeWord += vectorTag[i].c_str();
		if(!dbOp.InsertDataIntoTagTable(MAINTAG, vectorTag[i].c_str()))
		{
			return FALSE;
		}
	}
	if(!dbOp.InsertDataIntoMTInterpret(freeWord))
	{
		return FALSE;
	}
	for(int i = 0; i < vectorSystemTag.size(); i++)
	{
		if(!dbOp.InsertDataIntoTagTable(SYSTEMTAG, vectorSystemTag[i].c_str()))
		{
			return FALSE;
		}
	}
	if(!dbOp.InsertDataIntoTagTable(FOLDERTAG, folderTag))
	{
		return FALSE;
	}
	return TRUE;
}

/************************************************************************/
/* ���ܣ���Catalog.xml���н�������������洢�ڽṹ������                */
/* ������MaterialModifierInfo MaterialModifier���ݿ��Ľṹ��          */
/*       CatalogMetaDataInfo   CatalogMetaData���ݿ��Ľṹ��          */
/*       materialPath  �زĵİ�װ·��                                   */
/************************************************************************/
void CAnalysisXml::AnalysisCatalog(MaterialModifierInfo &mtInfo, CatalogMetaDataInfo &cmInfo, const CString materialPath)
{
	CMarkup markUp;
	MCD_STR dataStr = L"";
	STLString stlString;
	CString catalogPath = materialPath;
	catalogPath += _T("\\catalog.xml");
	if (markUp.Load(catalogPath))
	{
		if (markUp.FindElem(L"archive"))
		{
			markUp.IntoElem();
			if (markUp.FindElem(L"catalog"))
			{
				stlString = markUp.GetAttrib(L"uuid").GetString();
				mtInfo.catalogUuid = stlString.ToAnscii(CP_UTF8);
				stlString.clear();
				if (markUp.FindChildElem(L"readonly"))
				{
					stlString = markUp.GetChildData().GetString();
					cmInfo.readOnly = stlString.ToInt();
					stlString.clear();
				}
				if (markUp.FindChildElem(L"uploadable"))
				{
					stlString = markUp.GetChildData().GetString();
					cmInfo.uploadable = stlString.ToInt();
					stlString.clear();
				}
				markUp.IntoElem();
				if (markUp.FindElem(L"groups"))
				{
					markUp.IntoElem();
					if(markUp.FindElem(L"group"))
					{
						stlString = markUp.GetAttrib(L"parentuuid").GetString();
						mtInfo.parentUuid = stlString.ToAnscii(CP_UTF8);
						stlString.clear();
						stlString = markUp.GetAttrib(L"uuid").GetString();
						mtInfo.materialUuid = stlString.ToAnscii(CP_UTF8);
						stlString.clear();
						markUp.IntoElem();
						if (markUp.FindElem(L"items"))
						{
							markUp.IntoElem();
							if (markUp.FindElem(L"item"))
							{
								stlString = markUp.GetAttrib(L"parentuuid").GetString();
								if(0 != stlString.length())
								{
									mtInfo.parentUuid = stlString.ToAnscii(CP_UTF8);
								}
								stlString.clear();
								stlString = markUp.GetAttrib(L"uuid").GetString();
								if (0 != stlString.length())
								{
									mtInfo.materialUuid = stlString.ToAnscii(CP_UTF8);
								}
								stlString.clear();
							}
						}
						markUp.IntoElem();
						if (markUp.FindElem(L"tool"))
						{
							stlString = markUp.GetAttrib(L"name").GetString();
							cmInfo.createTool = stlString.ToAnscii(CP_UTF8);
							stlString.clear();
						}
						if (markUp.FindElem(L"type"))
						{
							stlString = markUp.GetData().GetString();
							cmInfo.materialKind = stlString.ToAnscii(CP_UTF8);
							stlString.clear();
						}
						if (markUp.FindElem(L"name"))
						{
							stlString = markUp.GetData().GetString();
							mtInfo.materialName = stlString.ToAnscii(CP_UTF8);
							stlString.clear();
						}
					}

				}
			}
		}
	}
}
/************************************************************************/
/* ���ܣ���info.xml���н�������������洢����������                     */
/* ������vectorTag ���������������洢����������Tagֵ                    */
/*       materialPath  �زĵİ�װ·��                                   */
/************************************************************************/
void CAnalysisXml::AnalysisInfo(std::vector <std::string> &vectorTag, const CString materialPath)
{
	CMarkup markUp;
	MCD_STR dataStr = L"";
	STLString stlString;
	CString infoPath = materialPath;
	infoPath += _T("\\info.xml");
	if (markUp.Load(infoPath))
	{
		if (markUp.FindElem(L"infolist"))
		{
			markUp.IntoElem();
			if (markUp.FindElem(L"info"))
			{
				while(markUp.FindChildElem(L"datalist"))
				{
					
					if ("tag" == markUp.GetChildAttrib(L"key"))
					{
						markUp.IntoElem();
						while(markUp.FindChildElem(L"data"))
						{
							stlString = markUp.GetChildData().GetString();
							vectorTag.push_back(stlString.ToAnscii(CP_UTF8));
							stlString.clear();
						}
					}
				}
			}
		}
	}
}

/************************************************************************/
/* ���ܣ���LayerData.xml���н�������������洢����������                */
/* ������vecorSystemTag ���������������洢����������systemtagֵ         */
/*       systemFolder  �ز�����·��                                     */
/*       materialPath  �زĵİ�װ·��                                   */
/************************************************************************/
void CAnalysisXml::AnalysisLayerData(std::vector <std::string> &vecorSystemTag, std::string &systemFolder, const CString materialPath)
{
	CMarkup markUp;
	MCD_STR dataStr = L"";
	STLString stlString;
	CString layerDataPath = materialPath;
    layerDataPath += _T("\\icedata\\LayerData.xml");
	if (markUp.Load(layerDataPath))
	{
		if (markUp.FindElem(L"infolist"))
		{
			markUp.IntoElem();
			if (markUp.FindElem(L"info"))
			{
				markUp.IntoElem();
				while(markUp.FindElem(L"datalist"))
				{
					if ("systemtag" == markUp.GetAttrib(L"key"))
					{
						while (markUp.FindChildElem(L"data"))
						{
							stlString = markUp.GetChildData().GetString();
							vecorSystemTag.push_back(stlString.ToAnscii(CP_UTF8));
							stlString.clear();
						}
					}
					if ("foldertag" == markUp.GetAttrib(L"key"))
					{
						if (markUp.FindChildElem(L"data"))
						{
							stlString = markUp.GetChildData().GetString();
							systemFolder = stlString.ToAnscii(CP_UTF8);
							stlString.clear();
						}
					}

				}
			}
		}
	}
}
