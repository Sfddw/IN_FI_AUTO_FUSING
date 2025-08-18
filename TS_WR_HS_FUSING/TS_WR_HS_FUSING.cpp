
// TS_WR_HS_FUSING.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "TS_WR_HS_FUSING.h"
#include "TS_WR_HS_FUSINGDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTS_WR_HS_FUSINGApp

BEGIN_MESSAGE_MAP(CTS_WR_HS_FUSINGApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTS_WR_HS_FUSINGApp 생성

CTS_WR_HS_FUSINGApp::CTS_WR_HS_FUSINGApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.

	m_pApp			= (CTS_WR_HS_FUSINGApp*) AfxGetApp();

	m_pRS232Ctrl	= new CRs232Ctrl();		// RS232 Control Class 생성
	lpSystemInfo	= new SYSTEMINFO;
	lpModelInfo = new MODEL_INFO;
}


// 유일한 CTS_WR_HS_FUSINGApp 개체입니다.

CTS_WR_HS_FUSINGApp theApp;
CTS_WR_HS_FUSINGApp* m_pApp;


// CTS_WR_HS_FUSINGApp 초기화

BOOL CTS_WR_HS_FUSINGApp::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다.
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));

	InitLoadSystemInfo();

	CTS_WR_HS_FUSINGDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 여기에 [확인]을 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 여기에 [취소]를 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}

	// 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고  응용 프로그램을 끝낼 수 있도록 FALSE를
	// 반환합니다.
	return FALSE;
}

BOOL CTS_WR_HS_FUSINGApp::Rs232_receiveACK(DWORD waitTime)
{

#if 1
	DWORD stTick = ::GetTickCount();

	while(1)
	{
		DWORD edTick = ::GetTickCount();
		if((edTick-stTick) > waitTime)
		{
			return  FALSE;				// Time Out
		}

		if(m_b232IsReceiveACK==TRUE)		// ACK Receive
		{
			return TRUE;
		}

		ProcessMessage();
	}
#else
	int nTime;

	for(nTime=0; nTime<waitTime; nTime++)
	{
		if(m_b232IsReceiveACK==TRUE)		// ACK Receive
			break;

		ProcessMessage();

		Sleep(1);
	}

#endif

	return FALSE;
}


BOOL CTS_WR_HS_FUSINGApp::Rs232_setReceivePacket(char* szpacket)
{
	int nLoop=0;
	int nEndCnt, nSaveCnt=0;
	char flagSaveOn=FALSE;

	Sleep(10);

	nEndCnt = strlen(szpacket);

	CTime t = CTime::GetCurrentTime();
	CString s = t.Format("%H:%M:%S");
	TRACE("[%s][RECEIVE] %s \r\n", s, szpacket);
	for(nLoop=0; nLoop<nEndCnt; nLoop++)
	{
		if(szpacket[nLoop] == 0x02)
		{
			flagSaveOn = TRUE;
		}

		if(flagSaveOn == TRUE)
		{
			szRecvData[nSaveCnt] = szpacket[nLoop];
			nSaveCnt += 1;
		}

		if(szpacket[nLoop] == 0x03)
		{
			m_b232IsReceiveACK = TRUE;
			break;
		}
	}

	return  TRUE;
}


BOOL CTS_WR_HS_FUSINGApp::Rs232_sendData(unsigned char* sendmsg, unsigned long dwsize)
{
	m_b232IsReceiveACK = FALSE;

	m_pRS232Ctrl->rs232_WritePort(sendmsg, dwsize);

	return TRUE;
}

int CTS_WR_HS_FUSINGApp::PacketSend(unsigned char nCmd, unsigned char *sendMsg, int size)
{
	unsigned char szMakingPacket[COM_LENGTH]={0,};
	int totLen;

	totLen = makeProtocol(nCmd, ADDR_PC, ADDR_CTRL, (char *)sendMsg, (char *)szMakingPacket, size);
	Rs232_sendData(szMakingPacket, totLen);

	CTime t = CTime::GetCurrentTime();
	CString s = t.Format("%H:%M:%S");
	TRACE("[%s][SEND] %s \r\n", s, szMakingPacket);

	if(Rs232_receiveACK(3000) == TRUE)
	{//OK
		Sleep(50);
		return TRUE;
	}
	else
	{
		CTime t = CTime::GetCurrentTime();
		CString s = t.Format("%H:%M:%S");
		TRACE("[%s] NO RECEIVE ERROR \r\n", s);
	}

	return FALSE;
}

