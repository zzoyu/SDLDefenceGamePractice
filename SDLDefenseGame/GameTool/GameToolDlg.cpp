
// GameToolDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "GameTool.h"
#include "GameToolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGameToolDlg 대화 상자




CGameToolDlg::CGameToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGameToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGameToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_QUOTES, m_listQuotes);
	DDX_Control(pDX, IDC_LIST_QUOTES, m_listQuotes);
	DDX_Control(pDX, IDC_COMBO_CHAR, m_comboChar);
	DDX_Control(pDX, IDC_COMBO_EMOT, m_comboEmot);
	DDX_Control(pDX, IDC_LIST_TILE, m_listTile);
	DDX_Control(pDX, IDC_PREVIEW, m_picPreview);
	DDX_Control(pDX, IDC_COMBO_DIR, m_comboDirection);
}

BEGIN_MESSAGE_MAP(CGameToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CI_OPEN, &CGameToolDlg::OnBnClickedButtonCiOpen)
	ON_BN_CLICKED(IDC_BUTTON_TI_OPEN, &CGameToolDlg::OnBnClickedButtonTiOpen)
	ON_BN_CLICKED(IDC_BUTTON_CI_NEW, &CGameToolDlg::OnBnClickedButtonCiNew)
	ON_BN_CLICKED(IDC_BUTTON_TI_NEW, &CGameToolDlg::OnBnClickedButtonTiNew)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CGameToolDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CGameToolDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CGameToolDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CGameToolDlg::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_UP, &CGameToolDlg::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &CGameToolDlg::OnBnClickedButtonDown)
ON_STN_CLICKED(IDC_PREVIEW, &CGameToolDlg::OnStnClickedPreview)
ON_BN_CLICKED(IDC_CHECK_ERASE, &CGameToolDlg::OnBnClickedCheckErase)
ON_BN_CLICKED(IDC_CHECK_FILL, &CGameToolDlg::OnBnClickedCheckFill)
ON_BN_CLICKED(IDC_BUTTON_RESET, &CGameToolDlg::OnBnClickedButtonReset)
ON_BN_CLICKED(IDC_CHECK_START, &CGameToolDlg::OnBnClickedCheckStart)
END_MESSAGE_MAP()


// CGameToolDlg 메시지 처리기

BOOL CGameToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	((CButton*)GetDlgItem( IDC_RADIO_START ))->SetCheck(1);

	m_iOnStartCnt = 0;
	m_iOnEndCnt = 0;
	ZeroMemory( m_arrMap, sizeof( m_arrMap ) );

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGameToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGameToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGameToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGameToolDlg::OnBnClickedButtonCiOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog m_fileDlg( TRUE, L"dat", L"char_info", OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, L"게임 정보 파일 (*.dat)", this );
	if( m_fileDlg.DoModal() != IDOK )
		return;

	CStdioFile m_file;
	CString m_strContent, m_strTemp;
	setlocale( LC_ALL, "korean" );
	SetDlgItemText( IDC_EDIT_CHAR_INFO, m_fileDlg.GetFileName() );
	m_file.Open( m_fileDlg.GetPathName(), CFile::modeRead );

	int m_iStart, m_iEnd, i;

	m_comboChar.Clear();
	m_comboEmot.Clear();

	for( int j=0; j<2; j++ )
	{
		m_file.ReadString( m_strContent );
	
		m_iStart = m_strContent.Find( L":" ), i = 0;
		m_strTemp = m_strContent.Mid( m_iStart );

		while( true )
		{
			m_iEnd = m_strTemp.Find( L",", 1 ) -1;

			if( m_iEnd < 0 )
				m_iEnd = m_strTemp.GetLength() - 1;

			if( j == 0 )
				m_comboChar.InsertString( i, m_strTemp.Mid( 1, m_iEnd ) );
			else
				m_comboEmot.InsertString( i, m_strTemp.Mid( 1, m_iEnd ) );
			m_strTemp = m_strTemp.Mid( m_iEnd + 1 );

			i++;

			if( m_strTemp.Find( L"," ) == -1 )
				break;
		}
	}

	m_file.Close();
}


