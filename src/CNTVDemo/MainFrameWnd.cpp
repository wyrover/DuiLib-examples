#include "stdafx.h"
#include "MainFrameWnd.h"
#include "UserCenterWnd.h"
#include "UserLoginWnd.h"
#include "TopBarWnd.h"
#include "VolumeWnd.h"
#include "VolumeTipWnd.h"
#include "VolumeBackgroundWnd.h"
#include "UIMenu.h"
#include <exdisp.h>
#include <comdef.h>
#include <stdio.h>
#include "Resource.h"

CMainFrameWnd::CMainFrameWnd()
{
    m_pclCloseBtn = NULL;
    m_pclMaxBtn = NULL;
    m_pclRestoreBtn = NULL;
    m_pclMinBtn = NULL;
    m_pclHistBtn = NULL;
    m_pclSysMenuBtn = NULL;
    m_pclSearchEdt = NULL;
    m_pclSearchBtn = NULL;
    m_pclUserCenterBtn = NULL;
    m_pclUserLoginBtn = NULL;
    m_hUserCenterWnd = NULL;
    m_bUserCenterClicked = false;
    m_pclTopBarWnd = NULL;
    m_pclBottomBarWnd = NULL;
}


CMainFrameWnd::~CMainFrameWnd()
{
    m_pclCloseBtn = NULL;
    m_pclMaxBtn = NULL;
    m_pclRestoreBtn = NULL;
    m_pclMinBtn = NULL;
    m_pclHistBtn = NULL;
    m_pclSysMenuBtn = NULL;
    m_pclSearchEdt = NULL;
    m_pclSearchBtn = NULL;
    m_pclUserCenterBtn = NULL;
    m_pclUserLoginBtn = NULL;
    m_hUserCenterWnd = NULL;
    m_bUserCenterClicked = false;
    m_pclTopBarWnd = NULL;
    m_pclBottomBarWnd = NULL;
}

LPCTSTR CMainFrameWnd::GetWindowClassName() const
{
    return _T("MainFrameWnd");
}

UINT CMainFrameWnd::GetClassStyle() const
{
    return (UI_CLASSSTYLE_FRAME | CS_DBLCLKS);
}

void CMainFrameWnd::Init()
{
    m_pclCloseBtn = static_cast<CButtonUI*>(m_clPaintManager.FindControl(_T("mf_close")));
    m_pclMaxBtn = static_cast<CButtonUI*>(m_clPaintManager.FindControl(_T("mf_max")));
    m_pclRestoreBtn = static_cast<CButtonUI*>(m_clPaintManager.FindControl(_T("mf_restore")));
    m_pclMinBtn = static_cast<CButtonUI*>(m_clPaintManager.FindControl(_T("mf_mini")));
    m_pclHistBtn = static_cast<CButtonUI*>(m_clPaintManager.FindControl(_T("mf_history")));
    m_pclSysMenuBtn = static_cast<CButtonUI*>(m_clPaintManager.FindControl(_T("mf_menu")));
    m_pclSearchEdt = static_cast<CEditUI*>(m_clPaintManager.FindControl(_T("mf_searchword")));
    m_pclSearchBtn = static_cast<CButtonUI*>(m_clPaintManager.FindControl(_T("mf_search")));
    m_pclUserCenterBtn = static_cast<CButtonUI*>(m_clPaintManager.FindControl(_T("mf_personal")));
    m_pclUserLoginBtn = static_cast<CButtonUI*>(m_clPaintManager.FindControl(_T("mf_login")));
}

LRESULT CMainFrameWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    LONG iStyle = ::GetWindowLong(*this, GWL_STYLE);
    iStyle &= ~WS_CAPTION;
    ::SetWindowLong(*this, GWL_STYLE, iStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    m_clPaintManager.Init(m_hWnd);
    CDialogBuilder clBuilder;
    CControlUI* pRoot = clBuilder.Create(_T("mainframe.xml"), (UINT)0, NULL, &m_clPaintManager);
    ASSERT(pRoot && "Failed to parse XML");
    m_clPaintManager.AttachDialog(pRoot);
    m_clPaintManager.AddNotifier(this);
    Init();
    CreateTray();
    return 0;
}

