
// TS_WR_HS_FUSINGDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

struct BarcodeInfo
{
	int modelNum = 0;
	CString pn = _T("");
	CString name = _T("");
	bool found = false; // 데이터를 찾았는지 여부

	// RESOLUTION
	int PIXEL;
	int SWAP;
	float MCLK;
	int H_TOTAL;
	int H_WIDTH;
	int H_ACTIVE;
	int H_BP;
	int H_FP;
	int V_TOTAL;
	int V_WIDTH;
	int V_ACTIVE;
	int V_BP;
	int V_FP;

	// INTERFACE
	int SIGNAL_TYPE;
	int SIGNAL_BIT;
	int BIT_SEL;
	int LVDS_SEL;
	int DATA_FORMAT;
	int PRE_EMPHASTS;
	int DIV_MODE;
	int COPEN_CHK;
	int GPIO1;
	int GPIO2;
	int GPIO3;
	int GPIO4; 
	int GPIO5;
	int GPIO6;
	int GPIO7;
	int GPIO8;

	// POWER_SEQ
	int SEQ_SELECTION;
	int SEQ_TIME_1;
	int SEQ_TIME_2;
	int SEQ_TIME_3;
	int SEQ_TIME_4;
	int SEQ_OFF_DIN;

	// POWER SET
	float VCC;
	float VDD;
	float VBL;
	float VCC_OFFSET;
	float VBL_OFFSET;
	float VBL2;
	float VBL2_OFFSET;

	// POWER_LIMIT

	int ICC_LOW;
	int IDD_LOW;
	int IBL_LOW;
	int ICC_HIGH;
	int IDD_HIGH;
	int IBL_HIGH;
	float VCC_LOW;
	float VDD_LOW;
	float VBL_LOW;
	float VCC_HIGH;
	float VDD_HIGH;
	float VBL_HIGH;
	int IBL2_LOW;
	int IBL2_HIGH;
	float VBL2_LOW;
	float VBL2_HIGH;

	// FLICKER
	int VCOM_MODE;
	int VCOM_IC;
	int VCOM_DEFAULT;
	int VCOM_MIN;
	int VCOM_MAX;
	int VCOM_DEV_ADDR;
	int VCOM_DATA_SIZE;
	int VCOM_REG_ADDR;
	int VCOM_CONTROL_ADDR;
	int VCOM_WR_DATA;
	int VCOM_RD_DATA;

	// PTN00_NAME ~ PTN08_NAME
	CString PTN00_NAME;
	CString PTN01_NAME;
	CString PTN02_NAME;
	CString PTN03_NAME;
	CString PTN04_NAME;
	CString PTN05_NAME;
	CString PTN06_NAME;
	CString PTN07_NAME;
	CString PTN08_NAME;


};


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

	void WriteInitFile(); // init 메모장 생성

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
	BarcodeInfo FindDataInDB(CString partNumber);
	bool CheckOracleDBConnection();

	bool InsertModelInfoToDB(const BarcodeInfo& info);
	CStringArray modelList;

protected:
	CTS_WR_HS_FUSINGApp* m_pApp;
	LPMODELINFO		lpModelInfo;
	LPSYSTEMINFO	lpSysInfo;
	
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

	COLORREF m_colorRs232Bg;
	COLORREF m_colorMesBg;

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
	afx_msg CString OnCbnSelchangeCmbModelName(CString Model_Name);
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
	afx_msg bool OnBnClickedBcrPortOpen();
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

	CString m_strFolderPath; // 폴더 경로

	CString m_strKeyBuffer;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnStnClickedLogo();
	afx_msg void OnBnClickedBtnBrowse();
	afx_msg void OnBnClickedButtonSystem();
};


