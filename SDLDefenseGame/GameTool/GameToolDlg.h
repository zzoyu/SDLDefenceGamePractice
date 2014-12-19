
// GameToolDlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "CharInfoDlg.h"
#include "TileInfoDlg.h"

#include <locale.h>
#include <vector>

// CGameToolDlg ��ȭ ����
class CGameToolDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CGameToolDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_GAMETOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCiOpen();
	afx_msg void OnBnClickedButtonTiOpen();
	afx_msg void OnBnClickedButtonCiNew();
	afx_msg void OnBnClickedButtonTiNew();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	

	int m_iOnStartCnt;
	int m_iOnEndCnt;
	CListBox m_listQuotes;
	CComboBox m_comboChar;
	CComboBox m_comboEmot;
	
	typedef struct _tileInfo
	{
		CString strName;
		bool bLayable;
		int iLevel;
	} TILE_INFO;

	typedef struct _quoteInfo
	{
		CString strChar;
		CString strEmot;
		CString strQuote;
	} QUOTE_INFO;

	typedef struct _startInfo
	{
		int iX;
		int iY;
		int iDirection;	// ��(1)/��(2)/��(3)/��(4)
	} START_INFO;

	std::vector<TILE_INFO> m_vTileInfo;
	CListBox m_listTile;
	CStatic m_picPreview;
	afx_msg void OnStnClickedPreview();

	START_INFO m_stStartInfo;
	int m_arrMap[2][9][10];

	bool m_bIsEraseMode;
	bool m_bIsFillMode;
	bool m_bIsSetStartMode;
	afx_msg void OnBnClickedCheckErase();
	afx_msg void OnBnClickedCheckFill();

	void DrawMap( CDC *_pDC );
	void Filling( int _iX, int _iY, int _iSrc, int _iTo );
	afx_msg void OnBnClickedButtonReset();
	void UpdateQuoteList();
	std::vector<QUOTE_INFO> m_vQuoteOnStart;
	std::vector<QUOTE_INFO> m_vQuoteOnEnd;
	afx_msg void OnBnClickedCheckStart();
	CComboBox m_comboDirection;
};
