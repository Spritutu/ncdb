#pragma once
#include <Windows.h>
#include <map>
#include <string>
class CMapLight;
using namespace std;

/************************************************************************/
/*	fun: ͼ���б�,���ڲ��� ָ����׺����ͼ��,�Ƿ��Ѵ���,                                                                   
	ret: �������,������CImageList���λ��>=0,���򷵻�-1
/************************************************************************/
typedef map<string, DWORD> ilMap;
class CImageMap
{
public:
	CImageMap(void);
	~CImageMap(void);

	bool Init();
	/************************************************************************/
	/*	fun: ��ȡָ���ļ����Ͷ�Ӧ��ͼ�����ڵ�����,�����������Ӳ�������Ӻ��index                                                                     */
	/************************************************************************/
	DWORD GetIndex(const char*);
	ilMap::iterator Find(const char* suffix);
	bool Insert(const char* key, DWORD idxImage );
	DWORD GetNewIndex();
	CImageList* GetImageList();
	void SetImageList(CImageList* );
private:
	CImageList* m_pIL;
	CMapLight* m_pMap;
};
