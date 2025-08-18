// T2CmdGen.cpp: implementation of the T2CmdGen class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "BoardAssySW.h"
#include "T2CmdGen.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

T2CmdGen::T2CmdGen()
{
	pbdData.RemoveAll();
	hResol = 0;
	vResol = 0;
}

T2CmdGen::T2CmdGen(int h, int v)
{
	pbdData.RemoveAll();
	hResol = h;
	vResol = v;
}

T2CmdGen::~T2CmdGen()
{
	
}

CString T2CmdGen::makeT2dataStrFromFile(CString pbdFilePath)
{
	CFile mFile;
	if( mFile.Open(pbdFilePath, CFile::modeRead) == FALSE )
	{
		return "";
	}
	
	WCHAR tmpBuff[fileBufSize] = {0};
	mFile.Read((void*)tmpBuff, sizeof(tmpBuff));
	CString tmpStr(tmpBuff);
	mFile.Close();
	return tmpStr;
}


CString T2CmdGen::makeT2PatternStr(CString dataStr, int width, int height)
{
	T2CmdGen* pObj = NULL;
	pObj = new T2CmdGen(width, height);

	CString retStr=_T("");
	int cnt = pObj->makeStringArray(dataStr);
	if( cnt > 0 )
	{
		retStr = pObj->makeObjStr(dataStr);
	}

	delete pObj;
	pObj = NULL;
	return retStr;
}

CString T2CmdGen::makeObjStr(CString dataStr)
{
	CString retStr=_T("");

	retStr.Format("");
	for(int i=0; i<pbdData.GetSize(); i++)
	{
		CString tmpStr("");
		tmpStr = pbdData.GetAt(i);
		retStr += makeSubStr(tmpStr, i);
	}

	return retStr;
}