LRESULT CMainFrameWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = FALSE;
    return 0;
}

LRESULT CMainFrameWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    ::PostQuitMessage(0);
    DeleteTray();
    bHandled = FALSE;
    return 0;
}

LRESULT CMainFrameWnd::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    if (m_pclBottomBarWnd != NULL) {
        ::PostMessage(m_pclBottomBarWnd->GetHWND(), WM_SHOWWINDOW, 0, 0);
    }

    if (::IsIconic(*this)) {
        bHandled = FALSE;
    }

    return ((wParam == 0) ? TRUE : FALSE);
}

LRESULT CMainFrameWnd::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    return 0;
}

LRESULT CMainFrameWnd::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    return 0;
}

LRESULT CMainFrameWnd::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    POINT stPoint;
    stPoint.x = GET_X_LPARAM(lParam);
    stPoint.y = GET_Y_LPARAM(lParam);
    ::ScreenToClient(*this, &stPoint);
    RECT stClientRect;
    ::GetClientRect(*this, &stClientRect);
    RECT stCastRect = m_clPaintManager.GetCaptionRect();

    if ((stPoint.x >= stClientRect.left + stCastRect.left)
        && (stPoint.x < stClientRect.right - stCastRect.right)
        && (stPoint.y >= stCastRect.top)
        && (stPoint.y < stCastRect.bottom)) {
        CControlUI* pclControl = static_cast<CControlUI*>(m_clPaintManager.FindControl(stPoint));

        if ((pclControl != NULL)
            && (_tcscmp(pclControl->GetClass(), _T("ButtonUI")) != 0)
            && (_tcscmp(pclControl->GetClass(), _T("OstPointionUI")) != 0)
            && (_tcscmp(pclControl->GetClass(), _T("TextUI")) != 0)
            && (_tcscmp(pclControl->GetClass(), _T("EditUI")) != 0)) {
            OnTopBar();
            OnBottomBar();
            return HTCAPTION;
        }
    }

    return HTCLIENT;
}

LRESULT CMainFrameWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    SIZE stRoundCorner = m_clPaintManager.GetRoundCorner();

    if (!::IsIconic(*this)
        && ((stRoundCorner.cx != 0) || (stRoundCorner.cy != 0))) {
        CDuiRect clRect;
        ::GetWindowRect(*this, &clRect);
        clRect.Offset(-clRect.left, -clRect.top);
        clRect.right++;
        clRect.bottom++;
        HRGN hRgn = ::CreateRoundRectRgn(clRect.left, clRect.top, clRect.right, clRect.bottom, stRoundCorner.cx, stRoundCorner.cy);
        ::SetWindowRgn(*this, hRgn, TRUE);
        ::DeleteObject(hRgn);
    }

    bHandled = FALSE;
    return 0;
}

LRESULT CMainFrameWnd::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    MONITORINFO stMonitor;
    stMonitor.cbSize = sizeof(stMonitor);
    ::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &stMonitor);
    CDuiRect clRect = stMonitor.rcWork;
    clRect.Offset(-clRect.left, -clRect.top);
    LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
    lpMMI->ptMaxPosition.x = clRect.left;
    lpMMI->ptMaxPosition.y = clRect.top;
    lpMMI->ptMaxSize.x = clRect.right;
    lpMMI->ptMaxSize.y = clRect.bottom;
    bHandled = FALSE;
    return 0;
}

LRESULT CMainFrameWnd::OnMoving(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    OnTopBar();
    OnBottomBar();
    return 0;
}

LRESULT CMainFrameWnd::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    // 有时会在收到WM_NCDESTROY后收到wParam为SC_CLOSE的WM_SYSCOMMAND
    if (wParam == SC_CLOSE) {
        ::PostQuitMessage(0L);
        DeleteTray();
        bHandled = TRUE;
        return 0;
    }

    BOOL bZoomed = ::IsZoomed(*this);
    LRESULT lResult = CWindowWnd::HandleMessage(uMsg, wParam, lParam);

    if (::IsZoomed(*this) != bZoomed) {
        bool bVisible = !!bZoomed;

        if (m_pclMaxBtn != NULL) {
            m_pclMaxBtn->SetVisible(bVisible);
        }

        if (m_pclRestoreBtn != NULL) {
            m_pclRestoreBtn->SetVisible(!bVisible);
        }
    }

    return lResult;
}

