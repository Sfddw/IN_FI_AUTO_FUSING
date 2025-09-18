
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
#include "CSetSystemDlg.h"

#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <initializer_list>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTS_WR_HS_FUSINGDlg 대화 상자


int St_flag = 0;

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
	DDX_Control(pDX, IDC_EDT_MODELSEARCH, m_editSearch);
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
	DDX_Control(pDX, IDC_PIC_SELECT, CtrlSelect);
	DDX_Control(pDX, IDC_PIC_SYSTEM, CtrlSystem);
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

	DDX_Text(pDX, IDC_EDIT_FOLDER, m_strFolderPath);
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
	ON_BN_CLICKED(IDC_BTN_BROWSE, &CTS_WR_HS_FUSINGDlg::OnBnClickedBtnBrowse)
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM, &CTS_WR_HS_FUSINGDlg::OnBnClickedButtonSystem)
	ON_BN_CLICKED(IDC_BTN_SEARCH, &CTS_WR_HS_FUSINGDlg::OnBnClickedBtnSearch)
	ON_STN_CLICKED(IDC_PIC_SELECT, &CTS_WR_HS_FUSINGDlg::OnStnClickedPicSelect)
	ON_STN_CLICKED(IDC_PIC_SYSTEM, &CTS_WR_HS_FUSINGDlg::OnStnClickedPicSystem)
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
	lpSysInfo = m_pApp->GetSystemInfo();

	if (lpSysInfo->m_sUserID == "PM")
	{
		GetDlgItem(IDC_BTN_SAVE)->EnableWindow(TRUE);

		WriteLogFile(_T("Program Start! [PM MODE]"));
	}
	else
	{
		GetDlgItem(IDC_BTN_SAVE)->EnableWindow(FALSE);
		WriteLogFile(_T("Program Start! [OP MODE]"));
	}

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	initControl();

	/* 타이틀 텍스트 설정 */
	CString windowText = _T("TS_MA_HS_FUSING_v");
	CString version;
	CVersionInfo::GetVersionInfo(version);
	windowText.Append(version);
	SetWindowTextA(windowText);

	OnBnClickedBtnPortOpen();
	Lf_InitColorBrush();

	SetTimer(10, 1000, NULL);

	

	//m_colorRs232Bg = RGB(0, 255, 0);

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
		if (lpSysInfo->f_ComPort == true)
		{
			m_colorRs232Bg = RGB(0, 255, 0); // 초록색;
			GetDlgItem(IDC_STATIC_RS232)->Invalidate();
		}
		else
		{
			m_colorRs232Bg = RGB(255, 0, 0);
			GetDlgItem(IDC_STATIC_RS232)->Invalidate();
		}

		/*if (CheckOracleDBConnection())
		{ 
			AfxMessageBox(_T("DB 연결 성공!"));
			m_colorMesBg = RGB(0, 255, 0);
			GetDlgItem(IDC_STATIC_MES)->Invalidate();
		}
		else
		{
			AfxMessageBox(_T("DB 연결 실패..."));
			m_colorMesBg = RGB(255, 0, 0);
				GetDlgItem(IDC_STATIC_MES)->Invalidate();
		}*/
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
		//return TRUE;
		return CDialog::PreTranslateMessage(pMsg);
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

	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
		/*if ((pWnd->GetDlgCtrlID() == IDC_STATIC)
			|| pWnd->GetDlgCtrlID() == IDC_STATIC_CONNECT)*/
		if (((pWnd->GetDlgCtrlID() == IDC_STATIC_CONNECT || 
			pWnd->GetDlgCtrlID() == IDC_STATIC_CONNECT2 ||
			pWnd->GetDlgCtrlID() == IDC_STATIC_CONNECT3 ||
			pWnd->GetDlgCtrlID() == IDC_STATIC_CONNECT4)))
		{
			pDC->SetBkColor(COLOR_SKYBLUE);
			pDC->SetTextColor(COLOR_BLACK);
			return m_Brush[COLOR_IDX_SKYBLUE];
		}
	}


	if ( GetDlgItem(IDC_EDT_MODEL)->GetSafeHwnd() == pWnd->m_hWnd )
	{
		pDC->SetBkColor(COLOR_GRAY224);
		pDC->SetTextColor(COLOR_BLUE);
		return mHbr;
	}

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_RS232)
	{
		pDC->SetBkColor(m_colorRs232Bg);

		// 텍스트색도 함께 바꿀 수 있음 (선택)
		if (m_colorRs232Bg == RGB(255, 0, 0))
			pDC->SetTextColor(RGB(255, 255, 255)); // 빨간배경엔 흰글씨

		// 브러시 반환 (배경용)
		static CBrush brush;
		brush.DeleteObject(); // 이전 브러시 제거
		brush.CreateSolidBrush(m_colorRs232Bg); // 현재 색상으로 생성
		return brush;
	}
	else if (pWnd->GetDlgCtrlID() == IDC_STATIC_MES)
	{
		pDC->SetBkColor(m_colorMesBg);

		if (m_colorMesBg == RGB(255, 0, 0))
			pDC->SetTextColor(RGB(255, 255, 255));

		static CBrush brushMes;
		brushMes.DeleteObject();
		brushMes.CreateSolidBrush(m_colorMesBg);
		return brushMes;
	}
	else if ((pWnd->GetDlgCtrlID() == IDC_EDIT_MODEL_NAME ||
		pWnd->GetDlgCtrlID() == IDC_EDIT_FUSING_STATUS))
	//else if (pWnd->GetDlgCtrlID() == IDC_EDIT_MODEL_NAME)
	{
		pDC->SetBkColor(m_colorFusingStatus);

		if (m_colorFusingStatus == RGB(255, 0, 0))
			pDC->SetTextColor(RGB(255, 255, 255));

		static CBrush brushFusing;
		brushFusing.DeleteObject();
		brushFusing.CreateSolidBrush(m_colorFusingStatus);
		return brushFusing;
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void CTS_WR_HS_FUSINGDlg::Lf_InitColorBrush()
{
	m_Brush[COLOR_IDX_USER_BACKGROUND].CreateSolidBrush(COLOR_USER_BACKGROUND);
	m_Brush[COLOR_IDX_BLACK].CreateSolidBrush(COLOR_BLACK);
	m_Brush[COLOR_IDX_WHITE].CreateSolidBrush(COLOR_WHITE);
	m_Brush[COLOR_IDX_RED].CreateSolidBrush(COLOR_RED);
	m_Brush[COLOR_IDX_RED128].CreateSolidBrush(COLOR_RED128);
	m_Brush[COLOR_IDX_GREEN].CreateSolidBrush(COLOR_GREEN);
	m_Brush[COLOR_IDX_GREEN128].CreateSolidBrush(COLOR_GREEN128);
	m_Brush[COLOR_IDX_BLUE].CreateSolidBrush(COLOR_BLUE);
	m_Brush[COLOR_IDX_BLUE128].CreateSolidBrush(COLOR_BLUE128);
	m_Brush[COLOR_IDX_ORANGE].CreateSolidBrush(COLOR_ORANGE);
	m_Brush[COLOR_IDX_YELLOW].CreateSolidBrush(COLOR_YELLOW);
	m_Brush[COLOR_IDX_MAGENTA].CreateSolidBrush(COLOR_MAGENTA);
	m_Brush[COLOR_IDX_VERDANT2].CreateSolidBrush(COLOR_VERDANT2);
	m_Brush[COLOR_IDX_SKYBLUE].CreateSolidBrush(COLOR_SKYBLUE);
	m_Brush[COLOR_IDX_JADEBLUE].CreateSolidBrush(COLOR_JADEBLUE);
	m_Brush[COLOR_IDX_JADEGREEN].CreateSolidBrush(COLOR_JADEGREEN);
	m_Brush[COLOR_IDX_BLUISH].CreateSolidBrush(COLOR_BLUISH);
	m_Brush[COLOR_IDX_PURPLE].CreateSolidBrush(COLOR_PURPLE);
	m_Brush[COLOR_IDX_LIGHT_GREEN].CreateSolidBrush(COLOR_LIGHT_GREEN);
	m_Brush[COLOR_IDX_LIGHT_RED].CreateSolidBrush(COLOR_LIGHT_RED);
	m_Brush[COLOR_IDX_LIGHT_YELLOW].CreateSolidBrush(COLOR_LIGHT_YELLOW);
	m_Brush[COLOR_IDX_LIGHT_ORANGE].CreateSolidBrush(COLOR_LIGHT_ORANGE);
	m_Brush[COLOR_IDX_DARK_RED].CreateSolidBrush(COLOR_DARK_RED);
	m_Brush[COLOR_IDX_DARK_GREEN].CreateSolidBrush(COLOR_DARK_GREEN);
	m_Brush[COLOR_IDX_DARK_BLUE].CreateSolidBrush(COLOR_DARK_BLUE);
	m_Brush[COLOR_IDX_DARK_MAGENTA].CreateSolidBrush(COLOR_DARK_MAGENTA);
	m_Brush[COLOR_IDX_DARK_ORANGE].CreateSolidBrush(COLOR_DARK_ORANGE);
	m_Brush[COLOR_IDX_DARK_YELLOW].CreateSolidBrush(COLOR_DARK_YELLOW);
	m_Brush[COLOR_IDX_GRAY96].CreateSolidBrush(COLOR_GRAY96);
	m_Brush[COLOR_IDX_GRAY128].CreateSolidBrush(COLOR_GRAY128);
	m_Brush[COLOR_IDX_GRAY159].CreateSolidBrush(COLOR_GRAY159);
	m_Brush[COLOR_IDX_GRAY192].CreateSolidBrush(COLOR_GRAY192);
	m_Brush[COLOR_IDX_GRAY224].CreateSolidBrush(COLOR_GRAY224);
	m_Brush[COLOR_IDX_GRAY240].CreateSolidBrush(COLOR_GRAY240);
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

	CString msg;
	msg.Format(_T("Barcode Scan LCM ID = [%s]"), Model_Name);
	WriteLogFile(msg);

	BarcodeInfo info = FindDataInDB(Model_Name);

	M_Name = info.name;


	msg.Format(_T("Return Model Name = [%s]"), M_Name);
	WriteLogFile(msg);

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
		m_colorFusingStatus = RGB(255, 0, 0);
		GetDlgItem(IDC_EDIT_MODEL_NAME)->Invalidate();
		GetDlgItem(IDC_EDIT_FUSING_STATUS)->Invalidate();

		GetDlgItem(IDC_EDIT_FUSING_STATUS)->SetWindowText(_T("FUSING FAIL"));

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

				CString msg;
				msg.Format(_T("Model Matching Success"));
				WriteLogFile(msg);
				break;
			}
		}

		if (bFound == false) // 모델 리스트에 MES로 받은 모델명이 없을 경우
		{
			//return _T("");
			CString msg;
			msg.Format(_T("There is no Matching Model Name"));
			AfxMessageBox(msg);

			m_colorFusingStatus = RGB(255,0, 0);
			GetDlgItem(IDC_EDIT_MODEL_NAME)->Invalidate();
			GetDlgItem(IDC_EDIT_FUSING_STATUS)->Invalidate();

			GetDlgItem(IDC_EDIT_FUSING_STATUS)->SetWindowText(_T("Model Matching Fail\r\nPlease add model information"));

			msg.Format(_T("Model Matching Fail"));
			WriteLogFile(msg);

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

			lpSysInfo->f_AutoFusing = true;
			COpBoxFusing Op_Fusing;
			//Op_Fusing.OnBnBcrScanFusing(info.OpBox_Send_Name);
			Op_Fusing.OnBnBcrScanFusing(M_Name);
			lpSysInfo->f_AutoFusing = false;

			m_colorFusingStatus = RGB(0, 255, 0);
			GetDlgItem(IDC_EDIT_MODEL_NAME)->Invalidate();
			GetDlgItem(IDC_EDIT_FUSING_STATUS)->Invalidate();
			GetDlgItem(IDC_EDIT_FUSING_STATUS)->SetWindowText(_T("FUSING OK"));

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

	//SetDlgItemText(IDC_EDIT_FOLDER, "");

}

