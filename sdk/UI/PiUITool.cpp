#include "StdAfx.h"
#include "PiUITool.h"
#include <shlobj.h>
#include "PiWindowPack.h"
#include "PiString.h"
#include "..\TextStringCut.h"
#include <commdlg.h>
#include "PiFileDialog.h"
#include "PathLight.h"
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "shlwapi.lib")

Pi_NameSpace_Using

#define STRING_PROP_NAME _T("OPENFILENAME")

ARR_STRING		CPIUITool::m_FileList;

typedef CPIUITool::tagSELECT_FILE_DIR tagSELECT_FILE_DIR;
tstring CPIUITool::GetOneDragFilePath(const HDROP& hd)
{
	tstring strName;
	strName.resize(FILENAME_MAX);

	DragQueryFile(hd, 0, &strName.at(0), FILENAME_MAX);
	return strName.c_str();
}

tstring CPIUITool::SelectDirectory(HWND hParent, tcpchar szBeginDir, tcpchar szTitle)
{
	wchar_t szBuf[MAX_PATH + 1] = { 0 };
	BROWSEINFO bi = { 0 };
	bi.hwndOwner = hParent;
	bi.pszDisplayName = szBuf;
	/*if (szBeginDir && *szBeginDir)
	{
		bi.pidlRoot = SHSimpleIDListFromPath(szBeginDir);
	}*/
	bi.lpszTitle = szTitle;
	bi.ulFlags = BIF_NEWDIALOGSTYLE /*| BIF_EDITBOX*/;

	//�ȵ���CoInitializeEx();
	LPITEMIDLIST lIL = SHBrowseForFolder(&bi);
	if (lIL)
	{
		SHGetPathFromIDList(lIL, szBuf);
	}
	return szBuf;
}



LONG g_lOriWndProc = NULL;
#define  ID_COMBO_ADDR	0x47c
#define  ID_LEFT_TOOBAR 0x4A0
LRESULT static __stdcall  _WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    bool bDeal = false;
	switch (uMsg)
	{
	case WM_COMMAND:
	{
		if (wParam == IDOK)
		{
			/*EndDialog(hwnd, 1);
			break;*/
			
			//TODO:���ѡ������ ��־���ⲿ
			LPOPENFILENAMEW pOFn = (LPOPENFILENAME)GetProp(hwnd, STRING_PROP_NAME);
			tagSELECT_FILE_DIR* pTag = (tagSELECT_FILE_DIR*)pOFn->lCustData;
			ARR_STRING& arr = CPIUITool::GetFileList();
			arr.clear();
			{
				wchar_t wcDirP[MAX_PATH] = { 0 };
				CommDlg_OpenSave_GetFolderPath(hwnd, wcDirP, sizeof(wcDirP));//��ѡģʽ�£� ���ֻѡ��һ���ļ��� �ļ��б�û��˫����
				::PathAddBackslash(wcDirP);
				arr.push_back(wcDirP);
			}

			if (pTag->bSelectMulti)
			{
                bDeal = true;
				tchar szBuf[MAX_PATH + 1] = { 0 };
				CommDlg_OpenSave_GetSpec(hwnd, szBuf, MAX_PATH);

				
				CPiString strTemp(szBuf);
				;
				if (!strTemp.Exist(_T("\"")))
				{
					arr.push_back(szBuf);
				}
				else
				{
					wstring strDist;
					CTextStringCut text(szBuf);

					text.GetInDQM(arr);
				}
                EndDialog(hwnd, 1);

				/*if (arr.size() > 1)
				{
					
					pTag->szSelectDir = wcDirPath;
					//arr.insert(arr.begin(), wcDirPath);
				}*/
				//ARR_STRING arr = CPiString::SpilitStrToArray(tstring(szBuf), _T("\""));
				//pTag->nSelectCount = arr.size();/*����*/
				//pTag->pFileLst = (int)arr;
			}
			else
			{
				tchar szBuf[MAX_PATH + 1] = { 0 };
				CommDlg_OpenSave_GetFilePath(hwnd, szBuf, MAX_PATH);
				arr.push_back(szBuf);

				wchar_t wcDirPath[MAX_PATH] = { 0 };
				HWND hComboAddr = GetDlgItem(hwnd, ID_COMBO_ADDR);
				if (hComboAddr != NULL)
				{
					GetWindowText(hComboAddr, wcDirPath, MAX_PATH);
				}
				if (!wcslen(wcDirPath))
				{
					break;
				}
				DWORD dwAttr = GetFileAttributes(wcDirPath);
				if (dwAttr != -1 && (FILE_ATTRIBUTE_DIRECTORY & dwAttr))
				{
					LPOPENFILENAMEW oFn = (LPOPENFILENAME)GetProp(hwnd, STRING_PROP_NAME);
					if (oFn)
					{
						int size = oFn->nMaxFile > MAX_PATH ? MAX_PATH : oFn->nMaxFile;
						memcpy(oFn->lpstrFile, wcDirPath, size * sizeof(wchar_t));
						RemoveProp(hwnd, STRING_PROP_NAME);
						EndDialog(hwnd, 1);
					}
					else
					{
						EndDialog(hwnd, 0);
					}
					RemoveProp(hwnd, STRING_PROP_NAME);
				}
				break;
			}
			break;

			
		}
		//////////////////////////////////////////////////////////////////////////
		//��������toolbar������WM_COMMOND��Ϣ���������ߵ�toolbar��, �����OK��ť�Ե���Ͽ�
		HWND hCtrl = (HWND)lParam;
		if (hCtrl == NULL)
		{
			break;
		}
		int ctrlId = GetDlgCtrlID(hCtrl);
		if (ctrlId == ID_LEFT_TOOBAR)
		{
			HWND hComboAddr = GetDlgItem(hwnd, ID_COMBO_ADDR);
			if (hComboAddr != NULL)
			{
				SetWindowTextW(hComboAddr, L"");
			}
		}
	}
	break;
	}
    if (bDeal)
    {
        return 1;
    }
	int i = CallWindowProc((WNDPROC)g_lOriWndProc, hwnd, uMsg, wParam, lParam);
	return i;
}