BOOL CTS_WR_HS_FUSINGApp::InitPortOpenRS232C(char nComNum)
{
	CString portName=_T("");
	DWORD dwBaud=115200;

	portName.Format(_T("COM%d"), nComNum);

	if(m_pRS232Ctrl->rs232_OpenPort(portName, dwBaud)==TRUE)
	{
		m_b232Open = TRUE;

		return TRUE;
	}
	else
	{
		CString strMsg;
		strMsg.Format(_T("%s Port Open Fail !!"), portName);
		AfxMessageBox(strMsg, MB_ICONERROR|MB_OK);
		m_b232Open = FALSE;

		return FALSE;
	}
}

BOOL CTS_WR_HS_FUSINGApp::cfgUart(char nPortNum)
{
	m_pRS232Ctrl->rs232_ClosePort();

	m_b232Open = FALSE;

	if(InitPortOpenRS232C(nPortNum) == FALSE)		return FALSE;
	Sleep(100);

	return TRUE;
}


/*
	packet 으로 checksum을 생성 한다.
	return : 생성된 checksum
*/

unsigned char CTS_WR_HS_FUSINGApp::makeChkSum(char *pBuff, int calcnt)
{
	int i;
	unsigned int calsum=0;
	
	for(i = 0; i < calcnt; i++)
	{
	   	calsum = calsum + pBuff[i];
    }
		
	return (unsigned char)calsum;
}

/*
	수신시 packet의 checksum 과 packet 으로 생성된 checksum을 비교 한다.
	return : compare OK(0)
		     compare NG(-1)
*/
char CTS_WR_HS_FUSINGApp::compareChksum(char *pBuff, int cnt)
{
	int i;
	unsigned char sum, etx; 
	int ch;
	unsigned int calsum=0;
	int rxsum;

	cnt += 12;	// "A1A2200029"
	
	for( i=0 ; i<cnt ; i++ )
	{
		ch = pBuff[ProtocolSender + i];
		calsum = calsum + ch;
	}

	sscanf_s(&pBuff[ProtocolSender + i++], "%02x", &rxsum);

	etx = pBuff[ProtocolSender + i + 1];

	sum = (unsigned char) (calsum & 0xFF);
	
	if( sum == rxsum )
	{
		if( etx == CMD_END_CHAR )	return(0);
		else							return (-1);
	}
	else		return(-1);
}

/*
	HEX 전송 가능 함.
    	반드시 puchar로 전송 할것.
    	넘겨 받은 parameter를 사용하여 packet을 만든다.

    	return : packet 길이.
    		     전송가능 한 packet.
*/
int CTS_WR_HS_FUSINGApp::makeProtocol(unsigned char cmdc, int sender, int recver, char *srcData, char *desData, int length)
{
	int size=0;
	int txsum0=0;

	sprintf(desData, "%c%02X%02X%02X%02X%04X", CMD_START_CHAR, sender, recver, 0, cmdc, length);
	size = strlen(desData);

	memcpy( (desData + size), srcData, length);
	size += length;
	
	txsum0 = makeChkSum( (desData + ProtocolSender), size - 1);
	sprintf( (desData + size), "%02X%c", txsum0, CMD_END_CHAR);

	size += 3;

	return (size);
}

LPSYSTEMINFO CTS_WR_HS_FUSINGApp::GetSystemInfo()
{
	ASSERT (NULL!= lpSystemInfo);
	VERIFY (NULL != lpSystemInfo);

	return lpSystemInfo;
}

LPMODELINFO CTS_WR_HS_FUSINGApp::GetModelInfo()
{
	ASSERT(NULL != lpSystemInfo);
	VERIFY(NULL != lpSystemInfo);

	return lpModelInfo;
}

void CTS_WR_HS_FUSINGApp::InitLoadSystemInfo()
{
	Read_SysIniFile(_T("SYSTEM"),		_T("MODEL_NAME_PATH"),			&lpSystemInfo->m_sModelNamePath);
	Read_SysIniFile(_T("SYSTEM"),		_T("LAST_MODEL_NAME"),			&m_pApp->m_sOldModelName);
}