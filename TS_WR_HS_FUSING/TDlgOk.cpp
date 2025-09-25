// TDlgOk.cpp: 구현 파일
//

#include "stdafx.h"
#include "TS_WR_HS_FUSING.h"
#include "afxdialogex.h"
#include "TDlgOk.h"


// TDlgOk 대화 상자

IMPLEMENT_DYNAMIC(TDlgOk, CDialogEx)

TDlgOk::TDlgOk(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIG_OK, pParent)
{

}

BOOL TDlgOk::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 다이얼로그 배경색 칠하기 등 추가 가능
    SetTimer(1, 5000, NULL); // ✅ 5초 후 자동 닫힘

    return TRUE;
}

void TDlgOk::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == 1)
    {
        KillTimer(1);
        EndDialog(IDOK); // 모달 다이얼로그일 경우
    }

    CDialogEx::OnTimer(nIDEvent);
}

TDlgOk::~TDlgOk()
{
}

void TDlgOk::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(TDlgOk, CDialogEx)
END_MESSAGE_MAP()


// TDlgOk 메시지 처리기