//void CTS_WR_HS_FUSINGDlg::OnBnClickedBtnFusing()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//
//	//execGetVersionCheck();
//
//	OnBnClickedBtnSave();
//
//	if(m_pApp->m_b232Open == FALSE)
//	{
//		AfxMessageBox("Fusing FAIL. Comport is not Opened.", MB_ICONERROR|MB_OK);
//		return;
//	}
//
//	if(execSystemFusing() == 0)
//	{
//		/* 2019.04.02. KSM. 1st 패턴 삭제. */
//		//Sleep(100);
//		//exec1stPatternFusing();
//
//		Sleep(100);
//		execPatternFusing();
//
//		Sleep(100);
//		execControlIOFusing();
//
//		AfxMessageBox("Fusing Success.", MB_ICONINFORMATION|MB_OK);
//	}
//}

void CTS_WR_HS_FUSINGDlg::OnBnClickedBtnFusing()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	COpBoxFusing OpFusing;
	CString modelText;
	GetDlgItemText(IDC_EDT_MODEL, modelText);
	lpSysInfo->f_AutoFusing = true;
	OpFusing.OnBnBcrScanFusing(modelText);
	lpSysInfo->f_AutoFusing = false;
}


void CTS_WR_HS_FUSINGDlg::OnBnClickedBtnClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	WriteLogFile(_T("Program Exit"));
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
	hbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_LOGO));
	tbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_TEST));
	sbit = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_SYSTEM));

	CtrlLogo.SetBitmap(hbit);
	CtrlSelect.SetBitmap(tbit);
	CtrlSystem.SetBitmap(sbit);
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

	m_Font[0].CreateFont(150, 70, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[1].CreateFont(50, 30, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	


	//for (int id : {IDC_STATIC1, IDC_STATIC2, IDC_STATIC3, IDC_STATIC4, IDC_STATIC5, IDC_STATIC6, IDC_STATIC7, IDC_STATIC8, IDC_STATIC9, IDC_STATIC10, IDC_STATIC11, IDC_STATIC12
	//	, IDC_STATIC13, IDC_STATIC14, IDC_STATIC15, IDC_STATIC16, IDC_STATIC17, IDC_STATIC18, IDC_STATIC19, IDC_STATIC20, IDC_STATIC21, IDC_STATIC22
	//	, IDC_STATIC23, IDC_STATIC24, IDC_STATIC25, IDC_STATIC26, IDC_STATIC26, IDC_STATIC28, IDC_STATIC29, IDC_STATIC30, IDC_STATIC31, IDC_STATIC32
	//	, IDC_STATIC33, IDC_STATIC34, IDC_STATIC35, IDC_STATIC36, IDC_STATIC37, IDC_STATIC38, IDC_STATIC39, IDC_STATIC40, IDC_STATIC41, IDC_STATIC42
	//	, IDC_STATIC43, IDC_STATIC44, IDC_STATIC45, IDC_STATIC46, IDC_STATIC47, IDC_STATIC48, IDC_STATIC49, IDC_STATIC50, IDC_STATIC51})
	//{
	//	CWnd* pWnd = GetDlgItem(id);
	//	if (pWnd != nullptr)
	//	{
	//		// 크기만 바꾸고 위치는 그대로
	//		CRect rect;
	//		pWnd->GetWindowRect(&rect);
	//		ScreenToClient(&rect);

	//		int newWidth = rect.Width() + 50;   // 가로 +50
	//		int newHeight = rect.Height() + 20;  // 세로 +20

	//		pWnd->SetWindowPos(nullptr,
	//			rect.left, rect.top,
	//			newWidth, newHeight,
	//			SWP_NOZORDER | SWP_NOMOVE);
	//	}
	//}

	m_Font[2].CreateFont(26, 10, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[3].CreateFont(23, 10, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[4].CreateFont(21, 9, 0, 0, FW_DONTCARE, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[5].CreateFont(19, 8, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[6].CreateFont(17, 7, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[7].CreateFont(15, 6, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[8].CreateFont(13, 5, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[9].CreateFont(11, 4, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);

	m_Font[10].CreateFont(23, 10, 0, 0, FW_DONTCARE, 0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_FONT);


	// Model Information

	//////////////////
	GetDlgItem(IDC_STATIC_CONNECT2)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_STATIC_CONNECT3)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_STATIC_CONNECT4)->SetFont(&m_Font[2]);
	/// PG TIMMING //
	GetDlgItem(IDC_GRP_TIMMING)->SetFont(&m_Font[2]);

	GetDlgItem(IDC_STATIC1)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC2)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC3)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC4)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC5)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC6)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC7)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC8)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC9)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC10)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC11)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC12)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC13)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC14)->SetFont(&m_Font[10]);

	GetDlgItem(IDC_EDT_MCLK)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_H_TOTAL)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_H_WIDTH)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_HACTIVE)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_HBPORCH)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_HFPORCH)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_CMB_PIXEL)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_CMB_SWAP)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_V_TOTAL)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_V_WIDTH)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_VACTIVE)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_VBPORCH)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_VFPORCH)->SetFont(&m_Font[10]);
	////////////////////

	// PATTERN
	GetDlgItem(IDC_GRP_PATTERN)->SetFont(&m_Font[2]);

	GetDlgItem(IDC_STT_PAT_NAME)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STT_PAT_GRAY)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_CMB_PAT_NAME)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_PAT_GRAY)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_LIST_PATVIEW)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_BTN_PAT_ADD)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_BTN_PAT_CHG)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_BTN_PAT_UP)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_BTN_PAT_DEL)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_BTN_PAT_DN)->SetFont(&m_Font[10]);
	/////////////////////

	// IF-[SIGNAL]
	GetDlgItem(IDC_GRP_SIGNAL)->SetFont(&m_Font[2]);

	GetDlgItem(IDC_STATIC15)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STATIC16)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STATIC17)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STATIC18)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STATIC19)->SetFont(&m_Font[4]);

	GetDlgItem(IDC_CMB_TYPE)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_CMB_BIT)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_CMB_COPEN)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_CMB_PEMPH)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_CMB_DIVISION)->SetFont(&m_Font[10]);
	/////////////////////

	// IF-[GPIO]
	GetDlgItem(IDC_GRP_GPIO)->SetFont(&m_Font[2]);

	GetDlgItem(IDC_STATIC20)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC21)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC22)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC23)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC24)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC25)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC26)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC27)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_CMB_GP1)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_CMB_GP2)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_CMB_GP3)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_CMB_GP4)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_CMB_GP5)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_CMB_GP6)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_CMB_GP7)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_CMB_GP8)->SetFont(&m_Font[10]);
	/////////////////////

	// SET FUNCTION
	GetDlgItem(IDC_GRP_FUNCTION)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_BUTTON_FLICKER)->SetFont(&m_Font[10]);
	/////////////////////

	// POWER[VOLT SET]
	GetDlgItem(IDC_GRP_PWRVOLCUR)->SetFont(&m_Font[2]);
	GetDlgItem(IDC_CMB_PWR_TYP)->SetFont(&m_Font[2]);

	GetDlgItem(IDC_STATIC31)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC32)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC33)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC34)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC35)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC36)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC37)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_SVCC)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_SVDD)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_SVBL)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_SVBL2)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_OVCC)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_OVBL)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_OVBL2)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC_STR_CNT)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC_STR_PWR_ID)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_STR_CNT1)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_STR_CNT2)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_STR_PWR_ID)->SetFont(&m_Font[10]);
	/////////////////////


	// POWER[LIMIT]
	GetDlgItem(IDC_GRP_PWRLIMIT)->SetFont(&m_Font[2]);

	GetDlgItem(IDC_STATIC38)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC39)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC40)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC41)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC42)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC43)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC44)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC45)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC46)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC47)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC48)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC49)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC50)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_STATIC51)->SetFont(&m_Font[10]);

	GetDlgItem(IDC_EDT_LICC)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_LIDD)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_LIBL)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_LIBL2)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_HICC)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_HIDD)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_HIBL)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_HIBL2)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_LVCC)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_LVDD)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_LVBL)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_LVBL2)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_HVCC)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_HVDD)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_HVBL)->SetFont(&m_Font[10]);
	GetDlgItem(IDC_EDT_HVBL2)->SetFont(&m_Font[10]);
	/////////////////////

	// POWER[SEQUENCE]
	GetDlgItem(IDC_GRP_PWRSEQ)->SetFont(&m_Font[2]);

	GetDlgItem(IDC_SEQ1_SEL)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_SEQ2_SEL)->SetFont(&m_Font[4]);

	GetDlgItem(IDC_EDT_TSEQ1)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STATIC28)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_EDT_TSEQ2)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STATIC29)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_EDT_TSEQ3)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STATIC30)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_EDT_TSEQ4)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_STT_SEQOFF_DIN_CNT)->SetFont(&m_Font[4]);
	GetDlgItem(IDC_EDT_SEQOFF_COUNT)->SetFont(&m_Font[4]);
	/////////////////////

	// BARCODE SCAN
	GetDlgItem(IDC_GRP_MODEL3)->SetFont(&m_Font[2]);

	GetDlgItem(IDC_STATIC52)->SetFont(&m_Font[8]);
	GetDlgItem(IDC_STATIC53)->SetFont(&m_Font[8]);
	GetDlgItem(IDC_EDIT_PN)->SetFont(&m_Font[8]);
	GetDlgItem(IDC_EDIT_MODEL_NAME)->SetFont(&m_Font[8]);
	GetDlgItem(IDC_EDIT_FUSING_STATUS)->SetFont(&m_Font[2]);
	/////////////////////

	// Title

	/////////////////////


	GetDlgItem(IDC_STATIC_RS232)->SetFont(&m_Font[6]);
	GetDlgItem(IDC_STATIC_MES)->SetFont(&m_Font[6]);
	GetDlgItem(IDC_STATIC_CONNECT)->SetFont(&m_Font[6]);
}


