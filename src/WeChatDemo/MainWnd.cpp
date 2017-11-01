#include "stdafx.h"
#include "MainWnd.h"
#include <stdio.h>


CMainWnd::CMainWnd()
{
    m_pclMinBtn = NULL;
    m_pclMaxBtn = NULL;
    m_pclRestoreBtn = NULL;
    m_pclCloseBtn = NULL;
    m_pclUserBtn = NULL;
    m_pclChatBtn = NULL;
    m_pclContactsBtn = NULL;
    m_pclSearchEdt = NULL;
    m_pclInputEdt = NULL;
    m_pclOutputEdt = NULL;
    m_pclInputFrame = NULL;
    m_pclSendFrame = NULL;
    m_pclChatTitleBtn = NULL;
    m_pclChatIcoBtn = NULL;
    m_pclBkgdCtrl = NULL;
    m_pclFriendsList = NULL;
    m_pclContactsList = NULL;
    m_strChatNormalImg = "";
    m_strChatHoverImg = "";
    m_strContactsNormalImg = "";
    m_strContactsHoverImg = "";
    m_strContactsClickImg = "";
    m_dwItemNormalColor = 0;
    m_dwItemNormalColor2 = 0;
    m_dwItemClickColor = 0;
    m_bChatClicked = false;
    m_bContactsClicked = false;
}


CMainWnd::~CMainWnd()
{
    m_pclMinBtn = NULL;
    m_pclMaxBtn = NULL;
    m_pclRestoreBtn = NULL;
    m_pclCloseBtn = NULL;
    m_pclUserBtn = NULL;
    m_pclChatBtn = NULL;
    m_pclContactsBtn = NULL;
    m_pclSearchEdt = NULL;
    m_pclInputEdt = NULL;
    m_pclOutputEdt = NULL;
    m_pclInputFrame = NULL;
    m_pclSendFrame = NULL;
    m_pclChatTitleBtn = NULL;
    m_pclChatIcoBtn = NULL;
    m_pclBkgdCtrl = NULL;
    m_pclFriendsList = NULL;
    m_pclContactsList = NULL;
    m_strChatNormalImg = "";
    m_strChatHoverImg = "";
    m_strContactsNormalImg = "";
    m_strContactsHoverImg = "";
    m_strContactsClickImg = "";
    m_dwItemNormalColor = 0;
    m_dwItemNormalColor2 = 0;
    m_dwItemClickColor = 0;
    m_bChatClicked = false;
    m_bContactsClicked = false;
}

LPCTSTR CMainWnd::GetWindowClassName() const
{
    return _T("MainWnd");
}

UINT CMainWnd::GetClassStyle() const
{
    return (UI_CLASSSTYLE_FRAME | CS_DBLCLKS);
}

CDuiString CMainWnd::GetSkinFolder()
{
    return CDuiString((CPaintManagerUI::GetInstancePath()) + _T("skin\\"));
}

CDuiString CMainWnd::GetSkinFile()
{
    return _T("mainwnd.xml");
}

void CMainWnd::Init()
{
    m_pclMinBtn = static_cast<CButtonUI *>(GetPaintManager()->FindControl(_T("minbtn")));
    m_pclMaxBtn = static_cast<CButtonUI *>(GetPaintManager()->FindControl(_T("maxbtn")));
    m_pclRestoreBtn = static_cast<CButtonUI *>(GetPaintManager()->FindControl(_T("restorebtn")));
    m_pclCloseBtn = static_cast<CButtonUI *>(GetPaintManager()->FindControl(_T("closebtn")));
    m_pclUserBtn = static_cast<CButtonUI *>(GetPaintManager()->FindControl(_T("userbtn")));
    m_pclChatBtn = static_cast<CButtonUI *>(GetPaintManager()->FindControl(_T("chatbtn")));
    m_pclContactsBtn = static_cast<CButtonUI *>(GetPaintManager()->FindControl(_T("contactsbtn")));
    m_pclSearchEdt = static_cast<CRichEditUI *>(GetPaintManager()->FindControl(_T("searchedt")));
    m_pclInputEdt = static_cast<CRichEditUI *>(GetPaintManager()->FindControl(_T("inputedt")));
    m_pclOutputEdt = static_cast<CRichEditUI *>(GetPaintManager()->FindControl(_T("outputedt")));
    m_pclInputFrame = static_cast<CHorizontalLayoutUI *>(GetPaintManager()->FindControl(_T("inputframe")));
    m_pclSendFrame = static_cast<CHorizontalLayoutUI *>(GetPaintManager()->FindControl(_T("sendframe")));
    m_pclChatTitleBtn = static_cast<CButtonUI *>(GetPaintManager()->FindControl(_T("chattitlebtn")));
    m_pclChatIcoBtn = static_cast<CButtonUI *>(GetPaintManager()->FindControl(_T("chatico")));
    m_pclBkgdCtrl = static_cast<CContainerUI *>(GetPaintManager()->FindControl(_T("bkgdico")));
    m_strChatNormalImg = m_pclChatBtn->GetNormalImage();
    m_strChatHoverImg = m_pclChatBtn->GetHotImage();
    m_strChatClickImg = m_pclChatBtn->GetPushedImage();
    m_strContactsNormalImg = m_pclContactsBtn->GetNormalImage();
    m_strContactsHoverImg = m_pclContactsBtn->GetHotImage();
    m_strContactsClickImg = m_pclContactsBtn->GetPushedImage();
    m_dwItemNormalColor = 0XFF3A3A3A;
    m_dwItemNormalColor2 = 0XFF5B5B5B;
    m_dwItemClickColor = 0XFF515050;
    InitFriends();
    InitContacts();
}

