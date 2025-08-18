#pragma once
#include "afxdialogex.h"


// SetFlicker 대화 상자

class SetFlicker : public CDialogEx
{
	DECLARE_DYNAMIC(SetFlicker)

public:
	SetFlicker(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SetFlicker();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SET_FLICKER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnCbnSelchangeComboMode();
	void SetEnableWindow(BOOL isEnable);

private:
	CTS_WR_HS_FUSINGApp* m_pApp;
	LPMODELINFO	lpModelInfo;

	CComboBox comboDataSize;
	CComboBox comboMode;
	CComboBox comboVcomIc;
	CString vcom_ctl_addr;
	CString vcom_default;
	CString vcom_dev_addr;
	CString vcom_max;
	CString vcom_min;
	CString vcom_reg_addr;
	CString vcom_rd;
	CString vcom_wr;
	CEdit editWr;
	CEdit editRegAddr;
	CEdit editRd;
	CEdit editMin;
	CEdit editMax;
	CEdit editDevAddr;
	CEdit editDefault;
	CEdit editCtlAddr;
};
