// OpBoxFusing.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TS_WR_HS_FUSING.h"
#include "TS_WR_HS_FUSINGDlg.h"
#include "OpBoxFusing.h"


// COpBoxFusing 대화 상자입니다.

IMPLEMENT_DYNAMIC(COpBoxFusing, CDialog)

COpBoxFusing::COpBoxFusing(CWnd* pParent /*=NULL*/)
	: CDialog(COpBoxFusing::IDD, pParent)
{

}

COpBoxFusing::~COpBoxFusing()
{
}

void COpBoxFusing::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SRC_MODEL, ctrlSrcModelList);
	DDX_Control(pDX, IDC_LIST_FUSING_MODEL, ctrlFusingModelList);
	DDX_Control(pDX, IDC_STT_FUSING_MSG, ctrlOpBoxFusingMsg);
}


BEGIN_MESSAGE_MAP(COpBoxFusing, CDialog)
	ON_BN_CLICKED(IDC_BTN_ADD, &COpBoxFusing::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, &COpBoxFusing::OnBnClickedBtnDel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SRC_MODEL, &COpBoxFusing::OnLvnItemchangedListSrcModel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_FUSING_MODEL, &COpBoxFusing::OnLvnItemchangedListFusingModel)
	ON_BN_CLICKED(IDC_BTN_UP, &COpBoxFusing::OnBnClickedBtnUp)
	ON_BN_CLICKED(IDC_BTN_DN, &COpBoxFusing::OnBnClickedBtnDn)
	ON_BN_CLICKED(IDC_BTN_SAVE, &COpBoxFusing::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_FUSING, &COpBoxFusing::OnBnClickedBtnFusing)
	ON_BN_CLICKED(IDC_BTN_EXPORT, &COpBoxFusing::OnBnClickedBtnExport)
END_MESSAGE_MAP()


// COpBoxFusing 메시지 처리기입니다.

BOOL COpBoxFusing::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	lpModelInfo	= new MODEL_INFO;

	funcInitModelList();
	fucSRC_AllModelList();

	funcLoadFusingModel_fromOperationINI();
	funcUpdateFusingModelList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL COpBoxFusing::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	// Alt+F4 동작하지 않도록 한다.
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

BOOL COpBoxFusing::DestroyWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialog::DestroyWindow();
}

void COpBoxFusing::funcInitModelList(void)
{
	/********************************************************************************************************/
	ctrlSrcModelList.InsertColumn( 0, "SOURCE MODEL FILE LIST", LVCFMT_CENTER, -1, -1 );
	ctrlSrcModelList.SetColumnWidth( 0, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER );
	ctrlSrcModelList.SetColumnWidth( 0, 300);

	DWORD dwStype1 = ctrlSrcModelList.GetExtendedStyle();
	dwStype1 |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	ctrlSrcModelList.SetExtendedStyle(dwStype1);


	/********************************************************************************************************/
	ctrlFusingModelList.InsertColumn( 0, "FUSING MODEL FILE LIST", LVCFMT_CENTER, -1, -1 );
	ctrlFusingModelList.SetColumnWidth( 0, LVSCW_AUTOSIZE | LVSCW_AUTOSIZE_USEHEADER );
	ctrlFusingModelList.SetColumnWidth( 0, 300);

	DWORD dwStype2 = ctrlFusingModelList.GetExtendedStyle();
	dwStype2 |= LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES;
	ctrlFusingModelList.SetExtendedStyle(dwStype2);
}


void COpBoxFusing::fucModDelete(char *szBuff)
{
	CharUpper (szBuff);
	char* pos, *pos2=NULL;
	do
	{
		pos = strrchr (szBuff, '.');
		if (pos == pos2)
			return;
		pos2 = pos;
		if (NULL == pos)
			return;
		if (!strcmp (pos, ".MOD"))
			*pos = NULL;
	} while (1);
}


