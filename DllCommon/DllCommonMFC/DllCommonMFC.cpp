// DllCommonMFC.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "DllCommonMFC.h"
#include "UI\PiFileDialog.h"
#include "PiString.h"
#include "platform/DelphiTrans.h"

Pi_NameSpace_Using

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static ARR_STRING g_lstSel;
//
//TODO:  ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ��  ����ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CDllCommonMFCApp

BEGIN_MESSAGE_MAP(CDllCommonMFCApp, CWinApp)
END_MESSAGE_MAP()


// CDllCommonMFCApp ����

CDllCommonMFCApp::CDllCommonMFCApp()
{
	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CDllCommonMFCApp ����

CDllCommonMFCApp theApp;

const GUID CDECL _tlid = { 0x6C7E93CE, 0x24A1, 0x4E7B, { 0x95, 0x30, 0x53, 0xE9, 0x21, 0xC4, 0x43, 0x4D } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CDllCommonMFCApp ��ʼ��

BOOL CDllCommonMFCApp::InitInstance()
{
	CWinApp::InitInstance();

	// ������ OLE ������(����)ע��Ϊ���С�  �⽫ʹ
	//  OLE ����Դ�����Ӧ�ó��򴴽�����
	COleObjectFactory::RegisterAll();

	return TRUE;
}

// DllGetClassObject - �����๤��

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllGetClassObject(rclsid, riid, ppv);
}


// DllCanUnloadNow - ���� COM ж�� DLL

STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return AfxDllCanUnloadNow();
}


// DllRegisterServer - ������ӵ�ϵͳע���

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return SELFREG_E_TYPELIB;

	if (!COleObjectFactory::UpdateRegistryAll())
		return SELFREG_E_CLASS;

	return S_OK;
}


// DllUnregisterServer - �����ϵͳע������Ƴ�

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return SELFREG_E_TYPELIB;

	if (!COleObjectFactory::UpdateRegistryAll(FALSE))
		return SELFREG_E_CLASS;

	return S_OK;
}





NCCOMMON_API int NCCOMMON_CALL SelectFileOrDir(tagSELECT_FILE_DIR* pTag)
{
	int nSel = 0;
	tstring  strSelectPath;
	tstring strBtnOkName(_T("ȷ��"));
	if (!pTag->szTitle || !*pTag->szTitle)
	{
		pTag->szTitle = _T("ѡ���ļ�(Ŀ¼)");
	}

	if (!pTag->szBtnOkName || !*pTag->szBtnOkName)
	{
		pTag->szBtnOkName = strBtnOkName.c_str();
	}
	tstring strFilter = CDelphiTrans::FilterToMFC(pTag->szFilter);
	pTag->szFilter = strFilter.c_str();

	CPiFileDialog dlgFile(pTag->szTitle, pTag->szFilter, pTag->szInitialDir, pTag->bSelectMulti);
	dlgFile.SetParam(pTag);
	if (!dlgFile.Popup())
	{
		return nSel;
	}
	g_lstSel = dlgFile.GetSelect();
	nSel = g_lstSel.size();
	return nSel;
}

NCCOMMON_API const wchar_t* QuerySelectFile(int nIndex)
{
	return g_lstSel.at((UINT)nIndex).c_str();

}

NCCOMMON_API bool NCCOMMON_CALL PopSaveDialog(tagSELECT_FILE_DIR* pTag, wchar_t* szPath)
{
	if (!szPath)
	{
		return false;
	}
	tstring strFilter = CDelphiTrans::FilterToMFC(pTag->szFilter);
	pTag->szFilter = strFilter.c_str();

	tstring strPath = CPIUITool::PopSaveDialog(pTag).c_str();
	if (strPath.length() >= MAX_PATH)
	{
		_tcscpy_s(szPath, MAX_PATH, _T("buf too small"));
		return false;
	}
	_tcscpy_s(szPath, MAX_PATH, strPath.c_str());
	return strPath.length() > 0;
}

