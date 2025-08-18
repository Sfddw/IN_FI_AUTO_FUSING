#pragma once

#include <direct.h>
#include <io.h>

class CIniProfileAPI
{
public:
	CIniProfileAPI(void);
	~CIniProfileAPI(void);
};

static TCHAR	wszConv[2048]={0,};
static char		szConv[2048]={0,};
static CString	sRetString;

/////////////////////////////////////////////////////////////////////////////
static void ProcessMessage()
{
	MSG msg;
	if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

/////////////////////////////////////////////////////////////////////////////
static int _str_to_dec(CString hexStr)
{
	int dwRtnData=0;
	TCHAR tmpdata=0;
	int nLength=0, index=0;

	hexStr.MakeUpper();

	nLength = hexStr.GetLength();
	while(nLength != 0)
	{
		// Hex Char에 해당하는 Decimal 값을 가져온다.
		if(hexStr.GetAt(index)=='0')			tmpdata=0;
		else if(hexStr.GetAt(index)=='1')		tmpdata=1;
		else if(hexStr.GetAt(index)=='2')		tmpdata=2;
		else if(hexStr.GetAt(index)=='3')		tmpdata=3;
		else if(hexStr.GetAt(index)=='4')		tmpdata=4;
		else if(hexStr.GetAt(index)=='5')		tmpdata=5;
		else if(hexStr.GetAt(index)=='6')		tmpdata=6;
		else if(hexStr.GetAt(index)=='7')		tmpdata=7;
		else if(hexStr.GetAt(index)=='8')		tmpdata=8;
		else if(hexStr.GetAt(index)=='9')		tmpdata=9;
		else if(hexStr.GetAt(index)=='A')		tmpdata=10;
		else if(hexStr.GetAt(index)=='B')		tmpdata=11;
		else if(hexStr.GetAt(index)=='C')		tmpdata=12;
		else if(hexStr.GetAt(index)=='D')		tmpdata=13;
		else if(hexStr.GetAt(index)=='E')		tmpdata=14;
		else if(hexStr.GetAt(index)=='F')		tmpdata=15;

		// 결과 값을 누적한다.
		dwRtnData += tmpdata;

		// Index 값을 증가 시킨다.
		index++;

		// 마지막 Data이면 while문을 빠져 나간다.
		if(nLength == index)	break;

		// 누적된 Data 값을 Shift 시킨다.
		dwRtnData <<= 4;
	}

	return dwRtnData;
}



/////////////////////////////////////////////////////////////////////////////
static int CALLBACK BrowseForFolder_CallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	if(uMsg == BFFM_INITIALIZED)
		SendMessage(hwnd, BFFM_SETSELECTION, (WPARAM)TRUE, (LPARAM)lpData);
	return 0;

}

static void Write_ProfileString(char *lpFileName, char *lpTitle, char *lpKey, char *lpValue)
{
	::WritePrivateProfileString(lpTitle, lpKey, lpValue, lpFileName);
}

static void Read_ProfileString(char *lpFileName, char *lpTitle, char *lpKey, CString *retValue)
{
	char wszData[512] = {0,};
	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), lpFileName);

	retValue->Format(_T("%s"), wszData);
}

static void Write_SysIniFile(char *lpTitle, char *lpKey, char *lpValue)
{
	::WritePrivateProfileString(lpTitle, lpKey, lpValue, _T(".\\Operation.ini"));
}

static void Write_SysIniFile(char *lpTitle, char *lpKey, int nData)
{
	CString szData;

	szData.Format(_T("%d"), nData);
	::WritePrivateProfileString(lpTitle, lpKey, szData, _T(".\\Operation.ini"));
}

static void Write_SysIniFile(char *lpTitle, char *lpKey, float fData)
{
	CString szData;

	szData.Format(_T("%f"), fData);
	::WritePrivateProfileString(lpTitle, lpKey, szData, _T(".\\Operation.ini"));
}

static void Read_SysIniFile(char *lpTitle, char *lpKey, int *pRetValue)
{
	char wszData[100] = {0,};

	*pRetValue = 0;
	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\Operation.ini"));        

	*pRetValue = _ttoi(wszData);
}

static void Read_SysIniFile(char *lpTitle, char *lpKey, float *pRetValue)
{
	char wszData[100] = {0,};

	*pRetValue = 0;
	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\Operation.ini"));        

	*pRetValue = (float)_tstof(wszData);
}

static void Read_SysIniFile(char *lpTitle, char *lpKey, CString *szRetString)
{
	char wszData[100] = {0,};

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), _T(".\\Operation.ini"));

	szRetString->Format(_T("%s"), wszData);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
static void Write_ModelFile(char *lpModelName, char *lpTitle, char *lpKey, char *lpValue)
{
	CString szModelPath;

	szModelPath.Format(_T(".\\Model\\%s.MOD"), lpModelName);
	::WritePrivateProfileString(lpTitle, lpKey, lpValue, szModelPath);        
}