void COpBoxFusing::fucSRC_AllModelList(void)
{
	char Datafolder[256];
	CString strTemp=_T("");
	int nCnt=0;

	WIN32_FIND_DATA wfd;
	HANDLE hSearch;

	sprintf (Datafolder, ".\\MODEL\\*.mod");

	hSearch = FindFirstFile (Datafolder, &wfd);

	ctrlSrcModelList.DeleteAllItems();

	if (hSearch != INVALID_HANDLE_VALUE)
	{
		if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		{
			fucModDelete ((LPSTR)(LPCTSTR)wfd.cFileName);

			strTemp.Format("%s", wfd.cFileName);
			ctrlSrcModelList.InsertItem(0, strTemp);

			ctrlSrcModelList.SetSelectionMark(0); // Item Select & Focus
			ctrlSrcModelList.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
		}
		while (FindNextFile (hSearch, &wfd))
		{
			if (wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
			{
				fucModDelete ((LPSTR)(LPCTSTR)wfd.cFileName);

				nCnt+=1;

				strTemp.Format("%s", wfd.cFileName);
				ctrlSrcModelList.InsertItem(nCnt, strTemp);

				ctrlSrcModelList.SetSelectionMark(nCnt); // Item Select & Focus
				ctrlSrcModelList.SetItemState(nCnt, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
			}
		}
		FindClose (hSearch);
	}
	else
	{
	}
}

void COpBoxFusing::OnBnClickedBtnAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nSrcPos, nPos, nCnt;
	CString strTemp;

	UpdateData(TRUE);

	POSITION SrcPos = ctrlSrcModelList.GetFirstSelectedItemPosition();
	nSrcPos = ctrlSrcModelList.GetNextSelectedItem(SrcPos);

	nCnt = ctrlFusingModelList.GetItemCount();
	if(nCnt >= 50)
	{
		AfxMessageBox("MODEL Count is OVER.", MB_ICONERROR|MB_OK);
		return;
	}

	POSITION Pos = ctrlFusingModelList.GetFirstSelectedItemPosition();
	nPos = ctrlFusingModelList.GetNextSelectedItem(Pos);

	//if(nPos < 0)
	{
		nPos = nCnt;
	}

	strTemp.Format("%s", szSRC_SelModelName);
	ctrlFusingModelList.InsertItem(nPos, strTemp);

	GetDlgItemText(IDC_EDT_PAT_GRAY, strTemp);
	ctrlFusingModelList.SetItem(nPos, 1, LVIF_TEXT, strTemp, 0, LVIF_STATE, 0, 0);

	ctrlFusingModelList.SetSelectionMark(nPos); // Item Select & Focus
	ctrlFusingModelList.SetItemState(nPos, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);

	ctrlSrcModelList.SetSelectionMark(nSrcPos); // --position); // 2007-09-12 : Item Select & Focus
	ctrlSrcModelList.SetItemState(nSrcPos, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
	ctrlSrcModelList.SetFocus();

	UpdateData(FALSE);
}

void COpBoxFusing::OnBnClickedBtnDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION Pos = ctrlFusingModelList.GetFirstSelectedItemPosition();
	int nPos = ctrlFusingModelList.GetNextSelectedItem(Pos);

	if(nPos < 0)
	{
		return;
	}

	ctrlFusingModelList.DeleteItem(nPos);

	if(!ctrlFusingModelList.GetItemCount())
	{
		return;
	}
	else
	{
		if (ctrlFusingModelList.GetItemCount() <= nPos)
			nPos--;

		ctrlFusingModelList.SetSelectionMark(nPos); // --position); // 2007-09-12 : Item Select & Focus
		ctrlFusingModelList.SetItemState(nPos, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
		ctrlFusingModelList.SetFocus();
	}

	UpdateData(TRUE);
}

void COpBoxFusing::OnLvnItemchangedListSrcModel(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(pNMListView->iItem < 0)
		return;
	if(pNMListView->uOldState && !pNMListView->uNewState)
		return;
	if(!pNMListView->uOldState && !pNMListView->uNewState) // 0, 0
		return;

	*pResult = 0;

	memset(szSRC_SelModelName, 0, sizeof(szSRC_SelModelName));
	ctrlSrcModelList.GetItemText( pNMListView->iItem, 0, szSRC_SelModelName, 30);

	*pResult = 0;
}

void COpBoxFusing::OnLvnItemchangedListFusingModel(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(pNMListView->iItem < 0)
		return;
	if(pNMListView->uOldState && !pNMListView->uNewState)
		return;
	if(!pNMListView->uOldState && !pNMListView->uNewState) // 0, 0
		return;

	*pResult = 0;

	memset(szFUSING_SelModelName, 0, sizeof(szFUSING_SelModelName));
	ctrlFusingModelList.GetItemText( pNMListView->iItem, 0, szFUSING_SelModelName, 30);

	*pResult = 0;
}

void COpBoxFusing::fucListCtrlSwapData(int pos1, int pos2)
{
	UpdateData(TRUE);

	char temp1 [64] = {0,};
	char temp2 [64] = {0,};
	int i = 0;

	for(i=0;i<2;i++)
	{
		ctrlFusingModelList.GetItemText(pos1, i, temp1, 30);
		ctrlFusingModelList.GetItemText(pos2, i, temp2, 30);
		ctrlFusingModelList.SetItem( pos2, i, LVIF_TEXT, temp1, 0, LVIF_STATE, 0, 0);
		ctrlFusingModelList.SetItem( pos1, i, LVIF_TEXT, temp2, 0, LVIF_STATE, 0, 0);
	}

	POSITION pos = ctrlFusingModelList.GetFirstSelectedItemPosition();
	int position = ctrlFusingModelList.GetNextSelectedItem(pos);

	UpdateData(FALSE);
}


void COpBoxFusing::OnBnClickedBtnUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	POSITION pos = ctrlFusingModelList.GetFirstSelectedItemPosition();
	int position = ctrlFusingModelList.GetNextSelectedItem(pos);
	if(position < 1)
	{
		return;
	}

	fucListCtrlSwapData(position, position-1);

	ctrlFusingModelList.SetSelectionMark(position); // Item Select & Focus
	ctrlFusingModelList.SetItemState(position-1, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
	ctrlFusingModelList.SetFocus();

	UpdateData(FALSE);
}

void COpBoxFusing::OnBnClickedBtnDn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	POSITION pos = ctrlFusingModelList.GetFirstSelectedItemPosition();
	int position = ctrlFusingModelList.GetNextSelectedItem(pos);
	int count = ctrlFusingModelList.GetItemCount();

	if(position > (count-2))
	{
		return;
	}
	fucListCtrlSwapData(position, position+1);

	ctrlFusingModelList.SetSelectionMark(position); // 2007-09-12 : Item Select & Focus
	ctrlFusingModelList.SetItemState(position+1, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
	ctrlFusingModelList.SetFocus();

	UpdateData(FALSE);
}


void COpBoxFusing::funcSaveFusingModelList(void)
{
	int nItemCnt, nLoop;

	nItemCnt = ctrlFusingModelList.GetItemCount();

	memset(szFusingModelList, 0, sizeof(szFusingModelList));

	for(nLoop=0; nLoop<nItemCnt; nLoop++)
	{
		ctrlFusingModelList.GetItemText( nLoop, 0, (LPSTR)(LPCSTR)szFusingModelList[nLoop], 64);
	}
}

void COpBoxFusing::funcUpdateFusingModelList(void)
{
	int nLoop;
	CString strTemp;

	ctrlFusingModelList.DeleteAllItems();

	for(nLoop=0; nLoop<50; nLoop++)
	{
		if(strlen(szFusingModelList[nLoop]) == 0)	return;

		strTemp.Format("%s", szFusingModelList[nLoop]);
		ctrlFusingModelList.InsertItem(nLoop, strTemp);

		ctrlFusingModelList.SetSelectionMark(nLoop);				// Item Select & Focus
		ctrlFusingModelList.SetItemState(nLoop, LVIS_SELECTED | LVIS_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED);
	}
}


void COpBoxFusing::funcSaveOperationINI(void)
{
	char szKey[16]={0,};
	char szValue[64]={0,};
	int nLoop;

	for(nLoop=0; nLoop<50; nLoop++)
	{
		sprintf(szKey, "MOD_%02d", nLoop);
		sprintf(szValue, "%s", "");
		Write_SysIniFile("OPBOX_FUSING_MODEL", szKey, szValue);
	}

	for(nLoop=0; nLoop<50; nLoop++)
	{
		if(strlen(szFusingModelList[nLoop]) == 0)	break;

		sprintf(szKey, "MOD_%02d", nLoop);
		sprintf(szValue, "%s", szFusingModelList[nLoop]);
		Write_SysIniFile("OPBOX_FUSING_MODEL", szKey, szValue);
	}
}

void COpBoxFusing::funcLoadFusingModel_fromOperationINI(void)
{
	char szKey[16]={0,};
	int nLoop;
	CString strTemp;

	memset(szFusingModelList, 0, sizeof(szFusingModelList));

	for(nLoop=0; nLoop<50; nLoop++)
	{
		sprintf(szKey, "MOD_%02d", nLoop);
		Read_SysIniFile("OPBOX_FUSING_MODEL", szKey, &strTemp);
		sprintf(szFusingModelList[nLoop], "%s", strTemp.GetBuffer(0));
	}
}

void COpBoxFusing::OnBnClickedBtnSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	funcSaveFusingModelList();

	funcSaveOperationINI();

	funcLoadFusingModel_fromOperationINI();

	funcUpdateFusingModelList();
}


int COpBoxFusing::execDelAllMod(void)
{
	char szTemp[8]={0,};
	int nResult=0;

	memset(m_pApp->szRecvData, 0, sizeof(m_pApp->szRecvData));

	if(m_pApp->PacketSend(CMD_CTRL_DELETE_ALL_MOD, (unsigned char *)szTemp, strlen(szTemp)) == TRUE)
	{//OK
		sscanf(&m_pApp->szRecvData[ProtocolData], "%01d", &nResult);
		if(nResult != 0)		return (-1);

		return 0;
	}

	return (-1);
}


int COpBoxFusing::execCreateModelFile(int nModelNumber)
{
	char szTemp[8]={0,};
	int nResult=0;

	memset(m_pApp->szRecvData, 0, sizeof(m_pApp->szRecvData));

	sprintf(szTemp, "%02d", nModelNumber);
	if(m_pApp->PacketSend(CMD_CTRL_CREATE_FILE, (unsigned char *)szTemp, strlen(szTemp)) == TRUE)
	{//OK
		sscanf(&m_pApp->szRecvData[ProtocolData], "%01d", &nResult);
		if(nResult == 0)		return 0;
	}

	return (-1);
}


void COpBoxFusing::funcLoadPAT_ModelFile(char *pModelName)
{
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

	/* 첫번째 패턴을 Load 한다. */
#if 0	/* 2019.04.02. KSM. 1st 패턴 삭제. */
	Read_ModelFile(pModelName, "1ST_PATTERN", "NAME", lpModelInfo->sz1stPtnName);
	Read_ModelFile(pModelName, "1ST_PATTERN", "GRAY", lpModelInfo->sz1stPtnGray);
#endif
}



void COpBoxFusing::funcLoadVariFromModelFile(char *pModelName)
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

	/**********************************************************************************************************/
	Read_ModelFile(pModelName, "POWER_SET", "POWER_TYPE", &lpModelInfo->nPowerType, "1");
	Read_ModelFile(pModelName, "POWER_SET", "STR_CNT1", &lpModelInfo->nStringCount[0]);
	Read_ModelFile(pModelName, "POWER_SET", "STR_CNT2", &lpModelInfo->nStringCount[1]);
#endif

	funcLoadPAT_ModelFile(pModelName);
}

