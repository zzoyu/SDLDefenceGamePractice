// InGameInfoDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GameTool.h"
#include "InGameInfoDlg.h"
#include "afxdialogex.h"


// CInGameInfoDlg ��ȭ �����Դϴ�.

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


// CInGameInfoDlg �޽��� ó�����Դϴ�.
