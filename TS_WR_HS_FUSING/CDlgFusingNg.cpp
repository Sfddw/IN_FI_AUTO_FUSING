// CDlgFusingNg.cpp: 구현 파일
//

#include "stdafx.h"
#include "TS_WR_HS_FUSING.h"
#include "afxdialogex.h"
#include "CDlgFusingNg.h"


// CDlgFusingNg 대화 상자

IMPLEMENT_DYNAMIC(CDlgFusingNg, CDialogEx)

CDlgFusingNg::CDlgFusingNg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIGA_FUSING_NG, pParent)
{
	m_brushBk.CreateSolidBrush(RGB(255, 0, 0));
}

CDlgFusingNg::~CDlgFusingNg()
{
}

BOOL CDlgFusingNg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (!m_strStatus.IsEmpty())
	{
		CString strText;
		strText.Format(_T("[%s]"), m_strStatus);
		SetDlgItemText(IDC_STATIC_STATUS, strText);
	}
	m_fontBig.CreatePointFont(1000, _T(""));
	m_fontModel.CreatePointFont(400, _T(""));
	GetDlgItem(IDC_STATIC_NG)->SetFont(&m_fontBig);
	GetDlgItem(IDC_STATIC_STATUS)->SetFont(&m_fontModel);

	return TRUE;
}

void CDlgFusingNg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgFusingNg, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDlgFusingNg 메시지 처리기

HBRUSH CDlgFusingNg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_DLG)   // 다이얼로그 배경
	{
		return (HBRUSH)m_brushBk.GetSafeHandle();
	}

	else if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_NG)
		{
			pDC->SetBkMode(TRANSPARENT);               // 글자 배경 투명
			pDC->SetTextColor(RGB(0, 0, 0));     // 검정
			return (HBRUSH)m_brushBk.GetSafeHandle();  // 다이얼로그와 같은 초록색 브러시
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_STATUS)
		{
			pDC->SetBkMode(TRANSPARENT);               // 글자 배경 투명
			pDC->SetTextColor(RGB(255, 255, 255));     // 검정
			return (HBRUSH)m_brushBk.GetSafeHandle();  // 다이얼로그와 같은 초록색 브러시
		}
	}




	return hbr;
}
