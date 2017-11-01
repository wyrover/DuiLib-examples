#include "stdafx.h"
#include "TopbarWnd.h"
#include "Shortcut.h"
#include <stdio.h>


CTopBarWnd::CTopBarWnd()
{
    m_pclDetailBtn = NULL;
    m_pclShareBtn = NULL;
    m_pclShotcutBtn = NULL;
    m_pclFavoriteBtn = NULL;
    m_pclUnFavoriteBtn = NULL;
    m_pclSetTopBtn = NULL;
    m_pclCancelTopBtn = NULL;
    m_hParentWnd = NULL;
    memset(m_szWParam, 0, sizeof(m_szWParam));
    memset(m_szLParam, 0, sizeof(m_szLParam));
}


CTopBarWnd::~CTopBarWnd()
{
    m_pclDetailBtn = NULL;
    m_pclShareBtn = NULL;
    m_pclShotcutBtn = NULL;
    m_pclFavoriteBtn = NULL;
    m_pclUnFavoriteBtn = NULL;
    m_pclSetTopBtn = NULL;
    m_pclCancelTopBtn = NULL;
    m_hParentWnd = NULL;
    memset(m_szWParam, 0, sizeof(m_szWParam));
    memset(m_szLParam, 0, sizeof(m_szLParam));
}

LPCTSTR CTopBarWnd::GetWindowClassName() const
{
    return _T("TopBarWnd");
}

UINT CTopBarWnd::GetClassStyle() const
{
    return (UI_CLASSSTYLE_FRAME | CS_DBLCLKS);
}

HWND CTopBarWnd::Create(HWND hWndParent, LPCTSTR pcszName, DWORD dwStyle, DWORD dwExStyle, int x, int y, int cx, int cy, HMENU hMenu)
{
    m_hParentWnd = hWndParent;
    return CWindowWnd::Create(hWndParent, pcszName, dwStyle, dwExStyle, x, y, cx, cy, hMenu);
}

void CTopBarWnd::Init()
{
    m_pclDetailBtn = static_cast<CButtonUI *>(m_clPaintManager.FindControl(_T("detail")));
    m_pclShareBtn = static_cast<CButtonUI *>(m_clPaintManager.FindControl(_T("share")));
    m_pclShotcutBtn = static_cast<CButtonUI *>(m_clPaintManager.FindControl(_T("pt_shutcut")));
    m_pclFavoriteBtn = static_cast<CButtonUI *>(m_clPaintManager.FindControl(_T("pt_favorites")));
    m_pclUnFavoriteBtn = static_cast<CButtonUI *>(m_clPaintManager.FindControl(_T("pt_unfavorites")));
    m_pclSetTopBtn = static_cast<CButtonUI *>(m_clPaintManager.FindControl(_T("pt_settop")));
    m_pclCancelTopBtn = static_cast<CButtonUI *>(m_clPaintManager.FindControl(_T("pt_canceltop")));
    m_pclDetailBtn->SetVisible(false);
    m_pclShareBtn->SetVisible(false);
    m_pclShotcutBtn->SetEnabled();
    m_pclFavoriteBtn->SetEnabled();
    m_pclSetTopBtn->SetEnabled();
}

LRESULT CTopBarWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    LONG iStyle = ::GetWindowLong(*this, GWL_STYLE);
    iStyle &= ~WS_CAPTION;
    ::SetWindowLong(*this, GWL_STYLE, iStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    m_clPaintManager.Init(m_hWnd);
    CDialogBuilder clBuilder;
    CControlUI* pRoot = clBuilder.Create(_T("topbar.xml"), (UINT)0, NULL, &m_clPaintManager);
    ASSERT(pRoot && "Failed to parse XML");
    m_clPaintManager.AttachDialog(pRoot);
    m_clPaintManager.AddNotifier(this);
    Init();
    return 0;
}

LRESULT CTopBarWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = FALSE;
    return 0;
}

LRESULT CTopBarWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = FALSE;
    return 0;
}

void CTopBarWnd::OnFinalMessage(HWND hWnd)
{
    delete this;
}

void CTopBarWnd::OnPrepare()
{
}

void CTopBarWnd::Notify(TNotifyUI& msg)
{
    if (msg.sType == _T("windowinit")) {
        OnPrepare();
    } else if (msg.sType == _T("click")) {
        if (msg.pSender == m_pclShotcutBtn) {
            WCHAR szPath[MAX_PATH] = { 0 };
            CShortcut::GetLinkPath(szPath, sizeof(szPath));
            CShortcut::CreateLink(szPath, L"CBox央视影音");
        } else if (msg.pSender == m_pclFavoriteBtn) {
            m_pclFavoriteBtn->SetVisible(false);
            m_pclUnFavoriteBtn->SetVisible(true);
            _snprintf_s(m_szWParam, sizeof(m_szWParam), "%s", m_pclFavoriteBtn->GetToolTip().GetData());
            _snprintf_s(m_szLParam, sizeof(m_szLParam), "%s", _T("添加收藏成功"));
            ::PostMessage(m_hParentWnd, WM_TOPMOST, 0, 0);
            ::PostMessage(m_hParentWnd, WM_FAVOURITE, (WPARAM)m_szWParam, (LPARAM)m_szLParam);
        } else if (msg.pSender == m_pclUnFavoriteBtn) {
            m_pclFavoriteBtn->SetVisible(true);
            m_pclUnFavoriteBtn->SetVisible(false);
            _snprintf_s(m_szWParam, sizeof(m_szWParam), "%s", m_pclFavoriteBtn->GetToolTip().GetData());
            _snprintf_s(m_szLParam, sizeof(m_szLParam), "%s", _T("取消收藏成功"));
            ::PostMessage(m_hParentWnd, WM_TOPMOST, 0, 0);
            ::PostMessage(m_hParentWnd, WM_FAVOURITE, (WPARAM)m_szWParam, (LPARAM)m_szLParam);
        } else if (msg.pSender == m_pclSetTopBtn) {
            m_pclSetTopBtn->SetVisible(false);
            m_pclCancelTopBtn->SetVisible(true);
            ::SendMessage(m_hParentWnd, WM_TOPMOST, 1, 0);
        } else if (msg.pSender == m_pclCancelTopBtn) {
            m_pclSetTopBtn->SetVisible(true);
            m_pclCancelTopBtn->SetVisible(false);
            ::SendMessage(m_hParentWnd, WM_TOPMOST, 0, 0);
        }
    }
}

LRESULT CTopBarWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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