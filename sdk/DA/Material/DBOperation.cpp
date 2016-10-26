#include "stdafx.h"
#include "DBOperation.h"
#include "sqlite3.h"
#pragma comment(lib,"sqlite3.lib")

//������
const char * CreateCatalogMetaDataStr = "CREATE TABLE CatalogMetaData(_PW_ID INTEGER PRIMARY KEY AUTOINCREMENT,\
										ModifierID INTEGER DEFAULT NULL, CreateTool TEXT DEFAULT NULL, \
										MaterialKind TEXT DEFAULT NULL, Lead TEXT DEFAULT NULL, \
										UseTool TEXT DEFAULT NULL, ReadOnly INTEGER DEFAULT NULL, \
										Uploadable INTEGER DEFAULT NULL, Antisocial INTEGER DEFAULT NULL,\
										Ideology INTEGER DEFAULT NULL, Sexual INTEGER DEFAULT NULL, \
										Violence INTEGER DEFAULT NULL, Clippy INTEGER DEFAULT NULL, \
										Gold INTEGER DEFAULT NULL, MaterialAlias INTEGER DEFAULT NULL,\
										Uploaded INTEGER DEFAULT NULL, Downloaded INTEGER DEFAULT NULL,\
										Created INTEGER DEFAULT NULL, InCatalog INTEGER DEFAULT NULL,\
										DownloadNotYet INTEGER DEFAULT NULL, Updated INTEGER DEFAULT NULL,\
										Editing INTEGER DEFAULT NULL);";

const char * CreateFolderTagStr = "CREATE TABLE FolderTag(_PW_ID INTEGER PRIMARY KEY AUTOINCREMENT,Title TEXT DEFAULT NULL);";

const char * CreateMaterialInterpretStr = "CREATE TABLE MaterialInterpret(_PW_ID INTEGER PRIMARY KEY AUTOINCREMENT,\
										  ModifierID INTEGER DEFAULT NULL, FreeWord TEXT DEFAULT NULL);";

const char * CreateMaterialModifierStr = "CREATE TABLE MaterialModifier(_PW_ID INTEGER PRIMARY KEY AUTOINCREMENT,\
										 MaterialName TEXT DEFAULT NULL, CatalogUuid TEXT DEFAULT NULL,\
										 CatalogContentId INTEGER DEFAULT NULL, CatalogUserId INTEGER DEFAULT NULL,\
										 MaterialUuid TEXT DEFAULT NULL, MaterialContentId INTEGER DEFAULT NULL,\
										 MaterialUserId INTEGER DEFAULT NULL, ParentUuid TEXT DEFAULT NULL,\
										 PathType INTEGER DEFAULT NULL, Path TEXT DEFAULT NULL);";

const char * CreateSystemTagStr = "CREATE TABLE SystemTag(_PW_ID INTEGER PRIMARY KEY AUTOINCREMENT, Title TEXT DEFAULT NULL);";

const char * CreateTableFolderTagElementMapStr = "CREATE TABLE TableFolderTagElementMap(_PW_ID INTEGER PRIMARY KEY AUTOINCREMENT,\
												 TagId INTEGER DEFAULT NULL, ElementId INTEGER DEFAULT NULL);";

const char * CreateTableSystemTagElementMapStr = "CREATE TABLE TableSystemTagElementMap(_PW_ID INTEGER PRIMARY KEY AUTOINCREMENT,\
												 TagId INTEGER DEFAULT NULL, ElementId INTEGER DEFAULT NULL);";

const char * CreateTableTagElementMapStr = "CREATE TABLE TableTagElementMap(_PW_ID INTEGER PRIMARY KEY AUTOINCREMENT, \
										   TagId INTEGER DEFAULT NULL, ElementId INTEGER DEFAULT NULL);";

const char * CreateTagStr = "CREATE TABLE Tag(_PW_ID INTEGER PRIMARY KEY AUTOINCREMENT, Title TEXT DEFAULT NULL);";

/************************************************************************/
/* ���ܣ����캯������ʼ����ʱ�����ݿ�·��·�����ݽ���                 */
/* ������pathStr ���ݿ�·��                                             */
/************************************************************************/
CDBOperation::CDBOperation(std::string pathStr)
{
	pathStr += "\\CatalogMaterial.cmdb";
	m_dbPath = pathStr;
}

CDBOperation::~CDBOperation()
{

}

