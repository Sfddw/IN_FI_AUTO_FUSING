// SetFlicker.cpp: 구현 파일
//

#include "stdafx.h"
#include "TS_WR_HS_FUSING.h"
#include "afxdialogex.h"
#include "SetFlicker.h"


// SetFlicker 대화 상자

IMPLEMENT_DYNAMIC(SetFlicker, CDialogEx)

SetFlicker::SetFlicker(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SET_FLICKER, pParent)
	, vcom_ctl_addr(_T(""))
	, vcom_default(_T(""))
	, vcom_dev_addr(_T(""))
	, vcom_max(_T(""))
	, vcom_min(_T(""))
	, vcom_reg_addr(_T(""))
	, vcom_rd(_T(""))
	, vcom_wr(_T(""))
{

}

SetFlicker::~SetFlicker()
{
}

void SetFlicker::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DATA_SIZE, comboDataSize);
	DDX_Control(pDX, IDC_COMBO_MODE, comboMode);
	DDX_Control(pDX, IDC_COMBO_VCOM_IC, comboVcomIc);
	DDX_Text(pDX, IDC_EDT_CTL_ADDR, vcom_ctl_addr);
	DDV_MaxChars(pDX, vcom_ctl_addr, 2);
	DDX_Text(pDX, IDC_EDT_DEF, vcom_default);
	DDV_MaxChars(pDX, vcom_default, 3);
	DDX_Text(pDX, IDC_EDT_DEV_ADDR, vcom_dev_addr);
	DDV_MaxChars(pDX, vcom_dev_addr, 2);
	DDX_Text(pDX, IDC_EDT_MAX, vcom_max);
	DDV_MaxChars(pDX, vcom_max, 3);
	DDX_Text(pDX, IDC_EDT_MIN, vcom_min);
	DDV_MaxChars(pDX, vcom_min, 3);
	DDX_Text(pDX, IDC_EDT_REG_ADDR, vcom_reg_addr);
	DDV_MaxChars(pDX, vcom_reg_addr, 2);
	DDX_Text(pDX, IDC_EDT_RD, vcom_rd);
	DDV_MaxChars(pDX, vcom_rd, 2);
	DDX_Text(pDX, IDC_EDT_WR, vcom_wr);
	DDV_MaxChars(pDX, vcom_wr, 2);
	DDX_Control(pDX, IDC_EDT_WR, editWr);
	DDX_Control(pDX, IDC_EDT_REG_ADDR, editRegAddr);
	DDX_Control(pDX, IDC_EDT_RD, editRd);
	DDX_Control(pDX, IDC_EDT_MIN, editMin);
	DDX_Control(pDX, IDC_EDT_MAX, editMax);
	DDX_Control(pDX, IDC_EDT_DEV_ADDR, editDevAddr);
	DDX_Control(pDX, IDC_EDT_DEF, editDefault);
	DDX_Control(pDX, IDC_EDT_CTL_ADDR, editCtlAddr);
}


BEGIN_MESSAGE_MAP(SetFlicker, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &SetFlicker::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_MODE, &SetFlicker::OnCbnSelchangeComboMode)
END_MESSAGE_MAP()


// SetFlicker 메시지 처리기


BOOL SetFlicker::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_pApp = (CTS_WR_HS_FUSINGApp*)AfxGetApp();
	lpModelInfo = m_pApp->GetModelInfo();

	/* Load Values */
	comboMode.SetCurSel(lpModelInfo->nVcomMode);
	comboVcomIc.SetCurSel(lpModelInfo->nVcomIc);
	comboDataSize.SetCurSel(lpModelInfo->nVcomDataSize);

	vcom_default.Format(_T("%d"), lpModelInfo->nVcomDefValue);
	vcom_min.Format(_T("%d"), lpModelInfo->nVcomMinValue);
	vcom_max.Format(_T("%d"), lpModelInfo->nVcomMaxValue);

	vcom_ctl_addr.Format(_T("%2X"), lpModelInfo->nVcomNonVol_ControlAddr);
	vcom_dev_addr.Format(_T("%2X"), lpModelInfo->nVcomDevAddr);
	vcom_reg_addr.Format(_T("%2X"), lpModelInfo->nVcomVolRegAddr);
	vcom_wr.Format(_T("%2X"), lpModelInfo->nVcomNonVol_WrData);
	vcom_rd.Format(_T("%2X"), lpModelInfo->nVcomNonVol_RdData);

	UpdateData(FALSE);

	/* Set Enable */
	if(comboMode.GetCurSel() == 0) SetEnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void SetFlicker::OnBnClickedCancel()
{

	/* 실제 저장은 메인 창에서 SAVE 눌렀을 때 진행..... */
	UpdateData(TRUE);

	lpModelInfo->nVcomMode = comboMode.GetCurSel();
	lpModelInfo->nVcomIc = comboVcomIc.GetCurSel();
	lpModelInfo->nVcomDataSize = comboDataSize.GetCurSel();

	lpModelInfo->nVcomDefValue = _ttoi(vcom_default);
	lpModelInfo->nVcomMinValue = _ttoi(vcom_min);
	lpModelInfo->nVcomMaxValue = _ttoi(vcom_max);

	lpModelInfo->nVcomNonVol_ControlAddr = _tcstol(vcom_ctl_addr, NULL, 16);
	lpModelInfo->nVcomDevAddr = _tcstol(vcom_dev_addr, NULL, 16);
	lpModelInfo->nVcomVolRegAddr = _tcstol(vcom_reg_addr, NULL, 16);
	lpModelInfo->nVcomNonVol_WrData = _tcstol(vcom_wr, NULL, 16);
	lpModelInfo->nVcomNonVol_RdData = _tcstol(vcom_rd, NULL, 16);

	CDialogEx::OnCancel();
}

void SetFlicker::SetEnableWindow(const BOOL isEnable)
{
	comboVcomIc.EnableWindow(isEnable);
	comboDataSize.EnableWindow(isEnable);
	editDefault.EnableWindow(isEnable);
	editMin.EnableWindow(isEnable);
	editMax.EnableWindow(isEnable);
	editCtlAddr.EnableWindow(isEnable);
	editDevAddr.EnableWindow(isEnable);
	editRegAddr.EnableWindow(isEnable);
	editWr.EnableWindow(isEnable);
	editRd.EnableWindow(isEnable);
}


void SetFlicker::OnCbnSelchangeComboMode()
{
	if (comboMode.GetCurSel() == 0)
	{
		SetEnableWindow(FALSE);
	}
	else
	{
		SetEnableWindow(TRUE);
	}
}
