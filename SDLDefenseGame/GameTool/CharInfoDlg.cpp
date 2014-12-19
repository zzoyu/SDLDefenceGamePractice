// CharInfoDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GameTool.h"
#include "CharInfoDlg.h"
#include "afxdialogex.h"


// CCharInfoDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CCharInfoDlg, CDialogEx)

CCharInfoDlg::CCharInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCharInfoDlg::IDD, pParent)
{

}

CCharInfoDlg::~CCharInfoDlg()
{
}

void CCharInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CHAR, m_listCharacter);
	DDX_Control(pDX, IDC_LIST_EMOT, m_listEmotion);
}


BEGIN_MESSAGE_MAP(CCharInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCharInfoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCharInfoDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_CHAR_ADD, &CCharInfoDlg::OnBnClickedButtonCharAdd)
	ON_BN_CLICKED(IDC_BUTTON_EMOT_ADD, &CCharInfoDlg::OnBnClickedButtonEmotAdd)
	ON_EN_CHANGE(IDC_EDIT_LOCATION, &CCharInfoDlg::OnEnChangeEditLocation)
END_MESSAGE_MAP()


// CCharInfoDlg �޽��� ó�����Դϴ�.


void CCharInfoDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if( ( m_listCharacter.GetCount() == 0 ) || ( m_listEmotion.GetCount() == 0 ) )
		AfxMessageBox( L"����Ʈ�� �ϳ� �̻��� ���� �ʿ��մϴ�." );
	else
	{
		CFileDialog m_fileDlg( FALSE, L"dat", L"char_info", OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY, L"���� ���� ���� (*.dat)", this );

		CString m_strContent = L"CHARACTERS:", m_strTemp;
		for( int i=0; i<m_listCharacter.GetCount(); i++ )
		{
			m_listCharacter.GetText(i,m_strTemp);
			if( i < m_listCharacter.GetCount()-1 )
				m_strTemp += L",";
			m_strContent = m_strContent + m_strTemp;
		}

		m_strContent = m_strContent + L"\nEMOTIONS:";
		for( int i=0; i<m_listEmotion.GetCount(); i++ )
		{
			m_listEmotion.GetText(i,m_strTemp);
			if( i < m_listEmotion.GetCount()-1 )
				m_strTemp += L",";
			m_strContent = m_strContent + m_strTemp;
		}

		GetDlgItemText( IDC_EDIT_LOCATION, m_strTemp );
		m_strContent.Format( L"%s\nLOCATION:%s", m_strContent, m_strTemp );

		if( m_fileDlg.DoModal() == IDOK )
		{
			CStdioFile m_file;
			setlocale( LC_ALL, "korean" );
			m_file.Open( m_fileDlg.GetPathName(), CFile::modeCreate|CFile::modeWrite );
			m_file.WriteString( m_strContent );
			m_file.Close();

			CDialogEx::OnOK();
		}
	}
}


void CCharInfoDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}


void CCharInfoDlg::OnBnClickedButtonCharAdd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString m_strTemp;
	GetDlgItemText( IDC_EDIT_CHAR_NAME, m_strTemp );
	m_listCharacter.AddString( m_strTemp );

	SetDlgItemText( IDC_EDIT_CHAR_NAME, NULL );
	(( CEdit * )GetDlgItem( IDC_EDIT_CHAR_NAME ))->SetFocus();
	//m_listCharacter.
}


void CCharInfoDlg::OnBnClickedButtonEmotAdd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString m_strTemp;
	GetDlgItemText( IDC_EDIT_EMOT_NAME, m_strTemp );
	m_listEmotion.AddString( m_strTemp );

	(( CEdit * )GetDlgItem( IDC_EDIT_EMOT_NAME ))->Clear();
	(( CEdit * )GetDlgItem( IDC_EDIT_EMOT_NAME ))->SetFocus();
}


void CCharInfoDlg::OnEnChangeEditLocation()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString m_strTemp, m_strExample;

	GetDlgItemText( IDC_EDIT_LOCATION, m_strTemp );
	m_strExample = m_strTemp;

	m_listCharacter.GetText( 0, m_strTemp );
	m_strExample = m_strExample + m_strTemp;

	m_listEmotion.GetText( 0, m_strTemp );
	m_strExample.Format( L"%s_%s.png", m_strExample, m_strTemp );

	SetDlgItemText( IDC_EDIT_SAMPLE, m_strExample );
}
