// CDlgFusingOk.cpp: 구현 파일
//

#include "stdafx.h"
#include "TS_WR_HS_FUSING.h"
#include "afxdialogex.h"
#include "CDlgFusingOk.h"


// CDlgFusingOk 대화 상자

IMPLEMENT_DYNAMIC(CDlgFusingOk, CDialogEx)

CDlgFusingOk::CDlgFusingOk(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIGA_FUSING_OK, pParent)
{
    m_brushBk.CreateSolidBrush(RGB(0, 200, 0));
}

CDlgFusingOk::~CDlgFusingOk()
{
}

BOOL CDlgFusingOk::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	

	if (!m_strModelName.IsEmpty())
	{
		CString strText;
		strText.Format(_T("[%s]"), m_strModelName);
		SetDlgItemText(IDC_STATIC_MODELNAME, strText);
	}
	m_fontBig.CreatePointFont(1000, _T(""));
	m_fontModel.CreatePointFont(500, _T(""));
	GetDlgItem(IDC_STATIC_OK)->SetFont(&m_fontBig);
	GetDlgItem(IDC_STATIC_MODELNAME)->SetFont(&m_fontModel);
	GetDlgItem(IDC_STATIC_CHECK)->SetFont(&m_fontModel);

	SetTimer(1, 5000, NULL);  // 1 = 타이머 ID, 5000ms = 5초

	return TRUE;
}

void CDlgFusingOk::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CDlgFusingOk::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)  // 우리가 건 타이머
	{
		KillTimer(1);   // 타이머 해제
		EndDialog(IDOK);  // 5초 뒤 자동 닫힘
	}

	CDialogEx::OnTimer(nIDEvent);
}

BEGIN_MESSAGE_MAP(CDlgFusingOk, CDialogEx)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()
// CDlgFusingOk 메시지 처리기


HBRUSH CDlgFusingOk::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

    if (nCtlColor == CTLCOLOR_DLG)   // ✅ 다이얼로그 배경
    {
        return (HBRUSH)m_brushBk.GetSafeHandle();
    }

	else if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_OK)
		{
			pDC->SetBkMode(TRANSPARENT);               // 글자 배경 투명
			pDC->SetTextColor(RGB(0, 0, 0));     // 검정
			return (HBRUSH)m_brushBk.GetSafeHandle();  // 다이얼로그와 같은 초록색 브러시
		}
		else if((pWnd->GetDlgCtrlID() == IDC_STATIC_MODELNAME || 
			pWnd->GetDlgCtrlID() == IDC_STATIC_CHECK))
		{
			pDC->SetBkMode(TRANSPARENT);               // 글자 배경 투명
			pDC->SetTextColor(RGB(255, 0, 0));     // 검정
			return (HBRUSH)m_brushBk.GetSafeHandle();  // 다이얼로그와 같은 초록색 브러시
		}
	}

    return hbr;
}
