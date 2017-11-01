#pragma once

class CTopBarWnd : public CWindowWnd, public INotifyUI
{
public:
    CTopBarWnd();
    ~CTopBarWnd();
public:
    LPCTSTR GetWindowClassName() const;
    UINT GetClassStyle() const;

    HWND Create(HWND hWndParent, LPCTSTR pcszName, DWORD dwStyle, DWORD dwExStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL);

    void Init();
public:
    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    void OnPrepare();
    void OnFinalMessage(HWND hWnd);

    void Notify(TNotifyUI& msg);
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
    CPaintManagerUI m_clPaintManager;

    CButtonUI *m_pclDetailBtn;
    CButtonUI *m_pclShareBtn;
    CButtonUI *m_pclShotcutBtn;
    CButtonUI *m_pclFavoriteBtn;
    CButtonUI *m_pclUnFavoriteBtn;
    CButtonUI *m_pclSetTopBtn;
    CButtonUI *m_pclCancelTopBtn;

    HWND m_hParentWnd;
    CHAR m_szWParam[128];
    CHAR m_szLParam[128];
};