UINT_PTR static __stdcall  MyFolderProc(HWND hdlg, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	//return 0;

	//OK��CANCEL��ť�ȿؼ�����Ϣ�ڸ����ڴ���
	int nRet = 0;	//return to default dialog box procedure
	switch (uiMsg)
	{
	case WM_INITDIALOG:
	{
		OutputDebugString(_T("hook WM_INITDIALOG \n"));
		//break;

		/*
		g_lOriWndProc = ::SetWindowLongW(hDlgCommon, GWL_WNDPROC, (LONG)_WndProc);
		break;*/
		HWND hDlgCommon = ::GetParent(hdlg);
		LPOPENFILENAME pON = (LPOPENFILENAME)lParam;
		tagSELECT_FILE_DIR* pTag = (tagSELECT_FILE_DIR*)pON->lCustData;
		::SetDlgItemText(hDlgCommon, IDOK, pTag->szBtnOkName);
		SetPropW(hDlgCommon, STRING_PROP_NAME, (HANDLE)(pON));
		g_lOriWndProc = ::SetWindowLongW(hDlgCommon, GWL_WNDPROC, (LONG)_WndProc);

		//������ʾ
		HWND hParentToCenter = ::GetDesktopWindow();
		if (pTag->bCenterToParent && pON->hwndOwner)
		{
			hParentToCenter = pON->hwndOwner;
		}
		CPiWindowPack::CenterWindow(hDlgCommon, hParentToCenter);
	}
	break;
	default:
		break;
	}
	if (uiMsg == WM_NOTIFY)
	{
		HWND hDlgCommon = ::GetParent(hdlg);
		LPOFNOTIFY lpOfNotify = (LPOFNOTIFY)lParam;
		if (lpOfNotify->hdr.code == CDN_INITDONE
			&& !g_lOriWndProc)
		{
			OutputDebugString(_T("dlg CDN_INITDONE\n"));
			nRet = 0;

			/*tagSELECT_FILE_DIR* pTag = (tagSELECT_FILE_DIR*)lpOfNotify->lpOFN->lCustData;
			::SetDlgItemText(hDlgCommon, IDOK, pTag->szBtnOkName);
			SetPropW(hDlgCommon, STRING_PROP_NAME, (HANDLE)(lpOfNotify->lpOFN));
			g_lOriWndProc = ::SetWindowLongW(hDlgCommon, GWL_WNDPROC, (LONG)_WndProc);

			//������ʾ
			HWND hParentToCenter = ::GetDesktopWindow();
			if (pTag->bCenterToParent && lpOfNotify->lpOFN->hwndOwner)
			{
			hParentToCenter = lpOfNotify->lpOFN->hwndOwner;
			}
			CPiWindowPack::CenterWindow(hDlgCommon, hParentToCenter);*/
		}
		switch (lpOfNotify->hdr.code)
		{
		case CDN_FILEOK:
			//OutputDebugString(_T(""));
		{
			LPOFNOTIFY lpOfNotify = (LPOFNOTIFY)lParam;
			//OutputDebugString(lpOfNotify->lpOFN->lpstrFile);

			ARR_STRING& arr = CPIUITool::GetFileList();
			arr.clear();
			{
				wchar_t wcDirP[MAX_PATH] = { 0 };
				CommDlg_OpenSave_GetFolderPath(hDlgCommon, wcDirP, sizeof(wcDirP));//��ѡģʽ�£� ���ֻѡ��һ���ļ��� �ļ��б�û��˫����
				::PathAddBackslash(wcDirP);
				arr.push_back(wcDirP);
			}
			arr.push_back(lpOfNotify->lpOFN->lpstrFile);
		}
			break;
		default:
			break;
		}
		if (lpOfNotify->hdr.code == CDN_SELCHANGE)
		{
			//return 0;
			LPOFNOTIFY lpOfNotify = (LPOFNOTIFY)lParam;
			tagSELECT_FILE_DIR* pTag = (tagSELECT_FILE_DIR*)lpOfNotify->lpOFN->lCustData;
			/*if (pTag->bSelectMulti)
			{
				return 0;	//����ѡ������ ����ϵͳĬ�ϵģ� ����˵�Ŀ¼
			}*/

			nRet = 0;
			wchar_t wcDirPath[MAX_PATH] = { 0 };
			CommDlg_OpenSave_GetFilePathW(GetParent(hdlg), wcDirPath, sizeof(wcDirPath));
            tstring strM(_T("select:"));
            strM += wcDirPath;
            strM += L"\n";
			OutputDebugString(strM.c_str());
			//return 0;

			HWND hComboAddr = GetDlgItem(GetParent(hdlg), ID_COMBO_ADDR);
			if (hComboAddr != NULL)
			{
				if (wcslen(wcDirPath))
				{
					//ȥ���ļ��п�ݷ�ʽ�ĺ�׺����
					int pathSize = wcslen(wcDirPath);
					if (pathSize >= 4)
					{
						/*wchar_t* wcExtension = PathFindExtensionW(wcDirPath);
						if (wcslen(wcExtension))
						{
						wcExtension = CharLowerW(wcExtension);
						if (!wcscmp(wcExtension, L".lnk"))
						{
						wcDirPath[pathSize - 4] = L'\0';
						}
						}*/
					}
					//
					SetWindowTextW(hComboAddr, wcDirPath);
				}
				else
				{
					SetWindowTextW(hComboAddr, L"");
				}
			}
		}

	}
	return nRet;	//return to default;
}
UINT_PTR static __stdcall  ProcHookSaveDlg(HWND hdlg, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	int nRet = 0;	//return to default dialog box procedure
	//return nRet;	//����Ի��� �����ù��Ӿͻ�ʹ�þɰ�Ĵ���UI�� ����Ҫ���⴦��

	//OK��CANCEL��ť�ȿؼ�����Ϣ�ڸ����ڴ���
	switch (uiMsg)
	{
	case WM_INITDIALOG:
	{
		OutputDebugString(_T("hook WM_INITDIALOG \n"));
		//break;

		/*
		g_lOriWndProc = ::SetWindowLongW(hDlgCommon, GWL_WNDPROC, (LONG)_WndProc);
		break;*/
		HWND hDlgCommon = ::GetParent(hdlg);
		LPOPENFILENAME pON = (LPOPENFILENAME)lParam;
		tagSELECT_FILE_DIR* pTag = (tagSELECT_FILE_DIR*)pON->lCustData;
		::SetDlgItemText(hDlgCommon, IDOK, pTag->szBtnOkName);
		//CPiWindowPack::TopMostWindow(hDlgCommon);
		

		/*SetPropW(hDlgCommon, STRING_PROP_NAME, (HANDLE)(pON));
		g_lOriWndProc = ::SetWindowLongW(hDlgCommon, GWL_WNDPROC, (LONG)_WndProc);*/

		//������ʾ
		HWND hParentToCenter = ::GetDesktopWindow();
		if (pTag->bCenterToParent && pON->hwndOwner)
		{
			hParentToCenter = pON->hwndOwner;
		}
		CPiWindowPack::CenterWindow(hDlgCommon, hParentToCenter);
	}
		break;
	default:
		break;
	}
	
	return nRet;	//return to default;
}
int CPIUITool::SelectFileOrDir(tagSELECT_FILE_DIR* pTag)
{
	//setlocale(LC_ALL, "chs");
	tstring strTitle(_T("ѡ��һ���ļ�(Ŀ¼)"));
	tstring strBtnOkName(_T("ȷ��"));
	if (pTag->szTitle && *pTag->szTitle)
	{
		strTitle = pTag->szTitle;
	}

	if (!pTag->szBtnOkName || !*pTag->szBtnOkName)
	{
		pTag->szBtnOkName = strBtnOkName.c_str();
	}
	if (!pTag->szFilter || !*pTag->szFilter)
	{
		pTag->szFilter = _T("All(*.*)\0 * .*\0\0");
	}
	OPENFILENAMEW openFile;
	memset(&openFile, 0, sizeof(openFile));
	openFile.lStructSize = sizeof(openFile);

	wchar_t    szFileName[MAX_PATH] = { 0 };
	OPENFILENAME openFileName = { 0 };
	openFile.lStructSize = sizeof(OPENFILENAME);
	openFile.nMaxFile = MAX_PATH;
	openFile.lpstrFilter = pTag->szFilter;	//��һ��Ϊ1
	openFile.lpstrFile = szFileName;	//TODO:ѡ������ ���buf̫С�� GetOpenFileName�᷵��false,  CommDlgExtendedError ����FNERR_BUFFERTOOSMALL.�� openFile.lpstrFileǰ�����ֽ�Ϊ�����С
	openFile.nFilterIndex = 1;
	openFile.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_ENABLEHOOK | OFN_HIDEREADONLY;
	
	openFile.hInstance = (HMODULE)GetCurrentProcess();
	openFile.lpfnHook = MyFolderProc;
	openFile.lpstrTitle = strTitle.c_str();
	openFile.lpstrInitialDir = pTag->szInitialDir;
	openFile.hwndOwner = pTag->hParent;
	openFile.lCustData = (LPARAM)pTag;

	if (pTag->bSelectMulti)
	{
		openFile.Flags |= OFN_ALLOWMULTISELECT;
	}
	BOOL b = GetOpenFileName(&openFile);
	int nSel = 1;
	if (pTag->bSelectMulti)
	{
		CPIUITool::AlterPath();
		nSel = CPIUITool::GetFileList().size() - 1;
	}
	return nSel; ;
}

