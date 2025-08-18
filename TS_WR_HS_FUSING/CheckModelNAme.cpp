// CheckModelNAme.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TS_WR_HS_FUSING.h"
#include "CheckModelNAme.h"


// CCheckModelNAme 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCheckModelNAme, CDialog)

CCheckModelNAme::CCheckModelNAme(CWnd* pParent /*=NULL*/)
	: CDialog(CCheckModelNAme::IDD, pParent)
{

}

CCheckModelNAme::~CCheckModelNAme()
{
}

void CCheckModelNAme::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCheckModelNAme, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CCheckModelNAme 메시지 처리기입니다.

BOOL CCheckModelNAme::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	lpSystemInfo	= m_pApp->GetSystemInfo();
	m_pApp->m_bIsChange = FALSE;
	m_nSendFlag = 0;
	m_nHostFindFlag=0;
	m_nLocalFindFlag=0;

	lpModelInfo	= new MODEL_INFO;
	
	Lf_InitFont();

	SetTimer(1, 1000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CCheckModelNAme::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	for(int i=0;i<5;i++)
	{
		m_FontH1[i].DeleteObject();
		m_Brush[i].DeleteObject();
	}
}


HBRUSH CCheckModelNAme::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	switch (nCtlColor)
	{
	case CTLCOLOR_MSGBOX:
		break;
	case CTLCOLOR_EDIT:
		break;
	case CTLCOLOR_LISTBOX:
		break;
	case CTLCOLOR_SCROLLBAR:
		break;
	case CTLCOLOR_BTN:
		break;
	case CTLCOLOR_STATIC:
		if(pWnd->GetDlgCtrlID()==IDC_STT_CHECKING_MODEL_NAME_TITLE)	
		{
			pDC->SetBkColor(COLOR_WHITE);
			pDC->SetTextColor(RGB(0,0,0));
			return m_Brush[0];
		}
		if(pWnd->GetDlgCtrlID() == IDC_STT_HOST_MODEL_NAME)
		{
			if(m_nHostFindFlag == 0)// ready 
			{
				pDC->SetBkColor(RGB(240,240,240));
				pDC->SetTextColor(RGB(0,0,0));
				return m_Brush[1];
			}
			else if(m_nHostFindFlag == 1)// fusing ng
			{
				pDC->SetBkColor(RGB(255,0,0));
				pDC->SetTextColor(RGB(0,0,0));
				return m_Brush[2];
			}
			else if(m_nHostFindFlag == 2)// fusing ok
			{
				pDC->SetBkColor(RGB(0,255,0));
				pDC->SetTextColor(RGB(0,0,0));
				return m_Brush[3];
			}
		}
		if(pWnd->GetDlgCtrlID() == IDC_STT_LOCAL_MODEL_NAME)
		{
			if(m_nLocalFindFlag == 0)// ready 
			{
				pDC->SetBkColor(RGB(240,240,240));
				pDC->SetTextColor(RGB(0,0,0));
				return m_Brush[1];
			}
			else if(m_nLocalFindFlag == 1)// fusing ng
			{
				pDC->SetBkColor(RGB(255,0,0));
				pDC->SetTextColor(RGB(0,0,0));
				return m_Brush[2];
			}
			else if(m_nLocalFindFlag == 2)// fusing ok
			{
				pDC->SetBkColor(RGB(0,255,0));
				pDC->SetTextColor(RGB(0,0,0));
				return m_Brush[3];
			}
		}
		if(pWnd->GetDlgCtrlID() == IDC_STT_FUSING_STATUS)
		{
			if(m_nSendFlag == 0)// ready 
			{
				pDC->SetBkColor(RGB(240,240,240));
				pDC->SetTextColor(RGB(0,0,0));
				return m_Brush[1];
			}
			else if(m_nSendFlag == 1)// fusing ng
			{
				pDC->SetBkColor(RGB(255,0,0));
				pDC->SetTextColor(RGB(0,0,0));
				return m_Brush[2];
			}
			else if(m_nSendFlag == 2)// fusing ok
			{
				pDC->SetBkColor(RGB(0,255,0));
				pDC->SetTextColor(RGB(0,0,0));
				return m_Brush[3];
			}
		}

		break;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void CCheckModelNAme::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.

	CRect rect;
	GetClientRect(&rect);
	rect.bottom = 75;
	dc.FillSolidRect(rect, COLOR_WHITE);
	rect.top = rect.bottom;
	rect.bottom+=3;
	dc.FillSolidRect(rect, COLOR_RED);
}

