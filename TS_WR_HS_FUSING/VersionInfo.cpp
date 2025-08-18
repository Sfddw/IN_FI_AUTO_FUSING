#include "stdafx.h"
#include "VersionInfo.h"

#pragma comment(lib,"Version.lib")       // version.lib를 Link

bool CVersionInfo::GetVersionInfo(CString& strProductVersion)
{
	// 현재 실행된 프로그램의 경로를 저장할 변수이다.
	char strFilePath[MAX_PATH];

	// 현재 실행된 프로그램의 경로를 얻는다.
	GetModuleFileName(AfxGetInstanceHandle(), strFilePath, sizeof(strFilePath));

	// 파일버전 정보를 읽기위한 버퍼크기 결정
	DWORD dummy;
	DWORD dwSize = GetFileVersionInfoSize((LPCTSTR)strFilePath, &dummy);
	if (dwSize == 0)
	{
		TRACE("GetFileVersionInfoSize failed with error %d\n", GetLastError());
		return false;
	}
	BYTE* pData = new BYTE[dwSize];

	// 파일버전 정보 읽기
	if (!GetFileVersionInfo((LPCTSTR)strFilePath, NULL, dwSize, pData))
	{
		TRACE("GetFileVersionInfo failed with error %d\n", GetLastError());
		delete pData;
		return false;
	}

	// 파일버전 정보를 읽기위한 변수설정 ( 파일버전 정보는 언어 리소스별로 구분되어 저장됨. )
	LPVOID pvProductVersion = NULL;

	struct LANGANDCODEPAGE
	{
		WORD wLanguage;
		WORD wCodePage;
	} *lpTranslate;
	UINT		cbTranslate;
	CString		strSubBlock;

	VerQueryValue(pData, _T("\\VarFileInfo\\Translation"), (LPVOID*)&lpTranslate, (PUINT)&cbTranslate);

	// 파일버전 정보에서 첫번째 언어에 해당하는 data를 읽어옴
	// 다중언어 리소스에서는 정확한 동작을 위해서는 data를 읽기 전에 언어코드, 코드페이지 정보를 지정하여야 함.
	// 버전에 관한 언어, 코드페이지 정보는 리소스파일의 "Block Header"에 기입되어 있음.
	strSubBlock.Format(_T("\\StringFileInfo\\%04x%04x\\ProductVersion"), lpTranslate[0].wLanguage,
		lpTranslate[0].wCodePage);
	if (!VerQueryValue(pData, (LPCTSTR)strSubBlock, &pvProductVersion, (PUINT)&dummy))
	{
		TRACE("Can't obtain ProductVersion from resources\n");
		delete pData;
		return false;
	}

	strProductVersion = (LPCTSTR)pvProductVersion;

	delete pData;
	return true;
}