void CGameToolDlg::OnBnClickedButtonTiOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog m_fileDlg( TRUE, L"dat", L"tile_info", OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, L"게임 정보 파일 (*.dat)", this );
	if( m_fileDlg.DoModal() != IDOK )
		return;

	CStdioFile m_file;
	CString m_strContent, m_strTemp;
	setlocale( LC_ALL, "korean" );
	SetDlgItemText( IDC_EDIT_TILE_INFO, m_fileDlg.GetFileName() );
	m_file.Open( m_fileDlg.GetPathName(), CFile::modeRead );

	TILE_INFO m_stInfo;
	int i=0;
	
	m_vTileInfo.clear();
	m_listTile.ResetContent();

	while( true )
	{
		m_file.ReadString( m_strContent );
	
		if( m_strContent.Find( L"LOCATION:" ) != -1 )
			break;

		m_stInfo.strName = m_strContent.Left( m_strContent.Find( L"," ) );
		
		if( m_strContent.Find( L",Y," ) != -1 )
			m_stInfo.bLayable = true;
		else
			m_stInfo.bLayable = false;

		if( m_strContent.Find( L",1" ) != -1 )
			m_stInfo.iLevel = 1;
		else
			m_stInfo.iLevel = 2;

		m_vTileInfo.push_back( m_stInfo );
		m_listTile.InsertString( i, m_strContent );
		i++;
	}

	m_file.Close();
	m_bIsEraseMode = false;
	m_bIsFillMode = false;
	m_bIsSetStartMode = false;

	ZeroMemory( &m_stStartInfo, sizeof( m_stStartInfo ) );

	CDC *m_pDC = m_picPreview.GetWindowDC();
	DrawMap( m_pDC );
}


void CGameToolDlg::OnBnClickedButtonCiNew()
{
	CCharInfoDlg m_childDlg;
	m_childDlg.DoModal();
}


void CGameToolDlg::OnBnClickedButtonTiNew()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CTileInfoDlg m_childDlg;
	m_childDlg.DoModal();
}


void CGameToolDlg::OnBnClickedButtonLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_listQuotes.ResetContent();
	m_iOnStartCnt = 0;
	m_iOnEndCnt = 0;
	
	CFileDialog m_fileDlg( TRUE, L"dat", L"scene", OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, L"게임 정보 파일 (*.dat)", this );

	CString m_strContent;

	QUOTE_INFO m_stTempQuoteInfo;

	m_vQuoteOnStart.clear();
	m_vQuoteOnEnd.clear();

	if( m_fileDlg.DoModal() == IDOK )
	{
		int m_iStart, m_iEnd;
		CStdioFile m_file;
		setlocale( LC_ALL, "korean" );
		m_file.Open( m_fileDlg.GetPathName(), CFile::modeRead );

		for( int i=0; m_file.ReadString( m_strContent ), m_strContent != L"END"; i++ )
		{
			m_iStart = m_strContent.Find( L" " )+1;
			m_iEnd = m_strContent.Find( '(' );
			m_stTempQuoteInfo.strChar = m_strContent.Mid( m_iStart, m_iEnd - m_iStart );

			m_iStart = m_iEnd+1;
			m_stTempQuoteInfo.strEmot = m_strContent.Mid( m_iStart, m_strContent.Find( ')' )-m_iStart );

			m_iStart = m_strContent.Find( L"):" ) + 2;
			m_stTempQuoteInfo.strQuote = m_strContent.Mid( m_iStart );

			if( m_strContent.Mid( 0, 1 ) == L"S" )
			{
				m_vQuoteOnStart.push_back( m_stTempQuoteInfo );
				m_iOnStartCnt++;
			}
			else
			{
				m_vQuoteOnEnd.push_back( m_stTempQuoteInfo );
				m_iOnEndCnt++;
			}
		}

		m_file.Read( &m_stStartInfo, sizeof( m_stStartInfo ) );
		m_file.Read( m_arrMap, sizeof( m_arrMap ) );
		m_file.Close();

		CDC *m_pDC = m_picPreview.GetWindowDC();
		DrawMap( m_pDC );
		UpdateQuoteList();
	}
}


void CGameToolDlg::OnBnClickedButtonSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if( m_listQuotes.GetCount() == 0 )
		AfxMessageBox( L"리스트에 하나 이상의 값이 필요합니다." );
	else
	{
		CFileDialog m_fileDlg( FALSE, L"dat", L"scene", OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY, L"게임 정보 파일 (*.dat)", this );

		CString m_strContent;

		if( m_fileDlg.DoModal() == IDOK )
		{
			CStdioFile m_file;
			setlocale( LC_ALL, "korean" );
			m_file.Open( m_fileDlg.GetPathName(), CFile::modeCreate|CFile::modeWrite );

			for( int i=0; i<m_listQuotes.GetCount(); i++ )
			{
				m_listQuotes.GetText(i,m_strContent);
				m_strContent = m_strContent + L"\n";
				m_file.WriteString( m_strContent );
			}

			m_file.WriteString( L"END\n" );

			m_file.Write( &m_stStartInfo, sizeof( m_stStartInfo ) );
			m_file.Write( m_arrMap, sizeof( m_arrMap ) );
			m_file.Close();
		}
	}
}