LRESULT CMainFrameWnd::OnShowWindow(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    switch (wParam) {
    case 1:
        ShowWindow(true);
        OnTopBar();
        OnBottomBar();
        break;

    case 0:
    default:
        ShowWindow(false);
        break;
    }

    return 0;
}

LRESULT CMainFrameWnd::OnTrayCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    switch (lParam) {
    case WM_MOUSEMOVE:
        break;

    case WM_LBUTTONDOWN:
    case WM_LBUTTONDBLCLK:
        ShowWindow(true);
        OnTopBar();
        OnBottomBar();
        ::PostMessage(m_pclBottomBarWnd->GetHWND(), WM_SHOWWINDOW, 0, 0);
        break;

    case WM_RBUTTONDOWN:
    case WM_RBUTTONDBLCLK: {
        CMenuWnd *pclMenu = new CMenuWnd();
        CDuiPoint stPoint;
        GetCursorPos(&stPoint);
        STRINGorID clXmlName(L"traymenu.xml");
        pclMenu->Init(NULL, clXmlName, stPoint, &this->m_clPaintManager);
    }
    break;

    default:
        break;
    }

    return 0;
}

LRESULT CMainFrameWnd::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    if (m_pclBottomBarWnd != NULL) {
        ::PostMessage(m_pclBottomBarWnd->GetHWND(), WM_SHOWWINDOW, 0, 0);
    }

    bHandled = false;
    return 0;
}

LRESULT CMainFrameWnd::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    OnTopBar();
    OnBottomBar();
    OnUserCenter();
    bHandled = false;
    return 0;
}

LRESULT CMainFrameWnd::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    OnTopBar();
    OnBottomBar();
    bHandled = false;
    return 0;
}

LRESULT CMainFrameWnd::OnFavorite(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    WCHAR *pszTitle = (WCHAR *)wParam;
    WCHAR *pszTip = (WCHAR *)lParam;
    ModifyTray(pszTitle, pszTip);
    return 0;
}

LRESULT CMainFrameWnd::OnTopMost(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    RECT stRect;
    GetWindowRect(m_hWnd, &stRect);

    switch (wParam) {
    case 1:
        SetWindowPos(m_hWnd, HWND_TOPMOST, stRect.left, stRect.top, stRect.right - stRect.left, stRect.bottom - stRect.top, SWP_NOMOVE || SWP_NOSIZE);
        break;

    case 0:
        SetWindowPos(m_hWnd, HWND_NOTOPMOST, stRect.left, stRect.top, stRect.right - stRect.left, stRect.bottom - stRect.top, SWP_NOMOVE || SWP_NOSIZE);
        break;

    default:
        break;
    }

    return 0;
}

void CMainFrameWnd::OnPrepare()
{
    CreateTopBar();
    CreateBottomBar();
}