int COpBoxFusing::funcGetSignalType(char cmbSignalType)
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


int COpBoxFusing::funcMakeSystemFusingPacket(char *pModelName, char *pszRtnPack)
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
	int nConvSignalType = funcGetSignalType(lpModelInfo->nSigType);

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
																																			, lpModelInfo->nPowerType\
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
																								, lpModelInfo->nStringCount[0]\
																								, lpModelInfo->nStringCount[1]);
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
#if 0
	sscanf(&pszRtnPack[nLenPos], "%01d%03d%01d%01d%01d", 0\
														, 0\
														, 0\
														, 0\
														, 0);
#else
	/* OTHER */
	sprintf(&pszRtnPack[nLenPos], "%01d%03d%01d%01d%01d%04d%03d%04d%04d%04d%04d", 9\
																				, 999\
																				, 0\
																				, 0\
																				, 0\
																				, (int)(lpModelInfo->fPWR_SetADD_VBL*10.0)\
																				, (int)(lpModelInfo->fPWR_SetADD_CURR*100.0)\
																				, (int)(lpModelInfo->fPWR_AddVBL_VoltLIMIT[0]*10)\
																				, (int)(lpModelInfo->fPWR_AddVBL_VoltLIMIT[1]*10)\
																				, (int)(lpModelInfo->nPWR_AddVBL_CurrLIMIT[0])\
																				, (int)(lpModelInfo->nPWR_AddVBL_CurrLIMIT[1]));
