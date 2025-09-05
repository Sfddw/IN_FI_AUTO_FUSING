#pragma once
#include "afxdialogex.h"
#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"


// CSetSystemDlg 대화 상자

class CSetSystemDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetSystemDlg)

public:
	CSetSystemDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSetSystemDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDC_SET_SYSTEM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	CString m_strOracleName;
	CString m_strUserID;
	CString m_strPassword;

	CString m_strModelFolderPath;
	CString m_strPatternFolderPath;

	virtual void OnOK();

	afx_msg void OnBnClickedButtonSelModel();
	afx_msg void OnBnClickedButtonSelPattern();
	afx_msg void OnBnClickedButtonModelCopyMod();
	afx_msg void OnBnClickedButtonPatternCopyMod();

	DECLARE_MESSAGE_MAP()
};