CString T2CmdGen::makeSubStr(CString dataStr, int idx)
{
	CString retStr("");
	CStringArray dStrAry;
	dStrAry.RemoveAll();

	CString tmpStr("");
	int i=0;
	while(1)
	{
		int oldI = i;
		i = dataStr.Find(",", i) + 1;
		if( i == 0 )
		{
			if( dataStr.GetLength() > oldI )
			{
				tmpStr = dataStr.Mid(oldI, dataStr.GetLength()-oldI);
				dStrAry.Add(tmpStr);
			}
			break;
		}
		tmpStr = dataStr.Mid(oldI, i-oldI-1);
		dStrAry.Add(tmpStr);
	}
	//////////////////////////////////////////////////////////////////////////
	tmpStr = dStrAry.GetAt(0);

	////////////////////////////////////////////////////////////////////////// TB
	if( tmpStr == "TB" )	// CDrawBitmap
	{
		// Reading
		tmpStr = dStrAry.GetAt(1);
		int m_nIndex = strtoul(tmpStr, 0, 16);

		tmpStr = dStrAry.GetAt(2);
		int x1 = (int)String2Float(tmpStr, hResol);
	
		tmpStr = dStrAry.GetAt(3);
		int y1 = (int)String2Float(tmpStr, vResol);

		tmpStr = dStrAry.GetAt(4);
		int x2 = (int)String2Float(tmpStr, hResol);
	
		tmpStr = dStrAry.GetAt(5);
		int y2 = (int)String2Float(tmpStr, vResol);

		tmpStr = dStrAry.GetAt(6);
		int m_nFillOpt = atoi(tmpStr);

		int m_BitmapSizeX = 0;
		int m_BitmapSizeY = 0;
		CString szBrush("");
		if( m_nIndex == 0xFF )
		{
			tmpStr = dStrAry.GetAt(7);
			m_BitmapSizeX = atoi(tmpStr);

			tmpStr = dStrAry.GetAt(8);
			m_BitmapSizeY = atoi(tmpStr);

			tmpStr = dStrAry.GetAt(9);
		// 2007-12-15 : User BitMap Pattern
			szBrush = tmpStr; // atoi(tmpStr);
		}

		int max = m_BitmapSizeX * m_BitmapSizeY;

		CString m_userBrush("");
		// 2007-12-15 : User BitMap Pattern
		m_userBrush = szBrush;
/*
		for(int i = 0 ; i < max ; i++)
		{
			m_userBrush += '8';
		}
//*/
		// Store
		CString strCode("");
		CString str("");
		CString szBmpPattern("");
		if( m_nIndex == 0xFF)
		{
			szBmpPattern.Format("DB%03d%02X", m_userBrush.GetLength()+7,m_BitmapSizeX);
			szBmpPattern += m_userBrush;
		}

		str.Format("%02X%04d%04d%04d%04d%01d",
					m_nIndex,
					x1,
					y1,
					x2,
					y2,
					m_nFillOpt);

		CString szData;
		int n = str.GetLength();

		szData.Format("TB%03d", n+5);
		szData  += str;
		strCode += szBmpPattern;
		strCode += szData;

		retStr = strCode;
	}
	////////////////////////////////////////////////////////////////////////// BD
	else if( tmpStr == "BD")	//2015.09.14. KSM. 추가.
	{
		CString str="";

		str.Format("BD%03d%s%s%s%s%s%s", 21, dStrAry.GetAt(1), dStrAry.GetAt(2), dStrAry.GetAt(3), dStrAry.GetAt(4), dStrAry.GetAt(5), dStrAry.GetAt(6));
		retStr = str;
	}
	////////////////////////////////////////////////////////////////////////// TA
	else if( tmpStr == "TA" )	// CDrawCanvasY
	{
		CString strCode("");
		CString str("");
		CString strBuf("");
		int iType=2;

		// Reading
		int nCurPos = 1;
		int nTotal  = dStrAry.GetSize();

		int m_yindex = 0;
		int m_xindex = 0;
		int endY = 0;
		int endX = 0;
		int nColorOpt = 0;
		int m_Clr2 = 0;
		CString Gradation("");
		CString BitCtrl("");

		while(nCurPos < nTotal)
		{
			if((nCurPos+2) > nTotal)
				break;

			tmpStr = dStrAry.GetAt(nCurPos++);
			m_yindex = strtoul(tmpStr, 0, 16);

			tmpStr = dStrAry.GetAt(nCurPos++);
			m_xindex = strtoul(tmpStr, 0, 16);


			if( m_xindex == 0 )
			{
				if((nCurPos + 5) > nTotal )
				{
					break;
				}
				// Reading
				tmpStr = dStrAry.GetAt(nCurPos++);
				endY = (int)String2Float(tmpStr, vResol);

				tmpStr = dStrAry.GetAt(nCurPos++);
				endX = (int)String2Float(tmpStr, hResol);

				tmpStr = dStrAry.GetAt(nCurPos++);
				nColorOpt = atoi(tmpStr);

				tmpStr = dStrAry.GetAt(nCurPos++);
				m_Clr2 = strtoul(tmpStr, 0, 16);

				tmpStr = dStrAry.GetAt(nCurPos++);
				Gradation = tmpStr;


				// Store
				endX |= ((nColorOpt&0x0F) << 12);
				if(iType == 0)
				{
					str.Format("%04X%04X%s", endX, m_Clr2, Gradation);
				}
				else if(iType == 1)
				{
					str.Format("%04X%04X%s%s", endX, m_Clr2, Gradation, "0");
				}
				else if(iType == 2)
				{
					tmpStr= dStrAry.GetAt(nCurPos++);
					BitCtrl = tmpStr;
					str.Format("%04X%04X%s%s", endX, m_Clr2, Gradation, BitCtrl);
				}

				strBuf += str;

			}
			else if( m_xindex > 0 )
			{
				if((nCurPos + 4) > nTotal )
				{
					break;
				}

				// Reading
				tmpStr = dStrAry.GetAt(nCurPos++);
				endX = (int)String2Float(tmpStr, hResol);

				tmpStr = dStrAry.GetAt(nCurPos++);
				nColorOpt = atoi(tmpStr);

				tmpStr = dStrAry.GetAt(nCurPos++);
				m_Clr2 = strtoul(tmpStr, 0, 16);

				tmpStr = dStrAry.GetAt(nCurPos++);
				Gradation = tmpStr;

				// Store
				endX |= ((nColorOpt&0x0F) << 12);
				if(iType == 0)
				{
					//					str.Format("%04X%04X%s", endX, m_Clr2, Gradation);
					str.Format("%1X%02X%04X%04X%s", m_yindex,m_xindex, endX, m_Clr2, Gradation);
				}
				else if(iType == 1)
				{
					//					str.Format("%04X%04X%s%s", endX, m_Clr2, Gradation, "0");
					str.Format("%1X%02X%04X%04X%s%s", m_yindex,m_xindex, endX, m_Clr2, Gradation, "0");
				}
				else if(iType == 2)
				{
					tmpStr= dStrAry.GetAt(nCurPos++);
					BitCtrl = tmpStr;
					//					str.Format("%04X%04X%s%s", endX, m_Clr2, Gradation, BitCtrl);
					str.Format("%1X%02X%04X%04X%s%s", m_yindex,m_xindex, endX, m_Clr2, Gradation, BitCtrl);
				}

				strBuf += str;
			}
		}

		strCode.Format("TA%03d%1X%02X%04d",strBuf.GetLength()+12,m_yindex,0,endY);
		strCode += strBuf;

		retStr = strCode;
	}
	////////////////////////////////////////////////////////////////////////// TD
	else if( tmpStr == "TD" )	// CDrawChess
	{
		CString strCode("");
		CString str("");

		tmpStr = dStrAry.GetAt(1);
		int m_nType = strtoul(tmpStr, 0, 10);

		int m_matrixY = 0;
		int m_matrixX = 0;
		int m_Clr1Opt = 0;
		int m_Clr2Opt = 0;
		CString m_szUser("");
		int m_Width = 0;
		int m_Height = 0;
		int m_clrOpt = 0;
		int m_clr = 0;

		if( m_nType == 1 )
		{
			// Reading..
			tmpStr = dStrAry.GetAt(2);
			m_matrixY = atoi(tmpStr);

			tmpStr = dStrAry.GetAt(3);
			m_matrixX = atoi(tmpStr);

			tmpStr = dStrAry.GetAt(4);
			m_Clr1Opt = atoi(tmpStr);

			tmpStr = dStrAry.GetAt(5);
			m_Clr2Opt = atoi(tmpStr);


			// Store..
			str.Format("%01d%02d%02d%01d%01d",m_nType,m_matrixY,m_matrixX,m_Clr1Opt,m_Clr2Opt);
		}
		else if(m_nType == 2)
		{
			// Reading..
			tmpStr = dStrAry.GetAt(2);
			m_matrixY = atoi(tmpStr);

			tmpStr = dStrAry.GetAt(3);
			m_matrixX = atoi(tmpStr);

			tmpStr = dStrAry.GetAt(4);
			m_Clr1Opt = atoi(tmpStr);

			tmpStr = dStrAry.GetAt(5);
			m_Clr2Opt = atoi(tmpStr);

			tmpStr = dStrAry.GetAt(6);
			m_szUser = tmpStr;

		
			// Store..
			CString strHex = Chess2AsciiHex(m_szUser,m_matrixX,m_matrixY);
			str.Format("%01d%02d%02d%01d%01d",m_nType,m_matrixY,m_matrixX,m_Clr1Opt,m_Clr2Opt);
			str += strHex;
		}
		else if(m_nType == 3)
		{
			// Reading..
			tmpStr = dStrAry.GetAt(2);
			m_matrixY = atoi(tmpStr);

			tmpStr = dStrAry.GetAt(3);
			m_matrixX = atoi(tmpStr);

			tmpStr = dStrAry.GetAt(4);
			m_Clr1Opt = atoi(tmpStr);

			tmpStr = dStrAry.GetAt(5);
			m_Clr2Opt = atoi(tmpStr);

			tmpStr = dStrAry.GetAt(6);
			m_Width = (int)String2Float(tmpStr, hResol);

			tmpStr = dStrAry.GetAt(7);
			m_Height = (int)String2Float(tmpStr, vResol);

			tmpStr = dStrAry.GetAt(8);
			m_clrOpt = strtoul(tmpStr, 0, 16);

			tmpStr = dStrAry.GetAt(9);
			m_clr = strtoul(tmpStr, 0, 16);		

		
			// Store..
			str.Format("%01d%02d%02d%1d%1d%04d%04d%01X%04X",
						m_nType,
						m_matrixY,	  m_matrixX,
						m_Clr1Opt,	  m_Clr2Opt,
  						m_Width,		  m_Height,
						m_clrOpt,		  m_clr );
		}

		strCode.Format("TD%03d",str.GetLength()+5);
		strCode += str;

		retStr = strCode;
	}
	////////////////////////////////////////////////////////////////////////// LC
	else if( tmpStr == "LC" )	// CDrawCircle
	{
		CString str("");

		tmpStr = dStrAry.GetAt(1);
		int m_centerY = (int)String2Float(tmpStr, vResol);

		tmpStr = dStrAry.GetAt(2);
		int m_centerX = (int)String2Float(tmpStr, hResol);

		int m_halfX = 0;
		tmpStr = dStrAry.GetAt(3);
		if( hResol <= vResol )
		{
			m_halfX = (int)String2Float(tmpStr, hResol);
		}
		else
		{
			m_halfX = (int)String2Float(tmpStr, vResol);
		}

		tmpStr = dStrAry.GetAt(5);
		int m_fillopt = atoi(tmpStr);

		str.Format("DC%03d%04d%04d%04dLC%03d%1d",17,m_centerY,m_centerX,m_halfX,6,m_fillopt);

		retStr = str;
	}
	////////////////////////////////////////////////////////////////////////// TC
	else if( tmpStr == "TC" )	// CDrawCross
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int x1 = (int)String2Float(tmpStr, hResol);

		tmpStr = dStrAry.GetAt(2);
		int y1 = (int)String2Float(tmpStr, vResol);

		tmpStr = dStrAry.GetAt(3);
		int x2 = (int)String2Float(tmpStr, hResol);

		tmpStr = dStrAry.GetAt(4);
		int y2 = (int)String2Float(tmpStr, vResol);

		// str.Format(_T("%04d%04d%04d%04d%1X%04X%04X%04X%04X%04X%04X%04X%02d"),
		// 			x1,y1,x2,y2,
		// 			m_BGClrOpt,m_clr,
		// 			m_Lineclr.red,m_Lineclr.green,m_Lineclr.blue,
		// 			m_LineclrAlt.red,m_LineclrAlt.green,m_LineclrAlt.blue,
		// 			m_LineTime);
		str.Format("%04d%04d%04d%04d%s%s%s%s%s%s%s%s%s",
					x1,y1,x2,y2,
					dStrAry.GetAt(5),dStrAry.GetAt(6),
					dStrAry.GetAt(7),dStrAry.GetAt(8),dStrAry.GetAt(9),
					dStrAry.GetAt(10),dStrAry.GetAt(11),dStrAry.GetAt(12),
					dStrAry.GetAt(13));
		tmpStr.Format("TC%03d%s", str.GetLength()+5, str);

		retStr = tmpStr;
	}
	////////////////////////////////////////////////////////////////////////// RH
	else if( tmpStr == "RH" )	// CDrawHRepeat
	{
#if 0
		CString str("");

		tmpStr = dStrAry.GetAt(1);

		int y1 = (int)String2Float(tmpStr, vResol);

		tmpStr = dStrAry.GetAt(2);
		int x1 = (int)String2Float(tmpStr, hResol);
		
		tmpStr = dStrAry.GetAt(3);
		int x2 = (int)String2Float(tmpStr, hResol);

		//str.Format(_T("RH%03d%04d%04d%04d%04X"),21,y1,x1,x2,repeat);
		str.Format("RH%03d%04d%04d%04d%s",21,y1,x1,x2,dStrAry.GetAt(4));

		retStr = str;
#else
//3D 패턴용 Repeat Command.
		CString str("");
		
		tmpStr = dStrAry.GetAt(1);
		int idx = atoi(tmpStr);
		
		tmpStr = dStrAry.GetAt(2);
		int y1 = (int)String2Float(tmpStr, vResol);
		
		tmpStr = dStrAry.GetAt(3);
		int x1 = (int)String2Float(tmpStr, hResol);
		
		tmpStr = dStrAry.GetAt(4);
		int x2 = (int)String2Float(tmpStr, hResol);
		
		//str.Format(_T("RH%03d%04d%04d%04d%04X"),21,y1,x1,x2,repeat);
		str.Format("%02d%04d%04d%04d%s%s%s%s%s",
			idx,
			y1,
			x1,
			x2,
			dStrAry.GetAt(5),	// 반복회수
			dStrAry.GetAt(6),	// 반복간격
			dStrAry.GetAt(7),	// Red Color
			dStrAry.GetAt(8),	// Green Color
			dStrAry.GetAt(9)	// Blue Color
			);
		tmpStr.Format("RH%03d%s", str.GetLength()+5, str);
		
		retStr = tmpStr;
#endif
	}
	////////////////////////////////////////////////////////////////////////// OL
	else if( tmpStr == "OL" )	// CDrawLine
	{
		CString str("");
		tmpStr = dStrAry.GetAt(2);
		int x1 = (int)String2Float(tmpStr, hResol);

		tmpStr = dStrAry.GetAt(3);
		int y1 = (int)String2Float(tmpStr, vResol);
		
		tmpStr = dStrAry.GetAt(4);
		int x2 = (int)String2Float(tmpStr, hResol);

		tmpStr = dStrAry.GetAt(5);
		int y2 = (int)String2Float(tmpStr, vResol);

		str.Format("OL%03d%04d%04d%04d%04d",21,x1,y1,x2,y2);

		retStr = str;
	}
	////////////////////////////////////////////////////////////////////////// LH
	else if( tmpStr == "LH" )	// CDrawHLine
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int y1 = (int)String2Float(tmpStr, vResol);

		tmpStr = dStrAry.GetAt(2);
		int x1 = (int)String2Float(tmpStr, hResol);
		
		tmpStr = dStrAry.GetAt(3);
		int x2 = (int)String2Float(tmpStr, hResol);

		str.Format("LH%03d%04d%04d%04d",17,y1,x1,x2);

		retStr = str;
	}
	////////////////////////////////////////////////////////////////////////// LV
	else if( tmpStr == "LV" )	// CDrawVLine
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int y1 = (int)String2Float(tmpStr, vResol);

		tmpStr = dStrAry.GetAt(2);
		int x1 = (int)String2Float(tmpStr, hResol);
		
		tmpStr = dStrAry.GetAt(3);
		int y2 = (int)String2Float(tmpStr, vResol);

		tmpStr = dStrAry.GetAt(4);
		int m_FillType = atoi(tmpStr);

		str.Format("LV%03d%04d%04d%04d%1d",18,y1,x1,y2,m_FillType);

		retStr = str;
	}
	////////////////////////////////////////////////////////////////////////// LW
	else if( tmpStr == "LW" )	// CDrawWLine
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int Xs = (int)String2Float(tmpStr, hResol);

		tmpStr = dStrAry.GetAt(2);
		int Xe = (int)String2Float(tmpStr, hResol);
		
		str.Format("LW%03d%04d%04d",13,Xs,Xe);

		retStr = str;
	}
	////////////////////////////////////////////////////////////////////////// LT
	else if( tmpStr == "LT" )	// CDrawTLine
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int y1 = (int)String2Float(tmpStr, vResol);
		if(y1 >= vResol)
			y1 = vResol-1;

		tmpStr = dStrAry.GetAt(2);
		int x1 = (int)String2Float(tmpStr, hResol);
		if(x1 >= hResol)
			x1 = hResol-1;
		
		tmpStr = dStrAry.GetAt(3);
		int y2 = (int)String2Float(tmpStr, vResol);
		if(y2 >= vResol)
			y2 = vResol-1;

		tmpStr = dStrAry.GetAt(4);
		int x2 = (int)String2Float(tmpStr, hResol);
		if(x2 >= hResol)
			x2 = hResol-1;

		tmpStr = dStrAry.GetAt(5);
		int m_FillType = atoi(tmpStr);

		str.Format("LT%03d%04d%04d%04d%04d%1d",22,y1,x1,y2,x2,m_FillType);

		retStr = str;
	}
	////////////////////////////////////////////////////////////////////////// LP
	else if( tmpStr == "LP" )	// CDrawPolyGon
	{
		CString str("");
		CString strMsg("");
		tmpStr = dStrAry.GetAt(1);
		int m_count = atoi(tmpStr);

		int max = m_count * 2 + 3;

		int ti = 2;

		int minx = 0;
		int maxx = 0;

		for(int i=0; i<m_count; i++)
		{
			tmpStr = dStrAry.GetAt(ti++);
			int m_szVY = (int)String2Float(tmpStr, vResol);
			tmpStr = dStrAry.GetAt(ti++);
			int m_szVX = (int)String2Float(tmpStr, hResol);

			if( i == 0 )
			{
				minx = m_szVX;
				maxx = m_szVX;
			}

			if(minx > m_szVX) minx = m_szVX;
			if(maxx < m_szVX) maxx = m_szVX;

			CString strVectex;
			strVectex.Format("%04d%04d", m_szVY, m_szVX);
			strMsg += strVectex;
		}

		tmpStr = dStrAry.GetAt(ti++);
		int m_FillType = atoi(tmpStr);

		str.Format("LP%03d%04d%s%1d",strMsg.GetLength()+10,(maxx-minx)/2,strMsg,m_FillType);

		retStr = str;
	}
	////////////////////////////////////////////////////////////////////////// LR
	else if( tmpStr == "LR" )	// CDrawRect
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int y1 = (int)String2Float(tmpStr, vResol);
		if(y1 >= vResol)
			y1 = vResol-1;

		tmpStr = dStrAry.GetAt(2);
		int x1 = (int)String2Float(tmpStr, hResol);
		if(x1 >= hResol)
			x1 = hResol-1;
		
		tmpStr = dStrAry.GetAt(3);
		int y2 = (int)String2Float(tmpStr, vResol);
		if(y2 >= vResol)
			y2 = vResol-1;

		tmpStr = dStrAry.GetAt(4);
		int x2 = (int)String2Float(tmpStr, hResol);
		if(x2 >= hResol)
			x2 = hResol-1;

		tmpStr = dStrAry.GetAt(5);
		int m_fillopt = atoi(tmpStr);

		str.Format("LR%03d%04d%04d%04d%04d%01d",22,y1,x1,y2,x2,m_fillopt);

		retStr = str;
	}

	////////////////////////////////////////////////////////////////////////// BS
	else if( tmpStr == "BS" )	// CDrawMyString
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int y1 = (int)String2Float(tmpStr, vResol);

		tmpStr = dStrAry.GetAt(2);
		int x1 = (int)String2Float(tmpStr, hResol);
		
		tmpStr = dStrAry.GetAt(3);
		int y2 = (int)String2Float(tmpStr, vResol);

		tmpStr = dStrAry.GetAt(4);
		int x2 = (int)String2Float(tmpStr, hResol);

		tmpStr = dStrAry.GetAt(6);

		str.Format("%04d%04d%04d%04d%s",y1,x1,y2,x2,tmpStr);
		tmpStr.Format("BS%03d%s",str.GetLength()+5,str);

		retStr = tmpStr;
	}
	////////////////////////////////////////////////////////////////////////// RV
	else if( tmpStr == "RV" )	// CDrawVRepeat
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int y1 = (int)String2Float(tmpStr, vResol);

		tmpStr = dStrAry.GetAt(2);
		int x1 = (int)String2Float(tmpStr, hResol);
		
		tmpStr = dStrAry.GetAt(3);
		int y2 = (int)String2Float(tmpStr, vResol);

		//str.Format(_T("RV%03d%04d%04d%04d%04X"),21,y1,x1,y2,repeat);
		str.Format("RV%03d%04d%04d%04d%s",21,y1,x1,y2,dStrAry.GetAt(4));

		retStr = str;
	}
	////////////////////////////////////////////////////////////////////////// BM
	else if( tmpStr == "BM" )	// CDrawXFile
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int x1 = (int)String2Float(tmpStr, hResol);

		tmpStr = dStrAry.GetAt(2);
		int y1 = (int)String2Float(tmpStr, vResol);
		
		tmpStr = dStrAry.GetAt(3);
		int x2 = (int)String2Float(tmpStr, hResol);

		tmpStr = dStrAry.GetAt(4);
		int y2 = (int)String2Float(tmpStr, vResol);

		str.Format("%04d%04d%04d%04d",x1,y1,x2,y2);
		tmpStr.Format("BM%03d%s", str.GetLength()+5, str);

		retStr = tmpStr;
	}
	////////////////////////////////////////////////////////////////////////// EV (Expand VLine)
	else if( tmpStr == "EV" )	// CDrawVLine
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int y1 = (int)String2Float(tmpStr, vResol);
		if(y1 >= vResol)
			y1 = vResol-1;
		else if(y1 < 0)
			y1 = 0;
		
		tmpStr = dStrAry.GetAt(2);
		int x1 = (int)String2Float(tmpStr, hResol);
		if(x1 >= hResol)
			x1 = hResol-1;
		else if(x1 < 0)
			x1 = 0;
		
		tmpStr = dStrAry.GetAt(3);
		int y2 = (int)String2Float(tmpStr, vResol);
		if(y2 >= vResol)
			y2 = vResol-1;
		else if(y2 < 0)
			y2 = 0;
		
		tmpStr = dStrAry.GetAt(4);
		int m_FillType = atoi(tmpStr);
		
		str.Format("%04d%04d%04d%1d%s%s%s",y1,x1,y2,m_FillType, dStrAry.GetAt(5), dStrAry.GetAt(6), dStrAry.GetAt(7));
		tmpStr.Format("EV%03d%s", str.GetLength()+5, str);
		
		retStr = tmpStr;
	}
	
	////////////////////////////////////////////////////////////////////////// EH (Expand HLine)
	else if( tmpStr == "EH" )	// CDrawExpandHLine
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int y1 = (int)String2Float(tmpStr, vResol);
		if(y1 >= vResol)
			y1 = vResol-1;
		else if(y1 < 0)
			y1 = 0;
		
		tmpStr = dStrAry.GetAt(2);
		int x1 = (int)String2Float(tmpStr, hResol);
		if(x1 >= hResol)
			x1 = hResol-1;
		else if(x1 < 0)
			x1 = 0;
		
		tmpStr = dStrAry.GetAt(3);
		int x2 = (int)String2Float(tmpStr, hResol);
		if(x2 >= hResol)
			x2 = hResol-1;
		else if(x2 < 0)
			x2 = 0;
		
		str.Format("%04d%04d%04d%s%s%s",y1,x1,x2,dStrAry.GetAt(4),dStrAry.GetAt(5),dStrAry.GetAt(6));
		tmpStr.Format("EH%03d%s", str.GetLength()+5, str);
		
		retStr = tmpStr;
	}
	////////////////////////////////////////////////////////////////////////// ER (Expand Rect)
	else if( tmpStr == "ER" )	// CDrawExpandRect
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int y1 = (int)String2Float(tmpStr, vResol);
		if(y1 >= vResol)
			y1 = vResol-1;
		
		tmpStr = dStrAry.GetAt(2);
		int x1 = (int)String2Float(tmpStr, hResol);
		if(x1 >= hResol)
			x1 = hResol-1;
		
		tmpStr = dStrAry.GetAt(3);
		int y2 = (int)String2Float(tmpStr, vResol);
		if(y2 >= vResol)
			y2 = vResol-1;
		
		tmpStr = dStrAry.GetAt(4);
		int x2 = (int)String2Float(tmpStr, hResol);
		if(x2 >= hResol)
			x2 = hResol-1;
		
		tmpStr = dStrAry.GetAt(5);
		int m_fillopt = atoi(tmpStr);
		
		str.Format("%04d%04d%04d%04d%01d%s%s%s",y1,x1,y2,x2,m_fillopt,dStrAry.GetAt(6),dStrAry.GetAt(7),dStrAry.GetAt(8));
		tmpStr.Format("ER%03d%s", str.GetLength()+5, str);
		
		retStr = tmpStr;
	}
	else if( tmpStr == "CD" )	// Color Description
	{
		CString str("");
		str.Format("CD%s%s%s%s%s%s%s%s%s%s%s%s", dStrAry.GetAt(1), dStrAry.GetAt(2), dStrAry.GetAt(3),
													dStrAry.GetAt(4), dStrAry.GetAt(5), dStrAry.GetAt(6),
													dStrAry.GetAt(7), dStrAry.GetAt(8), dStrAry.GetAt(9),
													dStrAry.GetAt(10), dStrAry.GetAt(11), dStrAry.GetAt(12));
		retStr = str;
	}
	else if( tmpStr == "CLN" )	// Line Color
	{
		CString str("");
		str.Format("CLN%s%s%s", dStrAry.GetAt(1), dStrAry.GetAt(2), dStrAry.GetAt(3));
		retStr = str;
	}
	else if( tmpStr == "CBT" )	// Bitmap Color
	{
		CString str("");
		str.Format("CBT%s%s%s", dStrAry.GetAt(1), dStrAry.GetAt(2), dStrAry.GetAt(3));
		retStr = str;
	}
	else if( tmpStr == "CFG" )	// FG Color
	{
		CString str("");
		str.Format("CFG%s%s%s", dStrAry.GetAt(1), dStrAry.GetAt(2), dStrAry.GetAt(3));
		retStr = str;
	}
	else if( tmpStr == "CBG" )	// BG Color
	{
		CString str("");
		str.Format("CBG%s%s%s", dStrAry.GetAt(1), dStrAry.GetAt(2), dStrAry.GetAt(3));
		retStr = str;
	}
	////////////////////////////////////////////////////////////////////////// EH (Expand HLine)
	else if( tmpStr == "EH" )	// CDrawExpandHLine
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int y1 = (int)String2Float(tmpStr, vResol);
		if(y1 >= vResol)
			y1 = vResol-1;
		else if(y1 < 0)
			y1 = 0;
		
		tmpStr = dStrAry.GetAt(2);
		int x1 = (int)String2Float(tmpStr, hResol);
		if(x1 >= hResol)
			x1 = hResol-1;
		else if(x1 < 0)
			x1 = 0;
		
		tmpStr = dStrAry.GetAt(3);
		int x2 = (int)String2Float(tmpStr, hResol);
		if(x2 >= hResol)
			x2 = hResol-1;
		else if(x2 < 0)
			x2 = 0;
		
		str.Format("%04d%04d%04d%s%s%s",y1,x1,x2,dStrAry.GetAt(4),dStrAry.GetAt(5),dStrAry.GetAt(6));
		tmpStr.Format("EH%03d%s", str.GetLength()+5, str);
		
		retStr = tmpStr;
	}
	////////////////////////////////////////////////////////////////////////// ER (Expand Rect)
	else if( tmpStr == "ER" )	// CDrawExpandRect
	{
		CString str("");
		tmpStr = dStrAry.GetAt(1);
		int y1 = (int)String2Float(tmpStr, vResol);
		if(y1 >= vResol)
			y1 = vResol-1;
		
		tmpStr = dStrAry.GetAt(2);
		int x1 = (int)String2Float(tmpStr, hResol);
		if(x1 >= hResol)
			x1 = hResol-1;
		
		tmpStr = dStrAry.GetAt(3);
		int y2 = (int)String2Float(tmpStr, vResol);
		if(y2 >= vResol)
			y2 = vResol-1;
		
		tmpStr = dStrAry.GetAt(4);
		int x2 = (int)String2Float(tmpStr, hResol);
		if(x2 >= hResol)
			x2 = hResol-1;
		
		tmpStr = dStrAry.GetAt(5);
		int m_fillopt = atoi(tmpStr);
		
		str.Format("%04d%04d%04d%04d%01d%s%s%s",y1,x1,y2,x2,m_fillopt,dStrAry.GetAt(6),dStrAry.GetAt(7),dStrAry.GetAt(8));
		tmpStr.Format("ER%03d%s", str.GetLength()+5, str);
		
		retStr = tmpStr;
	}

	return retStr;
}