void CTS_WR_HS_FUSINGDlg::initControl(void)
{
	fucAllPtnList();
	fucAllModelList();

	WriteInitFile(); // init txt 생성

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
	Write_ModelFile(pModelName, "RESOLUTION", "PIXEL",	lpModelInfo->nPixel, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "RESOLUTION", "SWAP",	lpModelInfo->nSwap, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "RESOLUTION", "MCLK",	lpModelInfo->fMclk, lpSysInfo->m_sModelSavePath);

	Write_ModelFile(pModelName, "RESOLUTION", "H_TOTAL", lpModelInfo->nHtotal, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "RESOLUTION", "H_WIDTH", lpModelInfo->nHwidth, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "RESOLUTION", "H_ACTIVE", lpModelInfo->nHact, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "RESOLUTION", "H_BP",	lpModelInfo->nHBP, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "RESOLUTION", "H_FP",	lpModelInfo->nHFP, lpSysInfo->m_sModelSavePath);

	Write_ModelFile(pModelName, "RESOLUTION", "V_TOTAL", lpModelInfo->nVtotal, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "RESOLUTION", "V_WIDTH", lpModelInfo->nVwidth, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "RESOLUTION", "V_ACTIVE", lpModelInfo->nVact, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "RESOLUTION", "V_BP",	lpModelInfo->nVBP, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "RESOLUTION", "V_FP",	lpModelInfo->nVFP, lpSysInfo->m_sModelSavePath);

	/**********************************************************************************************************/
	Write_ModelFile(pModelName, "INTERFACE", "SIGNAL_TYPE",		lpModelInfo->nSigType, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "INTERFACE", "SIGNAL_BIT",		lpModelInfo->nSigBit, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "INTERFACE", "BIT_SEL",			lpModelInfo->nBitSel, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "INTERFACE", "LVDS_SEL",		lpModelInfo->nLvdsSel, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "INTERFACE", "DATA_FORMAT",		lpModelInfo->nDataFormat, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "INTERFACE", "PRE_EMPHASIS",	lpModelInfo->nPreEmph, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "INTERFACE", "DIV_MODE",		lpModelInfo->nDIVmode, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "INTERFACE", "COPEN_CHK",		lpModelInfo->nCopenChk, lpSysInfo->m_sModelSavePath);

	Write_ModelFile(pModelName, "INTERFACE", "GPIO1",	lpModelInfo->nGPIO[0], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "INTERFACE", "GPIO2",	lpModelInfo->nGPIO[1], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "INTERFACE", "GPIO3",	lpModelInfo->nGPIO[2], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "INTERFACE", "GPIO4",	lpModelInfo->nGPIO[3], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "INTERFACE", "GPIO5",	lpModelInfo->nGPIO[4], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "INTERFACE", "GPIO6",	lpModelInfo->nGPIO[5], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "INTERFACE", "GPIO7",	lpModelInfo->nGPIO[6], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "INTERFACE", "GPIO8",	lpModelInfo->nGPIO[7], lpSysInfo->m_sModelSavePath);

	/**********************************************************************************************************/
	Write_ModelFile(pModelName, "POWER_SEQ", "SEQ_SELECTION",	lpModelInfo->nSeqSel, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "POWER_SEQ", "SEQ_TIME_1",		lpModelInfo->nTSeq[0], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "POWER_SEQ", "SEQ_TIME_2",		lpModelInfo->nTSeq[1], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "POWER_SEQ", "SEQ_TIME_3",		lpModelInfo->nTSeq[2], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "POWER_SEQ", "SEQ_TIME_4",		lpModelInfo->nTSeq[3], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "POWER_SEQ", "SEQ_OFF_DIN",		lpModelInfo->nPowerSeqOffDinCount, lpSysInfo->m_sModelSavePath);

	/**********************************************************************************************************/
	Write_ModelFile(pModelName, "POWER_SET", "VCC",		lpModelInfo->fPWR_SetVOLT[0], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "POWER_SET", "VDD",		lpModelInfo->fPWR_SetVOLT[1], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "POWER_SET", "VBL",		lpModelInfo->fPWR_SetVOLT[2], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "POWER_SET", "VBL2",	lpModelInfo->fPWR_SetADD_VBL, lpSysInfo->m_sModelSavePath);

	Write_ModelFile(pModelName, "POWER_SET", "VCC_OFFSET",	lpModelInfo->fPWR_OFFSET[0], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "POWER_SET", "VBL_OFFSET",	lpModelInfo->fPWR_OFFSET[1], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "POWER_SET", "VBL2_OFFSET",	lpModelInfo->fPWR_SetADD_CURR, lpSysInfo->m_sModelSavePath);

	/**********************************************************************************************************/
	Write_ModelFile(pModelName, "POWER_LIMIT", "ICC_LOW",	lpModelInfo->nPWR_currLIMIT[LIMIT_LOW][0], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "POWER_LIMIT", "IDD_LOW",	lpModelInfo->nPWR_currLIMIT[LIMIT_LOW][1], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "POWER_LIMIT", "IBL_LOW",	lpModelInfo->nPWR_currLIMIT[LIMIT_LOW][2], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "POWER_LIMIT", "IBL2_LOW",	lpModelInfo->nPWR_AddVBL_CurrLIMIT[0], lpSysInfo->m_sModelSavePath);

	Write_ModelFile(pModelName, "POWER_LIMIT", "ICC_HIGH",	lpModelInfo->nPWR_currLIMIT[LIMIT_HIGH][0], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "POWER_LIMIT", "IDD_HIGH",	lpModelInfo->nPWR_currLIMIT[LIMIT_HIGH][1], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "POWER_LIMIT", "IBL_HIGH",	lpModelInfo->nPWR_currLIMIT[LIMIT_HIGH][2], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "POWER_LIMIT", "IBL2_HIGH",	lpModelInfo->nPWR_AddVBL_CurrLIMIT[1], lpSysInfo->m_sModelSavePath);

	/**********************************************************************************************************/
	Write_ModelFile(pModelName, "POWER_LIMIT", "VCC_LOW",	lpModelInfo->fPWR_voltLIMIT[LIMIT_LOW][0], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "POWER_LIMIT", "VDD_LOW",	lpModelInfo->fPWR_voltLIMIT[LIMIT_LOW][1], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "POWER_LIMIT", "VBL_LOW",	lpModelInfo->fPWR_voltLIMIT[LIMIT_LOW][2], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "POWER_LIMIT", "VBL2_LOW",	lpModelInfo->fPWR_AddVBL_VoltLIMIT[0], lpSysInfo->m_sModelSavePath);

	Write_ModelFile(pModelName, "POWER_LIMIT", "VCC_HIGH",	lpModelInfo->fPWR_voltLIMIT[LIMIT_HIGH][0], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "POWER_LIMIT", "VDD_HIGH",	lpModelInfo->fPWR_voltLIMIT[LIMIT_HIGH][1], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "POWER_LIMIT", "VBL_HIGH",	lpModelInfo->fPWR_voltLIMIT[LIMIT_HIGH][2], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "POWER_LIMIT", "VBL2_HIGH",	lpModelInfo->fPWR_AddVBL_VoltLIMIT[1], lpSysInfo->m_sModelSavePath);

	/**********************************************************************************************************/
	Write_ModelFile(pModelName, "FLICKER", "VCOM_MODE", lpModelInfo->nVcomMode, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "FLICKER", "VCOM_IC", lpModelInfo->nVcomIc, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "FLICKER", "VCOM_DEFAULT", lpModelInfo->nVcomDefValue, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "FLICKER", "VCOM_MIN", lpModelInfo->nVcomMinValue, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "FLICKER", "VCOM_MAX", lpModelInfo->nVcomMaxValue, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "FLICKER", "VCOM_DEV_ADDR", lpModelInfo->nVcomDevAddr, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "FLICKER", "VCOM_DATA_SIZE", lpModelInfo->nVcomDataSize, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "FLICKER", "VCOM_REG_ADDR", lpModelInfo->nVcomVolRegAddr, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "FLICKER", "VCOM_CONTROL_ADDR", lpModelInfo->nVcomNonVol_ControlAddr, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "FLICKER", "VCOM_WR_DATA", lpModelInfo->nVcomNonVol_WrData, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "FLICKER", "VCOM_RD_DATA", lpModelInfo->nVcomNonVol_RdData, lpSysInfo->m_sModelSavePath);

	/**********************************************************************************************************/
	Write_ModelFile(pModelName, "POWER_SET", "POWER_TYPE", lpModelInfo->nPowerType, lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "POWER_SET", "STR_CNT1", lpModelInfo->nStringCount[0], lpSysInfo->m_sModelSavePath);
	Write_ModelFile(pModelName, "POWER_SET", "STR_CNT2", lpModelInfo->nStringCount[1], lpSysInfo->m_sModelSavePath);

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
		Write_ModelFile(pModelName, "FUSING_PATTERN", szModKey, "", lpSysInfo->m_sModelSavePath);

		sprintf(szModKey, "PTN%02d_GRAY", nLoop);
		Write_ModelFile(pModelName, "FUSING_PATTERN", szModKey, "", lpSysInfo->m_sModelSavePath);
	}
	
	
	for(nLoop=0; nLoop<nItemCnt; nLoop++)
	{
		sprintf(szModKey, "PTN%02d_NAME", nLoop);
		m_LCctrlPtnView.GetItemText( nLoop, 0, (LPSTR)(LPCSTR)szPtnName, sizeof(szPtnName));
		Write_ModelFile(pModelName, "FUSING_PATTERN", szModKey, szPtnName, lpSysInfo->m_sModelSavePath);

		sprintf(szModKey, "PTN%02d_GRAY", nLoop);
		m_LCctrlPtnView.GetItemText( nLoop, 1, (LPSTR)(LPCSTR)szPtnGray, sizeof(szPtnGray));
		Write_ModelFile(pModelName, "FUSING_PATTERN", szModKey, szPtnGray, lpSysInfo->m_sModelSavePath);
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

	//nPortNum = lpSysInfo->m_ComPort - 1;

	//if(m_pApp->cfgUart(nPortNum+1) == TRUE)
	//if(m_pApp->cfgUart(lpSysInfo->m_ComPort) == TRUE && lpSysInfo->f_ComPort == false)
	if(m_pApp->cfgUart(lpSysInfo->m_ComPort))
	{//OK
		//strTemp.Format("COM%d, PORT OPEN OK.", nPortNum+1);
		/*strTemp.Format("COM%d, PORT OPEN OK. ", lpSysInfo->m_ComPort);
		AfxMessageBox(strTemp, MB_ICONINFORMATION|MB_OK);*/
		lpSysInfo->f_ComPort = true;
		//m_colorRs232Bg = RGB(0, 255, 0);  // 초록색
		//GetDlgItem(IDC_STATIC_RS232)->Invalidate();
		CString msg;
		msg.Format(_T("Port[%d] Connect"), lpSysInfo->m_ComPort);
		WriteLogFile(msg);
	}
	else
	{
		/*m_colorRs232Bg = RGB(255, 0, 0);
		GetDlgItem(IDC_STATIC_RS232)->Invalidate();*/
		/*strTemp.Format("NOT CONNECT COM%d PORT.", nPortNum + 1);
		AfxMessageBox(strTemp, MB_ICONINFORMATION | MB_OK);*/
		CString msg;
		msg.Format(_T("Port[%d] Fail"), lpSysInfo->m_ComPort);
		WriteLogFile(msg);
	}

	if (lpSysInfo->m_sUserID == "PM")
	{
		if (CheckOracleDBConnection())
		{
			//AfxMessageBox(_T("DB 연결 성공!"));
			m_colorMesBg = RGB(0, 255, 0);
			GetDlgItem(IDC_STATIC_MES)->Invalidate();
			WriteLogFile(_T("MES SERVER Connect"));
		}
		else
		{
			AfxMessageBox(_T("DB Connect Fail"));
			m_colorMesBg = RGB(255, 0, 0);
			GetDlgItem(IDC_STATIC_MES)->Invalidate();
			WriteLogFile(_T("MES SERVER Fail"));
		}
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
//BarcodeInfo CTS_WR_HS_FUSINGDlg::FindDataInDB(CString partNumber)
//{
//	BarcodeInfo result; // 반환할 결과 객체
//
//	// 1. ODBC 핸들 변수 선언
//	SQLHENV hEnv = NULL;
//	SQLHDBC hDbc = NULL;
//	SQLHSTMT hStmt = NULL;
//	SQLRETURN ret;
//
//	// 2. ODBC 환경 설정 및 DB 연결
//	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
//	SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
//	SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);
//
//	ret = SQLConnectW(hDbc,
//		(SQLWCHAR*)L"OracleDB", SQL_NTS,
//		(SQLWCHAR*)L"system", SQL_NTS,
//		(SQLWCHAR*)L"1234", SQL_NTS);
//
//	// 3. 연결 성공 시 쿼리 실행
//	if (SQL_SUCCEEDED(ret)) {
//		SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
//		//SQLExecDirectW(hStmt, (SQLWCHAR*)L"SELECT * FROM BARCORD", SQL_NTS);
//		SQLExecDirectW(hStmt, (SQLWCHAR*)L"SELECT ID, PN, MODEL_NAME FROM MODEL_INFO", SQL_NTS);
//
//		SQLINTEGER modelNum_db;
//		SQLCHAR pn_db[64];
//		SQLCHAR name_db[64];
//
//		SQLBindCol(hStmt, 1, SQL_C_SLONG, &modelNum_db, 0, NULL);
//		SQLBindCol(hStmt, 2, SQL_C_CHAR, pn_db, sizeof(pn_db), NULL);
//		SQLBindCol(hStmt, 3, SQL_C_CHAR, name_db, sizeof(name_db), NULL);
//
//		// 4. 결과를 한 줄씩 가져와서 입력받은 partNumber와 비교
//		while (SQLFetch(hStmt) == SQL_SUCCESS) {
//			// DB에서 읽은 pn_db 값을 CString으로 변환하여 비교
//			if (partNumber == CString(pn_db))
//			{
//				// 일치하는 데이터를 찾았으면 결과 객체에 저장
//				result.modelNum = modelNum_db;
//				result.pn = CString(pn_db);
//				result.name = CString(name_db);
//				result.found = true; // 찾았다고 표시
//				break; // 루프 종료
//			}
//		}
//		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
//	}
//	else {
//		AfxMessageBox(_T("DB 연결에 실패했습니다."));
//	}
//
//	// 5. 연결 해제 및 핸들 정리
//	SQLDisconnect(hDbc);
//	SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
//	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
//
//	return result; // 최종 결과 반환
//}
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

	/*ret = SQLConnectW(hDbc,
		(SQLWCHAR*)L"OracleDB", SQL_NTS,
		(SQLWCHAR*)L"system", SQL_NTS,
		(SQLWCHAR*)L"1234", SQL_NTS);*/
	ret = SQLConnectW(hDbc,
		/*(SQLWCHAR*)L"Oracle1523", SQL_NTS,*/
		(SQLWCHAR*)L"OracleWifi", SQL_NTS,
		(SQLWCHAR*)L"system", SQL_NTS,
		(SQLWCHAR*)L"4321", SQL_NTS);

	// 3. 연결 성공 시 쿼리 실행
	if (SQL_SUCCEEDED(ret)) {
		SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

		// 3-1. partNumber를 쿼리에 포함
		CStringW queryW;
		//queryW.Format(L"SELECT * FROM MODEL_INFO WHERE PN = 'EAJ65813801'");
		//queryW.Format(L"SELECT GET_MODEL_NAME_BY_BARCODE('%s') FROM DUAL", (LPCWSTR)CStringW(partNumber));
		queryW.Format(L"SELECT FNC_RETURN_MODEL_BY_LCM('%s') FROM DUAL", (LPCWSTR)CStringW(partNumber));

		CString msg = _T("Barcode Scan ") + CString(queryW);
		WriteLogFile(msg);

		ret = SQLExecDirectW(hStmt, (SQLWCHAR*)queryW.GetString(), SQL_NTS);

		if (SQL_SUCCEEDED(ret)) {
			SQLINTEGER modelNum_db;
			SQLCHAR pn_db[64];
			SQLCHAR name_db[64];

			/*SQLBindCol(hStmt, 1, SQL_C_SLONG, &modelNum_db, 0, NULL);
			SQLBindCol(hStmt, 2, SQL_C_CHAR, pn_db, sizeof(pn_db), NULL);*/
			SQLBindCol(hStmt, 1, SQL_C_CHAR, name_db, sizeof(name_db), NULL);

			// 결과가 1건이면 가져옴
			/*if (SQLFetch(hStmt) == SQL_SUCCESS) {
				result.modelNum = modelNum_db;
				result.pn = CString(pn_db);
				result.name = CString(name_db);
				result.found = true;
			}*/
			if (SQLFetch(hStmt) == SQL_SUCCESS) {
				result.name = CString(name_db);
				result.found = true;

				CString msg;
				msg.Format(_T("Scan Success"));
				WriteLogFile(msg);
			}
		}

		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	}
	else {
		AfxMessageBox(_T("DB 연결에 실패했습니다."));
		CString msg;
		msg.Format(_T("Scan DB Fail"));
		WriteLogFile(msg);
	}

	// 5. 연결 해제 및 핸들 정리
	SQLDisconnect(hDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

	return result;
}

bool CTS_WR_HS_FUSINGDlg::CheckOracleDBConnection()
{
	// 1. ODBC 핸들 변수 선언
	SQLHENV hEnv = NULL;
	SQLHDBC hDbc = NULL;
	SQLRETURN ret;

	// 2. ODBC 환경 설정 및 연결 시도
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
	SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
	SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

	// 3. 연결 시도 (DSN, ID, PW는 실제 환경에 맞게 수정)
	ret = SQLConnectW(hDbc,
		//(SQLWCHAR*)L"Oracle1523", SQL_NTS,
		(SQLWCHAR*)L"OracleWifi", SQL_NTS,
		(SQLWCHAR*)L"system", SQL_NTS,
		(SQLWCHAR*)L"4321", SQL_NTS);

	bool isConnected = SQL_SUCCEEDED(ret);

	// 4. 정리
	if (isConnected)
		SQLDisconnect(hDbc);

	SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

	return isConnected;
}



bool CTS_WR_HS_FUSINGDlg::InsertModelInfoToDB(const BarcodeInfo& info)
{
	SQLHENV hEnv = NULL;
	SQLHDBC hDbc = NULL;
	SQLHSTMT hStmt = NULL;
	SQLRETURN ret;

	// 1. ODBC 환경 초기화
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
	SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
	SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

	// 2. Oracle 연결
	ret = SQLConnectW(hDbc,
		(SQLWCHAR*)L"OracleDB", SQL_NTS,
		(SQLWCHAR*)L"system", SQL_NTS,
		(SQLWCHAR*)L"1234", SQL_NTS);

	if (!SQL_SUCCEEDED(ret)) {
		AfxMessageBox(_T("DB 연결 실패"));
		SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
		SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
		return false;
	}

	// 3. Statement 핸들 생성
	SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

	// 4. INSERT 쿼리 문자열 작성 (간단한 예시로 고정된 값 사용)
	CStringW queryW;
	queryW.Format(
		L"INSERT INTO MODEL_INFO (ID, PIXEL, SWAP, MCLK, H_TOTAL, H_WIDTH, H_ACTIVE, H_BP, H_FP, "
		L"V_TOTAL, V_WIDTH, V_ACTIVE, V_BP, V_FP, SIGNAL_TYPE, SIGNAL_BIT, BIT_SEL, LVDS_SEL, DATA_FORMAT, "
		L"PRE_EMPHASIS, DIV_MODE, COPEN_CHK, GPIO1, GPIO2, GPIO3, GPIO4, GPIO5, GPIO6, GPIO7, GPIO8, "
		L"SEQ_SELECTION, SEQ_TIME_1, SEQ_TIME_2, SEQ_TIME_3, SEQ_TIME_4, SEQ_OFF_DIN, VCC, VDD, VBL, "
		L"VCC_OFFSET, VBL_OFFSET, VBL2, VBL2_OFFSET, ICC_LOW, IDD_LOW, IBL_LOW, IBL2_LOW, ICC_HIGH, IDD_HIGH, "
		L"IBL_HIGH, IBL2_HIGH, VCC_LOW, VDD_LOW, VBL_LOW, VBL2_LOW, VCC_HIGH, VDD_HIGH, VBL_HIGH, VBL2_HIGH, "
		L"VCOM_MODE, VCOM_IC, VCOM_DEFAULT, VCOM_MIN, VCOM_MAX, VCOM_DEV_ADDR, VCOM_DATA_SIZE, VCOM_REG_ADDR, "
		L"VCOM_CONTROL_ADDR, VCOM_WR_DATA, VCOM_RD_DATA, PTN00_NAME, PTN01_NAME, PTN02_NAME, PTN03_NAME, "
		L"PTN04_NAME, PTN05_NAME, PTN06_NAME, PTN07_NAME, PTN08_NAME, PN, MODEL_NAME) "
		L"VALUES (4, 3, 0, 594.000000, 4400, 160, 3840, 40, 360, 2250, 10, 2160, 30, 50, 1, 2, 0, 0, 0, 1, 0, 0, "
		L"1, 1, 1, 1, 1, 1, 1, 1, 0, 10, 100, 300, 500, 11, 12.000000, 5.000000, 76.000000, 0.000000, 0.680000, "
		L"76.000000, 0.680000, 0, 0, 0, 0, 2000, 500, 1000, 1000, 0.000000, 0.000000, 0.000000, 0.000000, "
		L"14.000000, 7.000000, 200.000000, 200.000000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "
		L"'%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
		L"GRAY_255", L"GRAY_200", L"GRAY_127", L"GRAY_64", L"GRAY_0",
		L"RED", L"GREEN", L"BLUE", L"COMPLEX-K(HSE)",
		(LPCWSTR)CStringW(info.pn), (LPCWSTR)CStringW(info.name)
	);

	// 5. SQL 실행

	ret = SQLExecDirectW(hStmt, queryW.GetBuffer(), SQL_NTS);
	queryW.ReleaseBuffer();

	if (SQL_SUCCEEDED(ret)) {
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
		SQLDisconnect(hDbc);
		SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
		SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
		return true;
	}
	else {
		AfxMessageBox(_T("INSERT 실패"));
	}

	SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	SQLDisconnect(hDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
	return false;
}

//// '연결 테스트' 버튼을 클릭했을 때 실행되는 함수
void CTS_WR_HS_FUSINGDlg::OnBnClickedButton2()
{
	/*BarcodeInfo bcr;
	InsertModelInfoToDB(bcr);*/
}



void CTS_WR_HS_FUSINGDlg::OnStnClickedLogo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CTS_WR_HS_FUSINGDlg::OnBnClickedBtnBrowse()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BROWSEINFO bi = { 0 };
	bi.lpszTitle = _T("폴더를 선택하세요");
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

	if (pidl != NULL)
	{
		TCHAR szPath[MAX_PATH];
		if (SHGetPathFromIDList(pidl, szPath))
		{
			m_strFolderPath = szPath;

			// UI에 경로 표시
			SetDlgItemText(IDC_EDIT_FOLDER, m_strFolderPath);
		}
		CoTaskMemFree(pidl);
	}
}


void CTS_WR_HS_FUSINGDlg::OnBnClickedButtonSystem()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CSetSystemDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		
	}
}