CControlUI * CMainWnd::CreateControl(LPCTSTR pcszName)
{
    CControlUI *pclControlUI = NULL;

    if (_tcsicmp(pcszName, _T("FriendsList")) == 0) {
        pclControlUI = new CFriendsListUI(GetPaintManager());
    } else if (_tcsicmp(pcszName, _T("ContactsList")) == 0) {
        pclControlUI = new CContactsListUI(GetPaintManager());
    }

    return pclControlUI;
}

void CMainWnd::InitFriends()
{
    m_pclFriendsList = (CFriendsListUI *)GetPaintManager()->FindControl(L"Friends");

    if (m_pclFriendsList == NULL) {
        return;
    }

    if (!m_clFriends.empty()) {
        m_clFriends.clear();
    }

    tagFriendsInfo stItem;
    CNode *pclRoot = NULL;
    CDuiString strTime = L"";
    SYSTEMTIME stTime;
    GetLocalTime(&stTime);
    strTime.Format(L"%02d:%02d", stTime.wHour, stTime.wMinute);
    stItem.m_bIsFolder = true;
    stItem.m_bIsEmpty = false;
    stItem.m_strID = _T("1");
    stItem.m_strIDIco = _T("fileico.png");
    stItem.m_strName = _T("文件传输助手");
    stItem.m_iType = 0;
    stItem.m_strTime = strTime;
    stItem.m_strMessage = _T("");
    stItem.m_strSoundIco = _T("");
    m_clFriends.push_back(stItem);
    pclRoot = m_pclFriendsList->AddNode(stItem, NULL);
    stItem.m_bIsFolder = true;
    stItem.m_bIsEmpty = false;
    stItem.m_strID = _T("2");
    stItem.m_strIDIco = _T("phonepay.png");
    stItem.m_strName = _T("手机充值");
    stItem.m_iType = 2;
    stItem.m_strTime = strTime;
    stItem.m_strMessage = _T("");
    stItem.m_strSoundIco = _T("");
    m_clFriends.push_back(stItem);
    m_pclFriendsList->AddNode(stItem, pclRoot);
    stItem.m_bIsFolder = true;
    stItem.m_bIsEmpty = false;
    stItem.m_strID = _T("3");
    stItem.m_strIDIco = _T("wepayico.png");
    stItem.m_strName = _T("微信支付");
    stItem.m_iType = 2;
    stItem.m_strTime = strTime;
    stItem.m_strMessage = _T("");
    stItem.m_strSoundIco = _T("");
    m_clFriends.push_back(stItem);
    m_pclFriendsList->AddNode(stItem, pclRoot);
    stItem.m_bIsFolder = true;
    stItem.m_bIsEmpty = false;
    stItem.m_strID = _T("4");
    stItem.m_strIDIco = _T("qqfinance.png");
    stItem.m_strName = _T("理财通");
    stItem.m_iType = 2;
    stItem.m_strTime = strTime;
    stItem.m_strMessage = _T("");
    stItem.m_strSoundIco = _T("");
    m_clFriends.push_back(stItem);
    m_pclFriendsList->AddNode(stItem, pclRoot);
    stItem.m_bIsFolder = true;
    stItem.m_bIsEmpty = false;
    stItem.m_strID = _T("5");
    stItem.m_strIDIco = _T("railway.png");
    stItem.m_strName = _T("铁路12306");
    stItem.m_iType = 2;
    stItem.m_strTime = strTime;
    stItem.m_strMessage = _T("");
    stItem.m_strSoundIco = _T("");
    m_clFriends.push_back(stItem);
    m_pclFriendsList->AddNode(stItem, pclRoot);
    stItem.m_bIsFolder = true;
    stItem.m_bIsEmpty = false;
    stItem.m_strID = _T("6");
    stItem.m_strIDIco = _T("publicico.png");
    stItem.m_strName = _T("订阅号");
    stItem.m_iType = 3;
    stItem.m_strTime = strTime;
    stItem.m_strMessage = _T("");
    stItem.m_strSoundIco = _T("");
    m_clFriends.push_back(stItem);
    m_pclFriendsList->AddNode(stItem, pclRoot);
    stItem.m_bIsFolder = true;
    stItem.m_bIsEmpty = false;
    stItem.m_strID = _T("7");
    stItem.m_strIDIco = _T("defaultcontact.png");
    stItem.m_strName = _T("VICTOR");
    stItem.m_iType = 1;
    stItem.m_strTime = strTime;
    stItem.m_strMessage = _T("");
    stItem.m_strSoundIco = _T("");
    m_clFriends.push_back(stItem);
    m_pclFriendsList->AddNode(stItem, pclRoot);
}