void CCheckModelNAme::Lf_InitFont()
{
	m_FontH1[0].CreateFont(55, 20, 0, 0, FW_ULTRABOLD, TRUE, 0, 0, 0, 0, 0, 0, 0, _T("Arial"));
	GetDlgItem(IDC_STT_CHECKING_MODEL_NAME_TITLE)->SetFont(&m_FontH1[0]);

	m_FontH1[1].CreateFont(24, 10, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("Arial"));
	GetDlgItem(IDCANCEL)->SetFont(&m_FontH1[1]);

	m_FontH1[2].CreateFont(20, 9, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("Arial"));
	GetDlgItem(IDC_STT_HOST_MODEL_NAME_TIT)->SetFont(&m_FontH1[2]);	
	GetDlgItem(IDC_STT_HOST_MODEL_NAME)->SetFont(&m_FontH1[2]);
	GetDlgItem(IDC_STT_LOCAL_MODEL_NAME_TIT)->SetFont(&m_FontH1[2]);
	GetDlgItem(IDC_STT_LOCAL_MODEL_NAME)->SetFont(&m_FontH1[2]);
	GetDlgItem(IDC_STT_FUSING_STATUS_TIT)->SetFont(&m_FontH1[2]);
	GetDlgItem(IDC_STT_FUSING_STATUS)->SetFont(&m_FontH1[2]);

	m_Brush[0].CreateSolidBrush (COLOR_WHITE);
	m_Brush[1].CreateSolidBrush (COLOR_GRAY240);
	m_Brush[2].CreateSolidBrush (COLOR_RED);
	m_Brush[3].CreateSolidBrush (COLOR_GREEN);
}

void CCheckModelNAme::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(nIDEvent == 1)
	{
		KillTimer(1);

		if(Lf_cmpModelName() == TRUE)
			Lf_setFusingData();		

		SetTimer(1, 1000, NULL);
	}
	CDialog::OnTimer(nIDEvent);
}

BOOL CCheckModelNAme::Lf_cmpModelName(void)
{
	BOOL bRtnCode=FALSE;
	CString strDataFolder, hostName, localName, sdata;

	WIN32_FIND_DATA wfd;
	HANDLE hSearch;

	/***************************************************************************************************/
	// Host경로에 지정된 파일이 있는지 없는지 판단한다.
	strDataFolder.Format(_T("%s\\*.mod"), lpSystemInfo->m_sModelNamePath);
	hSearch = FindFirstFile(strDataFolder, &wfd);

	if (hSearch != INVALID_HANDLE_VALUE)
	{
		if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		{
			bRtnCode = TRUE;
			m_nHostFindFlag = 2;
			hostName = wfd.cFileName;

			GetDlgItem(IDC_STT_HOST_MODEL_NAME)->SetWindowText(hostName);
		}
		FindClose (hSearch);
	}
	else
	{
		m_nHostFindFlag = 1;		
		GetDlgItem(IDC_STT_HOST_MODEL_NAME)->SetWindowText("Error. Can Not Find Host Model Name File");
		FindClose (hSearch);
	}

	if(bRtnCode == FALSE)	return FALSE;
	/***************************************************************************************************/
	// Local 경로에 Host모델과 동일한 파일이 있는지 확인한다.
	strDataFolder.Format(_T(".\\MODEL\\*.mod"));

	hSearch = FindFirstFile (strDataFolder, &wfd);

	if (hSearch != INVALID_HANDLE_VALUE)
	{
		if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		{
			localName = wfd.cFileName;
			localName = localName.Right(localName.GetLength()-2);
			if(hostName != localName)
			{
				while(FindNextFile (hSearch, &wfd))
				{
					if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
					{
						localName = wfd.cFileName;
						localName = localName.Right(localName.GetLength()-2);

						if(hostName == localName)	break;
					}
				}
			}
		}

		if(hostName == localName)
		{
			bRtnCode = TRUE;
			m_nLocalFindFlag = 2;
			localName = wfd.cFileName;
			localName.MakeUpper();			
			localName = localName.Left(localName.GetLength()-4);
			m_pApp->m_sNewModelName = localName;
			GetDlgItem(IDC_STT_LOCAL_MODEL_NAME)->SetWindowText(localName);
		}
		else
		{
			bRtnCode = FALSE;
			m_nLocalFindFlag = 1;
			GetDlgItem(IDC_STT_LOCAL_MODEL_NAME)->SetWindowText("Error. Can Not Find Local Model File");
		}

		FindClose (hSearch);
	}
	else
	{	
		m_nLocalFindFlag = 1;
		bRtnCode = FALSE;
		GetDlgItem(IDC_STT_LOCAL_MODEL_NAME)->SetWindowText("Error. Can Not Find Local Model File");
		FindClose (hSearch);		
	}

	return bRtnCode;
}

