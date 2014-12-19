#pragma once
#include "afxwin.h"

#include <locale>

// CTileInfoDlg 대화 상자입니다.

class CTileInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTileInfoDlg)

public:
	CTileInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTileInfoDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_TILEINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedButtonTileAdd();
	afx_msg void OnEnChangeEditLocationTile();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel2();
	CListBox m_listTile;

};
