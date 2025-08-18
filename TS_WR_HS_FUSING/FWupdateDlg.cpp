// FWupdateDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TS_WR_HS_FUSING.h"
#include "FWupdateDlg.h"


// CFWupdateDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CFWupdateDlg, CDialog)

CFWupdateDlg::CFWupdateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFWupdateDlg::IDD, pParent)
{

}

CFWupdateDlg::~CFWupdateDlg()
{
}

void CFWupdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STT_HEX_NAME, ctrlHexName);
	DDX_Control(pDX, IDC_STT_PROGRESS, ctrlUpdateProgress);
}


BEGIN_MESSAGE_MAP(CFWupdateDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_BROWSE_HEX, &CFWupdateDlg::OnBnClickedBtnBrowseHex)
	ON_BN_CLICKED(IDC_BTN_UPDATE, &CFWupdateDlg::OnBnClickedBtnUpdate)
END_MESSAGE_MAP()


// CFWupdateDlg 메시지 처리기입니다.

BOOL CFWupdateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CFWupdateDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if(pMsg->message == WM_SYSKEYDOWN && pMsg->wParam == VK_F4)
	{
		if (::GetKeyState(VK_MENU)<0)	return TRUE;
	}

	// 일반 Key 동작에 대한 Event
	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_RETURN:		return 1;
		case VK_ESCAPE:		return 1;
		case VK_SPACE:		return 1;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CFWupdateDlg::DestroyWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialog::DestroyWindow();
}

void CFWupdateDlg::OnBnClickedBtnBrowseHex()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString fileName;
	CString strTmp;
	char szHexPath[1024]={0,};

	GetCurrentDirectory(1024, szHexPath);

	//strFW_Location.Format("%s\\FW", szHexPath);
	strTmp.Format("%s\\FW\\*.hex", szHexPath);

	CFileDialog FileDlg(TRUE, NULL, strTmp, OFN_FILEMUSTEXIST, "Hex(*.hex)");

	if( FileDlg.DoModal() == IDOK ) 
	{
		strTmp = FileDlg.GetFileName();
		strFW_HexName = strTmp;
		strFW_Location = FileDlg.GetPathName();
		//strFW_Location.Format("%s\\FW", szHexPath);

		ctrlHexName.SetWindowText(strTmp);
	}
	else
	{
		ctrlHexName.SetWindowText("none");
		strFW_HexName.Empty();
	}
}

// Hex Format 으로 parsing.
// return 값을 "RECTYPE"

int CFWupdateDlg::strMakeDataPack(unsigned char *strSrc, unsigned char *szDest, int *cpyLen)
{
	unsigned char szConvertedLinData[256];
	int nLoop=0;
	int RECLEN, LOADOFFSET, RECTYP, CHKSUM;
	int nPosChkSum, nSum=0;
	unsigned char pp[2]={0,};

	if(strSrc[0] != ':')	return -1;

	memset(szConvertedLinData, 0, sizeof(szConvertedLinData));

	sscanf((char *)(strSrc+1), "%02X%04X%02X", &RECLEN, &LOADOFFSET, &RECTYP);

	nPosChkSum = ((RECLEN+5) * 2) - 1;
	sscanf((char *)(strSrc+nPosChkSum), "%02X", &CHKSUM);

	for(nLoop=0; nLoop<RECLEN; nLoop++)
	{
		sscanf((char *)(strSrc + 9 + (nLoop * 2)), "%02X", (char *)(&szConvertedLinData[nLoop]));
	}

	// confirm check sum
	pp[0] = (unsigned char)(LOADOFFSET);
	pp[1] = (unsigned char)(LOADOFFSET >> 8);
	nSum =  RECLEN + pp[0] + pp[1] + RECTYP + CHKSUM;

	for(nLoop=0; nLoop<RECLEN; nLoop++)
	{
		nSum += szConvertedLinData[nLoop];
		*(szDest + nLoop) = szConvertedLinData[nLoop];
	}

	*(cpyLen) = RECLEN;

	if( (nSum & 0x00FF) != 0x00 )	return -1;

	return RECTYP;
}