void CCheckModelNAme::Lf_setFusingData()
{
	CString sdata, strDataFolder;

	if(m_pApp->m_sNewModelName != m_pApp->m_sOldModelName)
	{
		GetDlgItem(IDC_STT_HOST_MODEL_NAME)->SetWindowText(m_pApp->m_sNewModelName);

		Lf_getLoadVariFromModelFile(m_pApp->m_sNewModelName.GetBuffer(0));
	
		if(Lf_setProcOpBoxFusing() == 0)//퓨징이 정상적으로 진행이 되었으면 올드네임에 최신네임으로 업데이트한다.  정상적으로 퓨징도 안됐는데 올드네임에 업데이트 해버리면 프로그램은 최신 모델이면서 오피박스는 이전 모델을 가져가기때문이다. 
		{
			m_pApp->m_bIsChange = TRUE;
			m_pApp->m_sOldModelName = m_pApp->m_sNewModelName;
			m_nSendFlag = 2;
			Write_SysIniFile(_T("SYSTEM"),		_T("LAST_MODEL_NAME"),		m_pApp->m_sOldModelName.GetBuffer(0));

			GetDlgItem(IDC_STT_FUSING_STATUS)->SetWindowText(_T("Fusing Complete."));
		}
		else
		{
			m_nSendFlag = 1;
			GetDlgItem(IDC_STT_FUSING_STATUS)->SetWindowText(_T("Fusing Error. Check up RS232 Communication."));
		}
	}
	else
	{
		m_pApp->m_bIsChange = FALSE;				
		GetDlgItem(IDC_STT_HOST_MODEL_NAME)->SetWindowText(m_pApp->m_sNewModelName);
		GetDlgItem(IDC_STT_FUSING_STATUS)->SetWindowText(_T("Old Model New Model Same. Fusing Skip"));
	}
}

