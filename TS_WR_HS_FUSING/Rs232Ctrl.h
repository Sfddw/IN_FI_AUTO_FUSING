#pragma once

#include "Rs232Port.h"
/////////////////////////////////////////////////////////////////////////////
// User Define
#define	RS232_WAIT_TIME		2000


class CRs232Ctrl
{
public:
	CRs232Ctrl(void);
	~CRs232Ctrl(void);

	BOOL  rs232_InitPort();

	BOOL  rs232_OpenPort(CString sPortName, unsigned long dwBaud);
	void  rs232_ClosePort(void);
	ULONG rs232_WritePort(unsigned char* wrbuff, unsigned long nToWriteLen);
	ULONG rs232_ReadPort(unsigned char* rdbuff, unsigned long length);

	CRs232Port* pR232Port;
};
