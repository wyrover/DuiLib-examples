#include "DuiLib\Animation\Animator.h"
#include "boost\smart_ptr.hpp"

#ifndef __UI_BUILD_CALLBACK_H__
#define __UI_BUILD_CALLBACK_H__


class CListElemUI 
    : public DuiLib::CListContainerElementUI
    , public boost::enable_shared_from_this<CListElemUI>
    , boost::noncopyable
{
public:                                                         
    LPCTSTR GetClass() const {return L"ListElem";} 
    static LPCTSTR GetInterfaceName() {return _T("ListElemUI");}        
    LPVOID GetInterface(LPCTSTR pstrName) {                     
        if( _tcscmp(pstrName, _T("ListElemUI")) == 0 )
            return this;     
        return __super::GetInterface(pstrName);
    }                
public:
    CListElemUI();
    virtual ~CListElemUI();

    void Init();
    virtual void DoEvent(TEventUI& event);
    virtual void DoPaint(HDC hDC, const RECT& rcPaint);
    virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

    static void safe_animator_update(boost::weak_ptr<CListElemUI> wpElem);
    static void safe_animator_complete(boost::weak_ptr<CListElemUI> wpElem);

    bool IsRunning();
    void Start();
    void Stop();
    void Pause();
    void SetInterval(int interval);
    void animator_update();
    void animator_complate();
protected:

private:
    int               m_nInterval;
    time_t               m_nStartTime;
    int               m_nCurrentTime;
    bool              m_bRunning;
    int               m_nMaxScore;
    CProgressUI*       m_pProgress;
    CLabelUI*          m_pState;
    CLabelUI*          m_pInterval;
    CButtonUI*          m_pNetRepairBtn;

    boost::function<void(void)>     m_completeCallback;
    boost::function<void(void)>     m_udpatecallback;
    boost::shared_ptr<DuiLib::IAnimator>        animator_;
};


class CMyListBodyUI : public CListBodyUI
{
public:
    CMyListBodyUI(CListUI* pOwner);
    void SetScrollPos(SIZE szPos);
};

class CMyListUI : public DuiLib::CListUI
{
    LPCTSTR GetClass() const {return L"MyList";} 
    static LPCTSTR GetInterfaceName() {return _T("MyListUI");}        
    LPVOID GetInterface(LPCTSTR pstrName) {                     
        if( _tcscmp(pstrName, _T("MyListUI")) == 0 )
            return this;     
        return __super::GetInterface(pstrName);
    }   
public:
    CMyListUI();

    virtual void SetScrollPos(SIZE szPos);
    virtual void DoEvent(TEventUI& event);
    virtual void ProcessScrollBar(RECT rc, int cxRequired, int cyRequired);
    void SetScrollCallbackOnce(boost::function<void(void)> func);

protected:
    bool OnScrollNotify(void* param);
    void SendScrollMsg();

private:
    bool m_bScrollMsgSended;
    CMyListBodyUI*			m_pMyListBody;
    boost::function<void(void)>     m_scrollallback;

};

class CDuiCallback : public IDialogBuilderCallback
{
public:
	CControlUI* CreateControl(LPCTSTR pstrClass);
	static CControlUI* StaticCreateControl(LPCTSTR pstrClass);
};


#endif //__UI_BASE_WND_H__