void CGameToolDlg::OnBnClickedButtonAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	QUOTE_INFO m_stTempInfo;
	int m_iCount;

	GetDlgItemText( IDC_COMBO_CHAR, m_stTempInfo.strChar );
	GetDlgItemText( IDC_COMBO_EMOT, m_stTempInfo.strEmot );
	GetDlgItemText( IDC_EDIT_QUOTE, m_stTempInfo.strQuote );

	if( ((CButton*)GetDlgItem( IDC_RADIO_START ))->GetCheck() == 1 )
	{
		m_vQuoteOnStart.push_back( m_stTempInfo );
		++m_iOnStartCnt;
		m_iCount = m_iOnStartCnt;
	}
	else
	{
		m_vQuoteOnEnd.push_back( m_stTempInfo );
		++m_iOnEndCnt;
		m_iCount = m_iOnStartCnt+m_iOnEndCnt;
	}

	UpdateQuoteList();
	m_listQuotes.SetCurSel( m_iCount-1 );
	SetDlgItemText( IDC_EDIT_QUOTE, NULL );
	(( CEdit * )GetDlgItem( IDC_EDIT_QUOTE ))->SetFocus();
}

void CGameToolDlg::OnBnClickedButtonDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if( m_listQuotes.GetCurSel() < m_iOnStartCnt )
	{
		m_vQuoteOnStart.erase( m_vQuoteOnStart.begin()+m_listQuotes.GetCurSel() );
		m_iOnStartCnt--;
	}
	else if( m_listQuotes.GetCurSel() != -1 )
	{
		m_vQuoteOnEnd.erase( m_vQuoteOnEnd.begin()+(m_listQuotes.GetCurSel()-m_iOnStartCnt) );
		m_iOnEndCnt--;
	}

	UpdateQuoteList();
}


void CGameToolDlg::OnBnClickedButtonUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	QUOTE_INFO m_stTempInfo1, m_stTempInfo2;

	if( m_listQuotes.GetCurSel() < m_iOnStartCnt && m_listQuotes.GetCurSel()-1 >= 0 )
	{
		m_stTempInfo1 = m_vQuoteOnStart.at( m_listQuotes.GetCurSel() );
		m_stTempInfo2 = m_vQuoteOnStart.at( m_listQuotes.GetCurSel()-1 );
		*(m_vQuoteOnStart.begin()+(m_listQuotes.GetCurSel()-1)) = m_stTempInfo1;
		*(m_vQuoteOnStart.begin()+( m_listQuotes.GetCurSel() )) = m_stTempInfo2;
	}
	else if( m_listQuotes.GetCurSel()-1 >= m_iOnStartCnt )
	{
		m_stTempInfo1 = m_vQuoteOnEnd.at( m_listQuotes.GetCurSel()-m_iOnStartCnt );
		m_stTempInfo2 = m_vQuoteOnEnd.at( m_listQuotes.GetCurSel()-m_iOnStartCnt-1 );
		m_vQuoteOnEnd.at( m_listQuotes.GetCurSel()-m_iOnStartCnt-1 ) = m_stTempInfo1;
		m_vQuoteOnEnd.at( m_listQuotes.GetCurSel()-m_iOnStartCnt ) = m_stTempInfo2;
	}
	UpdateQuoteList();
}

void CGameToolDlg::OnBnClickedButtonDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	QUOTE_INFO m_stTempInfo1, m_stTempInfo2;

	if( m_listQuotes.GetCurSel()+1 < m_iOnStartCnt )
	{
		m_stTempInfo1 = m_vQuoteOnStart.at( m_listQuotes.GetCurSel() );
		m_stTempInfo2 = m_vQuoteOnStart.at( m_listQuotes.GetCurSel()+1 );
		*(m_vQuoteOnStart.begin()+(m_listQuotes.GetCurSel()+1)) = m_stTempInfo1;
		*(m_vQuoteOnStart.begin()+( m_listQuotes.GetCurSel() )) = m_stTempInfo2;
	}
	else if( m_listQuotes.GetCurSel() >= m_iOnStartCnt && m_listQuotes.GetCurSel()+1 < m_vQuoteOnEnd.size()+m_iOnStartCnt )
	{
		m_stTempInfo1 = m_vQuoteOnEnd.at( m_listQuotes.GetCurSel()-m_iOnStartCnt );
		m_stTempInfo2 = m_vQuoteOnEnd.at( m_listQuotes.GetCurSel()-m_iOnStartCnt+1 );
		m_vQuoteOnEnd.at( m_listQuotes.GetCurSel()-m_iOnStartCnt+1 ) = m_stTempInfo1;
		m_vQuoteOnEnd.at( m_listQuotes.GetCurSel()-m_iOnStartCnt ) = m_stTempInfo2;
	}
	UpdateQuoteList();
}

