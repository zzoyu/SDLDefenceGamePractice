#pragma once
#include "afxwin.h"


// CInGameInfoDlg ��ȭ �����Դϴ�.

class CInGameInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInGameInfoDlg)

public:
	CInGameInfoDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CInGameInfoDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_INGAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_listInGameChar;
};
