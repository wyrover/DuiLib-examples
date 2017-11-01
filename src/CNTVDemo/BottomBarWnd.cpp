#include "stdafx.h"
#include "BottomBarWnd.h"
#include "Shortcut.h"
#include <stdio.h>


CBottomBarWnd::CBottomBarWnd()
{
    m_pclResolutionBtn = NULL;
    m_pclLiteWndBtn = NULL;
    m_pclEpisodeBtn = NULL;
    m_pclHSoundBtn = NULL;
    m_pclLSoundBtn = NULL;
    m_pclMuteBtn = NULL;
    m_pclFullScreenBtn = NULL;
    m_pclNormalScreenBtn = NULL;
    m_pclVolumeWnd = NULL;
    m_pclVolumeTipWnd = NULL;
    m_pclVolumeBackgroundWnd = NULL;
    m_pclScreenRatioWnd = NULL;
    memset(m_szWParam, 0, sizeof(m_szWParam));
    memset(m_szLParam, 0, sizeof(m_szLParam));
}


CBottomBarWnd::~CBottomBarWnd()
{
    m_pclResolutionBtn = NULL;
    m_pclLiteWndBtn = NULL;
    m_pclEpisodeBtn = NULL;
    m_pclHSoundBtn = NULL;
    m_pclLSoundBtn = NULL;
    m_pclMuteBtn = NULL;
    m_pclFullScreenBtn = NULL;
    m_pclNormalScreenBtn = NULL;
    m_pclVolumeWnd = NULL;
    m_pclVolumeTipWnd = NULL;
    m_pclVolumeBackgroundWnd = NULL;
    m_pclScreenRatioWnd = NULL;
    memset(m_szWParam, 0, sizeof(m_szWParam));
    memset(m_szLParam, 0, sizeof(m_szLParam));
}

LPCTSTR CBottomBarWnd::GetWindowClassName() const
{
    return _T("BottomBarWnd");
}

UINT CBottomBarWnd::GetClassStyle() const
{
    return (UI_CLASSSTYLE_FRAME | CS_DBLCLKS);
}

HWND CBottomBarWnd::Create(HWND hWndParent, LPCTSTR pcszName, DWORD dwStyle, DWORD dwExStyle, int x, int y, int cx, int cy, HMENU hMenu)
{
    m_hParentWnd = hWndParent;
    return CWindowWnd::Create(hWndParent, pcszName, dwStyle, dwExStyle, x, y, cx, cy, hMenu);
}

void CBottomBarWnd::Init()
{
    m_pclResolutionBtn = static_cast<CButtonUI *>(m_clPaintManager.FindControl(_T("pc_resolution")));
    m_pclLiteWndBtn = static_cast<CButtonUI *>(m_clPaintManager.FindControl(_T("pc_litewindow")));
    m_pclEpisodeBtn = static_cast<CButtonUI *>(m_clPaintManager.FindControl(_T("pc_episode")));
    m_pclHSoundBtn = static_cast<CButtonUI *>(m_clPaintManager.FindControl(_T("pc_soundhigh")));
    m_pclLSoundBtn = static_cast<CButtonUI *>(m_clPaintManager.FindControl(_T("pc_soundlow")));
    m_pclMuteBtn = static_cast<CButtonUI *>(m_clPaintManager.FindControl(_T("pc_mute")));
    m_pclFullScreenBtn = static_cast<CButtonUI *>(m_clPaintManager.FindControl(_T("pc_fullscreen")));
    m_pclNormalScreenBtn = static_cast<CButtonUI *>(m_clPaintManager.FindControl(_T("pc_exitfullscreen")));
    m_pclResolutionBtn->SetEnabled(false);
}

LRESULT CBottomBarWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    LONG iStyle = ::GetWindowLong(*this, GWL_STYLE);
    iStyle &= ~WS_CAPTION;
    ::SetWindowLong(*this, GWL_STYLE, iStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    m_clPaintManager.Init(m_hWnd);
    CDialogBuilder clBuilder;
    CControlUI* pRoot = clBuilder.Create(_T("bottombar.xml"), (UINT)0, NULL, &m_clPaintManager);
    ASSERT(pRoot && "Failed to parse XML");
    m_clPaintManager.AttachDialog(pRoot);
    m_clPaintManager.AddNotifier(this);
    Init();
    return 0;
}

LRESULT CBottomBarWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = FALSE;
    return 0;
}