void CGameToolDlg::OnStnClickedPreview()
{
	int m_iX, m_iY;

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if( m_listTile.GetCount() > 0 )
	{
		CDC *m_pDC = m_picPreview.GetWindowDC();
		POINT stPos;
		RECT stRect;
		(( CStatic * )GetDlgItem( IDC_PREVIEW ))->GetWindowRect( &stRect );
		::GetCursorPos( &stPos );
		stPos.x = stPos.x-stRect.left;
		stPos.y = stPos.y-stRect.top;
		m_iX = (stPos.x/24)*24;
		m_iY = (stPos.y/24)*24;

		if( m_iX < 10*24 && m_iY < 9*24 )
		{
			if( ( m_bIsEraseMode == false && m_bIsSetStartMode == false ) && ( m_listTile.GetCurSel() == -1 ) )
			{
				AfxMessageBox( L"타일을 선택해 주세요." );
				return;
			}

			if( m_bIsEraseMode == false && m_bIsFillMode == false && m_bIsSetStartMode == false )
				m_arrMap[m_vTileInfo.at( m_listTile.GetCurSel() ).iLevel-1][m_iY/24][m_iX/24] = m_listTile.GetCurSel()+1;
			else if( m_bIsEraseMode )
			{
				m_pDC->Rectangle( m_iX, m_iY, m_iX+24, m_iY+24 );
				if( m_arrMap[1][m_iY/24][m_iX/24] )
					m_arrMap[1][m_iY/24][m_iX/24] = 0;
				else
					m_arrMap[0][m_iY/24][m_iX/24] = 0;
			}
			else if( m_bIsFillMode && m_vTileInfo.at( m_listTile.GetCurSel() ).iLevel == 1 )
			{
				if( m_arrMap[0][m_iY/24][m_iX/24] == m_listTile.GetCurSel()+1 )
					Filling( m_iX/24, m_iY/24, m_arrMap[0][m_iY/24][m_iX/24], 0 );
				Filling( m_iX/24, m_iY/24, m_arrMap[0][m_iY/24][m_iX/24], m_listTile.GetCurSel()+1 );
			}
			else if( m_bIsFillMode && m_vTileInfo.at( m_listTile.GetCurSel() ).iLevel == 2 )
				AfxMessageBox( L"오브젝트는 채우기가 불가능합니다." );
			else if( m_bIsSetStartMode )
			{
				m_stStartInfo.iX = m_iX/24;
				m_stStartInfo.iY = m_iY/24;
				m_stStartInfo.iDirection = m_comboDirection.GetCurSel()+1;

				m_bIsSetStartMode = false;
				(( CButton * )GetDlgItem( IDC_CHECK_START ))->SetCheck( false );
			}
		}
		DrawMap( m_pDC );
	}
}

void CGameToolDlg::OnBnClickedCheckErase()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if( (( CButton * )GetDlgItem( IDC_CHECK_ERASE ))->GetCheck() == true )
		m_bIsEraseMode = true;
	else
		m_bIsEraseMode = false;
}

void CGameToolDlg::OnBnClickedCheckFill()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if( (( CButton * )GetDlgItem( IDC_CHECK_FILL ))->GetCheck() == true )
		m_bIsFillMode = true;
	else
		m_bIsFillMode = false;
}

void CGameToolDlg::OnBnClickedCheckStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if( (( CButton * )GetDlgItem( IDC_CHECK_START ))->GetCheck() == true )
		m_bIsSetStartMode = true;
	else
		m_bIsSetStartMode = false;
}


