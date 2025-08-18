#include "StdAfx.h"

#include "Rs232Ctrl.h"

/////////////////////////////////////////////////////////////////////////////


CRs232Ctrl::CRs232Ctrl(void)
{
	pR232Port = new CRs232Port;
}

CRs232Ctrl::~CRs232Ctrl(void)
{
	delete pR232Port;
}

BOOL CRs232Ctrl::rs232_InitPort()
{
	return TRUE;
}

BOOL CRs232Ctrl::rs232_OpenPort(CString sPortName, unsigned long dwBaud)
{
	BOOL nRetV=FALSE;

	nRetV = pR232Port->OpenPort1(sPortName, dwBaud, NULL);

	return nRetV;
}

void CRs232Ctrl::rs232_ClosePort(void)
{
	pR232Port->ClosePort1();
}

ULONG CRs232Ctrl::rs232_WritePort(unsigned char* wrbuff, unsigned long nToWriteLen)
{
	DWORD dwWritten=0;

	dwWritten = pR232Port->WritePort1(wrbuff, nToWriteLen);

	return dwWritten;
}

ULONG CRs232Ctrl::rs232_ReadPort (unsigned char* rdbuff, unsigned long length)
{

	return TRUE;
}