void CCheckModelNAme::Lf_getLoadVariFromModelFile(char *pModelName)
{
	/**********************************************************************************************************/
	Read_ModelFile(pModelName, "RESOLUTION", "PIXEL"		,	&lpModelInfo->nPixel);
	Read_ModelFile(pModelName, "RESOLUTION", "SWAP"		,	&lpModelInfo->nSwap);
	Read_ModelFile(pModelName, "RESOLUTION", "MCLK"		,	&lpModelInfo->fMclk);

	Read_ModelFile(pModelName, "RESOLUTION", "H_TOTAL"	,	&lpModelInfo->nHtotal);
	Read_ModelFile(pModelName, "RESOLUTION", "H_WIDTH"	,	&lpModelInfo->nHwidth);
	Read_ModelFile(pModelName, "RESOLUTION", "H_ACTIVE"	,	&lpModelInfo->nHact);
	Read_ModelFile(pModelName, "RESOLUTION", "H_BP"		,	&lpModelInfo->nHBP);
	Read_ModelFile(pModelName, "RESOLUTION", "H_FP"		,	&lpModelInfo->nHFP);

	Read_ModelFile(pModelName, "RESOLUTION", "V_TOTAL"	,	&lpModelInfo->nVtotal);
	Read_ModelFile(pModelName, "RESOLUTION", "V_WIDTH"	,	&lpModelInfo->nVwidth);
	Read_ModelFile(pModelName, "RESOLUTION", "V_ACTIVE"	,	&lpModelInfo->nVact);
	Read_ModelFile(pModelName, "RESOLUTION", "V_BP"		,	&lpModelInfo->nVBP);
	Read_ModelFile(pModelName, "RESOLUTION", "V_FP"		,	&lpModelInfo->nVFP);

	/**********************************************************************************************************/
	Read_ModelFile(pModelName, "INTERFACE", "SIGNAL_TYPE"	,	&lpModelInfo->nSigType);
	Read_ModelFile(pModelName, "INTERFACE", "SIGNAL_BIT"	,	&lpModelInfo->nSigBit);
	Read_ModelFile(pModelName, "INTERFACE", "BIT_SEL"		,	&lpModelInfo->nBitSel);
	Read_ModelFile(pModelName, "INTERFACE", "LVDS_SEL"		,	&lpModelInfo->nLvdsSel);
	Read_ModelFile(pModelName, "INTERFACE", "DATA_FORMAT"	,	&lpModelInfo->nDataFormat);
	Read_ModelFile(pModelName, "INTERFACE", "PRE_EMPHASIS"	,	&lpModelInfo->nPreEmph);
	Read_ModelFile(pModelName, "INTERFACE", "DIV_MODE"		,	&lpModelInfo->nDIVmode);
	Read_ModelFile(pModelName, "INTERFACE", "COPEN_CHK"		,	&lpModelInfo->nCopenChk);

	Read_ModelFile(pModelName, "INTERFACE", "GPIO1"			,	&lpModelInfo->nGPIO[0]);
	Read_ModelFile(pModelName, "INTERFACE", "GPIO2"			,	&lpModelInfo->nGPIO[1]);
	Read_ModelFile(pModelName, "INTERFACE", "GPIO3"			,	&lpModelInfo->nGPIO[2]);
	Read_ModelFile(pModelName, "INTERFACE", "GPIO4"			,	&lpModelInfo->nGPIO[3]);
	Read_ModelFile(pModelName, "INTERFACE", "GPIO5"			,	&lpModelInfo->nGPIO[4]);
	Read_ModelFile(pModelName, "INTERFACE", "GPIO6"			,	&lpModelInfo->nGPIO[5]);
	Read_ModelFile(pModelName, "INTERFACE", "GPIO7"			,	&lpModelInfo->nGPIO[6]);
	Read_ModelFile(pModelName, "INTERFACE", "GPIO8"			,	&lpModelInfo->nGPIO[7]);

	/**********************************************************************************************************/
	Read_ModelFile(pModelName, "POWER_SEQ", "SEQ_SELECTION"		,	&lpModelInfo->nSeqSel);
	Read_ModelFile(pModelName, "POWER_SEQ", "SEQ_TIME_1"		,	&lpModelInfo->nTSeq[0]);
	Read_ModelFile(pModelName, "POWER_SEQ", "SEQ_TIME_2"		,	&lpModelInfo->nTSeq[1]);
	Read_ModelFile(pModelName, "POWER_SEQ", "SEQ_TIME_3"		,	&lpModelInfo->nTSeq[2]);
	Read_ModelFile(pModelName, "POWER_SEQ", "SEQ_TIME_4"		,	&lpModelInfo->nTSeq[3]);
	Read_ModelFile(pModelName, "POWER_SEQ", "SEQ_OFF_DIN"		,	&lpModelInfo->nPowerSeqOffDinCount);

#if 0
	/**********************************************************************************************************/
	Read_ModelFile(pModelName, "POWER_SET", "VCC",		&lpModelInfo->fPWR_SetVOLT[0]);
	Read_ModelFile(pModelName, "POWER_SET", "VDD",		&lpModelInfo->fPWR_SetVOLT[1]);
	Read_ModelFile(pModelName, "POWER_SET", "VBL",		&lpModelInfo->fPWR_SetVOLT[2]);

	Read_ModelFile(pModelName, "POWER_SET", "VCC_OFFSET",	&lpModelInfo->fPWR_OFFSET[0]);
	Read_ModelFile(pModelName, "POWER_SET", "VBL_OFFSET",	&lpModelInfo->fPWR_OFFSET[1]);

	/**********************************************************************************************************/
	Read_ModelFile(pModelName, "POWER_LIMIT", "ICC_LOW",	&lpModelInfo->nPWR_currLIMIT[LIMIT_LOW][0]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "IDD_LOW",	&lpModelInfo->nPWR_currLIMIT[LIMIT_LOW][1]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "IBL_LOW",	&lpModelInfo->nPWR_currLIMIT[LIMIT_LOW][2]);

	Read_ModelFile(pModelName, "POWER_LIMIT", "ICC_HIGH",	&lpModelInfo->nPWR_currLIMIT[LIMIT_HIGH][0]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "IDD_HIGH",	&lpModelInfo->nPWR_currLIMIT[LIMIT_HIGH][1]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "IBL_HIGH",	&lpModelInfo->nPWR_currLIMIT[LIMIT_HIGH][2]);

	/**********************************************************************************************************/
	Read_ModelFile(pModelName, "POWER_LIMIT", "VCC_LOW",	&lpModelInfo->fPWR_voltLIMIT[LIMIT_LOW][0]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "VDD_LOW",	&lpModelInfo->fPWR_voltLIMIT[LIMIT_LOW][1]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "VBL_LOW",	&lpModelInfo->fPWR_voltLIMIT[LIMIT_LOW][2]);

	Read_ModelFile(pModelName, "POWER_LIMIT", "VCC_HIGH",	&lpModelInfo->fPWR_voltLIMIT[LIMIT_HIGH][0]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "VDD_HIGH",	&lpModelInfo->fPWR_voltLIMIT[LIMIT_HIGH][1]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "VBL_HIGH",	&lpModelInfo->fPWR_voltLIMIT[LIMIT_HIGH][2]);
#else
	/**********************************************************************************************************/
	Read_ModelFile(pModelName, "POWER_SET", "VCC",		&lpModelInfo->fPWR_SetVOLT[0]);
	Read_ModelFile(pModelName, "POWER_SET", "VDD",		&lpModelInfo->fPWR_SetVOLT[1]);
	Read_ModelFile(pModelName, "POWER_SET", "VBL",		&lpModelInfo->fPWR_SetVOLT[2]);
	Read_ModelFile(pModelName, "POWER_SET", "VBL2",		&lpModelInfo->fPWR_SetADD_VBL);

	Read_ModelFile(pModelName, "POWER_SET", "VCC_OFFSET",	&lpModelInfo->fPWR_OFFSET[0]);
	Read_ModelFile(pModelName, "POWER_SET", "VBL_OFFSET",	&lpModelInfo->fPWR_OFFSET[1]);
	Read_ModelFile(pModelName, "POWER_SET", "VBL2_OFFSET",	&lpModelInfo->fPWR_SetADD_CURR);

	/**********************************************************************************************************/
	Read_ModelFile(pModelName, "POWER_LIMIT", "ICC_LOW",	&lpModelInfo->nPWR_currLIMIT[LIMIT_LOW][0]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "IDD_LOW",	&lpModelInfo->nPWR_currLIMIT[LIMIT_LOW][1]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "IBL_LOW",	&lpModelInfo->nPWR_currLIMIT[LIMIT_LOW][2]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "IBL2_LOW",	&lpModelInfo->nPWR_AddVBL_CurrLIMIT[0]);

	Read_ModelFile(pModelName, "POWER_LIMIT", "ICC_HIGH",	&lpModelInfo->nPWR_currLIMIT[LIMIT_HIGH][0]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "IDD_HIGH",	&lpModelInfo->nPWR_currLIMIT[LIMIT_HIGH][1]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "IBL_HIGH",	&lpModelInfo->nPWR_currLIMIT[LIMIT_HIGH][2]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "IBL2_HIGH",	&lpModelInfo->nPWR_AddVBL_CurrLIMIT[1]);

	/**********************************************************************************************************/
	Read_ModelFile(pModelName, "POWER_LIMIT", "VCC_LOW",	&lpModelInfo->fPWR_voltLIMIT[LIMIT_LOW][0]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "VDD_LOW",	&lpModelInfo->fPWR_voltLIMIT[LIMIT_LOW][1]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "VBL_LOW",	&lpModelInfo->fPWR_voltLIMIT[LIMIT_LOW][2]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "VBL2_LOW",	&lpModelInfo->fPWR_AddVBL_VoltLIMIT[0]);

	Read_ModelFile(pModelName, "POWER_LIMIT", "VCC_HIGH",	&lpModelInfo->fPWR_voltLIMIT[LIMIT_HIGH][0]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "VDD_HIGH",	&lpModelInfo->fPWR_voltLIMIT[LIMIT_HIGH][1]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "VBL_HIGH",	&lpModelInfo->fPWR_voltLIMIT[LIMIT_HIGH][2]);
	Read_ModelFile(pModelName, "POWER_LIMIT", "VBL2_HIGH",	&lpModelInfo->fPWR_AddVBL_VoltLIMIT[1]);
#endif

	char szModKey[16];
	int nItemCnt;
	int nLoop;

	for(nLoop=0; nLoop<16; nLoop++)
	{
		sprintf(szModKey, "PTN%02d_NAME", nLoop);
		Read_ModelFile(pModelName, "FUSING_PATTERN", szModKey, lpModelInfo->szPtnName[nLoop]);

		sprintf(szModKey, "PTN%02d_GRAY", nLoop);
		Read_ModelFile(pModelName, "FUSING_PATTERN", szModKey, lpModelInfo->szPtnGray[nLoop]);
	}
}