void CMainFrameWnd::Notify(TNotifyUI& msg)
{
    m_bUserCenterClicked = false;

    if (msg.sType == _T("windowinit")) {
        OnPrepare();
    } else if (msg.sType == _T("setfocus")) {
        if (msg.pSender == m_pclSearchEdt) {
            m_pclSearchEdt->SetText(L"");
        }
    } else if (msg.sType == _T("click")) {
        if (msg.pSender == m_pclCloseBtn) {
            PostQuitMessage(0);
            DeleteTray();
            return;
        } else if (msg.pSender == m_pclMinBtn) {
            SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
            return;
        } else if (msg.pSender == m_pclMaxBtn) {
            SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
            OnTopBar();
            OnBottomBar();
            return;
        } else if (msg.pSender == m_pclRestoreBtn) {
            SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
            OnTopBar();
            OnBottomBar();
            return;
        } else if (msg.pSender == m_pclSysMenuBtn) {
            CMenuWnd *pclMenu = new CMenuWnd();
            CDuiPoint stPoint;
            stPoint.x = m_pclSysMenuBtn->GetPos().left;
            stPoint.y = m_pclSysMenuBtn->GetPos().bottom;
            ClientToScreen(m_hWnd, &stPoint);
            STRINGorID clXmlName(L"mainmenu.xml");
            pclMenu->Init(NULL, clXmlName, stPoint, &this->m_clPaintManager);
        } else if (msg.pSender == m_pclSearchBtn) {
            m_pclSearchEdt->SetText(L"暂不支持该功能！");
        } else if ((msg.pSender == m_pclHistBtn)
                   || (msg.pSender == m_pclUserCenterBtn)) {
            CUserCenterWnd *pclWnd = new CUserCenterWnd();
            pclWnd->Create(m_hWnd, _T("UserCenterWnd"), WS_POPUP, NULL);
            m_hUserCenterWnd = pclWnd->GetHWND();
            RECT stMainRect;
            RECT stUserRect;
            int iUserWidth = 0;
            int iUserHeight = 0;
            GetWindowRect(m_hWnd, &stMainRect);
            GetWindowRect(pclWnd->GetHWND(), &stUserRect);
            iUserWidth = stUserRect.right - stUserRect.left;
            iUserHeight = stUserRect.bottom - stUserRect.top;
            MoveWindow(pclWnd->GetHWND(), stMainRect.right - iUserWidth,
                       stMainRect.bottom - iUserHeight - m_pclUserCenterBtn->GetHeight(), iUserWidth, iUserHeight, true);
            pclWnd->ShowWindow(true);
            m_bUserCenterClicked = true;
        } else if (msg.pSender == m_pclUserLoginBtn) {
            CUserLoginWnd *pclWnd = new CUserLoginWnd();
            pclWnd->Create(m_hWnd, _T("UserLoginWnd"), WS_POPUP, NULL);
            pclWnd->CenterWindow();
            pclWnd->ShowModal();
        }
    }
}

LRESULT CMainFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

    case WM_NCACTIVATE:
        lResult = OnNcActivate(uMsg, wParam, lParam, bHandled);
        break;

    case WM_NCCALCSIZE:
        lResult = OnNcCalcSize(uMsg, wParam, lParam, bHandled);
        break;

    case WM_NCPAINT:
        lResult = OnNcPaint(uMsg, wParam, lParam, bHandled);
        break;

    case WM_NCHITTEST:
        lResult = OnNcHitTest(uMsg, wParam, lParam, bHandled);
        break;

    case WM_SIZE:
        lResult = OnSize(uMsg, wParam, lParam, bHandled);
        break;

    case WM_GETMINMAXINFO:
        lResult = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled);
        break;

    case WM_MOVING:
        lResult = OnMoving(uMsg, wParam, lParam, bHandled);
        break;

    case WM_SYSCOMMAND:
        lResult = OnSysCommand(uMsg, wParam, lParam, bHandled);
        break;

    case WM_SHOWWINDOW:
        lResult = OnShowWindow(uMsg, wParam, lParam, bHandled);
        break;

    case WM_TRAYICON:
        lResult = OnTrayCommand(uMsg, wParam, lParam, bHandled);
        break;

    case WM_MOUSEMOVE:
        lResult = OnMouseMove(uMsg, wParam, lParam, bHandled);
        break;

    case WM_NCLBUTTONDOWN:
    case WM_LBUTTONDOWN:
        lResult = OnLButtonDown(uMsg, wParam, lParam, bHandled);
        break;

    case WM_NCLBUTTONUP:
        lResult = OnLButtonUp(uMsg, wParam, lParam, bHandled);
        break;

    case WM_FAVOURITE:
        lResult = OnFavorite(uMsg, wParam, lParam, bHandled);
        break;

    case WM_TOPMOST:
        lResult = OnTopMost(uMsg, wParam, lParam, bHandled);
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

void CMainFrameWnd::OnFinalMessage(HWND hWnd)
{
    delete this;
}

