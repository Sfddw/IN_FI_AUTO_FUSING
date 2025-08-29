
// TS_WR_HS_FUSINGDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "TS_WR_HS_FUSING.h"
#include "TS_WR_HS_FUSINGDlg.h"
#include "FWupdateDlg.h"
#include "OpBoxFusing.h"
#include "SystemMenu.h"
#include "CheckModelNAme.h"
#include "SetFlicker.h"
#include "VersionInfo.h"

#include <windows.h>
#include <sql.h>
#include <sqlext.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTS_WR_HS_FUSINGDlg 대화 상자




CTS_WR_HS_FUSINGDlg::CTS_WR_HS_FUSINGDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTS_WR_HS_FUSINGDlg::IDD, pParent)
	, ctrlEdtMCLK(_T(""))
	, ctrlEdtHtotal(_T(""))
	, ctrlEdtVtotal(_T(""))
	, ctrlEdtHwidth(_T(""))
	, ctrlEdtVwidth(_T(""))
	, ctrlEdtHact(_T(""))
	, ctrlEdtVact(_T(""))
	, ctrlEdtHBP(_T(""))
	, ctrlEdtVBP(_T(""))
	, ctrlEdtHFP(_T(""))
	, ctrlEdtVFP(_T(""))
	, ctrlEdtTSEQ1(_T(""))
	, ctrlEdtTSEQ2(_T(""))
	, ctrlEdtTSEQ3(_T(""))
	, ctrlEdtTSEQ4(_T(""))
	, ctrlEdtSVCC(_T(""))
	, ctrlEdtSVDD(_T(""))
	, ctrlEdtSVBL(_T(""))
	, ctrlEdtOVCC(_T(""))
	, ctrlEdtOVBL(_T(""))
	, ctrlEdtLICC(_T(""))
	, ctrlEdtLIDD(_T(""))
	, ctrlEdtLIBL(_T(""))
	, ctrlEdtHICC(_T(""))
	, ctrlEdtHIDD(_T(""))
	, ctrlEdtHIBL(_T(""))
	, ctrlEdtLVCC(_T(""))
	, ctrlEdtLVDD(_T(""))
	, ctrlEdtLVBL(_T(""))
	, ctrlEdtHVCC(_T(""))
	, ctrlEdtHVDD(_T(""))
	, ctrlEdtHVBL(_T(""))
	, ctrlRadSeqSel(0)
	, ctrlEdtPatGray(_T(""))
	, ctrlEdtModelName(_T(""))
	, strSeqOffDinCount(_T(""))
	, ctrlEdtSVBL2(_T(""))
	, ctrlEdtOVBL2(_T(""))
	, ctrlEdtLIBL2(_T(""))
	, ctrlEdtHIBL2(_T(""))
	, ctrlEdtLVBL2(_T(""))
	, ctrlEdtHVBL2(_T(""))
	, ctrlStrCnt1(_T(""))
	, ctrlStrPwrId(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTS_WR_HS_FUSINGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_TYPE, ctrlPgType);
	DDX_Control(pDX, IDC_CMB_PIXEL, ctrlPgPixel);
	DDX_Control(pDX, IDC_CMB_BIT, ctrlPgBit);
	DDX_Control(pDX, IDC_CMB_SWAP, ctrlPgSwap);
	DDX_Control(pDX, IDC_CMB_DIVISION, ctrlPgDiv);
	DDX_Control(pDX, IDC_EDT_MCLK, ctrlPgClock);
	DDX_Control(pDX, IDC_EDT_H_TOTAL, ctrlPgHtotal);
	DDX_Control(pDX, IDC_EDT_H_WIDTH, ctrlPgHwidth);
	DDX_Control(pDX, IDC_EDT_HACTIVE, ctrlPgHactive);
	DDX_Control(pDX, IDC_EDT_HBPORCH, ctrlPgHBporch);
	DDX_Control(pDX, IDC_EDT_HFPORCH, ctrlPgHFporch);
	DDX_Control(pDX, IDC_EDT_V_TOTAL, ctrlPgVtotal);
	DDX_Control(pDX, IDC_EDT_V_WIDTH, ctrlPgVwidth);
	DDX_Control(pDX, IDC_EDT_VACTIVE, ctrlPgVactive);
	DDX_Control(pDX, IDC_EDT_VBPORCH, ctrlPgVBporch);
	DDX_Control(pDX, IDC_EDT_VFPORCH, ctrlPgVFporch);
	DDX_Control(pDX, IDC_CMB_BITSEL, ctrlIfBitSel);
	DDX_Control(pDX, IDC_CMB_LVSEL, ctrlIfLvSEL);
	DDX_Control(pDX, IDC_CMB_DFORM, ctrlIfDatForm);
	DDX_Control(pDX, IDC_CMB_PEMPH, ctrlIfPreEmph);

	DDX_Control(pDX, IDC_EDT_TSEQ1, ctrlTseq1);
	DDX_Control(pDX, IDC_EDT_TSEQ2, ctrlTseq2);
	DDX_Control(pDX, IDC_EDT_TSEQ3, ctrlTseq3);
	DDX_Control(pDX, IDC_EDT_TSEQ4, ctrlTseq4);
	DDX_Control(pDX, IDC_EDT_SVCC, ctrlSetVCC);
	DDX_Control(pDX, IDC_EDT_SVDD, ctrlSetVDD);
	DDX_Control(pDX, IDC_EDT_SVBL, ctrlSetVBL);
	DDX_Control(pDX, IDC_EDT_OVCC, ctrlOffVCC);
	DDX_Control(pDX, IDC_EDT_OVBL, ctrlOffVBL);
	DDX_Control(pDX, IDC_EDT_LICC, ctrlLICC);
	DDX_Control(pDX, IDC_EDT_LIDD, ctrlLIDD);
	DDX_Control(pDX, IDC_EDT_LIBL, ctrlLIBL);
	DDX_Control(pDX, IDC_EDT_HICC, ctrlHICC);
	DDX_Control(pDX, IDC_EDT_HIDD, ctrlHIDD);
	DDX_Control(pDX, IDC_EDT_HIBL, ctrlHIBL);
	DDX_Control(pDX, IDC_EDT_LVCC, ctrlLVCC);
	DDX_Control(pDX, IDC_EDT_LVDD, ctrlLVDD);
	DDX_Control(pDX, IDC_EDT_LVBL, ctrlLVBL);
	DDX_Control(pDX, IDC_EDT_HVCC, ctrlHVCC);
	DDX_Control(pDX, IDC_EDT_HVDD, ctrlHVDD);
	DDX_Control(pDX, IDC_EDT_HVBL, ctrlHVBL);
	DDX_Control(pDX, IDC_EDT_PAT_GRAY, ctrlPAT_Gray);
	DDX_Control(pDX, IDC_LIST_PATVIEW, m_LCctrlPtnView);
	DDX_Control(pDX, IDC_CMB_PAT_NAME, ctrlPatList);

	DDX_Text(pDX, IDC_EDT_MCLK, ctrlEdtMCLK);
	DDV_MaxChars(pDX, ctrlEdtMCLK, 7);
	DDX_Text(pDX, IDC_EDT_H_TOTAL, ctrlEdtHtotal);
	DDV_MaxChars(pDX, ctrlEdtHtotal, 5);
	DDX_Text(pDX, IDC_EDT_V_TOTAL, ctrlEdtVtotal);
	DDV_MaxChars(pDX, ctrlEdtVtotal, 5);
	DDX_Text(pDX, IDC_EDT_H_WIDTH, ctrlEdtHwidth);
	DDV_MaxChars(pDX, ctrlEdtHwidth, 4);
	DDX_Text(pDX, IDC_EDT_V_WIDTH, ctrlEdtVwidth);
	DDV_MaxChars(pDX, ctrlEdtVwidth, 4);
	DDX_Text(pDX, IDC_EDT_HACTIVE, ctrlEdtHact);
	DDV_MaxChars(pDX, ctrlEdtHact, 4);
	DDX_Text(pDX, IDC_EDT_VACTIVE, ctrlEdtVact);
	DDV_MaxChars(pDX, ctrlEdtVact, 4);
	DDX_Text(pDX, IDC_EDT_HBPORCH, ctrlEdtHBP);
	DDV_MaxChars(pDX, ctrlEdtHBP, 4);
	DDX_Text(pDX, IDC_EDT_VBPORCH, ctrlEdtVBP);
	DDV_MaxChars(pDX, ctrlEdtVBP, 4);
	DDX_Text(pDX, IDC_EDT_HFPORCH, ctrlEdtHFP);
	DDV_MaxChars(pDX, ctrlEdtHFP, 4);
	DDX_Text(pDX, IDC_EDT_VFPORCH, ctrlEdtVFP);
	DDV_MaxChars(pDX, ctrlEdtVFP, 4);

	DDX_Text(pDX, IDC_EDT_TSEQ1, ctrlEdtTSEQ1);
	DDV_MaxChars(pDX, ctrlEdtTSEQ1, 4);
	DDX_Text(pDX, IDC_EDT_TSEQ2, ctrlEdtTSEQ2);
	DDV_MaxChars(pDX, ctrlEdtTSEQ2, 4);
	DDX_Text(pDX, IDC_EDT_TSEQ3, ctrlEdtTSEQ3);
	DDV_MaxChars(pDX, ctrlEdtTSEQ3, 4);
	DDX_Text(pDX, IDC_EDT_TSEQ4, ctrlEdtTSEQ4);
	DDV_MaxChars(pDX, ctrlEdtTSEQ4, 4);
	DDX_Text(pDX, IDC_EDT_SVCC, ctrlEdtSVCC);
	DDV_MaxChars(pDX, ctrlEdtSVCC, 5);
	DDX_Text(pDX, IDC_EDT_SVDD, ctrlEdtSVDD);
	DDV_MaxChars(pDX, ctrlEdtSVDD, 4);
	DDX_Text(pDX, IDC_EDT_SVBL, ctrlEdtSVBL);
	DDV_MaxChars(pDX, ctrlEdtSVBL, 5);
	DDX_Text(pDX, IDC_EDT_OVCC, ctrlEdtOVCC);
	DDV_MaxChars(pDX, ctrlEdtOVCC, 3);
	DDX_Text(pDX, IDC_EDT_OVBL, ctrlEdtOVBL);
	DDV_MaxChars(pDX, ctrlEdtOVBL, 4);
	DDX_Text(pDX, IDC_EDT_LICC, ctrlEdtLICC);
	DDV_MaxChars(pDX, ctrlEdtLICC, 5);
	DDX_Text(pDX, IDC_EDT_LIDD, ctrlEdtLIDD);
	DDV_MaxChars(pDX, ctrlEdtLIDD, 4);
	DDX_Text(pDX, IDC_EDT_LIBL, ctrlEdtLIBL);
	DDV_MaxChars(pDX, ctrlEdtLIBL, 5);
	DDX_Text(pDX, IDC_EDT_HICC, ctrlEdtHICC);
	DDV_MaxChars(pDX, ctrlEdtHICC, 5);
	DDX_Text(pDX, IDC_EDT_HIDD, ctrlEdtHIDD);
	DDV_MaxChars(pDX, ctrlEdtHIDD, 4);
	DDX_Text(pDX, IDC_EDT_HIBL, ctrlEdtHIBL);
	DDV_MaxChars(pDX, ctrlEdtHIBL, 5);
	DDX_Text(pDX, IDC_EDT_LVCC, ctrlEdtLVCC);
	DDV_MaxChars(pDX, ctrlEdtLVCC, 5);
	DDX_Text(pDX, IDC_EDT_LVDD, ctrlEdtLVDD);
	DDV_MaxChars(pDX, ctrlEdtLVDD, 4);
	DDX_Text(pDX, IDC_EDT_LVBL, ctrlEdtLVBL);
	DDV_MaxChars(pDX, ctrlEdtLVBL, 5);
	DDX_Text(pDX, IDC_EDT_HVCC, ctrlEdtHVCC);
	DDV_MaxChars(pDX, ctrlEdtHVCC, 5);
	DDX_Text(pDX, IDC_EDT_HVDD, ctrlEdtHVDD);
	DDV_MaxChars(pDX, ctrlEdtHVDD, 4);
	DDX_Text(pDX, IDC_EDT_HVBL, ctrlEdtHVBL);
	DDV_MaxChars(pDX, ctrlEdtHVBL, 5);
	DDX_Radio(pDX, IDC_SEQ1_SEL, ctrlRadSeqSel);
	DDX_Text(pDX, IDC_EDT_PAT_GRAY, ctrlEdtPatGray);
	DDV_MaxChars(pDX, ctrlEdtPatGray, 4);
	DDX_Text(pDX, IDC_EDT_MODEL, ctrlEdtModelName);
	DDV_MaxChars(pDX, ctrlEdtModelName, 32);
	DDX_Control(pDX, IDC_CMB_MODEL_NAME, ctrlSelModelName);
	DDX_Control(pDX, IDC_CMB_GP1, ctrlGPIO1);
	DDX_Control(pDX, IDC_CMB_GP2, ctrlGPIO2);
	DDX_Control(pDX, IDC_CMB_GP3, ctrlGPIO3);
	DDX_Control(pDX, IDC_CMB_GP4, ctrlGPIO4);
	DDX_Control(pDX, IDC_CMB_GP5, ctrlGPIO5);
	DDX_Control(pDX, IDC_CMB_GP6, ctrlGPIO6);
	DDX_Control(pDX, IDC_CMB_GP7, ctrlGPIO7);
	DDX_Control(pDX, IDC_CMB_GP8, ctrlGPIO8);
	DDX_Control(pDX, IDC_CMB_COMPORT, ctrlComPort);
	DDX_Control(pDX, IDC_CMB_1ST_PTN, ctrl1StPtnSel);
	DDX_Text(pDX, IDC_EDT_SEQOFF_COUNT, strSeqOffDinCount);
	DDV_MaxChars(pDX, strSeqOffDinCount, 2);
	DDX_Control(pDX, IDC_LOGO, CtrlLogo);
	DDX_Control(pDX, IDC_CMB_COPEN, ctrlCopenchk);
	DDX_Text(pDX, IDC_EDT_SVBL2, ctrlEdtSVBL2);
	DDV_MaxChars(pDX, ctrlEdtSVBL2, 5);
	DDX_Text(pDX, IDC_EDT_OVBL2, ctrlEdtOVBL2);
	DDV_MaxChars(pDX, ctrlEdtOVBL2, 5);
	DDX_Text(pDX, IDC_EDT_LIBL2, ctrlEdtLIBL2);
	DDX_Text(pDX, IDC_EDT_HIBL2, ctrlEdtHIBL2);
	DDV_MaxChars(pDX, ctrlEdtHIBL2, 5);
	DDV_MaxChars(pDX, ctrlEdtLIBL2, 5);
	DDX_Text(pDX, IDC_EDT_LVBL2, ctrlEdtLVBL2);
	DDV_MaxChars(pDX, ctrlEdtLVBL2, 5);
	DDX_Text(pDX, IDC_EDT_HVBL2, ctrlEdtHVBL2);
	DDV_MaxChars(pDX, ctrlEdtHVBL2, 5);
	DDX_Control(pDX, IDC_CMB_PWR_TYP, ctrlPwrType);
	DDX_Text(pDX, IDC_EDT_STR_CNT1, ctrlStrCnt1);
	DDV_MaxChars(pDX, ctrlStrCnt1, 2);
	DDX_Text(pDX, IDC_EDT_STR_CNT2, ctrlStrCnt2);
	DDV_MaxChars(pDX, ctrlStrCnt2, 2);
	DDX_Text(pDX, IDC_EDT_STR_PWR_ID, ctrlStrPwrId);
	DDV_MaxChars(pDX, ctrlStrPwrId, 2);
}

