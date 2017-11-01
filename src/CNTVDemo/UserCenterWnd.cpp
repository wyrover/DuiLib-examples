#include "stdafx.h"
#include "UserCenterWnd.h"


CUserCenterWnd::CUserCenterWnd()
{
    m_pclCloseBtn = NULL;
}


CUserCenterWnd::~CUserCenterWnd()
{
    m_pclCloseBtn = NULL;
}

LPCTSTR CUserCenterWnd::GetWindowClassName() const
{
    return _T("UserCenterWnd");
}

UINT CUserCenterWnd::GetClassStyle() const
{
    return (UI_CLASSSTYLE_FRAME | CS_DBLCLKS);
}

void CUserCenterWnd::Init()
{
    m_pclCloseBtn = static_cast<CButtonUI*>(m_clPaintManager.FindControl(_T("close")));
}

LRESULT CUserCenterWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    LONG iStyle = ::GetWindowLong(*this, GWL_STYLE);
    iStyle &= ~WS_CAPTION;
    ::SetWindowLong(*this, GWL_STYLE, iStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    m_clPaintManager.Init(m_hWnd);
    CDialogBuilder clBuilder;
    CControlUI* pRoot = clBuilder.Create(_T("personalcenter.xml"), (UINT)0, NULL, &m_clPaintManager);
    ASSERT(pRoot && "Failed to parse XML");
    m_clPaintManager.AttachDialog(pRoot);
    m_clPaintManager.AddNotifier(this);
    Init();
    return 0;
}

LRESULT CUserCenterWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = FALSE;
    return 0;
}

LRESULT CUserCenterWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = FALSE;
    return 0;
}

void CUserCenterWnd::OnFinalMessage(HWND hWnd)
{
    delete this;
}

void CUserCenterWnd::OnPrepare()
{
}

void CUserCenterWnd::Notify(TNotifyUI& msg)
{
    if (msg.sType == _T("windowinit")) {
        OnPrepare();
    } else if (msg.sType == _T("click")) {
        if (msg.pSender == m_pclCloseBtn) {
            Close();
        }
    }
}

LRESULT CUserCenterWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT lResult = 0;
    BOOL bHandled = TRUE;

    switch (uMsg) {
    case WM_CREATE:
        lResult = OnCreate(uMsg, wParam, lParam, bHandled);
        break;

    case WM_CLOSE:
        lResult = OnClose(uMsg, wParam, lParam, bHandled);
        break;

    case WM_DESTROY:
        lResult = OnDestroy(uMsg, wParam, lParam, bHandled);
        break;

    default:
        bHandled = FALSE;
        break;
    }

    if (bHandled) {
        return lResult;
    }

    if (m_clPaintManager.MessageHandler(uMsg, wParam, lParam, lResult)) {
        return lResult;
    }

    return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}