#endif
	nLenPos = strlen(pszRtnPack);

	return nLenPos;
}


int COpBoxFusing::execSystemFusing(char *pModName)
{
	char szFusingPacket[COM_LENGTH]={0,};
	int nResult=-1;

	funcMakeSystemFusingPacket(pModName, szFusingPacket);

	if(m_pApp->PacketSend(CMD_CTRL_FUSING_SYSTEM_INFO, (unsigned char *)szFusingPacket, strlen(szFusingPacket)) == TRUE)
	{
		sscanf(&m_pApp->szRecvData[ProtocolData], "%01d", &nResult);
		if(nResult == 0)		return 0;
	}

	return (-1);
}


int COpBoxFusing::funcMakePatternFusingPacket(char *pszRtnPack)
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
		//strTmp = T2CmdGen::makeT2FileStr(strTmp);
		strTmp = T2CmdGen::makeT2PatternStr(strTmp, lpModelInfo->nHact, lpModelInfo->nVact);

		lpData = lpData+strTmp;
		lpData = lpData+"^";
	}

	sprintf(pszRtnPack, "%s", lpData.GetBuffer(0));

	return 0;
}


int COpBoxFusing::execPatternFusing(void)
{
	char szFusingPacket[COM_LENGTH]={0,};
	int nResult=-1;

	if(funcMakePatternFusingPacket(szFusingPacket) < 0)
	{
		//AfxMessageBox("PATTERN LIST EMPTY.", MB_ICONERROR|MB_OK);
		return (-1);
	}

	/*CTime t = CTime::GetCurrentTime();
	CString s = t.Format("%H:%M:%S");
	TRACE("[%s][SEND] %s \r\n", s, szFusingPacket);*/
	if(m_pApp->PacketSend(CMD_CTRL_FUSING_PATTERN, (unsigned char *)szFusingPacket, strlen(szFusingPacket)) == TRUE)
	{
		sscanf(&m_pApp->szRecvData[ProtocolData], "%01d", &nResult);
		if(nResult == 0)		return 0;
	} 

	return (-1);
}


