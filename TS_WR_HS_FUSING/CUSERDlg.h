#pragma once
#include "afxdialogex.h"


// CUSERDlg 대화 상자

class CUSERDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUSERDlg)

public:
	CUSERDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.

	void initControl(void);

	void fucDrawLogin(void);

	virtual ~CUSERDlg();

	LPSYSTEMINFO	lpSysInfo;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USER_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

/// <summary>
/// 사용자 정의 Function
/// </summary>

public:

	void Lf_InitColorBrush();
	void Lf_InitFontset();

protected:
	CFont m_Font[FONT_IDX_MAX];
	CBrush m_Brush[COLOR_IDX_MAX];
	CFont* m_pDefaultFont;

/// 
/// 

public:

	CStatic CtrlLogin;
	CEdit m_nLoginID;

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnBnClickedBtnLogin();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
