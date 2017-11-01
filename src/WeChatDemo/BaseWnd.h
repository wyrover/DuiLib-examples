#pragma once

class CBaseWnd : public CWindowWnd, public INotifyUI, public IMessageFilterUI, public IDialogBuilderCallback
{
public:
    CBaseWnd();
    virtual ~CBaseWnd();
public:
    virtual LPCTSTR GetWindowClassName() const;
    virtual UINT GetClassStyle() const;

    virtual void Init();

    virtual CControlUI * CreateControl(LPCTSTR pstrName);
public:
    virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    virtual void OnPrepare();
    virtual void OnFinalMessage(HWND hWnd);

    virtual void Notify(TNotifyUI &msg);
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
protected:
    virtual CDuiString GetSkinFolder();
    virtual CDuiString GetSkinFile() = 0;

    virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);

    CPaintManagerUI * GetPaintManager();
private:
    CPaintManagerUI m_clPaintManager;
};

