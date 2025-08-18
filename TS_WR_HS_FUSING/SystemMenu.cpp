// SystemMenu.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TS_WR_HS_FUSING.h"
#include "SystemMenu.h"


// CSystemMenu 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSystemMenu, CDialog)

CSystemMenu::CSystemMenu(CWnd* pParent /*=NULL*/)
	: CDialog(CSystemMenu::IDD, pParent)
{

}

CSystemMenu::~CSystemMenu()
{
}

void CSystemMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MODELNAME_PATH, m_edtModelFilePath);
}


BEGIN_MESSAGE_MAP(CSystemMenu, CDialog)
	ON_BN_CLICKED(IDC_BTN_MODELFILE_PATH, &CSystemMenu::OnBnClickedBtnModelfilePath)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CSystemMenu::OnBnClickedBtnSave)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSystemMenu 메시지 처리기입니다.

BOOL CSystemMenu::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	lpSystemInfo	= m_pApp->GetSystemInfo();

	Lf_InitControlItem();
	Lf_InitFont();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CSystemMenu::Lf_InitControlItem()
{
	m_edtModelFilePath.SetWindowText(lpSystemInfo->m_sModelNamePath);
}

void CSystemMenu::OnBnClickedBtnModelfilePath()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sdata;

	UpdateData(TRUE);
	m_edtModelFilePath.GetWindowText(sdata);
	m_edtModelFilePath.SetWindowText(FileLoadDialog(sdata));
	UpdateData(FALSE);
}

CString CSystemMenu::FileLoadDialog(CString Temp)
{
	ITEMIDLIST *pidlBrowse;
	BROWSEINFO BrInfo;
	TCHAR pszPathname[256];
	BOOL bRtn=FALSE;

	_stprintf_s(pszPathname, _T("%s"), Temp);	
	BrInfo.hwndOwner = GetSafeHwnd();
	BrInfo.pidlRoot = NULL;
	memset(&BrInfo, 0, sizeof(BrInfo));
	BrInfo.pszDisplayName = NULL;

	BrInfo.lpszTitle = _T("Select Folder";)
		BrInfo.ulFlags = BIF_RETURNONLYFSDIRS;

	BrInfo.ulFlags = BIF_RETURNONLYFSDIRS;
	BrInfo.lpfn = BrowseForFolder_CallbackProc;
	BrInfo.lParam = (LPARAM)pszPathname;

	if(pidlBrowse = SHBrowseForFolder(&BrInfo))
	{
		if(SUCCEEDED(SHGetPathFromIDList(pidlBrowse, pszPathname)))
			bRtn = TRUE;

		LPMALLOC pMalloc;
		if(SUCCEEDED(SHGetMalloc(&pMalloc)))
		{
			pMalloc->Free(pidlBrowse);
			pMalloc->Release();
		}
	}

	if(pidlBrowse != NULL)
	{
		return  pszPathname;
	}
	else
	{
		return Temp;
	}
}

void CSystemMenu::OnBnClickedBtnSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sdata = _T("");
	char szBuff[512]={0,};

	m_edtModelFilePath.GetWindowText(lpSystemInfo->m_sModelNamePath);
	Write_SysIniFile(_T("SYSTEM"),		_T("MODEL_NAME_PATH"),					lpSystemInfo->m_sModelNamePath.GetBuffer(0));
}

void CSystemMenu::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
	CRect rect;
	GetClientRect(&rect);
	rect.bottom = 75;
	dc.FillSolidRect(rect, COLOR_WHITE);
	rect.top = rect.bottom;
	rect.bottom+=3;
	dc.FillSolidRect(rect, COLOR_RED);
}

void CSystemMenu::Lf_InitFont()
{
	m_FontH1[0].CreateFont(55, 20, 0, 0, FW_ULTRABOLD, TRUE, 0, 0, 0, 0, 0, 0, 0, _T("Arial"));
	GetDlgItem(IDC_STT_SYSTEM_MENU_TITLE)->SetFont(&m_FontH1[0]);

	m_FontH1[1].CreateFont(24, 10, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("Arial"));
	GetDlgItem(IDC_BTN_SAVE)->SetFont(&m_FontH1[1]);
	GetDlgItem(IDCANCEL)->SetFont(&m_FontH1[1]);

	m_Brush[0].CreateSolidBrush (COLOR_WHITE);
}

HBRUSH CSystemMenu::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	switch (nCtlColor)
	{
	case CTLCOLOR_MSGBOX:
		break;
	case CTLCOLOR_EDIT:
		break;
	case CTLCOLOR_LISTBOX:
		break;
	case CTLCOLOR_SCROLLBAR:
		break;
	case CTLCOLOR_BTN:
		break;
	case CTLCOLOR_STATIC:
		if(pWnd->GetDlgCtrlID()==IDC_STT_SYSTEM_MENU_TITLE)	
		{
			pDC->SetBkColor(COLOR_WHITE);
			pDC->SetTextColor(COLOR_BLACK);
			return m_Brush[0];
		}
		break;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}
