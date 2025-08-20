#pragma once
#include <afxstr.h>

typedef struct _ST_INSPWORKINFO_
{
    int     m_AgnInStartLayer;
    int     m_AgnInStartChannel;
    int     m_AgingErrorRack;
    CString m_nSerialID;
} INSPWORKINFO, * LPINSPWORKINFO;