void CMainWnd::UpdateFriends()
{
}

void CMainWnd::InitContacts()
{
    m_pclContactsList = (CContactsListUI *)GetPaintManager()->FindControl(L"Contacts");

    if (m_pclContactsList == NULL) {
        return;
    }

    if (!m_clContacts.empty()) {
        m_clContacts.clear();
    }

    tagContactsInfo stItem;
    CNode *pclRootA = NULL;
    stItem.m_bIsFolder = true;
    stItem.m_bIsEmpty = false;
    stItem.m_strID = _T("0");
    stItem.m_strName = _T("公众号");
    m_clContacts.push_back(stItem);
    pclRootA = m_pclContactsList->AddNode(stItem, NULL);
    stItem.m_bIsFolder = false;
    stItem.m_bIsEmpty = false;
    stItem.m_iType = 2;
    stItem.m_strID = _T("1");
    stItem.m_strIDIco = _T("publicico.png");
    stItem.m_strName = _T("公众号");
    m_clContacts.push_back(stItem);
    m_pclContactsList->AddNode(stItem, pclRootA);
    CNode *pclRootB = NULL;
    stItem.m_bIsFolder = true;
    stItem.m_bIsEmpty = false;
    stItem.m_strID = _T("A");
    stItem.m_strName = _T("A");
    m_clContacts.push_back(stItem);
    pclRootB = m_pclContactsList->AddNode(stItem, NULL);
    stItem.m_bIsFolder = false;
    stItem.m_bIsEmpty = false;
    stItem.m_iType = 1;
    stItem.m_strID = _T("1");
    stItem.m_strIDIco = _T("defaultcontact.png");
    stItem.m_strName = _T("赵明");
    m_clContacts.push_back(stItem);
    m_pclContactsList->AddNode(stItem, pclRootB);
    stItem.m_bIsFolder = false;
    stItem.m_bIsEmpty = false;
    stItem.m_iType = 1;
    stItem.m_strID = _T("2");
    stItem.m_strIDIco = _T("defaultcontact.png");
    stItem.m_strName = _T("钱亮");
    m_clContacts.push_back(stItem);
    m_pclContactsList->AddNode(stItem, pclRootB);
    stItem.m_bIsFolder = false;
    stItem.m_bIsEmpty = false;
    stItem.m_iType = 1;
    stItem.m_strID = _T("3");
    stItem.m_strIDIco = _T("defaultcontact.png");
    stItem.m_strName = _T("孙武");
    m_clContacts.push_back(stItem);
    m_pclContactsList->AddNode(stItem, pclRootB);
    stItem.m_bIsFolder = false;
    stItem.m_bIsEmpty = false;
    stItem.m_iType = 1;
    stItem.m_strID = _T("4");
    stItem.m_strIDIco = _T("defaultcontact.png");
    stItem.m_strName = _T("李宏");
    m_clContacts.push_back(stItem);
    m_pclContactsList->AddNode(stItem, pclRootB);
    CNode *pclRootC = NULL;
    stItem.m_bIsFolder = true;
    stItem.m_bIsEmpty = false;
    stItem.m_iType = 1;
    stItem.m_strID = _T("B");
    stItem.m_strName = _T("B");
    m_clContacts.push_back(stItem);
    pclRootC = m_pclContactsList->AddNode(stItem, NULL);
    stItem.m_bIsFolder = false;
    stItem.m_bIsEmpty = false;
    stItem.m_iType = 1;
    stItem.m_strID = _T("1");
    stItem.m_strIDIco = _T("defaultcontact.png");
    stItem.m_strName = _T("赵琪");
    m_clContacts.push_back(stItem);
    m_pclContactsList->AddNode(stItem, pclRootC);
    stItem.m_bIsFolder = false;
    stItem.m_bIsEmpty = false;
    stItem.m_iType = 1;
    stItem.m_strID = _T("2");
    stItem.m_strIDIco = _T("defaultcontact.png");
    stItem.m_strName = _T("钱丽");
    m_clContacts.push_back(stItem);
    m_pclContactsList->AddNode(stItem, pclRootC);
    stItem.m_bIsFolder = false;
    stItem.m_bIsEmpty = false;
    stItem.m_iType = 1;
    stItem.m_strID = _T("3");
    stItem.m_strIDIco = _T("defaultcontact.png");
    stItem.m_strName = _T("孙静");
    m_clContacts.push_back(stItem);
    m_pclContactsList->AddNode(stItem, pclRootC);
    stItem.m_bIsFolder = false;
    stItem.m_bIsEmpty = false;
    stItem.m_iType = 1;
    stItem.m_strID = _T("4");
    stItem.m_strIDIco = _T("defaultcontact.png");
    stItem.m_strName = _T("李明");
    m_clContacts.push_back(stItem);
    m_pclContactsList->AddNode(stItem, pclRootC);
    m_pclContactsList->SetVisible(false);
}