ARR_STRING& CPIUITool::GetFileList()
{
	return m_FileList;
}

void CPIUITool::AlterPath()
{
	if (m_FileList.size() < 2)	//	1��Ԫ�أ� �ǵ�ѡģʽ,Ԫ��Ϊ����·���� 2��Ԫ�أ� ��ѡģʽ��ѡ��1���� >=3��Ԫ��, ��ѡ�� ѡ��һ���ļ�(Ŀ¼),�Ƿ�ѡ�����ļ��� ��һ��Ԫ��Ϊ�ļ��б����ڵ�Ŀ¼·��,�ڶ�����ʼ���ļ���
	{
		return;
	}
	tstring& strDir{ m_FileList[0] };
	for (UINT i = 1; i < m_FileList.size(); ++i)
	{
		m_FileList[i] = strDir + m_FileList[i];
	}
	
	
}

tcpchar CPIUITool::QuerySelectFile(UNINT nIndex)
{
	ARR_STRING& arr = CPIUITool::GetFileList();
	if (!arr.size() || nIndex >= arr.size() - 1)
	{
		return _T("");
	}

	return arr[nIndex + 1].c_str();
}

tstring CPIUITool::PopSaveDialog(tagSELECT_FILE_DIR* pTag)
{
	tstring strTitle(_T("ѡ��һ���ļ�(Ŀ¼)"));
	tstring strBtnOkName(_T("ȷ��"));
	if (pTag->szTitle && *pTag->szTitle)
	{
		strTitle = pTag->szTitle;
	}
	if (!pTag->szFilter || !*pTag->szFilter)
	{
		pTag->szFilter = _T("All(*.*)\0 * .*\0\0");
	}
	if (pTag->szDefExt && *pTag->szDefExt == '.')
	{
		++pTag->szDefExt;
	}
	OPENFILENAMEW openFile;
	memset(&openFile, 0, sizeof(openFile));
	openFile.lStructSize = sizeof(openFile);

	tstring strFilePath(MAX_PATH, 0);
	if (pTag->szInitialFileName)
	{
		strFilePath = pTag->szInitialFileName;
	}
	wchar_t    szFileName[MAX_PATH] = { 0 };
	OPENFILENAME openFileName = { 0 };
	openFile.lStructSize = sizeof(OPENFILENAME);
	openFile.nMaxFile = MAX_PATH;
	openFile.lpstrFilter = pTag->szFilter;	//��һ��Ϊ1
	openFile.lpstrTitle = pTag->szTitle;
	openFile.lpstrFile = &strFilePath.at(0);
	openFile.nMaxFile = strFilePath.capacity();
	openFile.nFilterIndex = 1;
	//openFile.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST /*| OFN_ENABLEHOOK*/ | OFN_HIDEREADONLY;
	openFile.Flags = OFN_EXPLORER | OFN_ENABLEHOOK;
	openFile.lpfnHook = ProcHookSaveDlg;
	openFile.lpstrDefExt = pTag->szDefExt;
	openFile.lpstrFilter = pTag->szFilter;
	openFile.lpstrTitle = strTitle.c_str();
	openFile.lpstrInitialDir = pTag->szInitialDir;
	openFile.hwndOwner = pTag->hParent;
	openFile.lCustData = (LPARAM)pTag;
	
	if (!GetSaveFileName(&openFile))
	{
		//TODO:����·��̫��������
		return _T("");
	}
	CPiString strSel(openFile.lpstrFile);
	CPathLight strPath(openFile.lpstrFile);
	//����:1. ֻ���ļ���, 2�ļ���+"."�� 3. �ļ���.��׺
	//1,2�������Ҫ��Ӻ�׺
	/*if (strPath.GetExt().length() < 2)
	{
		strPath.AddSuffix(pTag->szDefExt);
	}
	strSel = strPath.GetPath();*/

	
	pTag->nFilterIndex = openFile.nFilterIndex;
	return strSel;
}

int CPIUITool::SelectFileOrDirVista(tagSELECT_FILE_DIR* pTag)
{
	tstring strTitle(_T("ѡ���ļ�(Ŀ¼)"));
	tstring strBtnOkName(_T("ȷ��"));
	if (pTag->szTitle && *pTag->szTitle)
	{
		strTitle = pTag->szTitle;
	}

	if (!pTag->szBtnOkName || !*pTag->szBtnOkName)
	{
		pTag->szBtnOkName = strBtnOkName.c_str();
	}
	if (!pTag->szFilter || !*pTag->szFilter)
	{
		pTag->szFilter = _T("All Files (*.*)|*.*||");
	}

	CPiFileDialog dlgFile(pTag->szTitle, pTag->szFilter);
	if (!dlgFile.Popup())
	{
		return 0;
	}
	return dlgFile.GetSelect().size();
}
