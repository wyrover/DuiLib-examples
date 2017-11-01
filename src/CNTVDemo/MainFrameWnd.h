#pragma once

#include <ShellAPI.h>
#include "TopBarWnd.h"
#include "BottomBarWnd.h"

class CMainFrameWnd : public CWindowWnd, public INotifyUI
{
public:
    CMainFrameWnd();
    ~CMainFrameWnd();
public:
    LPCTSTR GetWindowClassName() const;
    UINT GetClassStyle() const;
    void Init();
public:
    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnMoving(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnShowWindow(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnTrayCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnFavorite(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnTopMost(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    void OnPrepare();
    void OnFinalMessage(HWND hWnd);

    void Notify(TNotifyUI& msg);
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
    void CreateTray();
    void ModifyTray(LPCTSTR lpcszTitle, LPCTSTR lpcszTip);
    void DeleteTray();

    void CreateTopBar();
    void CreateBottomBar();

    void OnTopBar();
    void OnBottomBar();
    void OnUserCenter();
private:
    CPaintManagerUI m_clPaintManager;

    CButtonUI *m_pclCloseBtn;
    CButtonUI *m_pclMaxBtn;
    CButtonUI *m_pclRestoreBtn;
    CButtonUI *m_pclMinBtn;
    CButtonUI *m_pclHistBtn;
    CButtonUI *m_pclSysMenuBtn;
    CButtonUI *m_pclUserCenterBtn;
    CButtonUI *m_pclUserLoginBtn;

    CEditUI *m_pclSearchEdt;
    CButtonUI *m_pclSearchBtn;

    HWND m_hUserCenterWnd;
    bool m_bUserCenterClicked;

    CTopBarWnd *m_pclTopBarWnd;
    CBottomBarWnd *m_pclBottomBarWnd;

    NOTIFYICONDATAW m_stTrayData;
};

