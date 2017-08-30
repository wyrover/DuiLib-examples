#ifndef __UI_MAIN_FRM_H__
#define __UI_MAIN_FRM_H__

#include <atlwin.h>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>

#include "Resource.h"
#include "BuilderCallback.h"


class CMainFrm
    : public DuiLib::WindowImplBase       
{

public:
    CMainFrm();
    ~CMainFrm();

    virtual LPCTSTR GetWindowClassName() const{return _T("CMainFrm");};
    virtual CDuiString GetSkinFolder() {return _T("res");}
    virtual CDuiString GetSkinFile() {return _T("main_frm.xml");}
    //virtual UILIB_RESOURCETYPE GetResourceType() const {return UILIB_FILE;}
    virtual CDuiString GetZIPFileName() const {return _T("res.zip");}
    virtual LPCTSTR GetResourceID() const {return MAKEINTRESOURCE(IDR_ZIPRES_SKIN);}
    virtual CControlUI* CreateControl(LPCTSTR pstrClass)
    {
        return CDuiCallback::StaticCreateControl(pstrClass);
    }
    virtual LONG GetStyle()
    {
        LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
        styleValue &= ~(WS_CAPTION | WS_MAXIMIZEBOX | WS_SYSMENU | WS_SIZEBOX);
        return styleValue;
    }
    virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam)
    {
        if (wParam == VK_RETURN) {
            return FALSE;
        } else if (wParam == VK_ESCAPE) {
            //Close();
            return TRUE;
        }
        return FALSE;
    }

    void InitWindow();

    virtual void OnFinalMessage(HWND hWnd){__super::OnFinalMessage(hWnd);}
    virtual void Notify(TNotifyUI& msg);

    DUI_DECLARE_MESSAGE_MAP()
    virtual void OnClick(TNotifyUI& msg);
    virtual void OnValueChanged(TNotifyUI& msg);
    virtual void OnScroll(TNotifyUI& msg);
protected:

protected:
    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnCopyData(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

private:

private:
    
};



#endif //__UI_BASE_WND_H__