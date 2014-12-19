// TileInfoDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "GameTool.h"
#include "TileInfoDlg.h"
#include "afxdialogex.h"


// CTileInfoDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTileInfoDlg, CDialogEx)

CTileInfoDlg::CTileInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTileInfoDlg::IDD, pParent)
{

}

CTileInfoDlg::~CTileInfoDlg()
{
}

void CTileInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TILE, m_listTile);
}


BEGIN_MESSAGE_MAP(CTileInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDOK2, &CTileInfoDlg::OnBnClickedOk2)
	ON_BN_CLICKED(IDC_BUTTON_TILE_ADD, &CTileInfoDlg::OnBnClickedButtonTileAdd)
	ON_EN_CHANGE(IDC_EDIT_LOCATION_TILE, &CTileInfoDlg::OnEnChangeEditLocationTile)
	ON_BN_CLICKED(IDCANCEL2, &CTileInfoDlg::OnBnClickedCancel2)
END_MESSAGE_MAP()


// CTileInfoDlg �޽��� ó�����Դϴ�.


void CTileInfoDlg::OnBnClickedOk2()
{
	if( m_listTile.GetCount() == 0 )
		AfxMessageBox( L"����Ʈ�� �ϳ� �̻��� ���� �ʿ��մϴ�." );
	else
	{
		CFileDialog m_fileDlg( FALSE, L"dat", L"tile_info", OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY, L"���� ���� ���� (*.dat)", this );

		CString m_strContent, m_strTemp;

		if( m_fileDlg.DoModal() == IDOK )
		{
			CStdioFile m_file;
			setlocale( LC_ALL, "korean" );
			m_file.Open( m_fileDlg.GetPathName(), CFile::modeCreate|CFile::modeWrite );

			for( int i=0; i<m_listTile.GetCount(); i++ )
			{
				m_listTile.GetText(i,m_strContent);
				m_strContent = m_strContent + L"\n";
				m_file.WriteString( m_strContent );
			}
			GetDlgItemText( IDC_EDIT_LOCATION_TILE, m_strTemp );
			m_strContent.Format( L"LOCATION:%s", m_strTemp );
			m_file.WriteString( m_strContent );

			m_file.Close();

			CDialogEx::OnOK();
		}
	}
}

void CTileInfoDlg::OnBnClickedCancel2()
{
	CDialogEx::OnCancel();
}



void CTileInfoDlg::OnBnClickedButtonTileAdd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString m_strString;

	GetDlgItemText( IDC_EDIT_TILE_NAME, m_strString );

	if( ((CButton*)GetDlgItem( IDC_RADIO_YES ))->GetCheck() == 1 )
		m_strString.Format( L"%s,Y", m_strString );
	else
		m_strString.Format( L"%s,N", m_strString );

	if( ((CButton*)GetDlgItem( IDC_RADIO_1 ))->GetCheck() == 1 )
		m_strString.Format( L"%s,1", m_strString );
	else
		m_strString.Format( L"%s,2", m_strString );

	m_listTile.InsertString( m_listTile.GetCount(), m_strString );
	m_listTile.SetCurSel( m_listTile.GetCount()-1 );

	SetDlgItemText( IDC_EDIT_TILE_NAME, NULL );
	(( CEdit * )GetDlgItem( IDC_EDIT_TILE_NAME ))->SetFocus();
}


void CTileInfoDlg::OnEnChangeEditLocationTile()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString m_strTemp, m_strExample;

	GetDlgItemText( IDC_EDIT_LOCATION_TILE, m_strTemp );
	m_strExample = m_strTemp;

	m_listTile.GetText( 0, m_strTemp );
	m_strExample = m_strExample + m_strTemp.Left(m_strTemp.Find( L"," ));
	m_strExample.Format( L"%s.png", m_strExample );

	SetDlgItemText( IDC_EDIT_SAMPLE_TILE, m_strExample );
}


BOOL CTileInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	(( CButton * )GetDlgItem( IDC_RADIO_YES ))->SetCheck(TRUE);
	(( CButton * )GetDlgItem( IDC_RADIO_1 ))->SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}