BEGIN_MESSAGE_MAP(CTS_WR_HS_FUSINGDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_RS232_RECEIVE1, OnRs232Receive1)
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CTS_WR_HS_FUSINGDlg::OnBnClickedBtnClose)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PATVIEW, &CTS_WR_HS_FUSINGDlg::OnLvnItemchangedListPatview)
	ON_BN_CLICKED(IDC_BTN_PAT_ADD, &CTS_WR_HS_FUSINGDlg::OnBnClickedBtnPatAdd)
	ON_BN_CLICKED(IDC_BTN_PAT_DEL, &CTS_WR_HS_FUSINGDlg::OnBnClickedBtnPatDel)
	ON_BN_CLICKED(IDC_BTN_PAT_CHG, &CTS_WR_HS_FUSINGDlg::OnBnClickedBtnPatChg)
	ON_BN_CLICKED(IDC_BTN_PAT_UP, &CTS_WR_HS_FUSINGDlg::OnBnClickedBtnPatUp)
	ON_BN_CLICKED(IDC_BTN_PAT_DN, &CTS_WR_HS_FUSINGDlg::OnBnClickedBtnPatDn)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CTS_WR_HS_FUSINGDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_FUSING, &CTS_WR_HS_FUSINGDlg::OnBnClickedBtnFusing)
	ON_CBN_SELCHANGE(IDC_CMB_MODEL_NAME, &CTS_WR_HS_FUSINGDlg::OnCbnSelchangeCmbModelName)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_SAVEAS, &CTS_WR_HS_FUSINGDlg::OnBnClickedBtnSaveas)
	ON_BN_CLICKED(IDC_BTN_PORT_OPEN, &CTS_WR_HS_FUSINGDlg::OnBnClickedBtnPortOpen)
	ON_BN_CLICKED(IDC_BTN_FW_UPDATE, &CTS_WR_HS_FUSINGDlg::OnBnClickedBtnFwUpdate)
	ON_BN_CLICKED(IDC_BTN_OPBOX, &CTS_WR_HS_FUSINGDlg::OnBnClickedBtnOpbox)
	ON_BN_CLICKED(IDC_BTN_SYSTEM_MENU, &CTS_WR_HS_FUSINGDlg::OnBnClickedBtnSystemMenu)
	ON_BN_CLICKED(IDC_BUTTON_FLICKER, &CTS_WR_HS_FUSINGDlg::OnBnClickedButtonFlicker)
	ON_BN_CLICKED(IDC_BUTTON2, &CTS_WR_HS_FUSINGDlg::OnBnClickedButton2)
	ON_STN_CLICKED(IDC_LOGO, &CTS_WR_HS_FUSINGDlg::OnStnClickedLogo)
END_MESSAGE_MAP()


// CTS_WR_HS_FUSINGDlg 메시지 처리기
LRESULT CTS_WR_HS_FUSINGDlg::OnRs232Receive1(WPARAM wParam, LPARAM lParam)
{
	m_pApp->Rs232_setReceivePacket((char*)wParam);

	if(m_pApp->m_b232IsReceiveACK == TRUE)
	{

	}

	return (0);
}


BOOL CTS_WR_HS_FUSINGDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	//lpModelInfo	= new MODEL_INFO;
	m_pApp = (CTS_WR_HS_FUSINGApp*)AfxGetApp();
	lpModelInfo	= m_pApp->GetModelInfo();

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	initControl();

	/* 타이틀 텍스트 설정 */
	CString windowText = _T("TS_MA_HS_FUSING_v");
	CString version;
	CVersionInfo::GetVersionInfo(version);
	windowText.Append(version);
	SetWindowTextA(windowText);

	return FALSE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTS_WR_HS_FUSINGDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

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
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTS_WR_HS_FUSINGDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTS_WR_HS_FUSINGDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CTS_WR_HS_FUSINGDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(nIDEvent == 10)
	{

	}

	CDialog::OnTimer(nIDEvent);
}

BOOL CTS_WR_HS_FUSINGDlg::PreTranslateMessage(MSG* pMsg)
{
	// Alt+F4 방지
	if (pMsg->message == WM_SYSKEYDOWN && pMsg->wParam == VK_F4)
	{
		if (::GetKeyState(VK_MENU) < 0) return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN) // 키 입력 로직 추가
	{
		CString msg;
		msg.Format(_T("key: %d, msg: %d, hwnd: 0x%08X"), pMsg->wParam, pMsg->message, (DWORD_PTR)pMsg->hwnd);
		OutputDebugString(msg + _T("\n"));
		switch (pMsg->wParam)
		{
		//case 'S':
		//	//m_bSavePressed = true;  // S 키가 먼저 눌림
		//	return TRUE;

		case VK_RETURN: // 엔터키 입력시
			funcBarcodeScan();
			m_strKeyBuffer = _T("");
			return TRUE;

		case VK_ESCAPE:
		case VK_SPACE:
			return TRUE;

		default:
		{
			TCHAR ch = (TCHAR)pMsg->wParam;
			if (_istprint(ch))
			{
				m_strKeyBuffer.AppendChar(ch);
			}
		}
		return TRUE;
		}
	}
	else if (pMsg->message == WM_KEYUP)
	{
		//if (pMsg->wParam == 'S')
		//	m_bSavePressed = false;  // S 키 뗐을 때도 초기화 가능
	}

	return CDialog::PreTranslateMessage(pMsg);
}

HBRUSH CTS_WR_HS_FUSINGDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if ( GetDlgItem(IDC_EDT_MODEL)->GetSafeHwnd() == pWnd->m_hWnd )
	{
		pDC->SetBkColor(COLOR_GRAY224);
		pDC->SetTextColor(COLOR_BLUE);
		return mHbr;
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

bool CTS_WR_HS_FUSINGDlg::funcBarcodeScan() // 바코드 스캔
{
		CEdit* pEdit_Pn = (CEdit*)GetDlgItem(IDC_EDIT_PN); // 파트넘버 text
		CEdit* pEdit_Model = (CEdit*)GetDlgItem(IDC_EDIT_MODEL_NAME); // 모델명 text
		pEdit_Pn->SetWindowText(_T(""));

		pEdit_Pn->SetWindowText(_T(m_strKeyBuffer));
		CString Model_Name = OnCbnSelchangeCmbModelName(m_strKeyBuffer);
		pEdit_Model->SetWindowText(Model_Name);

		return true;
		/*if (Model_Name == _T(""))
		{
			CString msg;
			msg.Format(_T("There is no Matching Model Name"));
			AfxMessageBox(msg);
			return false;
		}
		else
		{
			COpBoxFusing Cof;
			Cof.OnBnBcrScanFusing(Model_Name);
			return true;
		}*/
}

void CTS_WR_HS_FUSINGDlg::OnCbnSelchangeCmbModelName() // 모델 변경시 나머지 값들 셋팅 해주는 함수
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strGetModelName=_T("");

	funcModelEditReadOnly(TRUE);

	GetDlgItemText(IDC_CMB_MODEL_NAME, strGetModelName);

	ctrlEdtModelName.Format("%s", strGetModelName.GetBuffer(0));

	/* 모델 파일 선택시 해당 모델 LOAD 할 것. */
	funcLoadVariFromModelFile(ctrlEdtModelName.GetBuffer(0));

	funcLoadCtrlFormVari();
	UpdateData(FALSE);

	/* 패턴 목록을 갱신 한다. */
	funcUpdatePAT_List();
	UpdateData(FALSE);
}

CString CTS_WR_HS_FUSINGDlg::OnCbnSelchangeCmbModelName(CString Model_Name) // 바코드 스캔시 모델명 변경 후 셋팅 해주는 함수 (여기에 fusing 기능 추가 필요)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString M_Name;

	BarcodeInfo info = FindDataInDB(Model_Name);

	M_Name = info.name;

	/*if (Model_Name == "EAJ64811801")
	{
		M_Name = "07HC650DQG-ABXA2-A111";
	}
	else if (Model_Name == "EAJ65329801")
	{
		M_Name = "05_HC430DUN-ABXL1_3";
	}
	else if (Model_Name == "EAJ65329001")
	{
		M_Name = "01_HC55EQH-SLHA1";
	}
	else if (Model_Name == "EAJ65863901")
	{
		M_Name = "10_HC430DGG-ABWL1(BOE)";
	}
	else if (Model_Name == "EAJ64811908")
	{
		M_Name = "06_HC430DUN-ABTL1_5_7(BOE)";
	}
	else if (Model_Name == "EAJ64811911")
	{
		M_Name = "65QNED";
	}
	else if (Model_Name == "EAJ65329210")
	{
		M_Name = "22_HC500DQG-SLDA_1_3(LGD)";
	}
	else if (Model_Name == "EAJ65288601")
	{
		M_Name = "23_HC500DQG-VKDA(HKC)";
	}
	else if (Model_Name == "EAJ65740101")
	{
		M_Name = "24_HC500DQG-VKFL_1";
	}
	else if (Model_Name == "EAJ65740201")
	{
		M_Name = "25_HC500DQG-VKXL(A)1_3(HKC)";
	}
	else if (Model_Name == "EAJ65794101")
	{
		M_Name = "26_HC550DQG-ABDA_1_3(BOE)";
	}
	else if (Model_Name == "EAJ65794201")
	{
		M_Name = "39_HC700DQG-VHDA_1DDD";
	}*/

	if (M_Name == _T(""))
	{
		return _T("");
	}
	else
	{
		bool bFound = false;
		for (int i = 0; i < modelList.GetCount(); i++) // 모델리스트 처음부터 길이만큼 반복
		{
			if (M_Name.Compare(modelList[i]) == 0)
			{
				bFound = true;
				break;
			}
		}

		if (bFound == false) // 모델 리스트에 MES로 받은 모델명이 없을 경우
		{
			//return _T("");
			CString msg;
			msg.Format(_T("There is no Matching Model Name"));
			AfxMessageBox(msg);

			return M_Name;
		}
		else
		{

			funcModelEditReadOnly(TRUE);

			//GetDlgItemText(IDC_CMB_MODEL_NAME, M_Name);

			ctrlEdtModelName.Format("%s", M_Name.GetBuffer(0));

			/* 모델 파일 선택시 해당 모델 LOAD 할 것. */
			funcLoadVariFromModelFile(ctrlEdtModelName.GetBuffer(0));

			funcLoadCtrlFormVari();
			UpdateData(FALSE);

			/* 패턴 목록을 갱신 한다. */
			funcUpdatePAT_List();
			UpdateData(FALSE);

			COpBoxFusing Op_Fusing;
			Op_Fusing.OnBnBcrScanFusing(M_Name);

			return M_Name;
		}
	}
}

void CTS_WR_HS_FUSINGDlg::OnBnClickedBtnSave() // 세이브 버튼 클릭
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString strModelFile=_T("");

	funcModelEditReadOnly(TRUE);
	
	/* 컨트롤의 값을 변수로 저장 한다. */
	funcSaveCtrlToVari();

	/* 변수의 값을 모델 파일로 저장 한다. */
	strModelFile = ctrlEdtModelName;
	funcSaveVariToModelFile(strModelFile.GetBuffer(0));

	/* 모델 파일 선택시 해당 모델 LOAD 한다. */
	funcLoadVariFromModelFile(ctrlEdtModelName.GetBuffer(0));

	/* 변수의 값을 컨트롤에 적용 한다.*/
	funcLoadCtrlFormVari();
	UpdateData(FALSE);

	/* 패턴 목록을 갱신 한다. */
	funcUpdatePAT_List();

	/* 모델 목록을 갱신 한다. */
	funcUpdateModel_List();

	UpdateData(FALSE);

}