void CTS_WR_HS_FUSINGDlg::WriteInitFile()
{
	// 1. INFO 폴더 경로
	CString folderPath = _T(".\\INFO");

	// 2. 파일 경로 설정
	CString filePath = folderPath + _T("\\init.txt");

	// 3. 이미 파일이 존재하면 아무 작업 없이 종료
	if (GetFileAttributes(filePath) != INVALID_FILE_ATTRIBUTES)
	{
		// 파일이 이미 존재하므로 다시 쓰지 않음
		Read_InitFile("SYSTEM", "PORT", &lpSysInfo->m_ComPort);
		return;
	}

	// 4. INFO 폴더 존재 확인, 없으면 생성
	if (GetFileAttributes(folderPath) == INVALID_FILE_ATTRIBUTES)
	{
		if (!CreateDirectory(folderPath, NULL))
		{
			AfxMessageBox(_T("INFO FOLDER CREATE FAIL"));
			return;
		}
	}

	// 5. 저장할 내용 구성
	CString content;
	content += _T("[SYSTEM]\r\n");
	content += _T("PORT=1\r\n");

	// 6. 파일 쓰기
	CStdioFile file;
	if (file.Open(filePath, CFile::modeCreate | CFile::modeWrite | CFile::typeText))
	{
		file.WriteString(content);
		file.Close();
	}
	else
	{
		AfxMessageBox(_T("init.txt File Create Fail"));
	}
}