void CMainWnd::UpdateContacts()
{
}

bool CMainWnd::CheckFriendsItemColor(CControlUI *pclControl)
{
    m_bChatClicked = true;
    m_pclChatBtn->SetBkImage(m_strChatClickImg);

    if (pclControl == NULL) {
        return false;
    }

    int iCount = m_pclFriendsList->GetCount();
    CControlUI *pclTemp = NULL;

    for (int i = 0; i < iCount; i++) {
        pclTemp = m_pclFriendsList->GetItemAt(i);

        if (pclTemp == pclControl) {
            pclTemp->SetBkColor(m_dwItemClickColor);
        } else {
            pclTemp->SetBkColor(m_dwItemNormalColor);
        }
    }

    return true;
}

bool CMainWnd::CheckContactsItemColor(CControlUI *pclControl)
{
    if (pclControl == NULL) {
        return false;
    }

    CNode *pclNode = (CNode *)pclControl->GetTag();

    if (pclNode == NULL) {
        return false;
    }

    if (pclNode->HasChild()) {
        return true;
    }

    int iCount = m_pclContactsList->GetCount();
    CControlUI *pclTemp = NULL;

    for (int i = 0; i < iCount; i++) {
        pclTemp = m_pclContactsList->GetItemAt(i);

        if (pclTemp == pclControl) {
            pclTemp->SetBkColor(m_dwItemClickColor);
        } else {
            pclTemp->SetBkColor(m_dwItemNormalColor);
        }
    }

    return true;
}

bool CMainWnd::CheckChatInfo(CControlUI *pclControl)
{
    CListContainerElementUI *pclElement = (CListContainerElementUI *)pclControl;

    if (pclElement == NULL) {
        return false;
    }

    CNode *pclNode = (CNode *)pclElement->GetTag();

    if (pclNode == NULL) {
        return false;
    }

    bool bVisible = false;
    int iType = pclNode->GetData().m_iType;

    switch (iType) {
    case 1:
    case 2:
        bVisible = true;
        break;

    case 3:
    default:
        break;
    }

    m_pclChatIcoBtn->SetVisible(bVisible);
    m_pclChatTitleBtn->SetText(pclNode->GetData().m_strText.c_str());

    if (!m_pclChatTitleBtn->IsVisible()) {
        m_pclChatTitleBtn->SetVisible(true);
    }

    return true;
}

