

typedef struct{
	int nPixel;
	int nSwap;

	float fMclk;

	int nHtotal;
	int nHwidth;
	int nHact;
	int nHBP;
	int nHFP;

	int nVtotal;
	int nVwidth;
	int nVact;
	int nVBP;
	int nVFP;

	int nSigType;
	int nSigBit;
	int nBitSel;
	int nLvdsSel;
	int nCopenChk;

	int nDataFormat;
	int nDIVmode;
	int nPreEmph;

	int nSeqSel;			/* 0 : VCC First */
							/* 1 : SIGNAL First */

	int nTSeq[4];			/* [SEQ1_Time][SEQ2_Time][SEQ3_Time][SEQ4_Time] */

	float fPWR_SetVOLT[3];	/* [VCC][VDD][VBL] */
	float fPWR_OFFSET[2];	/* [VCC_OFFSET][VBL_OFFSET] */

	int nPWR_currLIMIT[2][3];	/* MIN : [0]-[ICC][IDD][IBL] */
								/* MAX : [1]-[ICC][IDD][IBL] */

	float fPWR_voltLIMIT[2][3];	/* MIN : [0]-[VCC][VDD][VBL] */
								/* MAX : [1]-[VCC][VDD][VBL] */

	/*********************************************************/
	float fPWR_SetADD_VBL;
	float fPWR_SetADD_CURR;

	int nPWR_AddVBL_CurrLIMIT[2];	/* MIN-[0] , MAX-[1] */
	float fPWR_AddVBL_VoltLIMIT[2];	/* MIN-[0] , MAX-[1] */
	/*********************************************************/

	int nGPIO[8];

	int nSelModel;

	char szPtnName[16][64];
	char szPtnGray[16][6];

	char sz1stPtnName[64];
	char sz1stPtnGray[6];

	int nPowerSeqOffDinCount;

	int nVcomMode = 0;
	int nVcomIc = 0;
	int nVcomDefValue = 0;
	int nVcomMinValue = 0;
	int nVcomMaxValue = 0;
	int nVcomDevAddr = 0;
	int nVcomDataSize = 0;
	int nVcomVolRegAddr = 0;
	int nVcomNonVol_ControlAddr = 0;
	int nVcomNonVol_WrData = 0;
	int nVcomNonVol_RdData = 0;

	/* 0-edge, 1-direct, 2-led_driver */
	int nPowerType = 1;
	int nStringCount[2] = {6,6};
	int nPowerId = 1;

}MODEL_INFO, *LPMODELINFO;

typedef struct{
	CString m_sModelNamePath;
}SYSTEMINFO, *LPSYSTEMINFO;

