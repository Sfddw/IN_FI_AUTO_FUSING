
// TS_WR_HS_FUSINGDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"




// CTS_WR_HS_FUSINGDlg 대화 상자
class CTS_WR_HS_FUSINGDlg : public CDialog
{
// 생성입니다.
public:
	CTS_WR_HS_FUSINGDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

	void fucInsertListColum(void);
	void fucPdbDelete(char *szBuff);
	void fucAllPtnList(void);
	void fucPtnDataChange(int sel);
	void fuc1stPtnDataChange(void);
	void fucListCtrlSwapData(int pos1, int pos2);

	void fucDrawLogo(void);

	void funcDefaultTimmingLoad(void);
	void funcDefaultIFLoad(void);
	void funcDefaultPWRLoad(void);
	void funcDefaultGray(void);

	void fucModDelete(char *szBuff);
	void fucAllModelList(void);

	void initFontSet(void);
	void initControl(void);

	void funcModelEditReadOnly(char onoff);

	void funcSaveCtrlToVari(void);
	void funcSaveVariToModelFile(char *pModelName);
	void funcSavePAT_ModelFile(char *pModelName);

	void funcLoadCtrlFormVari(void);
	void funcLoadVariFromModelFile(char *pModelName);
	void funcLoadPAT_ModelFile(char *pModelName);
	void funcUpdatePAT_List(void);
	void funcUpdateModel_List(void);

	/* Command Function */
	int execGetVersionCheck(void);

	int funcGetSignalType(char cmbSignalType);
	int funcMakeSystemFusingPacket(char *pszRtnPack);
	int execSystemFusing(void);

	int funcMake1stPatternFusingPacket(char *pszRtnPack);
	int exec1stPatternFusing(void);

	int funcMakePatternFusingPacket(char *pszRtnPack);
	int execPatternFusing(void);

	int funcMakeCtrlIOFusingPacket(char *pszRtnPacket);
	int execControlIOFusing(void);

	bool funcBarcodeScan();

	CStringArray modelList;

protected:
	CTS_WR_HS_FUSINGApp* m_pApp;
	LPMODELINFO		lpModelInfo;
	
	CComboBox* m_pComboInternal;
	//CComboBox* m_pCmb1stPtn;		/* 2019.04.02. KSM. 1st 패턴 삭제. */
	CComboBox* m_pComboModel;

	CFont mFontH1;
	HBRUSH mHbr;

