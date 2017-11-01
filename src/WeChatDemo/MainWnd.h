#pragma once

#include "BaseWnd.h"
#include "FriendsList.h"
#include "ContactsList.h"

class CMainWnd : public CBaseWnd
{
public:
    CMainWnd();
    ~CMainWnd();
public:
    LPCTSTR GetWindowClassName() const;
    UINT GetClassStyle() const;

    CDuiString GetSkinFolder();
    CDuiString GetSkinFile();

    void Init();

    CControlUI * CreateControl(LPCTSTR pcszName);
public:
    void InitFriends();
    void UpdateFriends();

    void InitContacts();
    void UpdateContacts();

    bool CheckFriendsItemColor(CControlUI *pclControl);
    bool CheckContactsItemColor(CControlUI *pclControl);

    bool CheckChatInfo(CControlUI *pclControl);
public:
    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    void OnPrepare();
    void OnFinalMessage(HWND hWnd);

    void Notify(TNotifyUI& msg);
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

    LRESULT ResponseDefaultKeyEvent(WPARAM wParam);
private:
    CButtonUI *m_pclMinBtn;
    CButtonUI *m_pclMaxBtn;
    CButtonUI *m_pclRestoreBtn;
    CButtonUI *m_pclCloseBtn;

    CButtonUI *m_pclUserBtn;
    CButtonUI *m_pclChatBtn;
    CButtonUI *m_pclContactsBtn;

    CRichEditUI *m_pclSearchEdt;
    CRichEditUI *m_pclInputEdt;
    CRichEditUI *m_pclOutputEdt;
    CHorizontalLayoutUI *m_pclInputFrame;
    CHorizontalLayoutUI *m_pclSendFrame;

    CButtonUI *m_pclChatTitleBtn;
    CButtonUI *m_pclChatIcoBtn;

    CContainerUI *m_pclBkgdCtrl;

    CFriendsListUI *m_pclFriendsList;
    CContactsListUI *m_pclContactsList;

    CDuiString m_strChatNormalImg;
    CDuiString m_strChatHoverImg;
    CDuiString m_strChatClickImg;

    CDuiString m_strContactsNormalImg;
    CDuiString m_strContactsHoverImg;
    CDuiString m_strContactsClickImg;

    DWORD m_dwItemNormalColor;
    DWORD m_dwItemNormalColor2;
    DWORD m_dwItemClickColor;

    bool m_bChatClicked;
    bool m_bContactsClicked;

    std::vector<tagFriendsInfo> m_clFriends;
    std::vector<tagContactsInfo> m_clContacts;
};