int CCheckModelNAme::Lf_getSignalType(char cmbSignalType)
{
	int nRtnVal=tpLVDS;

	switch(cmbSignalType)
	{
	case 0 ://LVDS
		{
			nRtnVal=tpLVDS;
		}break;

	case 1 ://Vx1
		{
			nRtnVal=tpVx1;
		}break;
	}

	return nRtnVal;
}

int CCheckModelNAme::Lf_makeSystemFusingPacket(char *pModelName, char *pszRtnPack)
{
	CString strTmp("");
	int nInterface=0;
	int nLenPos=0;
	float fClock=0;

	strTmp.Format("%s", pModelName);
	for(int n=strTmp.GetLength(); n< 30; n++)
	{
		strTmp.Insert(n, "*");
	}

	sprintf(pszRtnPack, "%s%02d", strTmp.GetBuffer(0), 99);
	nLenPos = strlen(pszRtnPack);

	switch(lpModelInfo->nPixel)
	{
	case 0:		/* SINGLE */
		{
			nInterface = 0;
		}break;

	case 1:		/* DUAL */
		{
			nInterface = 1;
			fClock = lpModelInfo->fMclk/(float)2.0;
		}break;

	case 2:		/* QUAD */
		{
			nInterface = 2;
			fClock = lpModelInfo->fMclk/(float)4.0;
		}break;

	case 3:		/* OCTA */
		{
			nInterface = 3;
			fClock = lpModelInfo->fMclk/(float)8.0;
		}break;

	case 4:		/* HEXA */
		{
			nInterface = 4;
			fClock = lpModelInfo->fMclk/(float)16.0;
		}break;
	}

	int nMode = 0;
	int nBitsSwap = lpModelInfo->nSwap << 4;

	int nDotClockInv=0;
	int nHsyncPolarity = 0x00;
	int nVsyncPolarity = 0x00;
	int nConvSignalType = Lf_getSignalType(lpModelInfo->nSigType);

	sprintf(&pszRtnPack[nLenPos], "INFO%02X%01X%04d%04d%06.2f%03d%04d%04d%03d%04d%04d%01d", (nInterface|nMode|nBitsSwap)\
		, (nDotClockInv|nHsyncPolarity|nVsyncPolarity)\
		, lpModelInfo->nHact\
		, lpModelInfo->nVact\
		, fClock\
		, lpModelInfo->nHwidth\
		, lpModelInfo->nHFP\
		, lpModelInfo->nHBP\
		, lpModelInfo->nVwidth\
		, lpModelInfo->nVFP\
		, lpModelInfo->nVBP\
		, lpModelInfo->nDIVmode);
	nLenPos = strlen(pszRtnPack);

	sprintf(&pszRtnPack[nLenPos], "%04d%03d%03d%03d%03d%02d%01d%02d%03d%02d%04d%01d%03d%01d%01d%01d%01d%01d%01d%01d%01d%02d%01d%01d%01d%01d", 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, nConvSignalType\
		, lpModelInfo->nSigBit\
		, lpModelInfo->nPixel\
		, lpModelInfo->nGPIO[1]\
		, lpModelInfo->nGPIO[2]\
		, 0\
		, lpModelInfo->nPreEmph\
		, 0\
		, 0\
		, lpModelInfo->nCopenChk\
		, 0\
		, 0\
		, 0);
	nLenPos = strlen(pszRtnPack);

	/* Power INFO */
	char szSeqChar;
	if(lpModelInfo->nSeqSel==1)	szSeqChar='S';
	else						szSeqChar='V';
	sprintf(&pszRtnPack[nLenPos], "%03d%03d%04d%03d%03d%03d%03d%c%03d%03d%03d%03d%03d",	int(lpModelInfo->fPWR_SetVOLT[0]*10.0)\
		, int(lpModelInfo->fPWR_SetVOLT[1]*10.0)\
		, int(lpModelInfo->fPWR_SetVOLT[2]*10.0)\
		, 0\
		, int(lpModelInfo->fPWR_OFFSET[0]*100.0)\
		, 0\
		, int(lpModelInfo->fPWR_OFFSET[1]*100.0)\
		, szSeqChar\
		, lpModelInfo->nTSeq[0]\
		, lpModelInfo->nTSeq[1]\
		, lpModelInfo->nTSeq[2]\
		, lpModelInfo->nTSeq[3]\
		,0);
	nLenPos = strlen(pszRtnPack);

	/* INVERTER INFO */
	sprintf(&pszRtnPack[nLenPos], "%01d%01d%01d%01d%01d%01d%01d%01d%01d%01d%01d%02d%01d%01d%01d%01d%01d%01d%01d%01d%01d%05d%03d%01d%01d%01d%01d", 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0);
	nLenPos = strlen(pszRtnPack);

	/* LIMIT INFO */
	sprintf(&pszRtnPack[nLenPos], "%04d%04d%04d%04d%04d%04d%04d%04d%04d%04d%04d%04d%02d%03d%03d", (int)(lpModelInfo->fPWR_voltLIMIT[0][0]*100)\
		, (int)(lpModelInfo->fPWR_voltLIMIT[1][0]*100)\
		, (int)(lpModelInfo->fPWR_voltLIMIT[0][1]*100)\
		, (int)(lpModelInfo->fPWR_voltLIMIT[1][1]*100)\
		, (int)(lpModelInfo->fPWR_voltLIMIT[0][2]*10)\
		, (int)(lpModelInfo->fPWR_voltLIMIT[1][2]*10)\
		, (int)(lpModelInfo->nPWR_currLIMIT[0][0])\
		, (int)(lpModelInfo->nPWR_currLIMIT[1][0])\
		, (int)(lpModelInfo->nPWR_currLIMIT[0][1])\
		, (int)(lpModelInfo->nPWR_currLIMIT[1][1])\
		, (int)(lpModelInfo->nPWR_currLIMIT[0][2])\
		, (int)(lpModelInfo->nPWR_currLIMIT[1][2])\
		, 0\
		, 0\
		, 0);
	nLenPos = strlen(pszRtnPack);

	/* LED/BL INFO */
	sprintf(&pszRtnPack[nLenPos], "%02x%02x%02x%02x%01d%01d%01d%04d%04d", 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0);
	nLenPos = strlen(pszRtnPack);

	/* HDCP/EP INFO */
	sprintf(&pszRtnPack[nLenPos], "%02X%02X%02X%02X%02X%02X%02X%02X", 0x55\
		, 0x55\
		, 0x55\
		, 0x55\
		, 0x55\
		, 0x55\
		, 0x55\
		, 0x55\
		, 0x55\
		, 0x55\
		, 0x55\
		, 0x55\
		, 0x55\
		, 0x55\
		, 0x55\
		, 0x55);
	nLenPos = strlen(pszRtnPack);

	/* MAINT INFO */
	sprintf(&pszRtnPack[nLenPos], "%01d%01d%03d%01d%01d", 0\
		, 0\
		, 0\
		, 0\
		, 0);
	nLenPos = strlen(pszRtnPack);

	/* PREDISPLAY */
	sprintf(&pszRtnPack[nLenPos], "%01d%01d%01d", 0\
		, 0\
		, 0);
	nLenPos = strlen(pszRtnPack);

	/* INV_LESS */
	sprintf(&pszRtnPack[nLenPos], "%01d%01d%01d%01d%03d%03d%03d%03d%01d", 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, 0);
	nLenPos = strlen(pszRtnPack);

	/* OTHER */
	sprintf(&pszRtnPack[nLenPos], "%01d%03d%01d%01d%01d%04d%03d%04d%04d%04d%04d", 0\
		, 0\
		, 0\
		, 0\
		, 0\
		, (int)(lpModelInfo->fPWR_SetADD_VBL*10.0)\
		, (int)(lpModelInfo->fPWR_SetADD_CURR*100.0)\
		, (int)(lpModelInfo->fPWR_AddVBL_VoltLIMIT[0]*10)\
		, (int)(lpModelInfo->fPWR_AddVBL_VoltLIMIT[1]*10)\
		, (int)(lpModelInfo->nPWR_AddVBL_CurrLIMIT[0])\
		, (int)(lpModelInfo->nPWR_AddVBL_CurrLIMIT[1]));

	nLenPos = strlen(pszRtnPack);

	return nLenPos;
}