void CTS_WR_HS_FUSINGDlg::OnBnClickedBtnSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strSearch;
	m_editSearch.GetWindowText(strSearch); // Edit Control에서 검색어 가져오기

	if (strSearch.IsEmpty()) {
		AfxMessageBox(_T("검색어를 입력하세요."));
		return;
	}

	// ComboBox에서 항목 검색
	int nCount = ctrlSelModelName.GetCount();
	for (int i = 0; i < nCount; ++i)
	{
		CString strItem;
		ctrlSelModelName.GetLBText(i, strItem); // i번째 아이템 텍스트 가져오기

		if (strItem.Find(strSearch) != -1) // 대소문자 무시 비교
		{
			ctrlSelModelName.SetCurSel(i); // 해당 항목 선택
			OnCbnSelchangeCmbModelName();
			return;
		}
	}

	// 검색 실패 시 메시지
	AfxMessageBox(_T("일치하는 모델명이 없습니다."));
}


void CTS_WR_HS_FUSINGDlg::OnStnClickedPicSelect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strSearch;
	m_editSearch.GetWindowText(strSearch); // Edit Control에서 검색어 가져오기

	if (strSearch.IsEmpty()) {
		AfxMessageBox(_T("검색어를 입력하세요."));
		return;
	}

	// ComboBox에서 항목 검색
	int nCount = ctrlSelModelName.GetCount();
	for (int i = 0; i < nCount; ++i)
	{
		CString strItem;
		ctrlSelModelName.GetLBText(i, strItem); // i번째 아이템 텍스트 가져오기

		if (strItem.Find(strSearch) != -1) // 대소문자 무시 비교
		{
			ctrlSelModelName.SetCurSel(i); // 해당 항목 선택
			OnCbnSelchangeCmbModelName();
			return;
		}
	}

	// 검색 실패 시 메시지
	AfxMessageBox(_T("일치하는 모델명이 없습니다."));
}


