#pragma once
#include "afxwin.h"

#include <locale>

// CTileInfoDlg ��ȭ �����Դϴ�.

class CTileInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTileInfoDlg)

public:
	CTileInfoDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTileInfoDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_TILEINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedButtonTileAdd();
	afx_msg void OnEnChangeEditLocationTile();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel2();
	CListBox m_listTile;

};
