#pragma once
#include "afxdialogex.h"
#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"


// TDlgOk 대화 상자

class TDlgOk : public CDialogEx
{
	DECLARE_DYNAMIC(TDlgOk)

public:
	TDlgOk(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~TDlgOk();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIG_OK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	DECLARE_MESSAGE_MAP()
};