void CTS_WR_HS_FUSINGDlg::OnBnClickedBtnFusing()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//execGetVersionCheck();

	OnBnClickedBtnSave();

	if(m_pApp->m_b232Open == FALSE)
	{
		AfxMessageBox("Fusing FAIL. Comport is not Opened.", MB_ICONERROR|MB_OK);
		return;
	}

	if(execSystemFusing() == 0)
	{
		/* 2019.04.02. KSM. 1st 패턴 삭제. */
		//Sleep(100);
		//exec1stPatternFusing();

		Sleep(100);
		execPatternFusing();

		Sleep(100);
		execControlIOFusing();

		AfxMessageBox("Fusing Success.", MB_ICONINFORMATION|MB_OK);
	}
}


void CTS_WR_HS_FUSINGDlg::OnBnClickedBtnClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnCancel();
}

void CTS_WR_HS_FUSINGDlg::OnLvnItemchangedListPatview(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(pNMListView->iItem < 0)
		return;
	if(pNMListView->uOldState && !pNMListView->uNewState)
		return;
	if(!pNMListView->uOldState && !pNMListView->uNewState) // 0, 0
		return;

	*pResult = 0;
	fucPtnDataChange(pNMListView->iItem);
	*pResult = 0;
}

void CTS_WR_HS_FUSINGDlg::fucInsertListColum()
{
	CRect rect,rect2;
	m_LCctrlPtnView.GetClientRect(&rect);
	m_LCctrlPtnView.InsertColumn( 0, "PATTERN NAME", LVCFMT_LEFT, -1, -1 );
	m_LCctrlPtnView.InsertColumn( 1, "FG", LVCFMT_LEFT, -1, -1 );

	m_LCctrlPtnView.SetColumnWidth( 0, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER ); // Pattern
	GetDlgItem(IDC_STT_PAT_NAME)->GetWindowRect(&rect2);
	m_LCctrlPtnView.SetColumnWidth( 0, rect2.Width()-3);

	m_LCctrlPtnView.SetColumnWidth( 1, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER ); // FG
	GetDlgItem(IDC_STT_PAT_GRAY)->GetWindowRect(&rect2);
	m_LCctrlPtnView.SetColumnWidth( 1, rect2.Width()-19);

	DWORD dwStype = m_LCctrlPtnView.GetExtendedStyle(); // CListCtrl::
	dwStype |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	m_LCctrlPtnView.SetExtendedStyle(dwStype); // CListCtrl::
}

void CTS_WR_HS_FUSINGDlg::fucPdbDelete(char *szBuff)
{
	CharUpper (szBuff);
	char* pos, *pos2=NULL;
	do
	{
		pos = strrchr (szBuff, '.');
		if (pos == pos2)
			return;
		pos2 = pos;
		if (NULL == pos)
			return;
		if (!strcmp (pos, ".PDB"))
			*pos = NULL;
	} while (1);
}

void CTS_WR_HS_FUSINGDlg::fucAllPtnList(void)
{

	char Datafolder[256];

	m_pComboInternal = (CComboBox* ) GetDlgItem(IDC_CMB_PAT_NAME); // Aging Pattern
	//m_pCmb1stPtn = (CComboBox* ) GetDlgItem(IDC_CMB_1ST_PTN);		/* 2019.04.02. KSM. 1st 패턴 삭제. */

	WIN32_FIND_DATA wfd;
	HANDLE hSearch;


	sprintf (Datafolder, ".\\PATTERN\\*.pdb", "Data");

	hSearch = FindFirstFile (Datafolder, &wfd);

	if (hSearch != INVALID_HANDLE_VALUE)
	{
		if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		{
			fucPdbDelete ((LPSTR)(LPCTSTR)wfd.cFileName);
			m_pComboInternal->AddString (wfd.cFileName);
			//m_pCmb1stPtn->AddString (wfd.cFileName);
		}
		while (FindNextFile (hSearch, &wfd))
		{
			if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				fucPdbDelete ((LPSTR)(LPCTSTR)wfd.cFileName);
				m_pComboInternal->AddString (wfd.cFileName);
				//m_pCmb1stPtn->AddString (wfd.cFileName);
			}
		}
		FindClose (hSearch);
	}
	else
	{
	}

	ctrlPatList.SetCurSel(0);
}

void CTS_WR_HS_FUSINGDlg::fucPtnDataChange(int sel)
{
	UpdateData(TRUE);

	int nAllpattern = 0;

	CString temp, temp2;
	char sztemp[30] = {0,};
	char szCompare[30] = {0,};

	m_LCctrlPtnView.GetItemText( sel, 0, sztemp, 30);
	nAllpattern = ctrlPatList.FindStringExact(nAllpattern, sztemp);
	if(nAllpattern == CB_ERR)
	{
		AfxMessageBox("Pattern File is not exist.", MB_OK);

		return;
	}


	ctrlPatList.SetCurSel(nAllpattern);

	m_LCctrlPtnView.GetItemText(sel, 1, sztemp, 30);

	CString strTemp=_T("");
	strTemp.Format("%s", sztemp);
	ctrlEdtPatGray=strTemp;

	UpdateData(FALSE);
}


void CTS_WR_HS_FUSINGDlg::fuc1stPtnDataChange(void)
{
	UpdateData(TRUE);

	CString temp;
	char sztemp[30] = {0,};
	int nAllpattern = 0;

	sprintf(sztemp, "%s", lpModelInfo->sz1stPtnName);

	nAllpattern = ctrl1StPtnSel.FindStringExact(nAllpattern, sztemp);
	if(nAllpattern == CB_ERR)
	{
		AfxMessageBox("1st Pattern File is not exist.", MB_OK);

		return;
	}

	ctrl1StPtnSel.SetCurSel(nAllpattern);
}

void CTS_WR_HS_FUSINGDlg::fucDrawLogo(void)
{
	HBITMAP hbit;
	hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_LOGO));

	CtrlLogo.SetBitmap(hbit);
}



void CTS_WR_HS_FUSINGDlg::OnBnClickedBtnPatAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nFgValue;
	int nPos, nCnt;
	CString strTemp;
	int nBitTemp;

	UpdateData(TRUE);

	GetDlgItemText(IDC_EDT_PAT_GRAY, strTemp);
	nFgValue=atoi(strTemp);
	
	nBitTemp = SIG_10BIT;
	switch(nBitTemp)
	{
	case SIG_6BIT:
		if(nFgValue>63)
		{
			AfxMessageBox("SET 6Bit, Range[0 ~ 63]", MB_OK);
			return;
		}break;

	case SIG_8BIT:
		if(nFgValue>255)
		{
			AfxMessageBox("SET 8Bit, Range[0 ~ 255]", MB_OK);
			return;
		}break;

	case SIG_10BIT:
		if(nFgValue>1023)
		{
			AfxMessageBox("SET 10Bit, Range[0 ~ 1023]", MB_OK);
			return;
		}break;
	}

	UpdateData(TRUE);

	nCnt = m_LCctrlPtnView.GetItemCount();

	POSITION Pos = m_LCctrlPtnView.GetFirstSelectedItemPosition();
	nPos = m_LCctrlPtnView.GetNextSelectedItem(Pos);

	if(nPos < 0)
	{
		nPos = nCnt;
	}

	ctrlPatList.GetWindowText(strTemp);
	m_LCctrlPtnView.InsertItem(nPos, strTemp);

	GetDlgItemText(IDC_EDT_PAT_GRAY, strTemp);
	m_LCctrlPtnView.SetItem(nPos, 1, LVIF_TEXT, strTemp, 0, LVIF_STATE, 0, 0);

	m_LCctrlPtnView.SetSelectionMark(nPos); // Item Select & Focus
	m_LCctrlPtnView.SetItemState(nPos, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);

	UpdateData(FALSE);
}

void CTS_WR_HS_FUSINGDlg::OnBnClickedBtnPatDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION Pos = m_LCctrlPtnView.GetFirstSelectedItemPosition();
	int nPos = m_LCctrlPtnView.GetNextSelectedItem(Pos);
	if(nPos < 0)
	{
		return;
	}

	m_LCctrlPtnView.DeleteItem(nPos);

	if(!m_LCctrlPtnView.GetItemCount())
	{
		//fucAgingPtnSizeUpdate();
		return;
	}
	else
	{
		if (m_LCctrlPtnView.GetItemCount() <= nPos)
			nPos--;

		m_LCctrlPtnView.SetSelectionMark(nPos); // --position); // 2007-09-12 : Item Select & Focus
		m_LCctrlPtnView.SetItemState(nPos, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
		m_LCctrlPtnView.SetFocus();
	}
	UpdateData(TRUE);
	//fucAgingPtnSizeUpdate();
}

void CTS_WR_HS_FUSINGDlg::OnBnClickedBtnPatChg()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nFgValue;
	int nPos;
	CString strTemp;
	int nBitTemp;

	UpdateData(TRUE);

	GetDlgItemText(IDC_EDT_PAT_GRAY, strTemp);
	nFgValue=atoi(strTemp);

	nBitTemp = SIG_10BIT;
	switch(nBitTemp)
	{
	case SIG_6BIT:
		if(nFgValue>63)
		{
			AfxMessageBox("SET 6Bit, Range[0 ~ 63]", MB_OK);
			return;
		}
		break;
	case SIG_8BIT:
		if(nFgValue>255)
		{
			AfxMessageBox("SET 8Bit, Range[0 ~ 255]", MB_OK);
			return;
		}
		break;

	case SIG_10BIT:
		if(nFgValue>1023)
		{
			AfxMessageBox("SET 10Bit, Range[0 ~ 1023]", MB_OK);
			return;
		}
		break;
	}

	POSITION pos = m_LCctrlPtnView.GetFirstSelectedItemPosition();
	nPos = m_LCctrlPtnView.GetNextSelectedItem(pos);
	if(nPos < 0)
	{
		return;
	}
	int x = ctrlPatList.GetCurSel();

	ctrlPatList.GetLBText(ctrlPatList.GetCurSel(),strTemp);
	m_LCctrlPtnView.SetItem( nPos, 0, LVIF_TEXT, strTemp, 0, LVIF_STATE, 0, 0);

	GetDlgItemText(IDC_EDT_PAT_GRAY, strTemp);
	m_LCctrlPtnView.SetItem( nPos, 1, LVIF_TEXT, strTemp, 0, LVIF_STATE, 0, 0);

	m_LCctrlPtnView.EnsureVisible( nPos, FALSE);

	m_LCctrlPtnView.SetSelectionMark(nPos); // 2007-09-12 : Item Select & Focus
	m_LCctrlPtnView.SetItemState(nPos, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);

	//fucAgingPtnSizeUpdate();
}

void CTS_WR_HS_FUSINGDlg::OnBnClickedBtnPatUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	POSITION pos = m_LCctrlPtnView.GetFirstSelectedItemPosition();
	int position = m_LCctrlPtnView.GetNextSelectedItem(pos);
	if(position < 1)
	{
		return;
	}

	fucListCtrlSwapData(position, position-1);

	m_LCctrlPtnView.SetSelectionMark(position); // Item Select & Focus
	m_LCctrlPtnView.SetItemState(position-1, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
	m_LCctrlPtnView.SetFocus();

	UpdateData(FALSE);
}

void CTS_WR_HS_FUSINGDlg::OnBnClickedBtnPatDn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	POSITION pos = m_LCctrlPtnView.GetFirstSelectedItemPosition();
	int position = m_LCctrlPtnView.GetNextSelectedItem(pos);
	int count = m_LCctrlPtnView.GetItemCount();

	if(position > (count-2))
	{
		return;
	}
	fucListCtrlSwapData(position, position+1);

	m_LCctrlPtnView.SetSelectionMark(position); // 2007-09-12 : Item Select & Focus
	m_LCctrlPtnView.SetItemState(position+1, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
	m_LCctrlPtnView.SetFocus();

	UpdateData(FALSE);
}

void CTS_WR_HS_FUSINGDlg::OnBnClickedBtnSaveas()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ctrlEdtModelName.Empty();
	GetDlgItem(IDC_EDT_MODEL)->SetFocus();

	funcModelEditReadOnly(FALSE);

	UpdateData(FALSE);

}



void CTS_WR_HS_FUSINGDlg::fucListCtrlSwapData(int pos1, int pos2)
{
	UpdateData(TRUE);

	char temp1 [64] = {0,};
	char temp2 [64] = {0,};
	int i = 0;

	for(i=0;i<2;i++)
	{
		m_LCctrlPtnView.GetItemText(pos1, i, temp1, 30);
		m_LCctrlPtnView.GetItemText(pos2, i, temp2, 30);
		m_LCctrlPtnView.SetItem( pos2, i, LVIF_TEXT, temp1, 0, LVIF_STATE, 0, 0);
		m_LCctrlPtnView.SetItem( pos1, i, LVIF_TEXT, temp2, 0, LVIF_STATE, 0, 0);
	}

	POSITION pos = m_LCctrlPtnView.GetFirstSelectedItemPosition();
	int position = m_LCctrlPtnView.GetNextSelectedItem(pos);

	UpdateData(FALSE);
}