	bool m_bSavePressed = false; // 키입력 변수




// 대화 상자 데이터입니다.
	enum { IDD = IDD_TS_WR_HS_FUSING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnRs232Receive1(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CComboBox ctrlPgType;
	CComboBox ctrlPgPixel;
	CComboBox ctrlPgBit;
	CComboBox ctrlPgSwap;
	CComboBox ctrlPgDiv;
	CEdit ctrlPgClock;
	CEdit ctrlPgHtotal;
	CEdit ctrlPgHwidth;
	CEdit ctrlPgHactive;
	CEdit ctrlPgHBporch;
	CEdit ctrlPgHFporch;
	CEdit ctrlPgVtotal;
	CEdit ctrlPgVwidth;
	CEdit ctrlPgVactive;
	CEdit ctrlPgVBporch;
	CEdit ctrlPgVFporch;
	CComboBox ctrlIfBitSel;
	CComboBox ctrlIfLvSEL;
	CComboBox ctrlIfDatForm;
	CComboBox ctrlIfPreEmph;

	CEdit ctrlTseq1;
	CEdit ctrlTseq2;
	CEdit ctrlTseq3;
	CEdit ctrlTseq4;
	CEdit ctrlSetVCC;
	CEdit ctrlSetVDD;
	CEdit ctrlSetVBL;
	CEdit ctrlOffVCC;
	CEdit ctrlOffVBL;
	CEdit ctrlLICC;
	CEdit ctrlLIDD;
	CEdit ctrlLIBL;
	CEdit ctrlHICC;
	CEdit ctrlHIDD;
	CEdit ctrlHIBL;
	CEdit ctrlLVCC;
	CEdit ctrlLVDD;
	CEdit ctrlLVBL;
	CEdit ctrlHVCC;
	CEdit ctrlHVDD;
	CEdit ctrlHVBL;
	CEdit ctrlPAT_Gray;
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBtnClose();
//	afx_msg void OnLvnItemchangedListPatview(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_LCctrlPtnView;
	CComboBox ctrlPatList;
	afx_msg void OnBnClickedBtnPatAdd();
	afx_msg void OnBnClickedBtnPatDel();
	afx_msg void OnBnClickedBtnPatChg();
	afx_msg void OnBnClickedBtnPatUp();
	afx_msg void OnBnClickedBtnPatDn();
	CString ctrlEdtMCLK;
	CString ctrlEdtHtotal;
	CString ctrlEdtVtotal;
	CString ctrlEdtHwidth;
	CString ctrlEdtVwidth;
	CString ctrlEdtHact;
	CString ctrlEdtVact;
	CString ctrlEdtHBP;
	CString ctrlEdtVBP;
	CString ctrlEdtHFP;
	CString ctrlEdtVFP;
	CString ctrlEdtTSEQ1;
	CString ctrlEdtTSEQ2;
	CString ctrlEdtTSEQ3;
	CString ctrlEdtTSEQ4;
	CString ctrlEdtSVCC;
	CString ctrlEdtSVDD;
	CString ctrlEdtSVBL;
	CString ctrlEdtOVCC;
	CString ctrlEdtOVBL;
	CString ctrlEdtLICC;
	CString ctrlEdtLIDD;
	CString ctrlEdtLIBL;
	CString ctrlEdtHICC;
	CString ctrlEdtHIDD;
	CString ctrlEdtHIBL;
	CString ctrlEdtLVCC;
	CString ctrlEdtLVDD;
	CString ctrlEdtLVBL;
	CString ctrlEdtHVCC;
	CString ctrlEdtHVDD;
	CString ctrlEdtHVBL;
	int ctrlRadSeqSel;
	afx_msg void OnBnClickedBtnSave();
	CString ctrlEdtPatGray;
	afx_msg void OnBnClickedBtnFusing();
	CString ctrlEdtModelName;
	CComboBox ctrlSelModelName;
	afx_msg void OnCbnSelchangeCmbModelName();
	afx_msg void OnCbnSelchangeCmbModelName(CString Model_Name);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnSaveas();
	CComboBox ctrlGPIO1;
	CComboBox ctrlGPIO2;
	CComboBox ctrlGPIO3;
	CComboBox ctrlGPIO4;
	CComboBox ctrlGPIO5;
	CComboBox ctrlGPIO6;
	CComboBox ctrlGPIO7;
	CComboBox ctrlGPIO8;
	afx_msg void OnBnClickedBtnPortOpen();
	CComboBox ctrlComPort;
	CComboBox ctrl1StPtnSel;
	CString strSeqOffDinCount;
	afx_msg void OnBnClickedBtnFwUpdate();
	CStatic CtrlLogo;
	CComboBox ctrlCopenchk;
	afx_msg void OnBnClickedBtnOpbox();
	afx_msg void OnLvnItemchangedListPatview(NMHDR *pNMHDR, LRESULT *pResult);
	CString ctrlEdtSVBL2;
	CString ctrlEdtOVBL2;
	CString ctrlEdtLIBL2;
	CString ctrlEdtHIBL2;
	CString ctrlEdtLVBL2;
	CString ctrlEdtHVBL2;
	afx_msg void OnBnClickedBtnSystemMenu();
	afx_msg void OnBnClickedButtonFlicker();
	void UpdateModelTotal();
	CComboBox ctrlPwrType;
	CString ctrlStrCnt1;
	CString ctrlStrCnt2;
	CString ctrlStrPwrId;
};


