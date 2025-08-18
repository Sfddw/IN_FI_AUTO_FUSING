#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// COpBoxFusing 대화 상자입니다.

class COpBoxFusing : public CDialog
{
	DECLARE_DYNAMIC(COpBoxFusing)

protected:
	char szSRC_SelModelName[64];
	char szFUSING_SelModelName[64];
	char szFusingModelList[50][64];


	/*****************************************************/
	LPMODELINFO		lpModelInfo;

	void funcLoadPAT_ModelFile(char *pModelName);
	void funcLoadVariFromModelFile(char *pModelName);

	int funcGetSignalType(char cmbSignalType);
	int funcMakeSystemFusingPacket(char *pModelName, char *pszRtnPack);
	int execSystemFusing(char *pModName);

	int funcMakePatternFusingPacket(char *pszRtnPack);
	int execPatternFusing(void);

	int funcMakeCtrlIOFusingPacket(char *pszRtnPacket);
	int execControlIOFusing(void);

	int funcMakeModelVoltCurrentPacket(char *pszRtnPacket);
	int execModelVoltCurrentFusing(void);
	/*****************************************************/
	int execDelAllMod(void);
	int execCreateModelFile(int nModelNumber);
	int procOpBoxFusing(int nModListNumber);


	void funcSaveFusingModelList(void);
	void funcSaveOperationINI(void);

	void funcUpdateFusingModelList(void);
	void funcLoadFusingModel_fromOperationINI(void);



	void funcInitModelList(void);
	void fucModDelete(char *szBuff);
	void fucSRC_AllModelList(void);

	void fucListCtrlSwapData(int pos1, int pos2);



public:
	COpBoxFusing(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~COpBoxFusing();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_OPBOX_FUSING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL DestroyWindow();
	CListCtrl ctrlSrcModelList;
	CListCtrl ctrlFusingModelList;
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnLvnItemchangedListSrcModel(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListFusingModel(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnUp();
	afx_msg void OnBnClickedBtnDn();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnFusing();
	CStatic ctrlOpBoxFusingMsg;
	afx_msg void OnBnClickedBtnExport();
};
