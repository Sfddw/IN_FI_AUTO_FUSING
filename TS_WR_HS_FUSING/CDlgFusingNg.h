#pragma once
#include "afxdialogex.h"
#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"


// CDlgFusingNg 대화 상자

class CDlgFusingNg : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFusingNg)

public:
	CDlgFusingNg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	BOOL OnInitDialog();
	CString m_strStatus;
	virtual ~CDlgFusingNg();

	

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIGA_FUSING_NG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CBrush m_Brush[COLOR_IDX_MAX];
	CFont m_fontBig; // 큰 글꼴 재사용용(선택)
	CFont m_fontModel; // 큰 글꼴 재사용용(선택)
	CBrush m_brushBk; // 배경색상 변경

	DECLARE_MESSAGE_MAP()
};
