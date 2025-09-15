// CUSERDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "TS_WR_HS_FUSING.h"
#include "TS_WR_HS_FUSINGDlg.h"
#include "afxdialogex.h"
#include "CUSERDlg.h"



// CUSERDlg 대화 상자

IMPLEMENT_DYNAMIC(CUSERDlg, CDialogEx)

CUSERDlg::CUSERDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USER_LOGIN, pParent)
{

}

CUSERDlg::~CUSERDlg()
{
}

void CUSERDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STT_UI_IMAGE, CtrlLogin);
	DDX_Control(pDX, IDC_EDT_MODELSEARCH, m_nLoginID);
}


BEGIN_MESSAGE_MAP(CUSERDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_LOGIN, &CUSERDlg::OnBnClickedBtnLogin)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CUSERDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_pApp = (CTS_WR_HS_FUSINGApp*)AfxGetApp();
	lpSysInfo = m_pApp->GetSystemInfo();

	fucDrawLogin();
	Lf_InitColorBrush();
	Lf_InitFontset();

	return TRUE;
}

void CUSERDlg::Lf_InitFontset()
{
	m_Font[0].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[1].CreateFont(44, 20, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_STT_UI_USERID_TITLE)->SetFont(&m_Font[1]);

	m_Font[2].CreateFont(32, 14, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_EDT_MODELSEARCH)->SetFont(&m_Font[2]);

	m_Font[3].CreateFont(26, 12, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
	GetDlgItem(IDC_BTN_LOGIN)->SetFont(&m_Font[3]);

	m_Font[4].CreateFont(19, 8, 0, 0, FW_BOLD, TRUE, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[5].CreateFont(16, 7, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);
}

HBRUSH CUSERDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
		if (pWnd->GetDlgCtrlID() == IDC_STT_UI_USERID_TITLE)
		{
			pDC->SetBkColor(COLOR_DARK_NAVY);
			pDC->SetTextColor(COLOR_WHITE);
			return m_Brush[COLOR_IDX_DARK_NAVY];
		}
	}

	return hbr;
}

BOOL CUSERDlg::OnEraseBkgnd(CDC* pDC)
{
	// 그냥 TRUE 반환해서 CDialogEx 기본 배경 칠하지 않음
	return TRUE;
}



void CUSERDlg::OnPaint()
{
	CPaintDC dc(this);

	CRect rect, rectOri;
	GetClientRect(&rect);
	rectOri = rect;

	// 위쪽 영역 (로그인 헤더 부분)
	rect.bottom = 60;
	dc.FillSolidRect(rect, COLOR_DARK_NAVY);

	// 아래쪽 영역 (본문 부분)
	rect.top = rect.bottom;
	rect.bottom = rectOri.bottom;
	dc.FillSolidRect(rect, COLOR_GRAY192);
}

void CUSERDlg::Lf_InitColorBrush()
{
	m_Brush[COLOR_IDX_BLACK].CreateSolidBrush(COLOR_BLACK);
	m_Brush[COLOR_IDX_WHITE].CreateSolidBrush(COLOR_WHITE);
	m_Brush[COLOR_IDX_RED].CreateSolidBrush(COLOR_RED);
	m_Brush[COLOR_IDX_GREEN].CreateSolidBrush(COLOR_GREEN);
	m_Brush[COLOR_IDX_BLUE].CreateSolidBrush(COLOR_BLUE);
	m_Brush[COLOR_IDX_SEABLUE].CreateSolidBrush(COLOR_SEABLUE);
	m_Brush[COLOR_IDX_ORANGE].CreateSolidBrush(COLOR_ORANGE);
	m_Brush[COLOR_IDX_VERDANT].CreateSolidBrush(COLOR_VERDANT);
	m_Brush[COLOR_IDX_JADEGREEN].CreateSolidBrush(COLOR_JADEGREEN);
	m_Brush[COLOR_IDX_JADEBLUE].CreateSolidBrush(COLOR_JADEBLUE);
	m_Brush[COLOR_IDX_JADERED].CreateSolidBrush(COLOR_JADERED);
	m_Brush[COLOR_IDX_LIGHT_RED].CreateSolidBrush(COLOR_LIGHT_RED);
	m_Brush[COLOR_IDX_LIGHT_GREEN].CreateSolidBrush(COLOR_LIGHT_GREEN);
	m_Brush[COLOR_IDX_LIGHT_BLUE].CreateSolidBrush(COLOR_LIGHT_BLUE);
	m_Brush[COLOR_IDX_LIGHT_ORANGE].CreateSolidBrush(COLOR_LIGHT_ORANGE);
	m_Brush[COLOR_IDX_DARK_RED].CreateSolidBrush(COLOR_DARK_RED);
	m_Brush[COLOR_IDX_DARK_ORANGE].CreateSolidBrush(COLOR_DARK_ORANGE);
	m_Brush[COLOR_IDX_GRAY128].CreateSolidBrush(COLOR_GRAY128);
	m_Brush[COLOR_IDX_GRAY224].CreateSolidBrush(COLOR_GRAY224);
	m_Brush[COLOR_IDX_BLUISH].CreateSolidBrush(COLOR_BLUISH);
	m_Brush[COLOR_IDX_DARK_BLUE].CreateSolidBrush(COLOR_DARK_BLUE);
	m_Brush[COLOR_IDX_DARK_NAVY].CreateSolidBrush(COLOR_DARK_NAVY);
}

void CUSERDlg::fucDrawLogin(void)
{
	HBITMAP lbit;
	lbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_USER_IMG));

	CtrlLogin.SetBitmap(lbit);
}


// CUSERDlg 메시지 처리기


void CUSERDlg::OnBnClickedBtnLogin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nLoginID.GetWindowTextA(lpSysInfo->m_sUserID);

	if (lpSysInfo->m_sUserID == "PM")
	{
		EndDialog(IDOK);
	}
	else
	{
		EndDialog(IDOK);
	}
	
}