int COpBoxFusing::funcMakeCtrlIOFusingPacket(char *pszRtnPacket)
{
	int nLenPos=0;

	/*sprintf(pszRtnPacket, "%01d%01d%01d%01d%01d%01d%01d%01d%02d", lpModelInfo->nGPIO[0]\
																, lpModelInfo->nGPIO[1]\
																, lpModelInfo->nGPIO[2]\
																, lpModelInfo->nGPIO[3]\
																, lpModelInfo->nGPIO[4]\
																, lpModelInfo->nGPIO[5]\
																, lpModelInfo->nGPIO[6]\
																, lpModelInfo->nGPIO[7]\
																, lpModelInfo->nPowerSeqOffDinCount);*/

	sprintf(pszRtnPacket, "%01d%01d%01d%01d%01d%01d%01d%01d%02d%01d%01d%03d%03d%03d%02X%01d%02X%02X%02X%02X"
		, lpModelInfo->nGPIO[0]\
		, lpModelInfo->nGPIO[1]\
		, lpModelInfo->nGPIO[2]\
		, lpModelInfo->nGPIO[3]\
		, lpModelInfo->nGPIO[4]\
		, lpModelInfo->nGPIO[5]\
		, lpModelInfo->nGPIO[6]\
		, lpModelInfo->nGPIO[7]\
		, lpModelInfo->nPowerSeqOffDinCount
		, lpModelInfo->nVcomMode
		, lpModelInfo->nVcomIc
		, lpModelInfo->nVcomDefValue
		, lpModelInfo->nVcomMinValue
		, lpModelInfo->nVcomMaxValue
		, lpModelInfo->nVcomDevAddr
		, lpModelInfo->nVcomDataSize
		, lpModelInfo->nVcomVolRegAddr
		, lpModelInfo->nVcomNonVol_ControlAddr
		, lpModelInfo->nVcomNonVol_WrData
		, lpModelInfo->nVcomNonVol_RdData
	);

	nLenPos = strlen(pszRtnPacket);

	return nLenPos;
}


