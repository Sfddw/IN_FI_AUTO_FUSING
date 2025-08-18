#pragma once
#include "afxwin.h"


// CFWupdateDlg 대화 상자입니다.

class CFWupdateDlg : public CDialog
{
	DECLARE_DYNAMIC(CFWupdateDlg)

public:
	CString strFW_Location;
	CString strFW_HexName;

	CString strHexParsePath;

	unsigned char *szParsingData;
	unsigned long nHexFileSize;

	int HexFileParsing(void);
	int strMakeDataPack(unsigned char *strSrc, unsigned char *szDest, int *cpyLen);

	int funcGotoBoot(void);
	int funcFwComplete(void);
	int procFwUpdate(void);

	CFWupdateDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CFWupdateDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_FW_UPDATE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedBtnBrowseHex();
	CStatic ctrlHexName;
	afx_msg void OnBnClickedBtnUpdate();
	CStatic ctrlUpdateProgress;
};