LRESULT CMainWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    LONG iStyle = ::GetWindowLong(*this, GWL_STYLE);
    iStyle &= ~WS_CAPTION;
    ::SetWindowLong(*this, GWL_STYLE, iStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
    GetPaintManager()->Init(m_hWnd);
    CDialogBuilder clBuilder;
    CControlUI* pRoot = clBuilder.Create(_T("mainwnd.xml"), (UINT)0, this, GetPaintManager());
    ASSERT(pRoot && "Failed to parse XML");
    GetPaintManager()->AttachDialog(pRoot);
    GetPaintManager()->AddNotifier(this);
    Init();
    return 0;
}

LRESULT CMainWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    bHandled = FALSE;
    return 0;
}

LRESULT CMainWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    ::PostQuitMessage(0);
    bHandled = FALSE;
    return 0;
}

LRESULT CMainWnd::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    // 有时会在收到WM_NCDESTROY后收到wParam为SC_CLOSE的WM_SYSCOMMAND
    if (wParam == SC_CLOSE) {
        ::PostQuitMessage(0);
        bHandled = TRUE;
        return 0;
    }

    BOOL bZoomed = ::IsZoomed(m_hWnd);
    LRESULT lResult = CWindowWnd::HandleMessage(uMsg, wParam, lParam);

    if (::IsZoomed(m_hWnd) != bZoomed) {
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

LRESULT CMainWnd::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    if (::IsIconic(m_hWnd)) {
        bHandled = FALSE;
    }

    return ((wParam == 0) ? TRUE : FALSE);
}

LRESULT CMainWnd::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    return 0;
}

LRESULT CMainWnd::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    return 0;
}


LRESULT CMainWnd::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    POINT stPoint;
    stPoint.x = GET_X_LPARAM(lParam);
    stPoint.y = GET_Y_LPARAM(lParam);
    ::ScreenToClient(m_hWnd, &stPoint);
    RECT stClientRect;
    ::GetClientRect(m_hWnd, &stClientRect);
    RECT stCastRect = GetPaintManager()->GetCaptionRect();

    if ((stPoint.x >= stClientRect.left + stCastRect.left)
        && (stPoint.x < stClientRect.right - stCastRect.right)
        && (stPoint.y >= stCastRect.top)
        && (stPoint.y < stCastRect.bottom)) {
        CControlUI *pclControl = static_cast<CControlUI *>(GetPaintManager()->FindControl(stPoint));

        if ((pclControl != NULL)
            && (_tcscmp(pclControl->GetClass(), _T("ButtonUI")) != 0)
            && (_tcscmp(pclControl->GetClass(), _T("VerticalLayout")) != 0)
            && (_tcscmp(pclControl->GetClass(), _T("RichEditUI")) != 0)) {
            return HTCAPTION;
        }
    }

    return HTCLIENT;
}

LRESULT CMainWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    SIZE stRoundCorner = GetPaintManager()->GetRoundCorner();

    if (!::IsIconic(m_hWnd)
        && ((stRoundCorner.cx != 0) || (stRoundCorner.cy != 0))) {
        CDuiRect clRect;
        ::GetWindowRect(m_hWnd, &clRect);
        clRect.Offset(-clRect.left, -clRect.top);
        clRect.right++;
        clRect.bottom++;
        HRGN hRgn = ::CreateRoundRectRgn(clRect.left, clRect.top, clRect.right, clRect.bottom, stRoundCorner.cx, stRoundCorner.cy);
        ::SetWindowRgn(m_hWnd, hRgn, TRUE);
        ::DeleteObject(hRgn);
    }

    bHandled = FALSE;
    return 0;
}

LRESULT CMainWnd::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    MONITORINFO stMonitor;
    stMonitor.cbSize = sizeof(stMonitor);
    ::GetMonitorInfo(::MonitorFromWindow(m_hWnd, MONITOR_DEFAULTTOPRIMARY), &stMonitor);
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

LRESULT CMainWnd::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
    POINT stPoint;
    GetCursorPos(&stPoint);
    ::ScreenToClient(*this, &stPoint);
    CDuiString strBkImg = L"";
    CControlUI *pclControl = static_cast<CControlUI *>(GetPaintManager()->FindControl(stPoint));

    if (pclControl == m_pclChatBtn) {
        strBkImg = (m_bChatClicked ? m_strChatClickImg : m_strChatHoverImg);
        m_pclChatBtn->SetBkImage(strBkImg);
    } else if (pclControl == m_pclContactsBtn) {
        strBkImg = (m_bContactsClicked ? m_strContactsClickImg : m_strContactsHoverImg);
        m_pclContactsBtn->SetBkImage(strBkImg);
    } else {
        strBkImg = (m_bChatClicked ? m_strChatClickImg : m_strChatNormalImg);
        m_pclChatBtn->SetBkImage(strBkImg);
        strBkImg = (m_bContactsClicked ? m_strContactsClickImg : m_strContactsNormalImg);
        m_pclContactsBtn->SetBkImage(strBkImg);
    }

    bHandled = FALSE;
    return 0;
}

