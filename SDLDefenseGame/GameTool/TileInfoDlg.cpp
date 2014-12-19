// TileInfoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GameTool.h"
#include "TileInfoDlg.h"
#include "afxdialogex.h"


// CTileInfoDlg 대화 상자입니다.

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


// CTileInfoDlg 메시지 처리기입니다.


void CTileInfoDlg::OnBnClickedOk2()
{
	if( m_listTile.GetCount() == 0 )
		AfxMessageBox( L"리스트에 하나 이상의 값이 필요합니다." );
	else
	{
		CFileDialog m_fileDlg( FALSE, L"dat", L"tile_info", OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY, L"게임 정보 파일 (*.dat)", this );

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
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

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	(( CButton * )GetDlgItem( IDC_RADIO_YES ))->SetCheck(TRUE);
	(( CButton * )GetDlgItem( IDC_RADIO_1 ))->SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}