int T2CmdGen::makeStringArray(CString dataStr)
{
	CString tmpStr("");
	int i=0;
	while(1)
	{
		int oldI = i;
		i = dataStr.Find("\n", i) + 1;
		if( i == 0 )
		{
			if( dataStr.GetLength() > oldI )
			{
				tmpStr = dataStr.Mid(oldI, dataStr.GetLength()-oldI-1);
				pbdData.Add(tmpStr);
			}
			break;
		}
		tmpStr = dataStr.Mid(oldI, i-oldI-1);
		pbdData.Add(tmpStr);
	}
	return pbdData.GetSize();
}

double T2CmdGen::String2Float(LPCTSTR pStrNum,int base)
{
//	CMLT2App* m_pApp = (CMLT2App*) AfxGetApp();
//	LPFUSINGINFO lpFusingInfo = m_pApp->GetFusingInfo();
	
	CString strNum(pStrNum);
	int nNumber = 0;

	strNum.TrimLeft();
	strNum.TrimRight();

	CString strReturn("");
	CString strValue("");

	BOOL bfraction = FALSE;
	BOOL bPoint = FALSE;
	double eReturn = 0.0;

	for(int i=0; i<strNum.GetLength(); i++)
	{
		char ch = strNum[i];

		if( isdigit(ch) )
		{
			strValue += ch;	
		}
		else if( ch == '%' )
		{
			CString pText = strValue;
			double value = 0.0;
			if(bPoint)
			{
				value = atof(pText);
			}
			else
			{
				value = atoi(pText);
			}

			eReturn += (base * value * 0.01);
			bPoint = FALSE;
			strValue = "";
		}
		else if( ch == '/' )
		{
			bfraction = TRUE;
			strValue += ch;
		}
		else if( ch == '.' )
		{
			bPoint = TRUE;
			strValue += ch;
		}
		else if( ch == '+' )
		{
			if( strValue.IsEmpty() )
			{
				strValue = '+';
				continue;
			}

			CString pText = strValue;
			double value = 0.0;

			if( bfraction )
			{
				double numerator = 0.0;
				double denominator = 0.0;

				int nIdx = strValue.Find('/');
				CString strNumerator	= strValue.Left(nIdx);
				CString strDenominator	= strValue.Right(strValue.GetLength() - (nIdx+1));

				numerator	= atof(strNumerator);
				denominator = atof(strDenominator);	
				denominator = (denominator == 0.0) ? 1.0 : denominator;	// 0.0인경우.

				value = ( base * 1.0 / denominator * numerator);
			}
			else if(bPoint)
			{
				value = atof(pText);
			}
			else
			{
				value = atoi(pText);
			}

			eReturn += value;
			bPoint = FALSE;
			bfraction = FALSE;
			strValue = "";
			strValue = '+';
		}
		else if(ch == '-')
		{	
			if(strValue.IsEmpty())
			{
				strValue = '-';
				continue;
			}
			
			CString pText = strValue;
			double value = 0.0;

			if(bfraction)
			{
				double numerator	= 0.0;
				double denominator	= 0.0;

				int nIdx = strValue.Find('/');
				CString strNumerator	= strValue.Left(nIdx);
				CString strDenominator	= strValue.Right(strValue.GetLength() - (nIdx+1));

				numerator	= atof(strNumerator);
				denominator = atof(strDenominator);	
				denominator = (denominator == 0.0) ? 1.0 : denominator;	// 0.0인경우.

				value = ( base * 1.0 / denominator * numerator);
			}
			else if(bPoint)  value = atof(pText);
			else			 value = atoi(pText);

			eReturn += value;
			bPoint		= FALSE;
			bfraction	= FALSE;
			strValue = "";
			strValue = '-';
		}
	}	

	if(!strValue.IsEmpty())
	{

		CString pText = strValue;
		double   value = 0.0;

		if(bfraction)
		{
			double numerator	= 0.0;
			double denominator	= 0.0;

			int nIdx = strValue.Find('/');
			CString strNumerator	= strValue.Left(nIdx);
			CString strDenominator	= strValue.Right(strValue.GetLength() - (nIdx+1));

			numerator	= atof(strNumerator);
			denominator = atof(strDenominator);	
			denominator = (denominator == 0.0) ? 1.0 : denominator;	// 0.0인경우.

			value = ( base * 1.0 / denominator * numerator);
		}
		else if(bPoint)  value = atof(pText);
		else			 value = atoi(pText);

		eReturn += value;
		bPoint		= FALSE;
		bfraction	= FALSE;
		strValue = "";
	}

//	if(lpFusingInfo->iSignalType == 2 || lpFusingInfo->iSignalType == 5)
//	{ 
//		if((int)eReturn % 2)
//		{
//			eReturn += 1;
//		}
//	}
	return eReturn;
}
	