void CTS_WR_HS_FUSINGDlg::funcDefaultTimmingLoad(void)
{
	/* Resolution default Load */
	ctrlPgPixel.SetCurSel(PIX_OCTA);
	ctrlPgSwap.SetCurSel(3);

	ctrlEdtMCLK.Format("594.00");

	ctrlEdtHtotal.Format("4400");
	ctrlEdtHwidth.Format("160");
	ctrlEdtHact.Format("3840");
	ctrlEdtHBP.Format("80");
	ctrlEdtHFP.Format("320");

	ctrlEdtVtotal.Format("2250");
	ctrlEdtVwidth.Format("10");
	ctrlEdtVact.Format("2160");
	ctrlEdtVBP.Format("30");
	ctrlEdtVFP.Format("50");
}

void CTS_WR_HS_FUSINGDlg::funcDefaultIFLoad(void)
{
	ctrlPgType.SetCurSel(1);
	ctrlPgBit.SetCurSel(SIG_10BIT);
	ctrlIfBitSel.SetCurSel(1);
	ctrlIfLvSEL.SetCurSel(1);
	ctrlIfDatForm.SetCurSel(0);
	ctrlPgDiv.SetCurSel(0);
	ctrlIfPreEmph.SetCurSel(1);

	ctrlGPIO1.SetCurSel(0);
	ctrlGPIO2.SetCurSel(0);
	ctrlGPIO3.SetCurSel(0);
	ctrlGPIO4.SetCurSel(0);
	ctrlGPIO5.SetCurSel(0);
	ctrlGPIO6.SetCurSel(0);
	ctrlGPIO7.SetCurSel(0);
	ctrlGPIO8.SetCurSel(0);

}

void CTS_WR_HS_FUSINGDlg::funcDefaultPWRLoad(void)
{
	ctrlRadSeqSel = 0;

	ctrlEdtTSEQ1.Format("100");
	ctrlEdtTSEQ2.Format("50");
	ctrlEdtTSEQ3.Format("200");
	ctrlEdtTSEQ4.Format("500");

	ctrlEdtSVCC.Format("12.0");
	ctrlEdtSVDD.Format("3.3");
	ctrlEdtSVBL.Format("24.0");

	ctrlEdtOVCC.Format("0.0");
	ctrlEdtOVBL.Format("0.0");

	ctrlEdtLICC.Format("0");
	ctrlEdtLIDD.Format("0");
	ctrlEdtLIBL.Format("0");

	ctrlEdtHICC.Format("3000");
	ctrlEdtHIDD.Format("500");
	ctrlEdtHIBL.Format("5000");

	ctrlEdtLVCC.Format("0.0");
	ctrlEdtLVDD.Format("0.0");
	ctrlEdtLVBL.Format("0.0");

	ctrlEdtHVCC.Format("14.0");
	ctrlEdtHVDD.Format("7.0");
	ctrlEdtHVBL.Format("27.0");
}

void CTS_WR_HS_FUSINGDlg::funcDefaultGray(void)
{
	int nSigBit, nMaxCol=0;

	nSigBit = ctrlPgBit.GetCurSel();

	switch(nSigBit)
	{
		case SIG_6BIT : nMaxCol = 63;		break;
		case SIG_8BIT : nMaxCol = 255;		break;
		case SIG_10BIT : nMaxCol = 1023;	break;
	}

	ctrlEdtPatGray.Format("%d", nMaxCol);
}

void CTS_WR_HS_FUSINGDlg::fucModDelete(char *szBuff)
{
	CharUpper (szBuff);
	char* pos, *pos2=NULL;
	do
	{
		pos = strrchr (szBuff, '.');
		if (pos == pos2)
			return;
		pos2 = pos;
		if (NULL == pos)
			return;
		if (!strcmp (pos, ".MOD"))
			*pos = NULL;
	} while (1);
}

void CTS_WR_HS_FUSINGDlg::fucAllModelList(void)
{
	char Datafolder[256];

	m_pComboModel = (CComboBox* ) GetDlgItem(IDC_CMB_MODEL_NAME);

	WIN32_FIND_DATA wfd;
	HANDLE hSearch;

	sprintf (Datafolder, ".\\MODEL\\*.mod");

	hSearch = FindFirstFile (Datafolder, &wfd);

	if (hSearch != INVALID_HANDLE_VALUE)
	{
		if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		{
			fucModDelete ((LPSTR)(LPCTSTR)wfd.cFileName);
			m_pComboModel->AddString (wfd.cFileName);
		}
		while (FindNextFile (hSearch, &wfd))
		{
			if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				fucModDelete ((LPSTR)(LPCTSTR)wfd.cFileName);
				m_pComboModel->AddString (wfd.cFileName);
			}
		}
		FindClose (hSearch);
	}
	else
	{
	}

	int nCount = m_pComboModel->GetCount();
	CString strModel;
	for (int i = 0; i < nCount; i++)
	{
		m_pComboModel->GetLBText(i, strModel);
		modelList.Add(strModel);  // 리스트에 모델명 추가

		// (선택) 디버그 출력
		CString strLog;
		strLog.Format(_T("모델 %d: %s\n"), i + 1, strModel);
		OutputDebugString(strLog);
	}

	ctrlSelModelName.SetCurSel(0);
}