void CTS_WR_HS_FUSINGDlg::OnStnClickedPicSystem()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_bSystemClicked = !m_bSystemClicked;

	if (m_bSystemClicked)
		CtrlSystem.SetBitmap(sbit);
	else
		CtrlSystem.SetBitmap(hbit);

	CSetSystemDlg dlg;
	if (dlg.DoModal() == IDOK)
	{

	}
}

void CTS_WR_HS_FUSINGDlg::WriteLogFile(const CString& Log_Message)
{
	// 1. LOG 폴더 경로
	CString folderPath = _T(".\\LOG");

	// 2. 폴더 존재 확인, 없으면 생성
	if (GetFileAttributes(folderPath) == INVALID_FILE_ATTRIBUTES)
	{
		if (!CreateDirectory(folderPath, NULL))
		{
			AfxMessageBox(_T("LOG FOLDER CREATE FAIL"));
			return;
		}
	}

	// 3. 오늘 날짜 파일명 구성 (예: 20250215MLOG.txt)
	CTime curTime = CTime::GetCurrentTime();
	CString dateStr;
	dateStr.Format(_T("%04d%02d%02dMLOG.txt"),
		curTime.GetYear(),
		curTime.GetMonth(),
		curTime.GetDay());

	CString filePath = folderPath + _T("\\") + dateStr;

	// 4. 현재 시간 포맷
	CString timeStr;
	timeStr.Format(_T("%02d:%02d:%02d"),
		curTime.GetHour(),
		curTime.GetMinute(),
		curTime.GetSecond());

	// 5. 로그 라인 구성
	CString logLine;
	logLine.Format(_T("[%s] : %s\r\n"), timeStr, Log_Message);

	// 6. 파일에 Append 모드로 쓰기
	CStdioFile file;
	if (file.Open(filePath,
		CFile::modeWrite | CFile::modeCreate | CFile::typeText | CFile::modeNoTruncate))
	{
		file.SeekToEnd(); // 기존 내용 뒤에 이어쓰기
		file.WriteString(logLine);
		file.Close();
	}
	else
	{
		AfxMessageBox(_T("MLOG.txt File Open Fail"));
	}
}