int CCheckModelNAme::Lf_setSystemFusing(char *pModName)
{
	char szFusingPacket[512]={0,};
	int nResult=-1;

	Lf_makeSystemFusingPacket(pModName, szFusingPacket);

	if(m_pApp->PacketSend(CMD_CTRL_FUSING_SYSTEM_INFO, (unsigned char *)szFusingPacket, strlen(szFusingPacket)) == TRUE)
	{
		sscanf(&m_pApp->szRecvData[ProtocolData], "%01d", &nResult);
		if(nResult == 0)		return 0;
	}

	return (-1);
}


int CCheckModelNAme::Lf_makePatternFusingPacket(char *pszRtnPack)
{
	int nPtnCnt;
	int nLoop;
	CString strTmp=("");
	CString lpData = ("");

	/* 패턴의 갯수를 얻는다. */
	for(nLoop=0; nLoop<16; nLoop++)
	{
		if(strlen(lpModelInfo->szPtnName[nLoop]) == 0)
		{
			nPtnCnt = nLoop;
			break;
		}
	}
	if(nPtnCnt == 0)	return (-1);

	strTmp.Format("%02X%02d", 0, nPtnCnt);
	lpData += strTmp;

	for(nLoop=0; nLoop<nPtnCnt; nLoop++)
	{
		CString szDataTmp("");
		strTmp.Format(".\\Pattern\\%s.pdb", lpModelInfo->szPtnName[nLoop]);
		strTmp = T2CmdGen::makeT2dataStrFromFile(strTmp);
		strTmp = T2CmdGen::makeT2PatternStr(strTmp, lpModelInfo->nHact, lpModelInfo->nVact);

		lpData = lpData+strTmp;
		lpData = lpData+"^";
	}

	sprintf(pszRtnPack, "%s", lpData.GetBuffer(0));

	return 0;
}


