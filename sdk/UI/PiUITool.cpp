#include "StdAfx.h"
#include "PiUITool.h"
#include <shlobj.h>
#include "PiWindowPack.h"
#pragma comment(lib, "shell32.lib")

#define STRING_PROP_NAME _T("OPENFILENAME")
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
	switch (uMsg)
	{
	case WM_SHOWWINDOW:
		//���ڼ�����ʾ�� �ɵ���λ��
		//OutputDebugString(_T("dlg init\n"));
		break;
	case WM_COMMAND:
	{
		if (wParam == IDOK)
		{
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
	int i = CallWindowProc((WNDPROC)g_lOriWndProc, hwnd, uMsg, wParam, lParam);
	return i;
}
UINT_PTR static __stdcall  MyFolderProc(HWND hdlg, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	//OK��CANCEL��ť�ȿؼ�����Ϣ�ڸ����ڴ���
	if (uiMsg == WM_NOTIFY)
	{
		HWND hDlgCommon = ::GetParent(hdlg);
		LPOFNOTIFY lpOfNotify = (LPOFNOTIFY)lParam;
		if (lpOfNotify->hdr.code == CDN_INITDONE
			&& !g_lOriWndProc)
		{
			tagSELECT_FILE_DIR* pTag = (tagSELECT_FILE_DIR*)lpOfNotify->lpOFN->lCustData;
			::SetDlgItemText(hDlgCommon, IDOK, pTag->szBtnOkName);
			SetPropW(hDlgCommon, STRING_PROP_NAME, (HANDLE)(lpOfNotify->lpOFN));
			g_lOriWndProc = ::SetWindowLongW(hDlgCommon, GWL_WNDPROC, (LONG)_WndProc);

			//������ʾ
			HWND hParentToCenter = ::GetDesktopWindow();
			if (pTag->bCenterToParent && lpOfNotify->lpOFN->hwndOwner)
			{
				hParentToCenter = lpOfNotify->lpOFN->hwndOwner;
			}
			CPiWindowPack::CenterWindow(hDlgCommon, hParentToCenter);
		}
		if (lpOfNotify->hdr.code == CDN_SELCHANGE)
		{
			wchar_t wcDirPath[MAX_PATH] = { 0 };
			CommDlg_OpenSave_GetFilePathW(GetParent(hdlg), wcDirPath, sizeof(wcDirPath));
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

					SetWindowTextW(hComboAddr, wcDirPath);
				}
				else
				{
					SetWindowTextW(hComboAddr, L"");
				}
			}
		}
	}
	return 1;
}
tstring CPIUITool::SelectFileOrDir(tagSELECT_FILE_DIR* pTag)
{
	setlocale(LC_ALL, "chs");
	tstring strTitle(_T("ѡ��һ���ļ�(Ŀ¼)"));
	tstring strBtnOkName(_T("ȷ��"));
	if (pTag->szTitle && *pTag->szTitle)
	{
		strTitle = pTag->szTitle;
	}

	if (pTag->szBtnOkName && *pTag->szBtnOkName)
	{
		pTag->szBtnOkName = strBtnOkName.c_str();
	}
	OPENFILENAMEW openFile;
	memset(&openFile, 0, sizeof(openFile));
	openFile.lStructSize = sizeof(openFile);

	wchar_t    szFileName[MAX_PATH] = { 0 };
	OPENFILENAME openFileName = { 0 };
	openFile.lStructSize = sizeof(OPENFILENAME);
	openFile.nMaxFile = MAX_PATH;
	openFile.lpstrFilter = L"All(*.*)\0*.*\0\0";
	openFile.lpstrFile = szFileName;
	openFile.nFilterIndex = 1;
	openFile.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_ENABLEHOOK | OFN_HIDEREADONLY;
	openFile.hInstance = (HMODULE)GetCurrentProcess();
	openFile.lpfnHook = MyFolderProc;
	openFile.lpstrTitle = strTitle.c_str();
	openFile.lpstrInitialDir = pTag->szBeginDir;
	openFile.hwndOwner = pTag->hParent;
	//string strBtnName = 
	openFile.lCustData = (LPARAM)pTag;
	BOOL b = GetOpenFileNameW(&openFile);
	return openFile.lpstrFile;
}
