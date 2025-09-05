// CSetSystemDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "TS_WR_HS_FUSING.h"
#include "afxdialogex.h"
#include "CSetSystemDlg.h"


// CSetSystemDlg 대화 상자

IMPLEMENT_DYNAMIC(CSetSystemDlg, CDialogEx)

CSetSystemDlg::CSetSystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDC_SET_SYSTEM, pParent)
{

}

CSetSystemDlg::~CSetSystemDlg()
{
}

void CSetSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ORACLE_NAME, m_strOracleName);
	DDX_Text(pDX, IDC_EDIT_USER_ID, m_strUserID);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
    DDX_Text(pDX, IDC_EDIT_MODELNAME_PATH, m_strModelFolderPath);
    DDX_Text(pDX, IDC_EDIT_PATTERNNAME_PATH, m_strPatternFolderPath);
}




BEGIN_MESSAGE_MAP(CSetSystemDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_MODELCOPY_MOD, &CSetSystemDlg::OnBnClickedButtonModelCopyMod)
    ON_BN_CLICKED(IDC_BUTTON_PATTERNCOPY_MOD, &CSetSystemDlg::OnBnClickedButtonPatternCopyMod)
    ON_BN_CLICKED(IDC_BUTTON_MODEL_PATH, &CSetSystemDlg::OnBnClickedButtonSelModel)
    ON_BN_CLICKED(IDC_BUTTON_PATTERN_PATH, &CSetSystemDlg::OnBnClickedButtonSelPattern)
END_MESSAGE_MAP()


// CSetSystemDlg 메시지 처리기

void CSetSystemDlg::OnOK()
{
	UpdateData(TRUE);

	AfxMessageBox(_T("Oracle Info Saved:\n") + m_strOracleName + _T(", ") + m_strUserID + _T(", ") + m_strPassword);

	CDialogEx::OnOK();
}

void CSetSystemDlg::OnBnClickedButtonSelModel()
{
    BROWSEINFO bi = { 0 };
    TCHAR szDisplayName[MAX_PATH];
    TCHAR szSelectedPath[MAX_PATH];

    bi.hwndOwner = this->m_hWnd;
    bi.lpszTitle = _T("복사할 대상 폴더를 선택하세요");
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    bi.pszDisplayName = szDisplayName;

    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
    if (pidl != NULL)
    {
        if (SHGetPathFromIDList(pidl, szSelectedPath))
        {
            m_strModelFolderPath = szSelectedPath;
            UpdateData(FALSE); // Edit Control에 갱신
        }
    }
}

void CSetSystemDlg::OnBnClickedButtonSelPattern()
{
    BROWSEINFO bi = { 0 };
    TCHAR szDisplayName[MAX_PATH];
    TCHAR szSelectedPath[MAX_PATH];

    bi.hwndOwner = this->m_hWnd;
    bi.lpszTitle = _T("복사할 대상 폴더를 선택하세요");
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    bi.pszDisplayName = szDisplayName;

    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
    if (pidl != NULL)
    {
        if (SHGetPathFromIDList(pidl, szSelectedPath))
        {
            m_strPatternFolderPath = szSelectedPath;
            UpdateData(FALSE); // Edit Control에 갱신
        }
    }
}

void CSetSystemDlg::OnBnClickedButtonModelCopyMod()
{
    UpdateData(TRUE); // m_strFolderPath 업데이트

    if (m_strModelFolderPath.IsEmpty())
    {
        AfxMessageBox(_T("폴더 경로를 먼저 선택해 주세요."));
        return;
    }

    CString sourceFolder = _T("C:\\Users\\time\\Documents\\IN_FI_AUTO_FUSING\\TS_WR_HS_FUSING\\MODEL\\");
    CString destFolder = m_strModelFolderPath;

    if (destFolder.Right(1) != _T("\\"))  // 경로 끝에 \ 없으면 추가
        destFolder += _T("\\");

    CFileFind finder;
    BOOL bWorking = finder.FindFile(sourceFolder + _T("*.MOD"));

    int copiedCount = 0;

    while (bWorking)
    {
        bWorking = finder.FindNextFile();

        if (finder.IsDots() || finder.IsDirectory())
            continue;

        CString fileName = finder.GetFileName();
        CString sourceFile = sourceFolder + fileName;
        CString destFile = destFolder + fileName;

        if (CopyFile(sourceFile, destFile, FALSE))
        {
            copiedCount++;
        }
        else
        {
            CString err;
            err.Format(_T("파일 복사 실패: %s"), fileName);
            AfxMessageBox(err);
        }
    }

    CString msg;
    msg.Format(_T("총 %d개 .MOD 파일을 복사했습니다."), copiedCount);
    AfxMessageBox(msg);
}

void CSetSystemDlg::OnBnClickedButtonPatternCopyMod()
{
    UpdateData(TRUE); // m_strModelFolderPath 업데이트

    if (m_strPatternFolderPath.IsEmpty())
    {
        AfxMessageBox(_T("폴더 경로를 먼저 선택해 주세요."));
        return;
    }

    CString sourceFolder = _T("C:\\Users\\time\\Documents\\IN_FI_AUTO_FUSING\\TS_WR_HS_FUSING\\PATTERN\\");
    CString destFolder = m_strPatternFolderPath;

    if (destFolder.Right(1) != _T("\\"))  // 경로 끝에 \ 없으면 추가
        destFolder += _T("\\");

    CFileFind finder;
    BOOL bWorking = finder.FindFile(sourceFolder + _T("*.pdb"));  // .mod → .pdb 로 변경

    int copiedCount = 0;

    while (bWorking)
    {
        bWorking = finder.FindNextFile();

        if (finder.IsDots() || finder.IsDirectory())
            continue;

        CString fileName = finder.GetFileName();
        CString sourceFile = sourceFolder + fileName;
        CString destFile = destFolder + fileName;

        if (CopyFile(sourceFile, destFile, FALSE))
        {
            copiedCount++;
        }
        else
        {
            CString err;
            err.Format(_T("파일 복사 실패: %s"), fileName);
            AfxMessageBox(err);
        }
    }

    CString msg;
    msg.Format(_T("총 %d개 .PDB 파일을 복사했습니다."), copiedCount);
    AfxMessageBox(msg);
}