int CCheckModelNAme::Lf_setPatternFusing(void)
{
	char szFusingPacket[2048]={0,};
	int nResult=-1;

	if(Lf_makePatternFusingPacket(szFusingPacket) < 0)
	{
		return (-1);
	}

	if(m_pApp->PacketSend(CMD_CTRL_FUSING_PATTERN, (unsigned char *)szFusingPacket, strlen(szFusingPacket)) == TRUE)
	{
		sscanf(&m_pApp->szRecvData[ProtocolData], "%01d", &nResult);
		if(nResult == 0)		return 0;
	}

	return (-1);
}

int CCheckModelNAme::Lf_makeCtrlIOFusingPacket(char *pszRtnPacket)
{
	int nLenPos=0;

	sprintf(pszRtnPacket, "%01d%01d%01d%01d%01d%01d%01d%01d%02d", lpModelInfo->nGPIO[0]\
		, lpModelInfo->nGPIO[1]\
		, lpModelInfo->nGPIO[2]\
		, lpModelInfo->nGPIO[3]\
		, lpModelInfo->nGPIO[4]\
		, lpModelInfo->nGPIO[5]\
		, lpModelInfo->nGPIO[6]\
		, lpModelInfo->nGPIO[7]\
		, lpModelInfo->nPowerSeqOffDinCount);
	nLenPos = strlen(pszRtnPacket);

	return nLenPos;
}