int CFWupdateDlg::HexFileParsing(void)
{
	CStdioFile file;
	unsigned char szLineData[256+16];
	unsigned long lineCnt=0, totalDataLen=0;
	int pointPos=0, nCpyLen=0, getRecType;

	if(strFW_HexName.GetLength() < 3)	return -1;

	//strHexParsePath = strFW_Location + "\\" + strFW_HexName;
	strHexParsePath = strFW_Location;

	if(file.Open(strHexParsePath.GetBuffer(0), CFile::modeRead))
	{
		CString str;
		unsigned long filesize;

		filesize = file.GetLength();
		szParsingData = (unsigned char *)malloc(filesize*sizeof(unsigned char));
		memset((char*)szParsingData, 0, filesize);

	#if 1
		while(file.ReadString(str))
		{
			memset(szLineData, 0, sizeof(szLineData));
			getRecType = strMakeDataPack((unsigned char *)str.GetBuffer(0), szLineData, &nCpyLen);

			/* RECTYPE 에 따른 동작. */
			switch(getRecType)
			{
			case -1 :
				{
					// Parsing Error.
					file.Close();
					nHexFileSize = 0;
					return -1;
				}break;

			case 0x00 :
				{
					// RECORD Type이 DATA 임.
					memcpy((char *)(szParsingData+totalDataLen), (char *)szLineData, nCpyLen);

					totalDataLen += nCpyLen;
					lineCnt += 1;
				}break;
			}
			/************************/
		}
	#else
		file.Read(szParsingData, filesize);
	#endif
	}
	else
	{
		file.Close();
	}

	nHexFileSize = totalDataLen;

	return 0;
}

#define	FLASH_PAGE_SIZE			2048
#define	CMD_FW_DOWNLOAD			0xF0
#define CMD_FW_COMPLETE			0xF2
#define	CMD_GOTO_BOOT_SECTION	0xF3

void CFWupdateDlg::OnBnClickedBtnUpdate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ctrlUpdateProgress.SetWindowText("");

	if(funcGotoBoot() == TRUE)
	{
		if(procFwUpdate() == TRUE)
		{
			if(funcFwComplete() == TRUE)
			{
				ctrlUpdateProgress.SetWindowText("  Firmware update Complete.");
			}
			else
			{
				ctrlUpdateProgress.SetWindowText("  Firmware Complete Fail.");
			}
		}
		else
		{
			ctrlUpdateProgress.SetWindowText("  Firmware update fail.");
		}
	}
	else
	{
		ctrlUpdateProgress.SetWindowText("  Firmware update Ready Fail.");
	}
}

int CFWupdateDlg::funcGotoBoot(void) 
{
	// TODO: Add your control notification handler code here
	int nRetV, nLoop;

	for(nLoop=0; nLoop<10; nLoop++)
	{
		nRetV = m_pApp->PacketSend(CMD_GOTO_BOOT_SECTION, (unsigned char *)"", 0);
		Sleep(200);
	}

	return TRUE;
}

int CFWupdateDlg::funcFwComplete(void) 
{
	// TODO: Add your control notification handler code here
	int nRetV=TRUE;

	nRetV = m_pApp->PacketSend(CMD_FW_COMPLETE, (unsigned char *)"", 0);

	return nRetV;
}

int CFWupdateDlg::procFwUpdate(void)
{
	int nSendPageCnt, nRemainPageCnt;
	int nRetV, nLoop;

	unsigned char szTempBuf[2058];
	char szProgressLog[128]={0,};
	int tmpLen;

	CString strRecvPacket("");

	if(HexFileParsing() < 0)
	{
		return FALSE;
	}

	// parsing 된 file 사이즈를 몇번 전송 할지 page cnt를 구한다.
	// 2048의 배수가 아닌 경우 나머지 data 전송을 위한 counter를 구한다.
	nSendPageCnt = nHexFileSize / FLASH_PAGE_SIZE;
	nRemainPageCnt = nHexFileSize % FLASH_PAGE_SIZE;

	for(nLoop=0; nLoop<nSendPageCnt; nLoop++)
	{
		memset((char *)szTempBuf, 0, sizeof(szTempBuf));

		sprintf((char *)szTempBuf, "%05X", (nLoop*FLASH_PAGE_SIZE));
		tmpLen = strlen((char *)szTempBuf);

		memcpy((char *)(&szTempBuf[tmpLen]), (char *)(szParsingData+(nLoop*FLASH_PAGE_SIZE)), FLASH_PAGE_SIZE);

		nRetV = m_pApp->PacketSend(CMD_FW_DOWNLOAD, (unsigned char *)szTempBuf, (FLASH_PAGE_SIZE+tmpLen));
		if(nRetV != TRUE)
		{
			break;
		}
		else
		{
			sprintf(szProgressLog, "        Progress : %d / %d.", nLoop, nSendPageCnt);
			ctrlUpdateProgress.SetWindowText(szProgressLog);
			Sleep(100);
		}
	}


	if((nRetV == TRUE) && (nRemainPageCnt != 0))
	{
		memset((char *)szTempBuf, 0, sizeof(szTempBuf));

		sprintf((char *)szTempBuf, "%05X", (nLoop*FLASH_PAGE_SIZE));
		tmpLen = strlen((char *)szTempBuf);

		memcpy((char *)(&szTempBuf[tmpLen]), (char *)(szParsingData+(nLoop*FLASH_PAGE_SIZE)), nRemainPageCnt);

		nRetV = m_pApp->PacketSend(CMD_FW_DOWNLOAD, (unsigned char *)szTempBuf, (nRemainPageCnt+tmpLen));
		Sleep(100);
	}

	free(szParsingData);

	return nRetV;
}


