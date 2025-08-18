#include "stdafx.h"
#include "VersionInfo.h"

#pragma comment(lib,"Version.lib")       // version.lib�� Link

bool CVersionInfo::GetVersionInfo(CString& strProductVersion)
{
	// ���� ����� ���α׷��� ��θ� ������ �����̴�.
	char strFilePath[MAX_PATH];

	// ���� ����� ���α׷��� ��θ� ��´�.
	GetModuleFileName(AfxGetInstanceHandle(), strFilePath, sizeof(strFilePath));

	// ���Ϲ��� ������ �б����� ����ũ�� ����
	DWORD dummy;
	DWORD dwSize = GetFileVersionInfoSize((LPCTSTR)strFilePath, &dummy);
	if (dwSize == 0)
	{
		TRACE("GetFileVersionInfoSize failed with error %d\n", GetLastError());
		return false;
	}
	BYTE* pData = new BYTE[dwSize];

	// ���Ϲ��� ���� �б�
	if (!GetFileVersionInfo((LPCTSTR)strFilePath, NULL, dwSize, pData))
	{
		TRACE("GetFileVersionInfo failed with error %d\n", GetLastError());
		delete pData;
		return false;
	}

	// ���Ϲ��� ������ �б����� �������� ( ���Ϲ��� ������ ��� ���ҽ����� ���еǾ� �����. )
	LPVOID pvProductVersion = NULL;

	struct LANGANDCODEPAGE
	{
		WORD wLanguage;
		WORD wCodePage;
	} *lpTranslate;
	UINT		cbTranslate;
	CString		strSubBlock;

	VerQueryValue(pData, _T("\\VarFileInfo\\Translation"), (LPVOID*)&lpTranslate, (PUINT)&cbTranslate);

	// ���Ϲ��� �������� ù��° �� �ش��ϴ� data�� �о��
	// ���߾�� ���ҽ������� ��Ȯ�� ������ ���ؼ��� data�� �б� ���� ����ڵ�, �ڵ������� ������ �����Ͽ��� ��.
	// ������ ���� ���, �ڵ������� ������ ���ҽ������� "Block Header"�� ���ԵǾ� ����.
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