void CMainWnd::OnFinalMessage(HWND hWnd)
{
    CBaseWnd::OnFinalMessage(hWnd);
    delete this;
}

void CMainWnd::OnPrepare()
{
}

void CMainWnd::Notify(TNotifyUI& msg)
{
    if (msg.sType == _T("windowinit")) {
        OnPrepare();
    } else if (msg.sType == _T("click")) {
        if (msg.pSender == m_pclMinBtn) {
            SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
            return;
        } else if (msg.pSender == m_pclMaxBtn) {
            SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
            return;
        } else if (msg.pSender == m_pclRestoreBtn) {
            SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
            return;
        } else if (msg.pSender == m_pclCloseBtn) {
            PostQuitMessage(0);
            return;
        } else if (msg.pSender == m_pclUserBtn) {
        } else if (msg.pSender == m_pclChatBtn) {
            m_pclFriendsList->SetVisible(true);
            m_pclContactsList->SetVisible(false);
            m_pclChatBtn->SetBkImage(m_strChatClickImg);
            m_pclContactsBtn->SetBkImage(m_strContactsNormalImg);
            m_bChatClicked = true;
            m_bContactsClicked = false;
        } else if (msg.pSender == m_pclContactsBtn) {
            m_pclFriendsList->SetVisible(false);
            m_pclContactsList->SetVisible(true);
            m_pclChatBtn->SetBkImage(m_strChatNormalImg);
            m_pclContactsBtn->SetBkImage(m_strContactsClickImg);
            m_bChatClicked = false;
            m_bContactsClicked = true;
        }

        m_pclSearchEdt->SetText(L"搜索");
    } else if (msg.sType == _T("setfocus")) {
        if (msg.pSender == m_pclSearchEdt) {
            m_pclSearchEdt->SetText(L"");
        }
    } else if (msg.sType == _T("itemclick")) {
        if (m_pclBkgdCtrl->IsVisible()) {
            m_pclBkgdCtrl->SetVisible(false);
        }

        if (!m_pclInputFrame->IsVisible()) {
            m_pclInputFrame->SetVisible(true);
        }

        if (!m_pclSendFrame->IsVisible()) {
            m_pclSendFrame->SetVisible(true);
        }

        if (!m_pclInputEdt->IsVisible()) {
            m_pclInputEdt->SetVisible(true);
        }

        m_pclInputEdt->SetFocus();
        m_pclInputEdt->SetSel(0, 0);

        if (m_pclFriendsList->GetItemIndex(msg.pSender) != -1) {
            if (_tcsicmp(msg.pSender->GetClass(), _T("ListContainerElementUI")) == 0) {
                CheckFriendsItemColor(msg.pSender);
                CheckChatInfo(msg.pSender);
            }
        }

        if (m_pclContactsList->GetItemIndex(msg.pSender) != -1) {
            if (_tcsicmp(msg.pSender->GetClass(), _T("ListContainerElementUI")) == 0) {
                CheckContactsItemColor(msg.pSender);
                CheckChatInfo(msg.pSender);
            }
        }
    }
}

LRESULT CMainWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

    case WM_SYSCOMMAND:
        lResult = OnSysCommand(uMsg, wParam, lParam, bHandled);
        break;

    case WM_NCACTIVATE :
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

    case WM_MOUSEMOVE:
        lResult = OnMouseMove(uMsg, wParam, lParam, bHandled);
        break;

    default:
        bHandled = FALSE;
        break;
    }

    if (bHandled) {
        return lResult;
    }

    if (GetPaintManager()->MessageHandler(uMsg, wParam, lParam, lResult)) {
        return lResult;
    }

    return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CMainWnd::ResponseDefaultKeyEvent(WPARAM wParam)
{
    if (wParam == VK_RETURN) {
        return FALSE;
    } else if (wParam == VK_ESCAPE) {
        return TRUE;
    }

    return FALSE;
}
