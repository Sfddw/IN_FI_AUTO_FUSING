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

}

CDlgFusingOk::~CDlgFusingOk()
{
}

BOOL CDlgFusingOk::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 다이얼로그 실행 후 5초 뒤에 WM_TIMER 발생
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
END_MESSAGE_MAP()

HBRUSH CDlgFusingOk::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	switch (nCtlColor)
	{
	case CTLCOLOR_STATIC:
		/*if ((pWnd->GetDlgCtrlID() == IDC_STATIC)
			|| pWnd->GetDlgCtrlID() == IDC_STATIC_CONNECT)*/
		if (pWnd->GetDlgCtrlID() == IDOK)
		{
			pDC->SetBkColor(COLOR_SKYBLUE);
			pDC->SetTextColor(COLOR_BLACK);
			return m_Brush[COLOR_IDX_SKYBLUE];
		}
	}
	return hbr;
}

void CDlgFusingOk::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if (nIDCtl == IDOK)
	{
		CDC dc;
		dc.Attach(lpDrawItemStruct->hDC);
		CRect rc = lpDrawItemStruct->rcItem;

		dc.FillSolidRect(rc, RGB(0, 200, 0)); // 초록 배경
		dc.SetTextColor(RGB(255, 255, 255));
		dc.SetBkMode(TRANSPARENT);

		CString text;
		GetDlgItem(IDOK)->GetWindowText(text);
		dc.DrawText(text, rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		dc.Detach();
		return;
	}

	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
// CDlgFusingOk 메시지 처리기