/************************************************************************/
/* ���ܣ���ʼ�����ݿ�����������򴴽�                               */
/* ��������                                                             */
/************************************************************************/
BOOL CDBOperation::InitCatalogMaterialDB()
{
	//�鿴���ݿ���Ƿ񴴽������δ��������Ҫ������
	sqlite3 *db = NULL;
	int result = 0;
	char *err = NULL;
	char **szResult;
	int row = -1,colum = -1;
	result = sqlite3_open(m_dbPath.c_str(), &db);
	if (result)
	{
		return FALSE;
	}
	char sql[2048] = {0};
	strcpy(sql , "select * from MaterialModifier;");
	sqlite3_get_table(db, sql, &szResult, &row, &colum, &err);
	if ((0 == row) || (0 == colum))
	{
		sqlite3_free_table(szResult);
		strcpy(sql, CreateMaterialModifierStr);
		sqlite3_exec(db, sql, 0, 0, &err);
		strcpy(sql, CreateCatalogMetaDataStr);
		sqlite3_exec(db, sql, 0, 0, &err);
		strcpy(sql, CreateFolderTagStr);
		sqlite3_exec(db, sql, 0, 0, &err);
		strcpy(sql, CreateMaterialInterpretStr);
		sqlite3_exec(db, sql, 0, 0, &err);
		strcpy(sql, CreateSystemTagStr);
		sqlite3_exec(db, sql, 0, 0, &err);
		strcpy(sql, CreateTableFolderTagElementMapStr);
		sqlite3_exec(db, sql, 0, 0, &err);
		strcpy(sql, CreateTableSystemTagElementMapStr);
		sqlite3_exec(db, sql, 0, 0, &err);
		strcpy(sql, CreateTableTagElementMapStr);
		sqlite3_exec(db, sql, 0, 0, &err);
		strcpy(sql, CreateTagStr);
		sqlite3_exec(db, sql, 0, 0, &err);
		sqlite3_close(db);
		return TRUE;
	}
	else
	{
		sqlite3_free_table(szResult);
		sqlite3_close(db);
		return TRUE;
	}
}

/************************************************************************/
/* ���ܣ���TAG���뵽�������ݿ������MAP���������                     */
/* ������tableType ������ͣ��������                                   */
/*       titleStr  ��Ҫ�����Titleֵ                                    */
/************************************************************************/

BOOL CDBOperation::InsertDataIntoTagTable(INSERTTAGTYPE tableType, std::string titleStr)
{
	sqlite3 *db = NULL;
	int result;
	result = sqlite3_open(m_dbPath.c_str(), &db);
	if (result)
	{
		return FALSE;
	}
	char * tagTabName;
	char * tagMapTabName;
	switch(tableType)
	{
	case MAINTAG:
		tagTabName = "Tag";
		tagMapTabName = "TableTagElementMap";
		break;
	case SYSTEMTAG:
		tagTabName = "SystemTag";
		tagMapTabName = "TableSystemTagElementMap";
		break;
	case FOLDERTAG:
		tagTabName = "FolderTag";
		tagMapTabName = "TableFolderTagElementMap";
		break;
	}
	char sql[2048] = {0};
	char **szResult;
	int colum = -1, row = -1;
	char *err = NULL;
	//�Ȳ�ѯTiTle�Ƿ��Ѿ����ڣ����������򲻲���
	sprintf(sql, "select _PW_ID from %s where Title = '%s';", tagTabName, titleStr.c_str());
	sqlite3_get_table(db, sql, &szResult, &row, &colum, &err);
	if (0 == row || 0 == colum)
	{
		//��������
		sprintf(sql, "insert into %s(Title)Values('%s')", tagTabName, titleStr.c_str());
		sqlite3_exec(db, sql, 0, 0, &err);
	}
	sprintf(sql, "Insert into %s(TagId,ElementId)Values((Select _PW_ID from %s Where Title='%s'),\
				 (Select MAX(_PW_ID)From MaterialModifier))", tagMapTabName, tagTabName, titleStr.c_str());
	sqlite3_exec(db, sql, 0, 0, &err);
	sqlite3_free_table(szResult);
	sqlite3_close(db);
	return TRUE;
}

/************************************************************************/
/* ���ܣ���MaterialModifier����в���                                   */
/* ������MaterialModifierInfo ����֮ǰ�����ýṹ��                    */
/************************************************************************/
BOOL CDBOperation::InsertDataIntoMTModifier(MaterialModifierInfo mtInfo)
{
	sqlite3 *db = NULL;
	int result;
	result = sqlite3_open(m_dbPath.c_str(), &db);
	if (result)
	{
		return FALSE;
	}

	char sql[2048] = {0};;
	char *err = NULL;
	sprintf(sql,"insert into MaterialModifier(MaterialName,CatalogUuid,CatalogContentId,\
				CatalogUserId, MaterialUuid, MaterialContentId,MaterialUserId,ParentUuid,\
				PathType,Path)Values('%s','%s',%d,%d,'%s',%d,%d,'%s',%d,'%s');"
				,mtInfo.materialName.c_str(),mtInfo.catalogUuid.c_str(), mtInfo.catalogContentId, mtInfo.catalogUserId,
				mtInfo.materialUuid.c_str(), mtInfo.materialContentId, mtInfo.materialUserId,
				mtInfo.parentUuid.c_str(), mtInfo.pathType, mtInfo.path.c_str());
	sqlite3_exec(db, sql, 0, 0, &err);
	sqlite3_close(db);
	return TRUE;
}

