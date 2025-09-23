#include "afxdialogex.h"
#include "resource.h"
#include "afxwin.h"
#include "afxcmn.h"

class CMyPictureCtrl : public CStatic
{
    DECLARE_DYNAMIC(CMyPictureCtrl)

public:
    CMyPictureCtrl();
    virtual ~CMyPictureCtrl();

protected:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

private:
    HBITMAP m_hBmpNormal;
    HBITMAP m_hBmpPressed;
};