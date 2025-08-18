
// TS_WR_HS_FUSING.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.
#include "Rs232Ctrl.h"


// CTS_WR_HS_FUSINGApp:
// �� Ŭ������ ������ ���ؼ��� TS_WR_HS_FUSING.cpp�� �����Ͻʽÿ�.
//

class CTS_WR_HS_FUSINGApp : public CWinAppEx
{

public:

	CRs232Ctrl*		m_pRS232Ctrl;

	/* Variable Definition */
	BOOL	m_b232IsReceiveACK;
	int		m_n232AckCommand;
	BOOL	m_b232Open;

	char szRecvData[512];
	CString m_sNewModelName;
	CString m_sOldModelName;
	BOOL	m_bIsChange;
	LPSYSTEMINFO	GetSystemInfo();
	LPMODELINFO	GetModelInfo();

	/* RS232 Protocol Maker. */
	unsigned char makeChkSum(char *pBuff, int calcnt);
	char compareChksum(char *pBuff, int cnt);
	int makeProtocol(unsigned char cmdc, int sender, int recver, char *srcData, char *desData, int length);

	/* Function Definition */
	BOOL Rs232_receiveACK(DWORD waitTime);
	BOOL Rs232_setReceivePacket(char* szpacket);
	BOOL Rs232_sendData(unsigned char* sendmsg, unsigned long dwsize);
	int PacketSend(unsigned char nCmd, unsigned char *sendMsg, int size);
	BOOL InitPortOpenRS232C(char nComNum);
	void InitLoadSystemInfo();
	BOOL cfgUart(char nPortNum);

	CTS_WR_HS_FUSINGApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()

protected:
	LPSYSTEMINFO	lpSystemInfo;
	LPMODELINFO		lpModelInfo;
};

extern CTS_WR_HS_FUSINGApp theApp;
extern CTS_WR_HS_FUSINGApp* m_pApp;