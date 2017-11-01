#include "stdafx.h"
#include "ScreenRatioWnd.h"


CScreenRatioWnd::CScreenRatioWnd()
{
}


CScreenRatioWnd::~CScreenRatioWnd()
{
}

LPCTSTR CScreenRatioWnd::GetWindowClassName() const
{
    return _T("ScreenRatioWnd");
}

UINT CScreenRatioWnd::GetClassStyle() const
{
    return (UI_CLASSSTYLE_FRAME | CS_DBLCLKS);
}

void CScreenRatioWnd::Init()
{
}

LRESULT CScreenRatioWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    LONG iStyle = ::GetWindowLong(*this, GWL_STYLE);
    iStyle &= ~WS_CAPTION;
    ::SetWindowLong(*this, GWL_STYLE, iStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    m_clPaintManager.Init(m_hWnd);
    CDialogBuilder clBuilder;
    CControlUI* pRoot = clBuilder.Create(_T("screenratio.xml"), (UINT)0, NULL, &m_clPaintManager);
    ASSERT(pRoot && "Failed to parse XML");
    m_clPaintManager.AttachDialog(pRoot);
    m_clPaintManager.AddNotifier(this);
    Init();
    return 0;
}

LRESULT CScreenRatioWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = FALSE;
    return 0;
}

LRESULT CScreenRatioWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = FALSE;
    return 0;
}

void CScreenRatioWnd::OnFinalMessage(HWND hWnd)
{
    delete this;
}

void CScreenRatioWnd::OnPrepare()
{
}

void CScreenRatioWnd::Notify(TNotifyUI& msg)
{
    if (msg.sType == _T("windowinit")) {
        OnPrepare();
    } else if (msg.sType == _T("click")) {
    }
}

LRESULT CScreenRatioWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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