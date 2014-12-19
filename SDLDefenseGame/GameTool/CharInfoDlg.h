#pragma once
#include "afxwin.h"
#include <locale.h>

// CCharInfoDlg 대화 상자입니다.

class CCharInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCharInfoDlg)

public:
	CCharInfoDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCharInfoDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_CHARINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