void CMainFrameWnd::CreateTray()
{
    m_stTrayData.cbSize = sizeof(NOTIFYICONDATA);
    m_stTrayData.hWnd = m_hWnd;
    m_stTrayData.uID = IDR_MAINFRAME;
    HICON hIcon = (HICON)::LoadImage(CPaintManagerUI::GetInstance(), MAKEINTRESOURCE(IDI_CNTVDEMO), IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
    m_stTrayData.hIcon = hIcon;
    m_stTrayData.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    m_stTrayData.uCallbackMessage = WM_TRAYICON;
    _snwprintf_s(m_stTrayData.szTip, sizeof(m_stTrayData.szTip), L"%s", L"CNTVDemo");
    Shell_NotifyIcon(NIM_ADD, &m_stTrayData);
}

void CMainFrameWnd::ModifyTray(LPCTSTR lpcszTitle, LPCTSTR lpcszTip)
{
    m_stTrayData.cbSize = sizeof(NOTIFYICONDATA);
    m_stTrayData.hWnd = m_hWnd;
    m_stTrayData.uID = IDR_MAINFRAME;
    HICON hIcon = (HICON)::LoadImage(CPaintManagerUI::GetInstance(), MAKEINTRESOURCE(IDI_CNTVDEMO), IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
    m_stTrayData.hIcon = hIcon;
    m_stTrayData.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_INFO;
    m_stTrayData.dwInfoFlags = NIIF_INFO;
    m_stTrayData.uCallbackMessage = WM_TRAYICON;
    _snwprintf_s(m_stTrayData.szInfoTitle, sizeof(m_stTrayData.szInfoTitle), L"%s", ((lpcszTitle != NULL) ? lpcszTitle : L""));
    _snwprintf_s(m_stTrayData.szInfo, sizeof(m_stTrayData.szTip), L"%s", ((lpcszTip != NULL) ? lpcszTip : L""));
    Shell_NotifyIcon(NIM_MODIFY, &m_stTrayData);
}

void CMainFrameWnd::DeleteTray()
{
    Shell_NotifyIcon(NIM_DELETE, &m_stTrayData);
}

void CMainFrameWnd::CreateTopBar()
{
    m_pclTopBarWnd = new CTopBarWnd();
    m_pclTopBarWnd->Create(m_hWnd, L"TopBarWnd", WS_POPUP, NULL);
    OnTopBar();
    m_pclTopBarWnd->ShowWindow(true);
}

void CMainFrameWnd::CreateBottomBar()
{
    m_pclBottomBarWnd = new CBottomBarWnd();
    m_pclBottomBarWnd->Create(m_hWnd, L"BottomBarWnd", WS_POPUP, NULL);
    OnBottomBar();
    m_pclBottomBarWnd->ShowWindow(true);
}

void CMainFrameWnd::OnTopBar()
{
    RECT stMainRect;
    RECT stUserRect;
    int iMainWidth = 0;
    int iUserHeight = 0;
    GetWindowRect(m_hWnd, &stMainRect);
    GetWindowRect(m_pclTopBarWnd->GetHWND(), &stUserRect);
    iMainWidth = stMainRect.right - stMainRect.left;
    iUserHeight = stUserRect.bottom - stUserRect.top;
    MoveWindow(m_pclTopBarWnd->GetHWND(), stMainRect.left + 2, stMainRect.top + m_pclSearchEdt->GetHeight(),
               iMainWidth - 4, iUserHeight, false);
}

void CMainFrameWnd::OnBottomBar()
{
    RECT stMainRect;
    RECT stUserRect;
    int iUserWidth = 0;
    int iUserHeight = 0;
    GetWindowRect(m_hWnd, &stMainRect);
    GetWindowRect(m_pclBottomBarWnd->GetHWND(), &stUserRect);
    iUserWidth = stUserRect.right - stUserRect.left;
    iUserHeight = stUserRect.bottom - stUserRect.top;
    int iMainWidth = stMainRect.right - stMainRect.left;
    MoveWindow(m_pclBottomBarWnd->GetHWND(), stMainRect.left + 2, stMainRect.bottom - m_pclUserCenterBtn->GetHeight() - iUserHeight,
               iMainWidth - 4, iUserHeight, false);
}

void CMainFrameWnd::OnUserCenter()
{
    if (!m_bUserCenterClicked) {
        return;
    }

    if (!IsWindow(m_hUserCenterWnd)) {
        return;
    }

    ::SendMessage(m_hUserCenterWnd, WM_CLOSE, 0, 0);
}