int CCheckModelNAme::Lf_setControlIOFusing(void)
{
	char szFusingPacket[2048]={0,};
	int nResult=-1;

	Lf_makeCtrlIOFusingPacket(szFusingPacket);

	if(m_pApp->PacketSend(CMD_CTRL_FUSING_CTRL_IO, (unsigned char *)szFusingPacket, strlen(szFusingPacket)) == TRUE)
	{
		sscanf(&m_pApp->szRecvData[ProtocolData], "%01d", &nResult);
		if(nResult == 0)		return 0;
	}

	return (-1);
}

int CCheckModelNAme::Lf_makeModelVoltCurrentPacket(char *pszRtnPacket)
{
	int nLenPos=0;

#if 1
	sprintf(pszRtnPacket, "[Vcc(%.1f),Icc(%.1f)][V:%.1f,I:%.3f]", lpModelInfo->fPWR_SetVOLT[0],\
		(float)lpModelInfo->nPWR_currLIMIT[1][0]/1000,\
		lpModelInfo->fPWR_SetVOLT[2],\
		lpModelInfo->fPWR_OFFSET[1]);



	nLenPos = strlen(pszRtnPacket);
#endif

	return nLenPos;
}

int CCheckModelNAme::Lf_setModelVoltCurrentFusing(void)
{
	char szFusingPacket[2048]={0,};
	int nResult=-1;

	Lf_makeModelVoltCurrentPacket(szFusingPacket);

	if(m_pApp->PacketSend(CMD_CTRL_WRITE_FILE, (unsigned char *)szFusingPacket, strlen(szFusingPacket)) == TRUE)
	{
		sscanf(&m_pApp->szRecvData[ProtocolData], "%01d", &nResult);
		if(nResult == 0)		return 0;
	}

	return (-1);
}

int CCheckModelNAme::Lf_setProcOpBoxFusing()
{
	int nResult=-1;

	Sleep(100);
	if(Lf_setSystemFusing(m_pApp->m_sNewModelName.GetBuffer(0)) != 0)
	{
		return (-1);
	}

	Sleep(100);
	if(Lf_setPatternFusing() != 0)
	{
		return (-1);
	}

	Sleep(100);
	if(Lf_setControlIOFusing() != 0)
	{
		return (-1);
	}

	Sleep(100);
	if(Lf_setModelVoltCurrentFusing() != 0)
	{
		return (-1);
	}

	Sleep(100);		//2019.05.06. KSM. ADD.


	return 0;
}























































