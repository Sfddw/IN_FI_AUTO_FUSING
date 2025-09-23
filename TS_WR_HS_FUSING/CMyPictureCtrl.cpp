#include "stdafx.h"
#include "CMyPictureCtrl.h"
#include "CSetSystemDlg.h"

IMPLEMENT_DYNAMIC(CMyPictureCtrl, CStatic)

BEGIN_MESSAGE_MAP(CMyPictureCtrl, CStatic)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

CMyPictureCtrl::CMyPictureCtrl()
{
    m_hBmpNormal = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_COG_O));
    m_hBmpPressed = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_COG_T));
}

CMyPictureCtrl::~CMyPictureCtrl()
{
    if (m_hBmpNormal)  DeleteObject(m_hBmpNormal);
    if (m_hBmpPressed) DeleteObject(m_hBmpPressed);
}

void CMyPictureCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
    SetBitmap(m_hBmpPressed); // ¥≠∑∂¿ª ∂ß
    //CStatic::OnLButtonDown(nFlags, point);
    CSetSystemDlg dlg;
    if (dlg.DoModal() == IDOK)
    {

    }
    SetBitmap(m_hBmpNormal); // ∂√¿ª ∂ß
}

void CMyPictureCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
    
    //CStatic::OnLButtonUp(nFlags, point);
}