LRESULT CBottomBarWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = FALSE;
    return 0;
}

LRESULT CBottomBarWnd::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bool bShowVolume = false;
    bool bShowRatio = false;
    CButtonUI *pclBtn = NULL;

    if (m_pclHSoundBtn->IsVisible()) {
        pclBtn = m_pclHSoundBtn;
    }

    if (m_pclLSoundBtn->IsVisible()) {
        pclBtn = m_pclLSoundBtn;
    }

    if (m_pclMuteBtn->IsVisible()) {
        pclBtn = m_pclMuteBtn;
    }

    CDuiPoint stCursorPoint;
    GetCursorPos(&stCursorPoint);
    RECT stVolumeRect = pclBtn->GetPos();
    CDuiPoint stVolumePoint;
    stVolumePoint.x = stVolumeRect.left;
    stVolumePoint.y = stVolumeRect.bottom;
    ClientToScreen(m_hWnd, &stVolumePoint);
    RECT stRatioRect = m_pclFullScreenBtn->GetPos();
    CDuiPoint stRatioPoint;
    stRatioPoint.x = stRatioRect.left;
    stRatioPoint.y = stRatioRect.bottom;
    ClientToScreen(m_hWnd, &stRatioPoint);
    int iVolumeHeight = 0;
    GetWindowRect(m_pclVolumeBackgroundWnd->GetHWND(), &stVolumeRect);
    iVolumeHeight = stVolumeRect.bottom - stVolumeRect.top;

    if ((stCursorPoint.x >= stVolumePoint.x) && (stCursorPoint.x <= stVolumePoint.x + pclBtn->GetWidth())
        && (stCursorPoint.y >= stVolumePoint.y - iVolumeHeight) && (stCursorPoint.y <= stVolumePoint.y)) {
        bShowVolume = true;
    } else if ((stCursorPoint.x >= stRatioPoint.x) && (stCursorPoint.x <= stRatioPoint.x + pclBtn->GetWidth())
               && (stCursorPoint.y >= stRatioPoint.y - iVolumeHeight) && (stCursorPoint.y <= stRatioPoint.y)) {
        bShowRatio = true;
    } else {
        bShowVolume = false;
        bShowRatio = false;
    }

    OnVolumeBackground(bShowVolume);
    OnVolume(bShowVolume);
    OnScreenRatio(bShowRatio);
    bHandled = FALSE;
    return 0;
}

LRESULT CBottomBarWnd::OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = FALSE;
    return 0;
}

LRESULT CBottomBarWnd::OnShowWindow(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    switch (wParam) {
    case 1:
        OnVolumeBackground(true);
        OnVolume(true);
        break;

    case 0:
        OnVolumeBackground(false);
        OnVolume(false);
        OnScreenRatio(false);
        break;

    default:
        break;
    }

    bHandled = FALSE;
    return 0;
}


void CBottomBarWnd::OnFinalMessage(HWND hWnd)
{
    delete this;
}

void CBottomBarWnd::OnPrepare()
{
    CreateVolume();
    CreateVolumeTip();
    CreateVolumeBackground();
    CreateScreenRatio();
}

void CBottomBarWnd::Notify(TNotifyUI& msg)
{
    if (msg.sType == _T("windowinit")) {
        OnPrepare();
    } else if (msg.sType == _T("click")) {
        if (msg.pSender == m_pclLiteWndBtn) {
        } else if (msg.pSender == m_pclEpisodeBtn) {
        } else if (msg.pSender == m_pclHSoundBtn) {
        } else if (msg.pSender == m_pclLSoundBtn) {
        } else if (msg.pSender == m_pclMuteBtn) {
        } else if (msg.pSender == m_pclFullScreenBtn) {
        } else if (msg.pSender == m_pclNormalScreenBtn) {
        }
    }
}

LRESULT CBottomBarWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

    case WM_MOUSEMOVE:
        lResult = OnMouseMove(uMsg, wParam, lParam, bHandled);
        break;

    case WM_MOUSELEAVE:
        lResult = OnMouseLeave(uMsg, wParam, lParam, bHandled);
        break;

    case WM_SHOWWINDOW:
        lResult = OnShowWindow(uMsg, wParam, lParam, bHandled);
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

void CBottomBarWnd::CreateVolume()
{
    m_pclVolumeWnd = new CVolumeWnd();
    m_pclVolumeWnd->Create(m_hWnd, L"VolumeWnd", WS_POPUP, NULL);
}

