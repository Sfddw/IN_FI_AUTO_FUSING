// CSetSystemDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "TS_WR_HS_FUSING.h"
#include "afxdialogex.h"
#include "CSetSystemDlg.h"
#include "TS_WR_HS_FUSINGDlg.h"


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
    DDX_Text(pDX, IDC_EDIT_MAIN_MODELPATH, m_strMainModelPath);
    DDX_Text(pDX, IDC_EDIT_MODELNAME_PATH, m_strModelFolderPath);
    DDX_Text(pDX, IDC_EDIT_PATTERNNAME_PATH, m_strPatternFolderPath);
    DDX_Control(pDX, IDC_CBOX_PORT, ctrlComPort);
}

BOOL CSetSystemDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    lpSysInfo = m_pApp->GetSystemInfo();
    int Com_Index;
    if (lpSysInfo->m_ComPort == 1)
    {
        Com_Index = 0;
    }
    else if (lpSysInfo->m_ComPort == 2)
    {
        Com_Index = 1;
    }
    else if (lpSysInfo->m_ComPort == 3)
    {
        Com_Index = 2;
    }
    else if (lpSysInfo->m_ComPort == 4)
    {
        Com_Index = 3;
    }
    else if (lpSysInfo->m_ComPort == 5)
    {
        Com_Index = 4;
    }
    else if (lpSysInfo->m_ComPort == 6)
    {
        Com_Index = 5;
    }
    else if (lpSysInfo->m_ComPort == 7)
    {
        Com_Index = 6;
    }
    else if (lpSysInfo->m_ComPort == 8)
    {
        Com_Index = 7;
    }
    else if (lpSysInfo->m_ComPort == 9)
    {
        Com_Index = 8;
    }
    else if (lpSysInfo->m_ComPort == 10)
    {
        Com_Index = 9;
    }


    // 콤보박스 기본값: COM3
    ctrlComPort.SetCurSel(Com_Index);  // 인덱스 2 → COM3
    lpSysInfo->c_ComPort = lpSysInfo->m_ComPort;

    return TRUE;
}




BEGIN_MESSAGE_MAP(CSetSystemDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_MODELCOPY_MOD, &CSetSystemDlg::OnBnClickedButtonModelCopyMod)
    ON_BN_CLICKED(IDC_BUTTON_PATTERNCOPY_MOD, &CSetSystemDlg::OnBnClickedButtonPatternCopyMod)
    ON_BN_CLICKED(IDC_BUTTON_MODEL_PATH, &CSetSystemDlg::OnBnClickedButtonSelModel)
    ON_BN_CLICKED(IDC_BUTTON_PATTERN_PATH, &CSetSystemDlg::OnBnClickedButtonSelPattern)
    ON_BN_CLICKED(IDC_BUTTON_SAVE_PATH, &CSetSystemDlg::OnBnClickedButtonSavePath)
END_MESSAGE_MAP()


// CSetSystemDlg 메시지 처리기

void CSetSystemDlg::OnOK()
{
	UpdateData(TRUE);

	/*AfxMessageBox(_T("Oracle Info Saved:\n") + m_strOracleName + _T(", ") + m_strUserID + _T(", ") + m_strPassword);

	CDialogEx::OnOK();*/
    int result = AfxMessageBox(_T("저장하시겠습니까?"), MB_OKCANCEL | MB_ICONQUESTION);
    int ComBoBox_Flag = 0;

    if (result == 1)
    {
        lpSysInfo->m_sModelSavePath = m_strMainModelPath; // 파일 경로 저장
        // (선택사항) 저장 성공 메시지 출력
        lpSysInfo->m_ComPort = ctrlComPort.GetCurSel() + 1; // COM PORT 저장
        Write_InitFile("SYSTEM", "PORT", lpSysInfo->m_ComPort);
        // 다이얼로그 종료
        if (lpSysInfo->c_ComPort != lpSysInfo->m_ComPort)
        {
            lpSysInfo->f_ComPort = false;
            if (m_pApp->cfgUart(lpSysInfo->m_ComPort) == TRUE && lpSysInfo->f_ComPort == false)
            {//OK
                CString strTemp;
                strTemp.Format("COM%d, PORT OPEN OK. ", lpSysInfo->m_ComPort);
                AfxMessageBox(strTemp, MB_ICONINFORMATION | MB_OK);
                lpSysInfo->f_ComPort = true;
            }
        }
        CDialogEx::OnOK();
    }
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

void CSetSystemDlg::OnBnClickedButtonSavePath()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
            m_strMainModelPath = szSelectedPath;
            UpdateData(FALSE); // Edit Control에 갱신
        }
    }
}