CString T2CmdGen::Chess2AsciiHex(CString& szBits,int x, int y)
{
	CString strChess("");
	
	if(x == 16)
	{
		strChess  = szBits;
	}
	else
	{
		CString strArray[16];
		
		for(int yi = 0  ;  yi < y ; yi++)
		{
			//잘라내기.
			strArray[yi] = szBits.Mid(yi*x,x);
			
			unsigned short uHex = 0;
			for(int xi = 0 ; xi < strArray[yi].GetLength() ; xi++)
			{
				if(strArray[yi].GetAt(xi) == '1')
					uHex |= (0x1 << (15-xi));
			}

			strArray[yi].Format("%04X",uHex);
		}

		for(int yi = 0 ; yi < y ; yi++)
			strChess += strArray[yi];

	}

	return strChess;
}

/////////////////////////////////////////////////////////////////////////////

// 2009-03-13 PDH. T2 File Parsing후 Fusing하기 위한 Function 추가.
CString T2CmdGen::makeT2FileStr(CString dataStr)
{
	T2CmdGen* pObj = NULL;
	pObj = new T2CmdGen;
	
	CString retStr("");
	int cnt = pObj->makeStringArray(dataStr);
	if( cnt > 0 )
	{
		retStr = pObj->makeFieldStr(dataStr);
	}
	
	delete pObj;
	pObj = NULL;
	return retStr;
}


// 	int nIndex = 0;
// 	int i;
// 	int nLength;
// 	nLength = retStr.GetLength();

// 	for(i=0; i<nLength; i++)
// 	{
// 		nIndex = retStr.Find(0x0D);
// 		if(nIndex!=-1)
// 		{
// 			retStr.Delete(nIndex, 1);
// 		}
// 	}




CString T2CmdGen::makeFieldStr(CString dataStr)
{
	CString retStr("");
	CString tmpStr("");
	CString parStr("");
	
	for(int nline=0; nline<pbdData.GetSize(); nline++)
	{
		tmpStr = pbdData.GetAt(nline);
		
		int oldI=0, i=0;
		i = tmpStr.Find(",", i) + 1;

		if( i == 0 )
		{
			if( tmpStr.GetLength() > oldI )
			{
				parStr = tmpStr.Mid(oldI, tmpStr.GetLength()-oldI);
			}
//			break;
		}
		else
		{
			parStr = dataStr.Mid(oldI, i-oldI-1);
			
			if( parStr != "NAME" )
			{
				retStr += tmpStr.Left(tmpStr.GetLength()-1);
			}
		}
	}
	
	return retStr;

}