void CBottomBarWnd::CreateVolumeTip()
{
    m_pclVolumeTipWnd = new CVolumeTipWnd();
    m_pclVolumeTipWnd->Create(m_hWnd, L"VolumeTipWnd", WS_POPUP, NULL);
}

void CBottomBarWnd::CreateVolumeBackground()
{
    m_pclVolumeBackgroundWnd = new CVolumeBackgroundWnd();
    m_pclVolumeBackgroundWnd->Create(m_hWnd, L"VolumeBackgroundWnd", WS_POPUP, NULL);
}

void CBottomBarWnd::CreateScreenRatio()
{
    m_pclScreenRatioWnd = new CScreenRatioWnd();
    m_pclScreenRatioWnd->Create(m_hWnd, L"ScreenRatioWnd", WS_POPUP, NULL);
}

void CBottomBarWnd::OnVolume(bool bShow)
{
    if (m_pclVolumeWnd == NULL) {
        return;
    }

    m_pclVolumeWnd->ShowWindow(bShow);

    if (bShow) {
        RECT stMainRect;
        RECT stUserRect;
        int iUserWidth = 0;
        int iUserHeight = 0;
        GetWindowRect(m_hWnd, &stMainRect);
        GetWindowRect(m_pclVolumeWnd->GetHWND(), &stUserRect);
        CDuiPoint stPoint;
        stPoint.x = m_pclLSoundBtn->GetPos().left;
        stPoint.y = m_pclLSoundBtn->GetPos().bottom;
        ClientToScreen(m_hWnd, &stPoint);
        iUserWidth = stUserRect.right - stUserRect.left;
        iUserHeight = stUserRect.bottom - stUserRect.top;
        MoveWindow(m_pclVolumeWnd->GetHWND(), stPoint.x, stPoint.y - m_pclLSoundBtn->GetHeight() - iUserHeight - 8,
                   iUserWidth, iUserHeight, false);
    }
}

void CBottomBarWnd::OnVolumeTip(bool bShow)
{
}

void CBottomBarWnd::OnVolumeBackground(bool bShow)
{
    if (m_pclVolumeBackgroundWnd == NULL) {
        return;
    }

    m_pclVolumeBackgroundWnd->ShowWindow(bShow);

    if (bShow) {
        RECT stMainRect;
        RECT stUserRect;
        int iUserWidth = 0;
        int iUserHeight = 0;
        GetWindowRect(m_hWnd, &stMainRect);
        GetWindowRect(m_pclVolumeBackgroundWnd->GetHWND(), &stUserRect);
        CDuiPoint stPoint;
        stPoint.x = m_pclLSoundBtn->GetPos().left;
        stPoint.y = m_pclLSoundBtn->GetPos().bottom;
        ClientToScreen(m_hWnd, &stPoint);
        iUserWidth = stUserRect.right - stUserRect.left;
        iUserHeight = stUserRect.bottom - stUserRect.top;
        MoveWindow(m_pclVolumeBackgroundWnd->GetHWND(), stPoint.x, stPoint.y - m_pclLSoundBtn->GetHeight() - iUserHeight - 2,
                   iUserWidth, iUserHeight, false);
    }
}

void CBottomBarWnd::OnScreenRatio(bool bShow)
{
    if (m_pclScreenRatioWnd == NULL) {
        return;
    }

    m_pclScreenRatioWnd->ShowWindow(bShow);

    if (bShow) {
        RECT stMainRect;
        RECT stUserRect;
        int iUserWidth = 0;
        int iUserHeight = 0;
        GetWindowRect(m_hWnd, &stMainRect);
        GetWindowRect(m_pclScreenRatioWnd->GetHWND(), &stUserRect);
        CDuiPoint stPoint;
        stPoint.x = m_pclFullScreenBtn->GetPos().left;
        stPoint.y = m_pclFullScreenBtn->GetPos().bottom;
        ClientToScreen(m_hWnd, &stPoint);
        iUserWidth = stUserRect.right - stUserRect.left;
        iUserHeight = stUserRect.bottom - stUserRect.top;
        MoveWindow(m_pclScreenRatioWnd->GetHWND(), stPoint.x - 11, stPoint.y - m_pclFullScreenBtn->GetHeight() - iUserHeight - 2,
                   iUserWidth, iUserHeight, false);
    }
}