void CTS_WR_HS_FUSINGDlg::initFontSet(void)
{
	mHbr = CreateSolidBrush(COLOR_GRAY224);
	mFontH1.CreateFont(28, 10, 0, 0, 800, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Times New Roman");
	GetDlgItem(IDC_EDT_MODEL)->SetFont(&mFontH1);
}


void CTS_WR_HS_FUSINGDlg::initControl(void)
{
	fucAllPtnList();
	fucAllModelList();

	fucInsertListColum();

	funcDefaultTimmingLoad();
	funcDefaultIFLoad();
	funcDefaultPWRLoad();
	funcDefaultGray();

	initFontSet();
	funcModelEditReadOnly(TRUE);
	
	ctrlSelModelName.SetCurSel(0);
	OnCbnSelchangeCmbModelName();

	ctrlComPort.SetCurSel(0);

	//fuc1stPtnDataChange();		/* 2019.04.02. KSM. 1st 패턴 삭제. */

	fucDrawLogo();

	GotoDlgCtrl(GetDlgItem(IDC_BTN_CLOSE));

	UpdateData(FALSE);
}

/* 모델 에디트 박스를 Read Only 로 속성 변경. */
void CTS_WR_HS_FUSINGDlg::funcModelEditReadOnly(char onoff)
{
	CWnd *pWnd = AfxGetMainWnd();
	HWND hWnd = pWnd->m_hWnd;
	HWND hEdit = ::GetDlgItem(m_hWnd, IDC_EDT_MODEL);

	SendMessageW(hEdit, EM_SETREADONLY, onoff, 0);
}

void CTS_WR_HS_FUSINGDlg::funcSaveCtrlToVari(void)
{
	UpdateData(TRUE);

	/* SAVE Resolution */
	lpModelInfo->nPixel = ctrlPgPixel.GetCurSel();
	lpModelInfo->nSwap = ctrlPgSwap.GetCurSel();
	
	lpModelInfo->fMclk = (float)atof(ctrlEdtMCLK.GetBuffer(0));

	lpModelInfo->nHtotal = atoi(ctrlEdtHtotal.GetBuffer(0));
	lpModelInfo->nHwidth = atoi(ctrlEdtHwidth.GetBuffer(0));
	lpModelInfo->nHact = atoi(ctrlEdtHact.GetBuffer(0));
	lpModelInfo->nHBP = atoi(ctrlEdtHBP.GetBuffer(0));
	lpModelInfo->nHFP = atoi(ctrlEdtHFP.GetBuffer(0));

	lpModelInfo->nVtotal = atoi(ctrlEdtVtotal.GetBuffer(0));
	lpModelInfo->nVwidth = atoi(ctrlEdtVwidth.GetBuffer(0));
	lpModelInfo->nVact = atoi(ctrlEdtVact.GetBuffer(0));
	lpModelInfo->nVBP = atoi(ctrlEdtVBP.GetBuffer(0));
	lpModelInfo->nVFP = atoi(ctrlEdtVFP.GetBuffer(0));

	/* SAVE SIGNAL */
	lpModelInfo->nSigType = ctrlPgType.GetCurSel();
	lpModelInfo->nSigBit = ctrlPgBit.GetCurSel();
	lpModelInfo->nBitSel = ctrlIfBitSel.GetCurSel();
	lpModelInfo->nLvdsSel = ctrlIfLvSEL.GetCurSel();
	lpModelInfo->nDataFormat = ctrlIfDatForm.GetCurSel();
	lpModelInfo->nPreEmph = ctrlIfPreEmph.GetCurSel();
	lpModelInfo->nDIVmode = ctrlPgDiv.GetCurSel();
	lpModelInfo->nCopenChk = ctrlCopenchk.GetCurSel();

	/* SAVE POWER */
	lpModelInfo->nSeqSel = ctrlRadSeqSel;
	lpModelInfo->nTSeq[0] = atoi(ctrlEdtTSEQ1.GetBuffer(0));
	lpModelInfo->nTSeq[1] = atoi(ctrlEdtTSEQ2.GetBuffer(0));
	lpModelInfo->nTSeq[2] = atoi(ctrlEdtTSEQ3.GetBuffer(0));
	lpModelInfo->nTSeq[3] = atoi(ctrlEdtTSEQ4.GetBuffer(0));

	lpModelInfo->fPWR_SetVOLT[0] = (float)atof(ctrlEdtSVCC.GetBuffer(0));
	lpModelInfo->fPWR_SetVOLT[1] = (float)atof(ctrlEdtSVDD.GetBuffer(0));
	lpModelInfo->fPWR_SetVOLT[2] = (float)atof(ctrlEdtSVBL.GetBuffer(0));
	lpModelInfo->fPWR_SetADD_VBL = (float)atof(ctrlEdtSVBL2.GetBuffer(0));			/* 2019.06.27. KSM. ADD.*/

	lpModelInfo->fPWR_OFFSET[0] = (float)atof(ctrlEdtOVCC.GetBuffer(0));
	lpModelInfo->fPWR_OFFSET[1] = (float)atof(ctrlEdtOVBL.GetBuffer(0));
	lpModelInfo->fPWR_SetADD_CURR = (float)atof(ctrlEdtOVBL2.GetBuffer(0));			/* 2019.06.27. KSM. ADD.*/

	lpModelInfo->nPWR_currLIMIT[LIMIT_LOW][0] = atoi(ctrlEdtLICC.GetBuffer(0));
	lpModelInfo->nPWR_currLIMIT[LIMIT_LOW][1] = atoi(ctrlEdtLIDD.GetBuffer(0));
	lpModelInfo->nPWR_currLIMIT[LIMIT_LOW][2] = atoi(ctrlEdtLIBL.GetBuffer(0));
	lpModelInfo->nPWR_AddVBL_CurrLIMIT[0]	= atoi(ctrlEdtLIBL2.GetBuffer(0));		/* 2019.06.27. KSM. ADD.*/

	lpModelInfo->nPWR_currLIMIT[LIMIT_HIGH][0] = atoi(ctrlEdtHICC.GetBuffer(0));
	lpModelInfo->nPWR_currLIMIT[LIMIT_HIGH][1] = atoi(ctrlEdtHIDD.GetBuffer(0));
	lpModelInfo->nPWR_currLIMIT[LIMIT_HIGH][2] = atoi(ctrlEdtHIBL.GetBuffer(0));
	lpModelInfo->nPWR_AddVBL_CurrLIMIT[1]	= atoi(ctrlEdtHIBL2.GetBuffer(0));			/* 2019.06.27. KSM. ADD.*/

	lpModelInfo->fPWR_voltLIMIT[LIMIT_LOW][0] = (float)atof(ctrlEdtLVCC.GetBuffer(0));
	lpModelInfo->fPWR_voltLIMIT[LIMIT_LOW][1] = (float)atof(ctrlEdtLVDD.GetBuffer(0));
	lpModelInfo->fPWR_voltLIMIT[LIMIT_LOW][2] = (float)atof(ctrlEdtLVBL.GetBuffer(0));
	lpModelInfo->fPWR_AddVBL_VoltLIMIT[0] = (float)atof(ctrlEdtLVBL2.GetBuffer(0));		/* 2019.06.27. KSM. ADD.*/

	lpModelInfo->fPWR_voltLIMIT[LIMIT_HIGH][0] = (float)atof(ctrlEdtHVCC.GetBuffer(0));
	lpModelInfo->fPWR_voltLIMIT[LIMIT_HIGH][1] = (float)atof(ctrlEdtHVDD.GetBuffer(0));
	lpModelInfo->fPWR_voltLIMIT[LIMIT_HIGH][2] = (float)atof(ctrlEdtHVBL.GetBuffer(0));
	lpModelInfo->fPWR_AddVBL_VoltLIMIT[1] = (float)atof(ctrlEdtHVBL2.GetBuffer(0));		/* 2019.06.27. KSM. ADD.*/

	lpModelInfo->nGPIO[0] = ctrlGPIO1.GetCurSel();
	lpModelInfo->nGPIO[1] = ctrlGPIO2.GetCurSel();
	lpModelInfo->nGPIO[2] = ctrlGPIO3.GetCurSel();
	lpModelInfo->nGPIO[3] = ctrlGPIO4.GetCurSel();
	lpModelInfo->nGPIO[4] = ctrlGPIO5.GetCurSel();
	lpModelInfo->nGPIO[5] = ctrlGPIO6.GetCurSel();
	lpModelInfo->nGPIO[6] = ctrlGPIO7.GetCurSel();
	lpModelInfo->nGPIO[7] = ctrlGPIO8.GetCurSel();

	lpModelInfo->nPowerSeqOffDinCount = atoi(strSeqOffDinCount.GetBuffer(0));
	if(lpModelInfo->nPowerSeqOffDinCount <= 3)		lpModelInfo->nPowerSeqOffDinCount = 4;

	lpModelInfo->nPowerType = ctrlPwrType.GetCurSel();
	lpModelInfo->nStringCount[0] = atoi(ctrlStrCnt1.GetBuffer(0));
	lpModelInfo->nStringCount[1] = atoi(ctrlStrCnt2.GetBuffer(0));
	lpModelInfo->nPowerId = atoi(ctrlStrPwrId.GetBuffer(0));
}


void CTS_WR_HS_FUSINGDlg::funcLoadCtrlFormVari(void)
{
	/* SAVE Resolution */
	ctrlPgPixel.SetCurSel(lpModelInfo->nPixel);
	ctrlPgSwap.SetCurSel(lpModelInfo->nSwap);

	ctrlEdtMCLK.Format("%.2f", lpModelInfo->fMclk);

	ctrlEdtHtotal.Format("%d", lpModelInfo->nHtotal);
	ctrlEdtHwidth.Format("%d", lpModelInfo->nHwidth);
	ctrlEdtHact.Format("%d", lpModelInfo->nHact);
	ctrlEdtHBP.Format("%d", lpModelInfo->nHBP);
	ctrlEdtHFP.Format("%d", lpModelInfo->nHFP);

	ctrlEdtVtotal.Format("%d", lpModelInfo->nVtotal);
	ctrlEdtVwidth.Format("%d", lpModelInfo->nVwidth);
	ctrlEdtVact.Format("%d", lpModelInfo->nVact);
	ctrlEdtVBP.Format("%d", lpModelInfo->nVBP);
	ctrlEdtVFP.Format("%d", lpModelInfo->nVFP);

	/* SAVE SIGNAL */
	ctrlPgType.SetCurSel(lpModelInfo->nSigType);
	ctrlPgBit.SetCurSel(lpModelInfo->nSigBit);
	ctrlIfBitSel.SetCurSel(lpModelInfo->nBitSel);
	ctrlIfLvSEL.SetCurSel(lpModelInfo->nLvdsSel);
	ctrlIfDatForm.SetCurSel(lpModelInfo->nDataFormat);
	ctrlIfPreEmph.SetCurSel(lpModelInfo->nPreEmph);
	ctrlPgDiv.SetCurSel(lpModelInfo->nDIVmode);
	ctrlCopenchk.SetCurSel(lpModelInfo->nCopenChk);

	/* SAVE POWER */
	ctrlRadSeqSel = lpModelInfo->nSeqSel;
	ctrlEdtTSEQ1.Format("%d", lpModelInfo->nTSeq[0]);
	ctrlEdtTSEQ2.Format("%d", lpModelInfo->nTSeq[1]);
	ctrlEdtTSEQ3.Format("%d", lpModelInfo->nTSeq[2]);
	ctrlEdtTSEQ4.Format("%d", lpModelInfo->nTSeq[3]);

	if(lpModelInfo->nPowerSeqOffDinCount <= 3)		lpModelInfo->nPowerSeqOffDinCount = 4;
	strSeqOffDinCount.Format("%d", lpModelInfo->nPowerSeqOffDinCount);

	ctrlEdtSVCC.Format("%.1f", lpModelInfo->fPWR_SetVOLT[0]);
	ctrlEdtSVDD.Format("%.1f", lpModelInfo->fPWR_SetVOLT[1]);
	ctrlEdtSVBL.Format("%.1f", lpModelInfo->fPWR_SetVOLT[2]);
	ctrlEdtSVBL2.Format("%.1f", lpModelInfo->fPWR_SetADD_VBL);

	ctrlEdtOVCC.Format("%.1f", lpModelInfo->fPWR_OFFSET[0]);
	ctrlEdtOVBL.Format("%.2f", lpModelInfo->fPWR_OFFSET[1]);
	ctrlEdtOVBL2.Format("%.2f", lpModelInfo->fPWR_SetADD_CURR);

	ctrlEdtLICC.Format("%d", lpModelInfo->nPWR_currLIMIT[LIMIT_LOW][0]);
	ctrlEdtLIDD.Format("%d", lpModelInfo->nPWR_currLIMIT[LIMIT_LOW][1]);
	ctrlEdtLIBL.Format("%d", lpModelInfo->nPWR_currLIMIT[LIMIT_LOW][2]);
	ctrlEdtLIBL2.Format("%d", lpModelInfo->nPWR_AddVBL_CurrLIMIT[0]);

	ctrlEdtHICC.Format("%d", lpModelInfo->nPWR_currLIMIT[LIMIT_HIGH][0]);
	ctrlEdtHIDD.Format("%d", lpModelInfo->nPWR_currLIMIT[LIMIT_HIGH][1]);
	ctrlEdtHIBL.Format("%d", lpModelInfo->nPWR_currLIMIT[LIMIT_HIGH][2]);
	ctrlEdtHIBL2.Format("%d", lpModelInfo->nPWR_AddVBL_CurrLIMIT[1]);

	ctrlEdtLVCC.Format("%.1f", lpModelInfo->fPWR_voltLIMIT[LIMIT_LOW][0]);
	ctrlEdtLVDD.Format("%.1f", lpModelInfo->fPWR_voltLIMIT[LIMIT_LOW][1]);
	ctrlEdtLVBL.Format("%.1f", lpModelInfo->fPWR_voltLIMIT[LIMIT_LOW][2]);
	ctrlEdtLVBL2.Format("%.1f", lpModelInfo->fPWR_AddVBL_VoltLIMIT[0]);

	ctrlEdtHVCC.Format("%.1f", lpModelInfo->fPWR_voltLIMIT[LIMIT_HIGH][0]);
	ctrlEdtHVDD.Format("%.1f", lpModelInfo->fPWR_voltLIMIT[LIMIT_HIGH][1]);
	ctrlEdtHVBL.Format("%.1f", lpModelInfo->fPWR_voltLIMIT[LIMIT_HIGH][2]);
	ctrlEdtHVBL2.Format("%.1f", lpModelInfo->fPWR_AddVBL_VoltLIMIT[1]);

	ctrlGPIO1.SetCurSel(lpModelInfo->nGPIO[0]);
	ctrlGPIO2.SetCurSel(lpModelInfo->nGPIO[1]);
	ctrlGPIO3.SetCurSel(lpModelInfo->nGPIO[2]);
	ctrlGPIO4.SetCurSel(lpModelInfo->nGPIO[3]);
	ctrlGPIO5.SetCurSel(lpModelInfo->nGPIO[4]);
	ctrlGPIO6.SetCurSel(lpModelInfo->nGPIO[5]);
	ctrlGPIO7.SetCurSel(lpModelInfo->nGPIO[6]);
	ctrlGPIO8.SetCurSel(lpModelInfo->nGPIO[7]);

	ctrlPwrType.SetCurSel(lpModelInfo->nPowerType);
	ctrlStrCnt1.Format("%d", lpModelInfo->nStringCount[0]);
	ctrlStrCnt2.Format("%d", lpModelInfo->nStringCount[1]);
	ctrlStrPwrId.Format("%d", lpModelInfo->nPowerId);
}



void CTS_WR_HS_FUSINGDlg::funcSaveVariToModelFile(char *pModelName)
{
	
	UpdateData(TRUE);
	UpdateModelTotal();

	/**********************************************************************************************************/
	Write_ModelFile(pModelName, "RESOLUTION", "PIXEL",	lpModelInfo->nPixel);
	Write_ModelFile(pModelName, "RESOLUTION", "SWAP",	lpModelInfo->nSwap);
	Write_ModelFile(pModelName, "RESOLUTION", "MCLK",	lpModelInfo->fMclk);

	Write_ModelFile(pModelName, "RESOLUTION", "H_TOTAL", lpModelInfo->nHtotal);
	Write_ModelFile(pModelName, "RESOLUTION", "H_WIDTH", lpModelInfo->nHwidth);
	Write_ModelFile(pModelName, "RESOLUTION", "H_ACTIVE", lpModelInfo->nHact);
	Write_ModelFile(pModelName, "RESOLUTION", "H_BP",	lpModelInfo->nHBP);
	Write_ModelFile(pModelName, "RESOLUTION", "H_FP",	lpModelInfo->nHFP);

	Write_ModelFile(pModelName, "RESOLUTION", "V_TOTAL", lpModelInfo->nVtotal);
	Write_ModelFile(pModelName, "RESOLUTION", "V_WIDTH", lpModelInfo->nVwidth);
	Write_ModelFile(pModelName, "RESOLUTION", "V_ACTIVE", lpModelInfo->nVact);
	Write_ModelFile(pModelName, "RESOLUTION", "V_BP",	lpModelInfo->nVBP);
	Write_ModelFile(pModelName, "RESOLUTION", "V_FP",	lpModelInfo->nVFP);

	/**********************************************************************************************************/
	Write_ModelFile(pModelName, "INTERFACE", "SIGNAL_TYPE",		lpModelInfo->nSigType);
	Write_ModelFile(pModelName, "INTERFACE", "SIGNAL_BIT",		lpModelInfo->nSigBit);
	Write_ModelFile(pModelName, "INTERFACE", "BIT_SEL",			lpModelInfo->nBitSel);
	Write_ModelFile(pModelName, "INTERFACE", "LVDS_SEL",		lpModelInfo->nLvdsSel);
	Write_ModelFile(pModelName, "INTERFACE", "DATA_FORMAT",		lpModelInfo->nDataFormat);
	Write_ModelFile(pModelName, "INTERFACE", "PRE_EMPHASIS",	lpModelInfo->nPreEmph);
	Write_ModelFile(pModelName, "INTERFACE", "DIV_MODE",		lpModelInfo->nDIVmode);
	Write_ModelFile(pModelName, "INTERFACE", "COPEN_CHK",		lpModelInfo->nCopenChk);

	Write_ModelFile(pModelName, "INTERFACE", "GPIO1",	lpModelInfo->nGPIO[0]);
	Write_ModelFile(pModelName, "INTERFACE", "GPIO2",	lpModelInfo->nGPIO[1]);
	Write_ModelFile(pModelName, "INTERFACE", "GPIO3",	lpModelInfo->nGPIO[2]);
	Write_ModelFile(pModelName, "INTERFACE", "GPIO4",	lpModelInfo->nGPIO[3]);
	Write_ModelFile(pModelName, "INTERFACE", "GPIO5",	lpModelInfo->nGPIO[4]);
	Write_ModelFile(pModelName, "INTERFACE", "GPIO6",	lpModelInfo->nGPIO[5]);
	Write_ModelFile(pModelName, "INTERFACE", "GPIO7",	lpModelInfo->nGPIO[6]);
	Write_ModelFile(pModelName, "INTERFACE", "GPIO8",	lpModelInfo->nGPIO[7]);

	/**********************************************************************************************************/
	Write_ModelFile(pModelName, "POWER_SEQ", "SEQ_SELECTION",	lpModelInfo->nSeqSel);
	Write_ModelFile(pModelName, "POWER_SEQ", "SEQ_TIME_1",		lpModelInfo->nTSeq[0]);
	Write_ModelFile(pModelName, "POWER_SEQ", "SEQ_TIME_2",		lpModelInfo->nTSeq[1]);
	Write_ModelFile(pModelName, "POWER_SEQ", "SEQ_TIME_3",		lpModelInfo->nTSeq[2]);
	Write_ModelFile(pModelName, "POWER_SEQ", "SEQ_TIME_4",		lpModelInfo->nTSeq[3]);
	Write_ModelFile(pModelName, "POWER_SEQ", "SEQ_OFF_DIN",		lpModelInfo->nPowerSeqOffDinCount);

	/**********************************************************************************************************/
	Write_ModelFile(pModelName, "POWER_SET", "VCC",		lpModelInfo->fPWR_SetVOLT[0]);
	Write_ModelFile(pModelName, "POWER_SET", "VDD",		lpModelInfo->fPWR_SetVOLT[1]);
	Write_ModelFile(pModelName, "POWER_SET", "VBL",		lpModelInfo->fPWR_SetVOLT[2]);
	Write_ModelFile(pModelName, "POWER_SET", "VBL2",	lpModelInfo->fPWR_SetADD_VBL);

	Write_ModelFile(pModelName, "POWER_SET", "VCC_OFFSET",	lpModelInfo->fPWR_OFFSET[0]);
	Write_ModelFile(pModelName, "POWER_SET", "VBL_OFFSET",	lpModelInfo->fPWR_OFFSET[1]);
	Write_ModelFile(pModelName, "POWER_SET", "VBL2_OFFSET",	lpModelInfo->fPWR_SetADD_CURR);

	/**********************************************************************************************************/
	Write_ModelFile(pModelName, "POWER_LIMIT", "ICC_LOW",	lpModelInfo->nPWR_currLIMIT[LIMIT_LOW][0]);
	Write_ModelFile(pModelName, "POWER_LIMIT", "IDD_LOW",	lpModelInfo->nPWR_currLIMIT[LIMIT_LOW][1]);
	Write_ModelFile(pModelName, "POWER_LIMIT", "IBL_LOW",	lpModelInfo->nPWR_currLIMIT[LIMIT_LOW][2]);
	Write_ModelFile(pModelName, "POWER_LIMIT", "IBL2_LOW",	lpModelInfo->nPWR_AddVBL_CurrLIMIT[0]);

	Write_ModelFile(pModelName, "POWER_LIMIT", "ICC_HIGH",	lpModelInfo->nPWR_currLIMIT[LIMIT_HIGH][0]);
	Write_ModelFile(pModelName, "POWER_LIMIT", "IDD_HIGH",	lpModelInfo->nPWR_currLIMIT[LIMIT_HIGH][1]);
	Write_ModelFile(pModelName, "POWER_LIMIT", "IBL_HIGH",	lpModelInfo->nPWR_currLIMIT[LIMIT_HIGH][2]);
	Write_ModelFile(pModelName, "POWER_LIMIT", "IBL2_HIGH",	lpModelInfo->nPWR_AddVBL_CurrLIMIT[1]);

	/**********************************************************************************************************/
	Write_ModelFile(pModelName, "POWER_LIMIT", "VCC_LOW",	lpModelInfo->fPWR_voltLIMIT[LIMIT_LOW][0]);
	Write_ModelFile(pModelName, "POWER_LIMIT", "VDD_LOW",	lpModelInfo->fPWR_voltLIMIT[LIMIT_LOW][1]);
	Write_ModelFile(pModelName, "POWER_LIMIT", "VBL_LOW",	lpModelInfo->fPWR_voltLIMIT[LIMIT_LOW][2]);
	Write_ModelFile(pModelName, "POWER_LIMIT", "VBL2_LOW",	lpModelInfo->fPWR_AddVBL_VoltLIMIT[0]);

	Write_ModelFile(pModelName, "POWER_LIMIT", "VCC_HIGH",	lpModelInfo->fPWR_voltLIMIT[LIMIT_HIGH][0]);
	Write_ModelFile(pModelName, "POWER_LIMIT", "VDD_HIGH",	lpModelInfo->fPWR_voltLIMIT[LIMIT_HIGH][1]);
	Write_ModelFile(pModelName, "POWER_LIMIT", "VBL_HIGH",	lpModelInfo->fPWR_voltLIMIT[LIMIT_HIGH][2]);
	Write_ModelFile(pModelName, "POWER_LIMIT", "VBL2_HIGH",	lpModelInfo->fPWR_AddVBL_VoltLIMIT[1]);

	/**********************************************************************************************************/
	Write_ModelFile(pModelName, "FLICKER", "VCOM_MODE", lpModelInfo->nVcomMode);
	Write_ModelFile(pModelName, "FLICKER", "VCOM_IC", lpModelInfo->nVcomIc);
	Write_ModelFile(pModelName, "FLICKER", "VCOM_DEFAULT", lpModelInfo->nVcomDefValue);
	Write_ModelFile(pModelName, "FLICKER", "VCOM_MIN", lpModelInfo->nVcomMinValue);
	Write_ModelFile(pModelName, "FLICKER", "VCOM_MAX", lpModelInfo->nVcomMaxValue);
	Write_ModelFile(pModelName, "FLICKER", "VCOM_DEV_ADDR", lpModelInfo->nVcomDevAddr);
	Write_ModelFile(pModelName, "FLICKER", "VCOM_DATA_SIZE", lpModelInfo->nVcomDataSize);
	Write_ModelFile(pModelName, "FLICKER", "VCOM_REG_ADDR", lpModelInfo->nVcomVolRegAddr);
	Write_ModelFile(pModelName, "FLICKER", "VCOM_CONTROL_ADDR", lpModelInfo->nVcomNonVol_ControlAddr);
	Write_ModelFile(pModelName, "FLICKER", "VCOM_WR_DATA", lpModelInfo->nVcomNonVol_WrData);
	Write_ModelFile(pModelName, "FLICKER", "VCOM_RD_DATA", lpModelInfo->nVcomNonVol_RdData);

	/**********************************************************************************************************/
	Write_ModelFile(pModelName, "POWER_SET", "POWER_TYPE", lpModelInfo->nPowerType);
	Write_ModelFile(pModelName, "POWER_SET", "STR_CNT1", lpModelInfo->nStringCount[0]);
	Write_ModelFile(pModelName, "POWER_SET", "STR_CNT2", lpModelInfo->nStringCount[1]);

	funcSavePAT_ModelFile(pModelName);
}

void CTS_WR_HS_FUSINGDlg::funcSavePAT_ModelFile(char *pModelName)
{
	char szPtnName[64];
	char szPtnGray[6];
	char szModKey[16];
	int nItemCnt;
	int nLoop;
	CString strTemp=_T("");

	nItemCnt = m_LCctrlPtnView.GetItemCount();

	for(nLoop=0; nLoop<16; nLoop++)
	{
		sprintf(szModKey, "PTN%02d_NAME", nLoop);
		Write_ModelFile(pModelName, "FUSING_PATTERN", szModKey, "");

		sprintf(szModKey, "PTN%02d_GRAY", nLoop);
		Write_ModelFile(pModelName, "FUSING_PATTERN", szModKey, "");
	}
	
	
	for(nLoop=0; nLoop<nItemCnt; nLoop++)
	{
		sprintf(szModKey, "PTN%02d_NAME", nLoop);
		m_LCctrlPtnView.GetItemText( nLoop, 0, (LPSTR)(LPCSTR)szPtnName, sizeof(szPtnName));
		Write_ModelFile(pModelName, "FUSING_PATTERN", szModKey, szPtnName);

		sprintf(szModKey, "PTN%02d_GRAY", nLoop);
		m_LCctrlPtnView.GetItemText( nLoop, 1, (LPSTR)(LPCSTR)szPtnGray, sizeof(szPtnGray));
		Write_ModelFile(pModelName, "FUSING_PATTERN", szModKey, szPtnGray);
	}

	/* 첫번째 패턴을 저장 한다. */
	#if 0	/* 2019.04.02. KSM. 1st 패턴 삭제. */
	GetDlgItemText(IDC_CMB_1ST_PTN, strTemp);
	Write_ModelFile(pModelName, "1ST_PATTERN", "NAME", strTemp.GetBuffer(0));
	Write_ModelFile(pModelName, "1ST_PATTERN", "GRAY", 0);
	#endif
}

void CTS_WR_HS_FUSINGDlg::funcLoadPAT_ModelFile(char *pModelName)
{
	char szModKey[16];
	int nItemCnt;
	int nLoop;

	for(nLoop=0; nLoop<16; nLoop++)
	{
		sprintf(szModKey, "PTN%02d_NAME", nLoop);
		Read_ModelFile(pModelName, "FUSING_PATTERN", szModKey, lpModelInfo->szPtnName[nLoop]);

		sprintf(szModKey, "PTN%02d_GRAY", nLoop);
		Read_ModelFile(pModelName, "FUSING_PATTERN", szModKey, lpModelInfo->szPtnGray[nLoop]);
	}

	/* 첫번째 패턴을 Load 한다. */
	#if 0	/* 2019.04.02. KSM. 1st 패턴 삭제. */
	Read_ModelFile(pModelName, "1ST_PATTERN", "NAME", lpModelInfo->sz1stPtnName);
	Read_ModelFile(pModelName, "1ST_PATTERN", "GRAY", lpModelInfo->sz1stPtnGray);
	#endif
}

void CTS_WR_HS_FUSINGDlg::funcLoadVariFromModelFile(char *pModelName)
{
	/**********************************************************************************************************/
	Read_ModelFile(pModelName, "RESOLUTION", "PIXEL"		,	&lpModelInfo->nPixel);
	Read_ModelFile(pModelName, "RESOLUTION", "SWAP"		,	&lpModelInfo->nSwap);
	Read_ModelFile(pModelName, "RESOLUTION", "MCLK"		,	&lpModelInfo->fMclk);

	Read_ModelFile(pModelName, "RESOLUTION", "H_TOTAL"	,	&lpModelInfo->nHtotal);
	Read_ModelFile(pModelName, "RESOLUTION", "H_WIDTH"	,	&lpModelInfo->nHwidth);
	Read_ModelFile(pModelName, "RESOLUTION", "H_ACTIVE"	,	&lpModelInfo->nHact);
	Read_ModelFile(pModelName, "RESOLUTION", "H_BP"		,	&lpModelInfo->nHBP);
	Read_ModelFile(pModelName, "RESOLUTION", "H_FP"		,	&lpModelInfo->nHFP);

	Read_ModelFile(pModelName, "RESOLUTION", "V_TOTAL"	,	&lpModelInfo->nVtotal);
	Read_ModelFile(pModelName, "RESOLUTION", "V_WIDTH"	,	&lpModelInfo->nVwidth);
	Read_ModelFile(pModelName, "RESOLUTION", "V_ACTIVE"	,	&lpModelInfo->nVact);
	Read_ModelFile(pModelName, "RESOLUTION", "V_BP"		,	&lpModelInfo->nVBP);
	Read_ModelFile(pModelName, "RESOLUTION", "V_FP"		,	&lpModelInfo->nVFP);

	/**********************************************************************************************************/
	Read_ModelFile(pModelName, "INTERFACE", "SIGNAL_TYPE"	,	&lpModelInfo->nSigType);
	Read_ModelFile(pModelName, "INTERFACE", "SIGNAL_BIT"	,	&lpModelInfo->nSigBit);
	Read_ModelFile(pModelName, "INTERFACE", "BIT_SEL"		,	&lpModelInfo->nBitSel);
	Read_ModelFile(pModelName, "INTERFACE", "LVDS_SEL"		,	&lpModelInfo->nLvdsSel);
	Read_ModelFile(pModelName, "INTERFACE", "DATA_FORMAT"	,	&lpModelInfo->nDataFormat);
	Read_ModelFile(pModelName, "INTERFACE", "PRE_EMPHASIS"	,	&lpModelInfo->nPreEmph);
	Read_ModelFile(pModelName, "INTERFACE", "DIV_MODE"		,	&lpModelInfo->nDIVmode);
	Read_ModelFile(pModelName, "INTERFACE", "COPEN_CHK"		,	&lpModelInfo->nCopenChk);

	Read_ModelFile(pModelName, "INTERFACE", "GPIO1"			,	&lpModelInfo->nGPIO[0]);
	Read_ModelFile(pModelName, "INTERFACE", "GPIO2"			,	&lpModelInfo->nGPIO[1]);
	Read_ModelFile(pModelName, "INTERFACE", "GPIO3"			,	&lpModelInfo->nGPIO[2]);
	Read_ModelFile(pModelName, "INTERFACE", "GPIO4"			,	&lpModelInfo->nGPIO[3]);
	Read_ModelFile(pModelName, "INTERFACE", "GPIO5"			,	&lpModelInfo->nGPIO[4]);
	Read_ModelFile(pModelName, "INTERFACE", "GPIO6"			,	&lpModelInfo->nGPIO[5]);
	Read_ModelFile(pModelName, "INTERFACE", "GPIO7"			,	&lpModelInfo->nGPIO[6]);
	Read_ModelFile(pModelName, "INTERFACE", "GPIO8"			,	&lpModelInfo->nGPIO[7]);

	/**********************************************************************************************************/
	Read_ModelFile(pModelName, "POWER_SEQ", "SEQ_SELECTION"		,	&lpModelInfo->nSeqSel);
	Read_ModelFile(pModelName, "POWER_SEQ", "SEQ_TIME_1"		,	&lpModelInfo->nTSeq[0]);
	Read_ModelFile(pModelName, "POWER_SEQ", "SEQ_TIME_2"		,	&lpModelInfo->nTSeq[1]);
	Read_ModelFile(pModelName, "POWER_SEQ", "SEQ_TIME_3"		,	&lpModelInfo->nTSeq[2]);
	Read_ModelFile(pModelName, "POWER_SEQ", "SEQ_TIME_4"		,	&lpModelInfo->nTSeq[3]);
	Read_ModelFile(pModelName, "POWER_SEQ", "SEQ_OFF_DIN"		,	&lpModelInfo->nPowerSeqOffDinCount);

	/**********************************************************************************************************/
	Read_ModelFile(pModelName, "POWER_SET", "VCC",		&lpModelInfo->fPWR_SetVOLT[0]);
	Read_ModelFile(pModelName, "POWER_SET", "VDD",		&lpModelInfo->fPWR_SetVOLT[1]);
	Read_ModelFile(pModelName, "POWER_SET", "VBL",		&lpModelInfo->fPWR_SetVOLT[2]);
	Read_ModelFile(pModelName, "POWER_SET", "VBL2",		&lpModelInfo->fPWR_SetADD_VBL);

	Read_ModelFile(pModelName, "POWER_SET", "VCC_OFFSET",	&lpModelInfo->fPWR_OFFSET[0]);
	Read_ModelFile(pModelName, "POWER_SET", "VBL_OFFSET",	&lpModelInfo->fPWR_OFFSET[1]);
	Read_ModelFile(pModelName, "POWER_SET", "VBL2_OFFSET",	&lpModelInfo->fPWR_SetADD_CURR);

	/**********************************************************************************************************/
	Read_ModelFile(pModelName, "POWER_LIMIT", "ICC_LOW",	&lpModelInfo->nPWR_currLIMIT[LIMIT_LOW][0]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "IDD_LOW",	&lpModelInfo->nPWR_currLIMIT[LIMIT_LOW][1]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "IBL_LOW",	&lpModelInfo->nPWR_currLIMIT[LIMIT_LOW][2]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "IBL2_LOW",	&lpModelInfo->nPWR_AddVBL_CurrLIMIT[0]);

	Read_ModelFile(pModelName, "POWER_LIMIT", "ICC_HIGH",	&lpModelInfo->nPWR_currLIMIT[LIMIT_HIGH][0]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "IDD_HIGH",	&lpModelInfo->nPWR_currLIMIT[LIMIT_HIGH][1]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "IBL_HIGH",	&lpModelInfo->nPWR_currLIMIT[LIMIT_HIGH][2]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "IBL2_HIGH",	&lpModelInfo->nPWR_AddVBL_CurrLIMIT[1]);

	/**********************************************************************************************************/
	Read_ModelFile(pModelName, "POWER_LIMIT", "VCC_LOW",	&lpModelInfo->fPWR_voltLIMIT[LIMIT_LOW][0]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "VDD_LOW",	&lpModelInfo->fPWR_voltLIMIT[LIMIT_LOW][1]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "VBL_LOW",	&lpModelInfo->fPWR_voltLIMIT[LIMIT_LOW][2]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "VBL2_LOW",	&lpModelInfo->fPWR_AddVBL_VoltLIMIT[0]);

	Read_ModelFile(pModelName, "POWER_LIMIT", "VCC_HIGH",	&lpModelInfo->fPWR_voltLIMIT[LIMIT_HIGH][0]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "VDD_HIGH",	&lpModelInfo->fPWR_voltLIMIT[LIMIT_HIGH][1]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "VBL_HIGH",	&lpModelInfo->fPWR_voltLIMIT[LIMIT_HIGH][2]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "VBL2_HIGH",	&lpModelInfo->fPWR_AddVBL_VoltLIMIT[1]);

	/**********************************************************************************************************/
	Read_ModelFile(pModelName, "FLICKER", "VCOM_MODE", &lpModelInfo->nVcomMode);
	Read_ModelFile(pModelName, "FLICKER", "VCOM_IC", &lpModelInfo->nVcomIc);
	Read_ModelFile(pModelName, "FLICKER", "VCOM_DEFAULT", &lpModelInfo->nVcomDefValue);
	Read_ModelFile(pModelName, "FLICKER", "VCOM_MIN", &lpModelInfo->nVcomMinValue);
	Read_ModelFile(pModelName, "FLICKER", "VCOM_MAX", &lpModelInfo->nVcomMaxValue);
	Read_ModelFile(pModelName, "FLICKER", "VCOM_DEV_ADDR", &lpModelInfo->nVcomDevAddr);
	Read_ModelFile(pModelName, "FLICKER", "VCOM_DATA_SIZE", &lpModelInfo->nVcomDataSize);
	Read_ModelFile(pModelName, "FLICKER", "VCOM_REG_ADDR", &lpModelInfo->nVcomVolRegAddr);
	Read_ModelFile(pModelName, "FLICKER", "VCOM_CONTROL_ADDR", &lpModelInfo->nVcomNonVol_ControlAddr);
	Read_ModelFile(pModelName, "FLICKER", "VCOM_WR_DATA", &lpModelInfo->nVcomNonVol_WrData);
	Read_ModelFile(pModelName, "FLICKER", "VCOM_RD_DATA", &lpModelInfo->nVcomNonVol_RdData);

	/**********************************************************************************************************/
	Read_ModelFile(pModelName, "POWER_SET", "POWER_TYPE", &lpModelInfo->nPowerType, "1");
	Read_ModelFile(pModelName, "POWER_SET", "STR_CNT1", &lpModelInfo->nStringCount[0]);
	Read_ModelFile(pModelName, "POWER_SET", "STR_CNT2", &lpModelInfo->nStringCount[1]);

	UpdateModelTotal();
	funcLoadPAT_ModelFile(pModelName);
}

void CTS_WR_HS_FUSINGDlg::funcUpdatePAT_List(void)
{
	CString strTemp=_T("");
	int nLoop;

	POSITION Pos = m_LCctrlPtnView.GetFirstSelectedItemPosition();

	m_LCctrlPtnView.DeleteAllItems();

	for(nLoop=0; nLoop<16; nLoop++)
	{
		if(strlen(lpModelInfo->szPtnName[nLoop]) == 0)	break;

		strTemp.Format("%s", lpModelInfo->szPtnName[nLoop]);
		m_LCctrlPtnView.InsertItem(nLoop, strTemp);

		strTemp.Format("%s", lpModelInfo->szPtnGray[nLoop]);
		m_LCctrlPtnView.SetItem(nLoop, 1, LVIF_TEXT, strTemp, 0, LVIF_STATE, 0, 0);

		m_LCctrlPtnView.SetSelectionMark(nLoop); // Item Select & Focus
		m_LCctrlPtnView.SetItemState(nLoop, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
	}
}

void CTS_WR_HS_FUSINGDlg::funcUpdateModel_List(void)
{
	int nLoop, nItemNo;
	CString strNowModel("");

	m_pComboModel = (CComboBox* ) GetDlgItem(IDC_CMB_MODEL_NAME);

	m_pComboModel->ResetContent();

	fucAllModelList();

	GetDlgItemText(IDC_EDT_MODEL, strNowModel);
	
	nItemNo = m_pComboModel->FindString(0, strNowModel);

	m_pComboModel->SetCurSel(nItemNo);
}


int CTS_WR_HS_FUSINGDlg::execGetVersionCheck(void)
{
	unsigned char szTemp[8]={0,};

	memset(m_pApp->szRecvData, 0, sizeof(m_pApp->szRecvData));
	if(m_pApp->PacketSend(CMD_CTRL_VER_GET, szTemp, 0) == TRUE)
	{
		Sleep(1);
	}

	return 0;
}

int CTS_WR_HS_FUSINGDlg::funcGetSignalType(char cmbSignalType)
{
	int nRtnVal=tpLVDS;
	
	switch(cmbSignalType)
	{
		case 0 ://LVDS
		{
			nRtnVal=tpLVDS;
		}break;

		case 1 ://Vx1
		{
			nRtnVal=tpVx1;
		}break;
	}

	return nRtnVal;
}


int CTS_WR_HS_FUSINGDlg::funcMakeSystemFusingPacket(char *pszRtnPack)
{
	CString strTmp("");
	int nInterface=0;
	int nLenPos=0;
	float fClock=0;

	GetDlgItemText(IDC_EDT_MODEL, strTmp);
	for(int n=strTmp.GetLength(); n< 30; n++)
	{
		strTmp.Insert(n, "*");
	}

	sprintf(pszRtnPack, "%s%02d", strTmp.GetBuffer(0), 99);
	nLenPos = strlen(pszRtnPack);

	switch(lpModelInfo->nPixel)
	{
		case 0:		/* SINGLE */
		{
			nInterface = 0;
		}break;

		case 1:		/* DUAL */
		{
			nInterface = 1;
			fClock = lpModelInfo->fMclk/(float)2.0;
		}break;

		case 2:		/* QUAD */
		{
			nInterface = 2;
			fClock = lpModelInfo->fMclk/(float)4.0;
		}break;

		case 3:		/* OCTA */
		{
			nInterface = 3;
			fClock = lpModelInfo->fMclk/(float)8.0;
		}break;

		case 4:		/* HEXA */
		{
			nInterface = 4;
			fClock = lpModelInfo->fMclk/(float)16.0;
		}break;
	}

	int nMode = 0;
	int nBitsSwap = lpModelInfo->nSwap << 4;

	int nDotClockInv=0;
	int nHsyncPolarity = 0x00;
	int nVsyncPolarity = 0x00;
	int nConvSignalType = funcGetSignalType(lpModelInfo->nSigType);

	sprintf(&pszRtnPack[nLenPos], "INFO%02X%01X%04d%04d%06.2f%03d%04d%04d%03d%04d%04d%01d", (nInterface|nMode|nBitsSwap)\
																						, (nDotClockInv|nHsyncPolarity|nVsyncPolarity)\
																						, lpModelInfo->nHact\
																						, lpModelInfo->nVact\
																						, fClock\
																						, lpModelInfo->nHwidth\
																						, lpModelInfo->nHFP\
																						, lpModelInfo->nHBP\
																						, lpModelInfo->nVwidth\
																						, lpModelInfo->nVFP\
																						, lpModelInfo->nVBP\
																						, lpModelInfo->nDIVmode);
	nLenPos = strlen(pszRtnPack);

	sprintf(&pszRtnPack[nLenPos], "%04d%03d%03d%03d%03d%02d%01d%02d%03d%02d%04d%01d%03d%01d%01d%01d%01d%01d%01d%01d%01d%02d%01d%01d%01d%01d", 0\
																																			, 0\
																																			, 0\
																																			, 0\
																																			, 0\
																																			, 0\
																																			, 0\
																																			, 0\
																																			, 0\
																																			, 0\
																																			, 0\
																																			, 0\
																																			, 0\
																																			, nConvSignalType\
																																			, lpModelInfo->nSigBit\
																																			, lpModelInfo->nPixel\
																																			, lpModelInfo->nGPIO[1]\
																																			, lpModelInfo->nGPIO[2]\
																																			, 0\
																																			, lpModelInfo->nPreEmph\
																																			, 0\
																																			, lpModelInfo->nPowerType\
																																			, lpModelInfo->nCopenChk\
																																			, 0\
																																			, 0\
																																			, 0);
	nLenPos = strlen(pszRtnPack);

	/* Power INFO */
	char szSeqChar;
	if(lpModelInfo->nSeqSel==1)	szSeqChar='S';
	else						szSeqChar='V';
	sprintf(&pszRtnPack[nLenPos], "%03d%03d%04d%03d%03d%03d%03d%c%03d%03d%03d%03d%03d",	int(lpModelInfo->fPWR_SetVOLT[0]*10.0)\
																						, int(lpModelInfo->fPWR_SetVOLT[1]*10.0)\
																						, int(lpModelInfo->fPWR_SetVOLT[2]*10.0)\
																						, 0\
																						, int(lpModelInfo->fPWR_OFFSET[0]*100.0)\
																						, 0\
																						, int(lpModelInfo->fPWR_OFFSET[1]*100.0)\
																						, szSeqChar\
																						, lpModelInfo->nTSeq[0]\
																						, lpModelInfo->nTSeq[1]\
																						, lpModelInfo->nTSeq[2]\
																						, lpModelInfo->nTSeq[3]\
																						,0);
	nLenPos = strlen(pszRtnPack);

	/* INVERTER INFO */
	sprintf(&pszRtnPack[nLenPos], "%01d%01d%01d%01d%01d%01d%01d%01d%01d%01d%01d%02d%01d%01d%01d%01d%01d%01d%01d%01d%01d%05d%03d%01d%01d%01d%01d", 0\
																																				, 0\
																																				, 0\
																																				, 0\
																																				, 0\
																																				, 0\
																																				, 0\
																																				, 0\
																																				, 0\
																																				, 0\
																																				, 0\
																																				, 0\
																																				, 0\
																																				, 0\
																																				, 0\
																																				, 0\
																																				, 0\
																																				, 0\
																																				, 0\
																																				, 0\
																																				, 0\
																																				, 0\
																																				, 0\
																																				, 0\
																																				, 0\
																																				, 0\
																																				, 0);
	nLenPos = strlen(pszRtnPack);

	/* LIMIT INFO */
	sprintf(&pszRtnPack[nLenPos], "%04d%04d%04d%04d%04d%04d%04d%04d%04d%04d%04d%04d%02d%03d%03d", (int)(lpModelInfo->fPWR_voltLIMIT[0][0]*100)\
																								, (int)(lpModelInfo->fPWR_voltLIMIT[1][0]*100)\
																								, (int)(lpModelInfo->fPWR_voltLIMIT[0][1]*100)\
																								, (int)(lpModelInfo->fPWR_voltLIMIT[1][1]*100)\
																								, (int)(lpModelInfo->fPWR_voltLIMIT[0][2]*10)\
																								, (int)(lpModelInfo->fPWR_voltLIMIT[1][2]*10)\
																								, (int)(lpModelInfo->nPWR_currLIMIT[0][0])\
																								, (int)(lpModelInfo->nPWR_currLIMIT[1][0])\
																								, (int)(lpModelInfo->nPWR_currLIMIT[0][1])\
																								, (int)(lpModelInfo->nPWR_currLIMIT[1][1])\
																								, (int)(lpModelInfo->nPWR_currLIMIT[0][2])\
																								, (int)(lpModelInfo->nPWR_currLIMIT[1][2])\
																								, 0\
																								, lpModelInfo->nStringCount[0]\
																								, lpModelInfo->nStringCount[1]);
	nLenPos = strlen(pszRtnPack);

	/* LED/BL INFO */
	sprintf(&pszRtnPack[nLenPos], "%02x%02x%02x%02x%01d%01d%01d%04d%04d", 0\
																		, 0\
																		, 0\
																		, 0\
																		, 0\
																		, 0\
																		, 0\
																		, 0\
																		, 0);
	nLenPos = strlen(pszRtnPack);

	/* HDCP/EP INFO */
	sprintf(&pszRtnPack[nLenPos], "%02X%02X%02X%02X%02X%02X%02X%02X", 0x55\
																	, 0x55\
																	, 0x55\
																	, 0x55\
																	, 0x55\
																	, 0x55\
																	, 0x55\
																	, 0x55\
																	, 0x55\
																	, 0x55\
																	, 0x55\
																	, 0x55\
																	, 0x55\
																	, 0x55\
																	, 0x55\
																	, 0x55);
	nLenPos = strlen(pszRtnPack);

	/* MAINT INFO */
	sprintf(&pszRtnPack[nLenPos], "%01d%01d%03d%01d%01d", 0\
														, 0\
														, 0\
														, 0\
														, 0);
	nLenPos = strlen(pszRtnPack);

	/* PREDISPLAY */
	sprintf(&pszRtnPack[nLenPos], "%01d%01d%01d", 0\
												, 0\
												, 0);
	nLenPos = strlen(pszRtnPack);

	/* INV_LESS */
	sprintf(&pszRtnPack[nLenPos], "%01d%01d%01d%01d%03d%03d%03d%03d%01d", 0\
																		, 0\
																		, 0\
																		, 0\
																		, 0\
																		, 0\
																		, 0\
																		, 0\
																		, 0);
	nLenPos = strlen(pszRtnPack);

	/* OTHER */
	sprintf(&pszRtnPack[nLenPos], "%01d%03d%01d%01d%01d%04d%03d%04d%04d%04d%04d", 9\
																				, 999\
																				, 0\
																				, 0\
																				, 0\
																				, (int)(lpModelInfo->fPWR_SetADD_VBL*10.0)\
																				, (int)(lpModelInfo->fPWR_SetADD_CURR*100.0)\
																				, (int)(lpModelInfo->fPWR_AddVBL_VoltLIMIT[0]*10)\
																				, (int)(lpModelInfo->fPWR_AddVBL_VoltLIMIT[1]*10)\
																				, (int)(lpModelInfo->nPWR_AddVBL_CurrLIMIT[0])\
																				, (int)(lpModelInfo->nPWR_AddVBL_CurrLIMIT[1]));
	nLenPos = strlen(pszRtnPack);

	return nLenPos;
}


int CTS_WR_HS_FUSINGDlg::execSystemFusing(void)
{
	char szFusingPacket[COM_LENGTH]={0,};

	funcMakeSystemFusingPacket(szFusingPacket);

	if(m_pApp->PacketSend(CMD_CTRL_FUSING_SYSTEM_INFO, (unsigned char *)szFusingPacket, strlen(szFusingPacket)) != TRUE)
	{
		AfxMessageBox("SYSTEM FUSING FAIL.", MB_ICONERROR|MB_OK);
		return (-1);
	}

	return 0;
}


int CTS_WR_HS_FUSINGDlg::funcMakePatternFusingPacket(char *pszRtnPack)
{
	int nPtnCnt;
	int nLoop;
	CString strTmp=("");
	CString lpData = ("");

	/* 패턴의 갯수를 얻는다. */
	for(nLoop=0; nLoop<16; nLoop++)
	{
		if(strlen(lpModelInfo->szPtnName[nLoop]) == 0)
		{
			nPtnCnt = nLoop;
			break;
		}
	}
	if(nPtnCnt == 0)	return (-1);

	strTmp.Format("%02X%02d", 0, nPtnCnt);
	lpData += strTmp;

	for(nLoop=0; nLoop<nPtnCnt; nLoop++)
	{
		CString szDataTmp("");
		strTmp.Format(".\\Pattern\\%s.pdb", lpModelInfo->szPtnName[nLoop]);
		strTmp = T2CmdGen::makeT2dataStrFromFile(strTmp);
		//strTmp = T2CmdGen::makeT2FileStr(strTmp);
		strTmp = T2CmdGen::makeT2PatternStr(strTmp, lpModelInfo->nHact, lpModelInfo->nVact);

		lpData = lpData+strTmp;
		lpData = lpData+"^";
	}

	sprintf(pszRtnPack, "%s", lpData.GetBuffer(0));

	return 0;
}


int CTS_WR_HS_FUSINGDlg::execPatternFusing(void)
{
	char szFusingPacket[COM_LENGTH]={0,};

	if(funcMakePatternFusingPacket(szFusingPacket) < 0)
	{
		AfxMessageBox("PATTERN LIST EMPTY.", MB_ICONERROR|MB_OK);
		return (-1);
	}

	if(m_pApp->PacketSend(CMD_CTRL_FUSING_PATTERN, (unsigned char *)szFusingPacket, strlen(szFusingPacket)) != TRUE)
	{
		AfxMessageBox("PATTERN FUSING FAIL.", MB_ICONERROR|MB_OK);
		return (-1);
	}

	return 0;
}


int CTS_WR_HS_FUSINGDlg::funcMake1stPatternFusingPacket(char *pszRtnPack)
{
	int nPtnCnt=1;
	CString strTmp=("");
	CString lpData = ("");

	if(strlen(lpModelInfo->sz1stPtnName) == 0)	return (-1);

	strTmp.Format("%02X%02d", 0, nPtnCnt);
	lpData += strTmp;

	CString szDataTmp("");
	strTmp.Format(".\\Pattern\\%s.pdb", lpModelInfo->sz1stPtnName);
	strTmp = T2CmdGen::makeT2dataStrFromFile(strTmp);
	//strTmp = T2CmdGen::makeT2FileStr(strTmp);
	strTmp = T2CmdGen::makeT2PatternStr(strTmp, lpModelInfo->nHact, lpModelInfo->nVact);

	lpData = lpData+strTmp;
	lpData = lpData+"^";

	sprintf(pszRtnPack, "%s", lpData.GetBuffer(0));

	return 0;
}


int CTS_WR_HS_FUSINGDlg::exec1stPatternFusing(void)
{
	char sz1stPtnPacket[2048]={0,};

	if(funcMake1stPatternFusingPacket(sz1stPtnPacket) < 0)
	{
		AfxMessageBox("FIRST PATTERN LIST EMPTY.", MB_ICONERROR|MB_OK);
		return (-1);
	}

	if(m_pApp->PacketSend(CMD_CTRL_FUSING_FIRST_PTN, (unsigned char *)sz1stPtnPacket, strlen(sz1stPtnPacket)) != TRUE)
	{
		AfxMessageBox("FIRST PATTERN FUSING FAIL.", MB_ICONERROR|MB_OK);
		return (-1);
	}

	return 0;
}


int CTS_WR_HS_FUSINGDlg::funcMakeCtrlIOFusingPacket(char *pszRtnPacket)
{
	int nLenPos=0;

	/*sprintf(pszRtnPacket, "%01d%01d%01d%01d%01d%01d%01d%01d%02d", lpModelInfo->nGPIO[0]\
																, lpModelInfo->nGPIO[1]\
																, lpModelInfo->nGPIO[2]\
																, lpModelInfo->nGPIO[3]\
																, lpModelInfo->nGPIO[4]\
																, lpModelInfo->nGPIO[5]\
																, lpModelInfo->nGPIO[6]\
																, lpModelInfo->nGPIO[7]\
																, lpModelInfo->nPowerSeqOffDinCount);*/

	sprintf(pszRtnPacket, "%01d%01d%01d%01d%01d%01d%01d%01d%02d%01d%01d%03d%03d%03d%02X%01d%02X%02X%02X%02X"
		, lpModelInfo->nGPIO[0]\
		, lpModelInfo->nGPIO[1]\
		, lpModelInfo->nGPIO[2]\
		, lpModelInfo->nGPIO[3]\
		, lpModelInfo->nGPIO[4]\
		, lpModelInfo->nGPIO[5]\
		, lpModelInfo->nGPIO[6]\
		, lpModelInfo->nGPIO[7]\
		, lpModelInfo->nPowerSeqOffDinCount
		, lpModelInfo->nVcomMode
		, lpModelInfo->nVcomIc
		, lpModelInfo->nVcomDefValue
		, lpModelInfo->nVcomMinValue
		, lpModelInfo->nVcomMaxValue
		, lpModelInfo->nVcomDevAddr
		, lpModelInfo->nVcomDataSize
		, lpModelInfo->nVcomVolRegAddr
		, lpModelInfo->nVcomNonVol_ControlAddr
		, lpModelInfo->nVcomNonVol_WrData
		, lpModelInfo->nVcomNonVol_RdData
	);

	nLenPos = strlen(pszRtnPacket);

	return nLenPos;
}


int CTS_WR_HS_FUSINGDlg::execControlIOFusing(void)
{
	char szFusingPacket[COM_LENGTH]={0,};

	funcMakeCtrlIOFusingPacket(szFusingPacket);

	if(m_pApp->PacketSend(CMD_CTRL_FUSING_CTRL_IO, (unsigned char *)szFusingPacket, strlen(szFusingPacket)) != TRUE)
	{
		AfxMessageBox("CONTROL IO FUSING FAIL.", MB_ICONERROR|MB_OK);
		return (-1);
	}

	return 0;
}


void CTS_WR_HS_FUSINGDlg::OnBnClickedBtnPortOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nPortNum;
	CString strTemp=_T("");

	UpdateData(TRUE);

	nPortNum = ctrlComPort.GetCurSel();

	if(m_pApp->cfgUart(nPortNum+1) == TRUE)
	{//OK
		strTemp.Format("COM%d, PORT OPEN OK.", nPortNum+1);
		AfxMessageBox(strTemp, MB_ICONINFORMATION|MB_OK);
	}
}

bool CTS_WR_HS_FUSINGDlg::OnBnClickedBcrPortOpen() // bcr 스캔시 포트 연결
{
	int nPortNum;
	CString strTemp = _T("");

	UpdateData(TRUE);

	nPortNum = ctrlComPort.GetCurSel();

	if (m_pApp->cfgUart(nPortNum + 1) == TRUE)
	{//OK
		/*strTemp.Format("COM%d, PORT OPEN OK.", nPortNum + 1);
		AfxMessageBox(strTemp, MB_ICONINFORMATION | MB_OK);*/

		return TRUE;
	}
	return FALSE;
}

void CTS_WR_HS_FUSINGDlg::OnBnClickedBtnFwUpdate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_pApp->m_b232Open == FALSE)
	{
		AfxMessageBox("Comport is not Opened.", MB_ICONERROR|MB_OK);
		return;
	}

	CFWupdateDlg	dlg;
	dlg.DoModal();
}

