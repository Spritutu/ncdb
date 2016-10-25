#pragma once
#include "DBDefined.h"

class CDBOperation
{
public:
	CDBOperation(std::string pathStr);
	virtual ~CDBOperation();
	BOOL InsertDataIntoTagTable(INSERTTAGTYPE tableType, std::string titleStr);//��������ӵ�Tag���Լ�Tag�Ĺ�������
	BOOL DeleteMaterialFromDB(const std::string uuidStr, const std::string dbPath); //���زĴ����ݿ��Ƴ�
	BOOL InitCatalogMaterialDB();//��ʼ�����ݿ��
    BOOL InsertDataIntoMTModifier(MaterialModifierInfo mtInfo);//�������ݵ�MaterialModifier����
	BOOL InsertDataIntoMTInterpret(std::string freeWorldStr);//�������ݵ�MaterialInterpret����
	BOOL InsertDataIntoCAMMetaData(CatalogMetaDataInfo cmInfo);//�������ݵ�CatalogMetaData����
protected:
private:
	std::string m_dbPath;
};