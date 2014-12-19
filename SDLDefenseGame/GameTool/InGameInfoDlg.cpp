// InGameInfoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GameTool.h"
#include "InGameInfoDlg.h"
#include "afxdialogex.h"


// CInGameInfoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CInGameInfoDlg, CDialogEx)

CInGameInfoDlg::CInGameInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInGameInfoDlg::IDD, pParent)
{

}

CInGameInfoDlg::~CInGameInfoDlg()
{
}

void CInGameInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CHAR, m_listInGameChar);
}


BEGIN_MESSAGE_MAP(CInGameInfoDlg, CDialogEx)
END_MESSAGE_MAP()


// CInGameInfoDlg 메시지 처리기입니다.
