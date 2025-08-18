// PortController.h: interface for the CRs232Port class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PORTCONTROLLER_H__026116A1_CB26_11D4_9A54_444553540000__INCLUDED_)
#define AFX_PORTCONTROLLER_H__026116A1_CB26_11D4_9A54_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// User Define
#define	WM_RS232_RECEIVE1		(WM_USER+100)

//__________________________________________________________________
#define BUFF_SIZE			2048
#define ASCII_LF			0x0A
#define ASCII_CR			0x0D
#define ASCII_XON			0x11
#define ASCII_XOFF			0x13
//__________________________________________________________________

class CRs232Port  
{
public:
	CRs232Port();
	virtual ~CRs232Port();
	//__________________________________________________________________
	BOOL OpenPort1 (CString strPortName, unsigned long dwBaud, unsigned short wParam);
	void ClosePort1 ();
	DWORD WritePort1 (unsigned char* pBuff, unsigned long nToWrite);
	DWORD ReadPort1 (BYTE *pBuff, DWORD nToRead);


	//__________________________________________________________________
	HANDLE m_hComm1; 
	CString m_strPortName1; 
	BOOL m_boolConnected1; 
	OVERLAPPED m_osRead1,m_osWrite1; 
	HANDLE m_hThreadWatchComm1; 
	WORD m_wPortID1;


	BYTE szCommRxBuff[1024];

protected:


};


DWORD ThreadWatchComm1 (CRs232Port* port_controller);

#endif // !defined(AFX_PORTCONTROLLER_H__026116A1_CB26_11D4_9A54_444553540000__INCLUDED_)
