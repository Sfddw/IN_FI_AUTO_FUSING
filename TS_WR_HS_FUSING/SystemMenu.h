#pragma once
#include "afxwin.h"


// CSystemMenu ��ȭ �����Դϴ�.

class CSystemMenu : public CDialog
{
	DECLARE_DYNAMIC(CSystemMenu)

public:
	CSystemMenu(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSystemMenu();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SYSTEM_MENU };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
