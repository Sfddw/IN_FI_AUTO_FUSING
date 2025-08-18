// SystemMenu.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TS_WR_HS_FUSING.h"
#include "SystemMenu.h"


// CSystemMenu ��ȭ �����Դϴ�.

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


// CSystemMenu �޽��� ó�����Դϴ�.

BOOL CSystemMenu::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	lpSystemInfo	= m_pApp->GetSystemInfo();

	Lf_InitControlItem();
	Lf_InitFont();
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CSystemMenu::Lf_InitControlItem()
{
	m_edtModelFilePath.SetWindowText(lpSystemInfo->m_sModelNamePath);
}

void CSystemMenu::OnBnClickedBtnModelfilePath()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString sdata = _T("");
	char szBuff[512]={0,};

	m_edtModelFilePath.GetWindowText(lpSystemInfo->m_sModelNamePath);
	Write_SysIniFile(_T("SYSTEM"),		_T("MODEL_NAME_PATH"),					lpSystemInfo->m_sModelNamePath.GetBuffer(0));
}

void CSystemMenu::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialog::OnPaint()��(��) ȣ������ ���ʽÿ�.
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

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
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
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}