static void Write_ModelFile(char *lpModelName, char *lpTitle, char *lpKey, int ndata)
{
	CString szData;
	CString szModelPath;

	szData.Format(_T("%d"), ndata);
	szModelPath.Format(_T(".\\Model\\%s.MOD"), lpModelName);
	::WritePrivateProfileString(lpTitle, lpKey, szData, szModelPath);        
}

static void Write_ModelFile(char *lpModelName, char *lpTitle, char *lpKey, long nData)
{
	CString szData;
	CString szModelPath;

	szData.Format(_T("%d"), nData);
	szModelPath.Format(_T(".\\Model\\%s.MOD"), lpModelName);
	::WritePrivateProfileString(lpTitle, lpKey, szData, szModelPath);        
}

static void Write_ModelFile(char *lpModelName, char *lpTitle, char *lpKey, double fdata)
{
	CString szData;
	CString szModelPath;

	szData.Format(_T("%f"), fdata);
	szModelPath.Format(_T(".\\Model\\%s.MOD"), lpModelName);
	::WritePrivateProfileString(lpTitle, lpKey, szData, szModelPath);        
}

static void Read_ModelFile(CString lpModelName, char *lpTitle, char *lpKey, CString *szRetString)
{
	char wszData[100] = {0,};
	CString szModelPath;

	// 모델 File 경로 설정
	szModelPath.Format(_T(".\\Model\\%s.MOD"), lpModelName);

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), szModelPath);

	szRetString->Format(_T("%s"), wszData);
}

static void Read_ModelFile(CString lpModelName, char *lpTitle, char *lpKey, char *szRetString)
{
	char wszData[100] = {0,};
	CString szModelPath;

	// Return Memory Initialize
	memset(szRetString,'\0',sizeof(szRetString));

	// 모델 File 경로 설정
	szModelPath.Format(_T(".\\Model\\%s.MOD"), lpModelName);

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), szModelPath);

	sprintf(szRetString, "%s", wszData);
}

static void Read_ModelFile(CString lpModelName, char *lpTitle, char *lpKey, int *pRetValue)
{
	CString szModelPath;
	char wszData[100] = {0,};

	// 모델 File 경로 설정
	*pRetValue = 0;
	szModelPath.Format(_T(".\\Model\\%s.MOD"), lpModelName);

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), szModelPath);        

	*pRetValue = atoi(wszData);
}

static void Read_ModelFile(CString lpModelName, char* lpTitle, char* lpKey, int* pRetValue, char* lpDefault)
{
	CString szModelPath;
	char wszData[100] = { 0, };

	// 모델 File 경로 설정
	*pRetValue = 0;
	szModelPath.Format(_T(".\\Model\\%s.MOD"), lpModelName);

	::GetPrivateProfileString(lpTitle, lpKey, lpDefault, wszData, sizeof(wszData), szModelPath);

	*pRetValue = atoi(wszData);
}

static void Read_ModelFile(CString lpModelName, char *lpTitle, char *lpKey, LONG *pRetValue)
{
	CString szModelPath;
	char wszData[100] = {0,};

	// 모델 File 경로 설정
	*pRetValue = 0;
	szModelPath.Format(_T(".\\Model\\%s.MOD"), lpModelName);

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), szModelPath);        

	*pRetValue = strtol(wszData, NULL, 10);
}

static void Read_ModelFile(CString lpModelName, char *lpTitle, char *lpKey, float *pRetValue)
{
	CString szModelPath;
	char wszData[100] = {0,};

	// 모델 File 경로 설정
	*pRetValue = 0;

	szModelPath.Format(_T(".\\Model\\%s.MOD"), lpModelName);

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), szModelPath);        

	*pRetValue = (float)atof(wszData);
}

static void Read_ModelFile(CString lpModelName, char *lpTitle, char *lpKey, double *pRetValue)
{
	CString szModelPath;
	char wszData[100] = {0,};

	// 모델 File 경로 설정
	*pRetValue = 0;

	szModelPath.Format(_T(".\\Model\\%s.MOD"), lpModelName);

	::GetPrivateProfileString(lpTitle, lpKey, 0, wszData, sizeof(wszData), szModelPath);        

	*pRetValue = atof(wszData);
}

/////////////////////////////////////////////////////////////////////////////
static void wchar_To_char(wchar_t* wszOrg, char* szConv)
{
	//먼저 길이를 구한다.
	int nMultiByteLen = WideCharToMultiByte(CP_ACP, 0, wszOrg, -1, NULL, 0, NULL,NULL);
	//변환한다.
	WideCharToMultiByte(CP_ACP, 0, wszOrg, -1, szConv, nMultiByteLen, NULL, NULL);
}

static char* wchar_To_char(wchar_t* wszOrg)
{
	//먼저 길이를 구한다.
	int nMultiByteLen = WideCharToMultiByte(CP_ACP, 0, wszOrg, -1, NULL, 0, NULL,NULL);
	//변환한다.
	WideCharToMultiByte(CP_ACP, 0, wszOrg, -1, szConv, nMultiByteLen, NULL, NULL);

	return szConv;
}
