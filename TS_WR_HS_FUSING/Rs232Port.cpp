  
#include "stdafx.h"
#include "Rs232Port.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern HWND hCommWnd;

CRs232Port::CRs232Port()
{
	m_hComm1 = (HANDLE) -1;
}

CRs232Port::~CRs232Port()
{
	m_boolConnected1 = FALSE;

	if (((HANDLE) -1) != m_hComm1)		ClosePort1 ();
}

//*******************************************************************************************************************************
// COM PORT 1
BOOL CRs232Port::OpenPort1 (CString sPortName, unsigned long dwBaud, unsigned short wPortID)
{
	COMMTIMEOUTS timeouts;
	DCB dcb;
	DWORD dwThreadID;
	m_boolConnected1 = FALSE;
	m_wPortID1 = wPortID;
	m_osRead1.Offset = 0;
	m_osRead1.OffsetHigh = 0;
	m_osRead1.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
	if (!m_osRead1.hEvent)
		return FALSE;
	m_osWrite1.Offset = 0;
	m_osWrite1.OffsetHigh = 0;
	m_osWrite1.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
	if (!m_osWrite1.hEvent)
		return FALSE;
	m_strPortName1 = sPortName;
	m_hComm1 = CreateFile (sPortName, 
							GENERIC_READ | GENERIC_WRITE, 
							0, 
							NULL, 
							OPEN_EXISTING, 
							FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 
							NULL);
  if (m_hComm1 == (HANDLE) -1)		return FALSE;
	SetCommMask (m_hComm1, EV_RXCHAR);
	SetupComm (m_hComm1, COM_LENGTH, COM_LENGTH);
	timeouts.ReadIntervalTimeout = 10;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;
	timeouts.WriteTotalTimeoutMultiplier = 2*CBR_115200 / dwBaud;
	timeouts.WriteTotalTimeoutConstant = 0;
	SetCommTimeouts (m_hComm1, &timeouts);
//____________________________________________________________________
	dcb.DCBlength = sizeof (DCB);
	GetCommState (m_hComm1, &dcb);
	dcb.BaudRate = dwBaud;
	dcb.ByteSize = 8;	// Keyence default = Data Bits : 8
	dcb.Parity = 0;		// Keyence default = Parity Bits : 2(even) (0-4: no, odd, even, mark, space)
	dcb.StopBits = 0;	// Keyence default = Stop Bits : 0(1Bits) (0-2, 1, 1.5, 2)

	dcb.fInX = dcb.fOutX = 0;
	dcb.XonChar = ASCII_XON;
	dcb.XoffChar = ASCII_XOFF;
	dcb.XonLim = 100;

	dcb.fDtrControl = DTR_CONTROL_DISABLE;
	dcb.fRtsControl = DTR_CONTROL_DISABLE;


	if (!SetCommState (m_hComm1, &dcb))		return FALSE;
	m_boolConnected1 = TRUE;

	m_hThreadWatchComm1 = CreateThread (NULL,
									   0,
									   (LPTHREAD_START_ROUTINE)ThreadWatchComm1,
									   this,
									   0,
									   &dwThreadID);

	if (!m_hThreadWatchComm1)
	{
		ClosePort1 ();
		return FALSE;
	}
	return TRUE;
}

void CRs232Port::ClosePort1 ()
{
	m_boolConnected1 = FALSE;
	SetCommMask ((void *)(m_hComm1), (unsigned long)0);
	PurgeComm (m_hComm1, PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR | EV_RXFLAG | EV_TXEMPTY | EV_ERR | EV_BREAK);
	CloseHandle (m_hComm1);
	m_hComm1 = (HANDLE) -1;
}

DWORD CRs232Port::WritePort1 (BYTE* pBuff, DWORD nToWrite)
{
	DWORD dwWritten, dwError, dwErrorFlags;
	COMSTAT comstat;
	if (!WriteFile (m_hComm1, pBuff, nToWrite, &dwWritten, &m_osWrite1))
	{
		//		DWORD dwErrorCode = GetLastError ();
		if (GetLastError () == ERROR_IO_PENDING)
		{
			while (!GetOverlappedResult (m_hComm1, &m_osWrite1, &dwWritten, TRUE))
			{
				dwError = GetLastError ();
				if (dwError != ERROR_IO_INCOMPLETE)
				{
					ClearCommError (m_hComm1, &dwErrorFlags, &comstat);
					break;
				}
			}
		}
		else
		{
			dwWritten = 0;
			ClearCommError (m_hComm1, &dwErrorFlags, &comstat);
		}
	}
	return dwWritten;
}

DWORD CRs232Port::ReadPort1 (BYTE* pBuff, DWORD nToRead)
{
	DWORD dwRead, dwError, dwErrorFlags;
	COMSTAT comstat;
	ClearCommError (m_hComm1, &dwErrorFlags, &comstat);
	dwRead = comstat.cbInQue;
	if (dwRead > 0)
	{
		Sleep (20);
		if (!ReadFile (m_hComm1, pBuff, nToRead, &dwRead, &m_osRead1))
		{
			if (GetLastError () == ERROR_IO_PENDING)
			{
				while (!GetOverlappedResult (m_hComm1, &m_osRead1, &dwRead, TRUE))
				{
					dwError = GetLastError ();
					if (dwError != ERROR_IO_INCOMPLETE)
					{
						ClearCommError (m_hComm1, &dwErrorFlags, &comstat);
						break;
					}
				}
			}
			else
			{
				dwRead = 0;
				ClearCommError (m_hComm1, &dwErrorFlags, &comstat);
			}
		}
	}
	return dwRead;
}

DWORD ThreadWatchComm1 (CRs232Port* port_controller) // CA310-1
{
	DWORD dwEvent;
	OVERLAPPED os;
	BOOL bOK = TRUE;
	BYTE buff [BUFF_SIZE] = {0,};
	DWORD dwsize;

	memset (&os, 0, sizeof (OVERLAPPED));
	memset (port_controller->szCommRxBuff, 0, sizeof(port_controller->szCommRxBuff));

	os.hEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
	if (!os.hEvent)
		bOK = FALSE;

	if (!SetCommMask (port_controller->m_hComm1, EV_RXCHAR))
		bOK = FALSE;

	if (!bOK)
	{
		AfxMessageBox (_T("Error while creating ThreadWatchComm 'COM1'"));
		return FALSE;
	}
	while (port_controller->m_boolConnected1)
	{
		dwEvent = 0;
		WaitCommEvent (port_controller->m_hComm1, &dwEvent, NULL);
		if ((dwEvent & EV_RXCHAR) == EV_RXCHAR)
		{
			dwsize = port_controller->ReadPort1 (buff, BUFF_SIZE);
 			if (dwsize > 0)
			{
				memcpy(port_controller->szCommRxBuff, buff, dwsize);
				//if((port_controller->szCommRxBuff[16] == 0x02) || (port_controller->szCommRxBuff[16] == '<'))
				{
					//*********************************************************************
					AfxGetApp()->GetMainWnd()->SendMessage(WM_RS232_RECEIVE1, (WPARAM)port_controller->szCommRxBuff, NULL);
					//*********************************************************************
				}

				memset (buff, 0x00, BUFF_SIZE);
			}
		}
		else
		{
			dwsize = port_controller->ReadPort1 (buff, BUFF_SIZE);
			if (dwsize > 0)
			{
				memset (buff, 0x00, BUFF_SIZE);
			}
		}
	}
	CloseHandle (os.hEvent);
	port_controller->m_hThreadWatchComm1 = NULL;
	return TRUE;
}