/************************************************************************/
/* ���ܣ���MaterialInterpret����в���                                  */
/* ������freeWorldStr  FreeWorld��ֵ                                    */
/************************************************************************/
BOOL CDBOperation::InsertDataIntoMTInterpret(std::string freeWorldStr)
{
	sqlite3 *db = NULL;
	int result;
	result = sqlite3_open(m_dbPath.c_str(), &db);
	if (result)
	{
		return FALSE;
	}

	char sql[2048] = {0};;
	char *err = NULL;
	sprintf(sql, "insert into MaterialInterpret(ModifierID, FreeWord)Values((Select \
				 MAX(_PW_ID) From MaterialModifier), '%s');",freeWorldStr.c_str());
	sqlite3_exec(db, sql, 0, 0, &err);
	sqlite3_close(db);
	return TRUE;
}

/************************************************************************/
/* ���ܣ���CatalogMetaData����в���                                    */
/* ������CatalogMetaDataInfo ����֮ǰ�����ýṹ��                     */
/************************************************************************/

BOOL CDBOperation::InsertDataIntoCAMMetaData(CatalogMetaDataInfo cmInfo)
{
	sqlite3 *db = NULL;
	int result;
	result = sqlite3_open(m_dbPath.c_str(), &db);
	if (result)
	{
		return FALSE;
	}
	char sql[2048] = {0};;
	char *err = NULL;
	sprintf(sql, "insert into CatalogMetaData(ModifierID,CreateTool,MaterialKind,Lead,UseTool,ReadOnly,\
				 Uploadable,Antisocial,Ideology,Sexual,Violence,Clippy,Gold,MaterialAlias,Uploaded,Downloaded,\
				 Created,InCatalog,DownloadNotYet,Updated,Editing)Values((Select MAX(_PW_ID) From MaterialModifier),\
				 '%s', '%s', '%s','%s',%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d);", cmInfo.createTool.c_str(), 
				 cmInfo.materialKind.c_str(),cmInfo.lead.c_str(),cmInfo.useTool.c_str(), cmInfo.readOnly, cmInfo.uploadable,
				 cmInfo.antisocial, cmInfo.ideology, cmInfo.sexual, cmInfo.violence, cmInfo.clippy, cmInfo.gold, 
				 cmInfo.materialAlias, cmInfo.uploaded, cmInfo.downloaded, cmInfo.created, cmInfo.inCatalog,
				 cmInfo.downloadNotYet, cmInfo.updated, cmInfo.editing);
	sqlite3_exec(db, sql, 0, 0, &err);
	sqlite3_close(db);
	return TRUE;

}

/************************************************************************/
/* ���ܣ���Ҫɾ�����زĵ����ݿ�������                                 */
/* ������uuid Ҫɾ�����زĵ�ID                                          */
/*       dbPath ���ݿ�·��                                              */
/************************************************************************/
BOOL CDBOperation::DeleteMaterialFromDB(const std::string uuidStr, const std::string dbPath)
{
	sqlite3 *db = NULL;
	int result;
	result = sqlite3_open(m_dbPath.c_str(), &db);
	if (result)
	{
		return FALSE;
	}
	char sql[2048] = {0};;
	char *err = NULL;
	sprintf(sql, "delete from CatalogMetaData where ModifierID = (select _PW_ID from\
				 MaterialModifier where CatalogUuid = '%s');", uuidStr.c_str());
	sqlite3_exec(db, sql, 0, 0, &err);

	sprintf(sql, "delete from TableTagElementMap where ElementId = (select _PW_ID from\
				 MaterialModifier where CatalogUuid = '%s');", uuidStr.c_str());
	sqlite3_exec(db, sql, 0, 0, &err);

	sprintf(sql, "delete from TableSystemTagElementMap where ElementId = (select _PW_ID \
				 from MaterialModifier where CatalogUuid = '%s');", uuidStr.c_str());
	sqlite3_exec(db, sql, 0, 0, &err);

	sprintf(sql, "delete from TableFolderTagElementMap where ElementId = (select _PW_ID\
				 from MaterialModifier where CatalogUuid = '%s');", uuidStr.c_str());
	sqlite3_exec(db, sql, 0, 0, &err);

	sprintf(sql, "delete from MaterialInterpret where ModifierID = (select _PW_ID from\
				 MaterialModifier where CatalogUuid = '%s');", uuidStr.c_str());
	sqlite3_exec(db, sql, 0, 0, &err);

	sprintf(sql, "delete from MaterialModifier where CatalogUuid = '%s';", uuidStr.c_str());
	sqlite3_exec(db, sql, 0, 0, &err);

	sqlite3_close(db);
	return TRUE;
}