int COpBoxFusing::execControlIOFusing(void)
{
	char szFusingPacket[COM_LENGTH]={0,};
	int nResult=-1;

	funcMakeCtrlIOFusingPacket(szFusingPacket);

	if(m_pApp->PacketSend(CMD_CTRL_FUSING_CTRL_IO, (unsigned char *)szFusingPacket, strlen(szFusingPacket)) == TRUE)
	{
		sscanf(&m_pApp->szRecvData[ProtocolData], "%01d", &nResult);
		if(nResult == 0)		return 0;
	}

	return (-1);
}

int COpBoxFusing::funcMakeModelVoltCurrentPacket(char *pszRtnPacket)
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

int COpBoxFusing::execModelVoltCurrentFusing(void)
{
	char szFusingPacket[COM_LENGTH]={0,};
	int nResult=-1;

	funcMakeModelVoltCurrentPacket(szFusingPacket);

	if(m_pApp->PacketSend(CMD_CTRL_WRITE_FILE, (unsigned char *)szFusingPacket, strlen(szFusingPacket)) == TRUE)
	{
		sscanf(&m_pApp->szRecvData[ProtocolData], "%01d", &nResult);
		if(nResult == 0)		return 0;
	}
	
	return (-1);
}



int COpBoxFusing::procOpBoxFusing(int nModListNumber)
{
	int nResult=-1;

	funcLoadVariFromModelFile(szFusingModelList[nModListNumber]);
	TRACE("%d - %s \r\n", nModListNumber, szFusingModelList[nModListNumber]);

	nResult = execCreateModelFile(nModListNumber);
	if(nResult == 0)
	{
		Sleep(100);
		if(execSystemFusing(szFusingModelList[nModListNumber]) != 0)
		{
			return (-1);
		}

		Sleep(100);
		if(execPatternFusing() != 0)
		{
			return (-1);
		}

		Sleep(100);
		if(execControlIOFusing() != 0)
		{
			return (-1);
		}
		
		Sleep(100);
		if(execModelVoltCurrentFusing() != 0)
		{
			return (-1);
		}

		Sleep(100);		//2019.05.06. KSM. ADD.
	}

	return 0;
}


void COpBoxFusing::OnBnClickedBtnFusing()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int nLoop;
	int nResult = 0;
	CString strMsg=_T("");

	ctrlOpBoxFusingMsg.SetWindowText("");

	OnBnClickedBtnSave();

	nResult = execDelAllMod();
	if(nResult == 0)
	{
		for(nLoop=0; nLoop<50; nLoop++)
		{
			if(strlen(szFusingModelList[nLoop]) == 0)	break;

			if(procOpBoxFusing(nLoop) != 0)
			{
				strMsg.Format("[ %s ] Fusing NG.", szFusingModelList[nLoop]);
				ctrlOpBoxFusingMsg.SetWindowText(strMsg.GetBuffer(0));
				AfxMessageBox("OP-Box FUSING FAIL.", MB_ICONERROR|MB_OK);
				return;
			}

			strMsg.Format("[ %s ] Fusing OK.", szFusingModelList[nLoop]);
			ctrlOpBoxFusingMsg.SetWindowText(strMsg.GetBuffer(0));
		}
	}
	else
	{
		ctrlOpBoxFusingMsg.SetWindowText("OP-Box FUSING FAIL.");
		AfxMessageBox("OP-Box FUSING FAIL.", MB_ICONERROR|MB_OK);
		return;
	}

	//AfxMessageBox("OP-Box FUSING SUCCESS.", MB_ICONWARNING|MB_OK);
	ctrlOpBoxFusingMsg.SetWindowText("OP-Box FUSING SUCCESS.");
}