void CGameToolDlg::DrawMap( CDC *_pDC )
{
	CString m_strTemp;
	_pDC->SetBkMode( TRANSPARENT );
	HBRUSH m_hOriginal, m_hBrush = CreateSolidBrush( RGB( 0, 0, 0 ) );

	for( int iY=0; iY<9; iY++ )
		for( int iX=0; iX<10; iX++ )
		{
			if( m_arrMap[0][iY][iX] )
			{
				m_strTemp.Format( L"%d", m_arrMap[0][iY][iX] );

				_pDC->Rectangle( iX*24, iY*24, iX*24+24, iY*24+24 );
				_pDC->TextOut( iX*24+1, iY*24+1, m_strTemp );
			}
			else
			{
				m_hOriginal = ( HBRUSH )_pDC->SelectObject( m_hBrush );
				_pDC->Rectangle( iX*24, iY*24, iX*24+24, iY*24+24 );
				_pDC->SelectObject( m_hOriginal );
			}

			if( m_arrMap[1][iY][iX] )
			{
				m_strTemp.Format( L"%d", m_arrMap[1][iY][iX] );

				_pDC->Ellipse( iX*24+5, iY*24+5, iX*24+19, iY*24+19 );
				_pDC->TextOut( iX*24+14, iY*24+10, m_strTemp );
			}
		}

	if( m_stStartInfo.iDirection )
	{
		HBRUSH m_hOriginal, m_hBrush = CreateSolidBrush( RGB( 255, 0, 0 ) );
		m_hOriginal = ( HBRUSH )_pDC->SelectObject( m_hBrush );
		_pDC->Rectangle( m_stStartInfo.iX*24, m_stStartInfo.iY*24+24, m_stStartInfo.iX*24+10, m_stStartInfo.iY*24+24-10 );

		switch( m_stStartInfo.iDirection )
		{
		case 1:
			m_strTemp = L"▶";
			break;
		case 2:
			m_strTemp = L"◀";
			break;
		case 3:
			m_strTemp = L"▼";
			break;
		case 4:
			m_strTemp = L"▲";
			break;
		default:
			m_strTemp = L"X";
			break;
		}

		HFONT m_hOriginalFont, m_hFont = CreateFont( 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, L"SYSTEM_FIXED_FONT" );
		m_hOriginalFont = ( HFONT )_pDC->SelectObject( m_hFont );
		_pDC->TextOut( m_stStartInfo.iX*24+1, m_stStartInfo.iY*24+24-9, m_strTemp );
		_pDC->SelectObject( m_hOriginal );
		_pDC->SelectObject( m_hOriginalFont );
		DeleteObject( m_hFont );
	}
	DeleteObject( m_hBrush );
}

void CGameToolDlg::Filling( int _iX, int _iY, int _iSrc, int _iTo )
{
	if( _iY > 0 )
		if( m_arrMap[0][_iY-1][_iX] == _iSrc )
		{
			m_arrMap[0][_iY-1][_iX] = _iTo;
			Filling( _iX, _iY-1, _iSrc, _iTo );
		}
	if( _iY < 8 )
		if( m_arrMap[0][_iY+1][_iX] == _iSrc )
		{
			m_arrMap[0][_iY+1][_iX] = _iTo;
			Filling( _iX, _iY+1, _iSrc, _iTo );
		}
	if( _iX > 0 )
		if( m_arrMap[0][_iY][_iX-1] == _iSrc )
		{
			m_arrMap[0][_iY][_iX-1] = _iTo;
			Filling( _iX-1, _iY, _iSrc, _iTo );
		}
	if( _iX < 9 )
		if( m_arrMap[0][_iY][_iX+1] == _iSrc )
		{
			m_arrMap[0][_iY][_iX+1] = _iTo;
			Filling( _iX+1, _iY, _iSrc, _iTo );
		}

	m_arrMap[0][_iY][_iX] = _iTo;
}

void CGameToolDlg::OnBnClickedButtonReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ZeroMemory( m_arrMap, sizeof( m_arrMap ) );
	DrawMap(m_picPreview.GetWindowDC());
}

void CGameToolDlg::UpdateQuoteList()
{
	CString m_strContent;

	int i=0;

	m_listQuotes.ResetContent();

	for( std::vector<QUOTE_INFO>::iterator it=m_vQuoteOnStart.begin(); it!=m_vQuoteOnStart.end(); it++, i++ )
	{
		m_strContent.Format( L"S:%d %s(%s):%s", i, (*it).strChar, (*it).strEmot, (*it).strQuote );
		m_listQuotes.InsertString(i,m_strContent);
	}

	for( std::vector<QUOTE_INFO>::iterator it=m_vQuoteOnEnd.begin(); it!=m_vQuoteOnEnd.end(); it++, i++ )
	{
		m_strContent.Format( L"E:%d %s(%s):%s", i-m_iOnStartCnt, (*it).strChar, (*it).strEmot, (*it).strQuote );
		m_listQuotes.InsertString(i,m_strContent);
	}
}
