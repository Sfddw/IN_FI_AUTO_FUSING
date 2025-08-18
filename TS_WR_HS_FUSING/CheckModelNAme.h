#pragma once


// CCheckModelNAme 대화 상자입니다.

class CCheckModelNAme : public CDialog
{
	DECLARE_DYNAMIC(CCheckModelNAme)

public:
	CCheckModelNAme(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCheckModelNAme();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CHECK_MODELNAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

	LPMODELINFO		lpModelInfo;

public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();

	void Lf_InitFont();
	BOOL Lf_cmpModelName(void);
	void Lf_setFusingData();
	void Lf_getLoadVariFromModelFile(char *pModelName);

protected:
	LPSYSTEMINFO	lpSystemInfo;
	int				m_nSendFlag;
	int				m_nHostFindFlag;
	int				m_nLocalFindFlag;
	
	int Lf_getSignalType(char cmbSignalType);
	int Lf_makeSystemFusingPacket(char *pModelName, char *pszRtnPack);
	int Lf_setSystemFusing(char *pModName);
	int Lf_makePatternFusingPacket(char *pszRtnPack);
	int Lf_setPatternFusing(void);
	int Lf_makeCtrlIOFusingPacket(char *pszRtnPacket);
	int Lf_setControlIOFusing(void);
	int Lf_makeModelVoltCurrentPacket(char *pszRtnPacket);
	int Lf_setModelVoltCurrentFusing(void);
	int Lf_setProcOpBoxFusing(void);

private:
	CFont m_FontH1[5];
	CBrush m_Brush[5];
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