void COpBoxFusing::OnBnClickedBtnExport()
{
	// TODO: OP BOX FUSING DATA 내보내기
	auto model_number = 0;
	auto file_name = CString();

	ctrlOpBoxFusingMsg.SetWindowText("");

	// 1. 세이브 폴더 클리어
	CFileFind finder;

	BOOL bWorking = finder.FindFile("SD_Card/*.*");

	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDots())
		{
			continue;
		}

		CString filePath = finder.GetFilePath();
		DeleteFile(filePath);
	}
	finder.Close();

	// 2. OP Box List 파일 생성
	for (const auto model : szFusingModelList)
	{
		if (strlen(model) == 0) break;

		funcLoadVariFromModelFile(model);

		// 2.1. 파일 생성 (text, utf-8)
		CreateDirectory(_T("SD_Card"), NULL);
		file_name.Format("SD_Card\\%02d.MOD", model_number++);
		CFile model_file(_T(file_name), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText);

		// 2.2. System Fusing
		char system_fusing_data[COM_LENGTH] = { 0, };
		char system_fusing_packet[COM_LENGTH] = { 0, };
		funcMakeSystemFusingPacket(model, system_fusing_data);
		m_pApp->makeProtocol(CMD_CTRL_FUSING_SYSTEM_INFO, ADDR_PC, ADDR_CTRL, system_fusing_data, system_fusing_packet, strlen(system_fusing_data));
		model_file.Write(system_fusing_packet, strlen(system_fusing_packet));

		model_file.Write("\r\n", strlen("\r\n"));

		// 2.3. Pattern Fusing
		char pattern_fusing_data[COM_LENGTH] = { 0, };
		char pattern_fusing_packet[COM_LENGTH] = { 0, };

		funcMakePatternFusingPacket(pattern_fusing_data);

		m_pApp->makeProtocol(CMD_CTRL_FUSING_PATTERN, ADDR_PC, ADDR_CTRL, pattern_fusing_data, pattern_fusing_packet, strlen(pattern_fusing_data));
		model_file.Write(pattern_fusing_packet, strlen(pattern_fusing_packet));

		model_file.Write("\r\n", strlen("\r\n"));

		// 2.4. GPIO Fusing
		char gpio_fusing_data[COM_LENGTH] = { 0, };
		char gpio_fusing_packet[COM_LENGTH] = { 0, };
		funcMakeCtrlIOFusingPacket(gpio_fusing_data);

		m_pApp->makeProtocol(CMD_CTRL_FUSING_CTRL_IO, ADDR_PC, ADDR_CTRL, gpio_fusing_data, gpio_fusing_packet, strlen(gpio_fusing_data));
		model_file.Write(gpio_fusing_packet, strlen(gpio_fusing_packet));

		model_file.Write("\r\n", strlen("\r\n"));

		// 2.5. Voltage Set Fusing
		char voltage_fusing_data[COM_LENGTH] = { 0, };
		char voltage_fusing_packet[COM_LENGTH] = { 0, };

		funcMakeModelVoltCurrentPacket(voltage_fusing_data);

		m_pApp->makeProtocol(CMD_CTRL_WRITE_FILE, ADDR_PC, ADDR_CTRL, voltage_fusing_data, voltage_fusing_packet, strlen(voltage_fusing_data));
		model_file.Write(voltage_fusing_packet, strlen(voltage_fusing_packet));

		model_file.Write("\r\n", strlen("\r\n"));

		// 2.6. File Close
		model_file.Close();
	}

	CFile test_file(_T("SD_Card\\TEST.TXT"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText);
	test_file.Close();

	CFile last_file(_T("SD_Card\\LAST.TXT"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText);
	last_file.Write("00", strlen("00"));
	last_file.Close();

	ctrlOpBoxFusingMsg.SetWindowText("OP-Box FUSING DATA EXPORT SUCCESS.");
}
