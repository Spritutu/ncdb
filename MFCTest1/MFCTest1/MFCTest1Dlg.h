
// MFCTest1Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "PiDropTarget.h"
#include "MyDropTarget.h"


// CMFCTest1Dlg �Ի���
class CMFCTest1Dlg : public CDialogEx
{
// ����
public:
	CMFCTest1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCTEST1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton1();
	void TestOleDrag();
	CButton m_btn1;

private:
	COleDataSource m_oleDataSource;
	bool			m_bDraging;

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBegindragFilelist(NMHDR* pNMHDR, LRESULT* pResult);

	bool BeginDrag();
	void DragIng();
	void DragIng2();
	void DragDui();

	bool				m_bBtnDown;
	//CPiDropTarget		m_DropTarget;
	CListCtrl			c_FileList;

	//CMyDropTarget		m_droptarget;
};
