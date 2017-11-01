#include "stdafx.h"
#include "UserLoginWnd.h"
#include <shellapi.h>


CUserLoginWnd::CUserLoginWnd()
{
    m_pclCloseBtn = NULL;
    m_pclRegisterBtn = NULL;
    m_pclRegainBtn = NULL;
    m_pclLoginBtn = NULL;
    m_pclUserEdt = NULL;
    m_pclPwdEdt = NULL;
    m_pclErrLbl = NULL;
}


CUserLoginWnd::~CUserLoginWnd()
{
    m_pclCloseBtn = NULL;
    m_pclRegisterBtn = NULL;
    m_pclRegainBtn = NULL;
    m_pclLoginBtn = NULL;
    m_pclUserEdt = NULL;
    m_pclPwdEdt = NULL;
    m_pclErrLbl = NULL;
}

LPCTSTR CUserLoginWnd::GetWindowClassName() const
{
    return _T("UserLoginWnd");
}

UINT CUserLoginWnd::GetClassStyle() const
{
    return (UI_CLASSSTYLE_FRAME | CS_DBLCLKS);
}

void CUserLoginWnd::Init()
{
    m_pclCloseBtn = static_cast<CButtonUI *>(m_clPaintManager.FindControl(_T("l_close")));
    m_pclRegisterBtn = static_cast<CButtonUI *>(m_clPaintManager.FindControl(_T("l_reguser")));
    m_pclRegainBtn = static_cast<CButtonUI *>(m_clPaintManager.FindControl(_T("l_forgetpwd")));
    m_pclLoginBtn = static_cast<CButtonUI *>(m_clPaintManager.FindControl(_T("l_login")));
    m_pclUserEdt = static_cast<CEditUI *>(m_clPaintManager.FindControl(_T("l_username")));
    m_pclPwdEdt = static_cast<CEditUI *>(m_clPaintManager.FindControl(_T("l_pwd")));
    m_pclErrLbl = static_cast<CLabelUI *>(m_clPaintManager.FindControl(_T("l_errorinfo")));
}

LRESULT CUserLoginWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    LONG iStyle = ::GetWindowLong(*this, GWL_STYLE);
    iStyle &= ~WS_CAPTION;
    ::SetWindowLong(*this, GWL_STYLE, iStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    m_clPaintManager.Init(m_hWnd);
    CDialogBuilder clBuilder;
    CControlUI* pRoot = clBuilder.Create(_T("login.xml"), (UINT)0, NULL, &m_clPaintManager);
    ASSERT(pRoot && "Failed to parse XML");
    m_clPaintManager.AttachDialog(pRoot);
    m_clPaintManager.AddNotifier(this);
    Init();
    return 0;
}

LRESULT CUserLoginWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = FALSE;
    return 0;
}

LRESULT CUserLoginWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = FALSE;
    return 0;
}

void CUserLoginWnd::OnFinalMessage(HWND hWnd)
{
    delete this;
}

void CUserLoginWnd::OnPrepare()
{
}

void CUserLoginWnd::Notify(TNotifyUI& msg)
{
    if (msg.sType == _T("windowinit")) {
        OnPrepare();
    } else if (msg.sType == _T("click")) {
        if (msg.pSender == m_pclCloseBtn) {
            Close();
        } else if ((msg.pSender == m_pclRegisterBtn)
                   || (msg.pSender == m_pclRegainBtn)) {
            ::ShellExecute(NULL, _T("open"), _T("https://github.com/duilib/duilib"), NULL, NULL, SW_SHOWNORMAL);
        } else if (msg.pSender == m_pclLoginBtn) {
            if (m_pclUserEdt->GetText().IsEmpty()) {
                m_pclErrLbl->SetText(_T("请输入用户名！"));
            } else if (m_pclPwdEdt->GetText().IsEmpty()) {
                m_pclErrLbl->SetText(_T("请输入密码！"));
            } else {
                m_pclErrLbl->SetText(_T("该功能暂不支持！"));
            }
        }
    }
}

LRESULT CUserLoginWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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