void CTS_WR_HS_FUSINGDlg::OnBnClickedBtnOpbox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	/*if(m_pApp->m_b232Open == FALSE)
	{
		AfxMessageBox("OpBox Can't Fusing. Please Comport Open.", MB_ICONERROR|MB_OK);
		return;
	}*/

	COpBoxFusing	dlg;
	dlg.DoModal();
}


void CTS_WR_HS_FUSINGDlg::OnBnClickedBtnSystemMenu()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CSystemMenu sysDlg;
	sysDlg.DoModal();
}


void CTS_WR_HS_FUSINGDlg::OnBnClickedButtonFlicker()
{
	SetFlicker flickerDlg;
	flickerDlg.DoModal();
}

void CTS_WR_HS_FUSINGDlg::UpdateModelTotal()
{
	lpModelInfo->nHtotal = lpModelInfo->nHwidth + lpModelInfo->nHBP + lpModelInfo->nHFP + lpModelInfo->nHact;
	lpModelInfo->nVtotal = lpModelInfo->nVwidth + lpModelInfo->nVBP + lpModelInfo->nVFP + lpModelInfo->nVact;
}

// .cpp 파일에 새 함수 구현
BarcodeInfo CTS_WR_HS_FUSINGDlg::FindDataInDB(CString partNumber)
{
	BarcodeInfo result; // 반환할 결과 객체

	// 1. ODBC 핸들 변수 선언
	SQLHENV hEnv = NULL;
	SQLHDBC hDbc = NULL;
	SQLHSTMT hStmt = NULL;
	SQLRETURN ret;

	// 2. ODBC 환경 설정 및 DB 연결
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
	SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
	SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

	ret = SQLConnectW(hDbc,
		(SQLWCHAR*)L"OracleDB", SQL_NTS,
		(SQLWCHAR*)L"system", SQL_NTS,
		(SQLWCHAR*)L"1234", SQL_NTS);

	// 3. 연결 성공 시 쿼리 실행
	if (SQL_SUCCEEDED(ret)) {
		SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
		SQLExecDirectW(hStmt, (SQLWCHAR*)L"SELECT MODEL_NUM, PN, NAME FROM BARCORD", SQL_NTS);

		SQLINTEGER modelNum_db;
		SQLCHAR pn_db[64];
		SQLCHAR name_db[64];

		SQLBindCol(hStmt, 1, SQL_C_SLONG, &modelNum_db, 0, NULL);
		SQLBindCol(hStmt, 2, SQL_C_CHAR, pn_db, sizeof(pn_db), NULL);
		SQLBindCol(hStmt, 3, SQL_C_CHAR, name_db, sizeof(name_db), NULL);

		// 4. 결과를 한 줄씩 가져와서 입력받은 partNumber와 비교
		while (SQLFetch(hStmt) == SQL_SUCCESS) {
			// DB에서 읽은 pn_db 값을 CString으로 변환하여 비교
			if (partNumber == CString(pn_db))
			{
				// 일치하는 데이터를 찾았으면 결과 객체에 저장
				result.modelNum = modelNum_db;
				result.pn = CString(pn_db);
				result.name = CString(name_db);
				result.found = true; // 찾았다고 표시
				break; // 루프 종료
			}
		}
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
	else {
		AfxMessageBox(_T("DB 연결에 실패했습니다."));
	}

	// 5. 연결 해제 및 핸들 정리
	SQLDisconnect(hDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

	return result; // 최종 결과 반환
}

//// '연결 테스트' 버튼을 클릭했을 때 실행되는 함수
void CTS_WR_HS_FUSINGDlg::OnBnClickedButton2()
{
}



void CTS_WR_HS_FUSINGDlg::OnStnClickedLogo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
