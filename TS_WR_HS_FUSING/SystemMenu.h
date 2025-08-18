#pragma once
#include "afxwin.h"


// CSystemMenu 대화 상자입니다.

class CSystemMenu : public CDialog
{
	DECLARE_DYNAMIC(CSystemMenu)

public:
	CSystemMenu(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSystemMenu();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SYSTEM_MENU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

protected:
	LPSYSTEMINFO	lpSystemInfo;
	
	CString FileLoadDialog(CString Temp);
	void Lf_InitControlItem();
	void Lf_InitFont();

public:
	virtual BOOL OnInitDialog();
	CEdit m_edtModelFilePath;
	afx_msg void OnBnClickedBtnModelfilePath();
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnPaint();

private:
	CFont m_FontH1[5];
	CBrush m_Brush[5];
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
