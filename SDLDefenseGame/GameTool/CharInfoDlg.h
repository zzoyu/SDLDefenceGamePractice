#pragma once
#include "afxwin.h"
#include <locale.h>

// CCharInfoDlg ��ȭ �����Դϴ�.

class CCharInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCharInfoDlg)

public:
	CCharInfoDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CCharInfoDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_CHARINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonCharAdd();
	afx_msg void OnBnClickedButtonEmotAdd();
	CListBox m_listCharacter;
	CListBox m_listEmotion;
	afx_msg void OnEnChangeEditLocation();
};
